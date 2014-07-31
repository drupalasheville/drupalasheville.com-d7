<?php

// Define how many orders/coupons get processed per batch.
define('COMMERCE_COUPON_ORDER_IMPORT_RATE', 15);
define('COMMERCE_COUPON_COUPON_IMPORT_RATE', 5);

/**
 * Update four coupons at a time.
 * 
 * @param type $sandbox
 * @return type
 */
function _commerce_coupon_update_coupons_multipass(&$sandbox, $drush) {
  if (!isset($sandbox['coupons']['progress'])) {
    $sandbox['coupons']['progress'] = 0;
    $sandbox['coupons']['current_id'] = 0;
    $sandbox['coupons']['max'] = db_query('SELECT COUNT(DISTINCT coupon_id) FROM {commerce_coupon}')->fetchField();
  }
  
  // Get the next four coupon ids
  $coupon_ids = db_select('commerce_coupon', 'c')
     ->fields('c', array('coupon_id'))
     ->condition('coupon_id', $sandbox['coupons']['current_id'], '>')
     ->range(0, COMMERCE_COUPON_COUPON_IMPORT_RATE)
     ->orderBy('coupon_id', 'ASC')
     ->execute()
     ->fetchCol();
  
  // Update the coupons
  if ($coupon_ids) {
    $coupons = commerce_coupon_load_multiple($coupon_ids);

    foreach ($coupons as $coupon) {
      $original_coupon = clone $coupon;
      $coupon_wrapper = entity_metadata_wrapper('commerce_coupon', $coupon);
      
      // Update code column.
      if (empty($coupon->code)) {
        $code = $coupon_wrapper->commerce_coupon_code->value();
        $coupon->code = $code;
      }

      // Find update information about this coupon type.
      $parameters = module_invoke_all('commerce_coupon_legacy_mapping', $coupon);
      
      if (!empty($parameters)) {
        // Determine if there is a suitable discount to use.
        $query = new EntityFieldQuery;
        $results = $query
          ->entityCondition('entity_type', 'commerce_discount')
          ->propertyCondition('type', 'order_discount')
          ->propertyCondition('name', $parameters['discount name'])
          ->execute();

        // Load matching discount.
        if (!empty($results['commerce_discount'])) {
          $discount_ids = array_keys($results['commerce_discount']);
          $discounts = entity_load('commerce_discount', $discount_ids);
          $discount = reset($discounts);
        }
        else {
          // Discount not found - create and save offer.
          $offer = entity_create('commerce_discount_offer', array(
            'type' => $parameters['offer type'],
          ));
          $offer_field = $parameters['offer field'];
          $offer_wrapper = entity_metadata_wrapper('commerce_discount_offer', $offer);
          $offer_wrapper->{$offer_field} = $parameters['offer value'];
          $offer_wrapper->save();

          // Create and save discount.
          $discount = entity_create('commerce_discount', array(
            'type' => 'order_discount',
            'name' => $parameters['discount name'],
            'label' => $parameters['label'],
            'component_title' => $parameters['label']
          ));

          $discount_wrapper = entity_metadata_wrapper('commerce_discount', $discount);
          // Set offer reference.
          $discount_wrapper->commerce_discount_offer = $offer;

          $discount_wrapper->save();
        }

        if ($discount) {
          $conditions = array();
          if (module_exists('commerce_coupon_usage') && !empty($coupon->commerce_coupon_number_of_uses)) {
            // Add an inline condition for number of uses. 
            $conditions[] = array(
              'condition_name' => 'commerce_coupon_usage_evaluate_usage',
              'condition_settings' => array(
                'max_usage' => $coupon_wrapper->commerce_coupon_number_of_uses->value()
              )
            );
          }

          // Set the bundle now.
          $coupon->type = 'discount_coupon';

          // Set inline conditions field. The wrapper just gets too confused here
          // b/c of the bundle change so we do not use it.
          if (!empty($conditions)) {          
            $lang = field_language('commerce_coupon', $coupon, 'commerce_coupon_conditions');          
            $coupon->commerce_coupon_conditions[$lang] = $conditions;
          }

          // Set discount reference and save.
          $lang = field_language('commerce_coupon', $coupon, 'commerce_discount_reference');
          $coupon->commerce_discount_reference[$lang][] = array('target_id' => $discount->discount_id);

          // Allow other modules to alter the coupon before it is saved.
          drupal_alter('commerce_coupon_update_pre_update', $original_coupon, $coupon, $discount);
          commerce_coupon_save($coupon);
        }
      }
      $sandbox['coupons']['progress']++;
      $sandbox['coupons']['current_id'] = $coupon->coupon_id;
    }
    
    if ($drush) {
      drush_print(t('Processed @n coupons', array('@n' => count($coupon_ids))));
    }      
  }
  else {
    $sandbox['coupons']['#finished'] = 1;
  }
    
  $sandbox['coupons']['#finished'] = empty($sandbox['coupons']['max']) ? 1 : ($sandbox['coupons']['progress'] / $sandbox['coupons']['max']);
}

/**
 * Update four orders at a
 * 
 * @param type $sandbox
 */
function _commerce_coupon_update_orders_multipass(&$sandbox, $drush) {
  $query = new EntityFieldQuery;
  $query
    ->entityCondition('entity_type', 'commerce_order')
    ->fieldCondition('commerce_coupon_order_reference', 'target_id', 'NULL', '!=');

  if (!isset($sandbox['orders']['progress'])) {
    $sandbox['orders']['progress'] = 0;
    $sandbox['orders']['current_id'] = 0;
    
    // Calculate the number of orders to need to be processed.
    $count_query = clone $query;    
    $sandbox['orders']['max'] = $count_query->count()->execute();
  }

  $results = $query
    ->propertyCondition('order_id', $sandbox['orders']['current_id'], '>')
    ->range(0, COMMERCE_COUPON_ORDER_IMPORT_RATE)       
    ->propertyOrderBy('order_id', 'ASC')
    ->execute();
  
  if (!empty($results['commerce_order'])) {
    $order_ids = $results['commerce_order'];
    $orders = commerce_order_load_multiple(array_keys($results['commerce_order']));
    foreach ($orders as $order) {
      $original_order = clone $order;

      // Transfer coupon reference to the new field.
      $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
      if ($order_wrapper->commerce_coupon_order_reference->value()) {
        $order_wrapper->commerce_coupons = $order_wrapper->commerce_coupon_order_reference->value();

        // Allow modules to alter the order before it is saved.
        drupal_alter('commerce_coupon_update_order_pre_update', $original_order, $order);
                
        if (module_exists('commerce_coupon_usage')) {
          $statuses = array_merge(commerce_order_statuses(array('state' => 'pending')), commerce_order_statuses(array('state' => 'completed')));

          // If the order is complete or pending, record a use of the coupon.
          if (in_array($order->status, array_keys($statuses))) {
            commerce_coupon_usage_record_usage($order);
          }        
        }
        $order_wrapper->save();
      }
      $sandbox['orders']['progress']++;
      $sandbox['orders']['current_id'] = $order->order_id;
    }
    
    if ($drush) {
      drush_print(t('Processed @n orders', array('@n' => count($order_ids))));
    }    
  }
  else {
    $sandbox['orders']['#finished'] = 1;
  }
  
  $sandbox['orders']['#finished'] = empty($sandbox['orders']['max']) ? 1 : ($sandbox['orders']['progress'] / $sandbox['orders']['max']);
}
