<?php

/**
 * @file
 * Coupon views extra data.
 */

/**
 * Alter the views data to enable some additional features for coupons in views.
 */
function commerce_coupon_views_data_alter(&$data) {
  if (isset($data['commerce_coupon'])) {
    $data['commerce_coupon']['table']['base']['access query tag'] = 'commerce_coupon_access';

    $data['commerce_coupon']['remove_from_order'] = array(
      'field' => array(
        'title' => t('Remove from Order'),
        'help' => t('Remove coupon from the order.'),
        'handler' => 'commerce_coupon_handler_field_coupon_order_remove',
      ),
    );
    $data['commerce_coupon']['discount_value_display'] = array(
      'field' => array(
        'title' => t('Discount value display'),
        'help' => t('Display text describing value of the discount(s) linked to this coupon.'),
        'handler' => 'commerce_coupon_handler_field_discount_value_display',
      ),
    );
    $data['commerce_coupon']['delete'] = array(
      'field' => array(
        'title' => t('Delete coupon'),
        'help' => t('Link to delete a coupon.'),
        'handler' => 'commerce_coupon_handler_field_coupon_delete',
      ),
    );
    $data['commerce_coupon']['edit'] = array(
      'field' => array(
        'title' => t('Edit coupon'),
        'help' => t('Link to edit a coupon.'),
        'handler' => 'commerce_coupon_handler_field_coupon_edit',
      ),
    );

    // uid relationship
    $data['commerce_coupon']['uid']['relationship'] = array(
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'field' => 'uid',
      'label' => t('Recipient'),
    );

    // Change created into a date field
    $data['commerce_coupon']['created'] = array(
      'title' => t('Created date'),
      'help' => t('The date the order was created.'),
      'field' => array(
        'handler' => 'views_handler_field_date',
        'click sortable' => TRUE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort_date',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_date',
      ),
    );

    // Add a special code argument handler
    $data['commerce_coupon']['code']['argument'] = array(
      'handler' => 'commerce_coupon_handler_argument_coupon_code'
    );

    // Add a special coupon id argument handler
    $data['commerce_coupon']['coupon_id']['argument'] = array(
      'handler' => 'commerce_coupon_handler_argument_coupon_id'
    );
  }
}

/**
 * Get the argument order if present.
 *
 * @param $handler
 * @return bool|mixed
 */
function _commerce_coupon_load_argument_order($handler) {
  // Determine if there is an order id argument. If multiple are present, use
  // the first found.
  if (isset($handler->view->argument)) {
    foreach ($handler->view->argument as $alias => $argument) {
      if ($argument instanceof commerce_order_handler_argument_order_order_id) {
        $order_id = (int) $handler->view->argument[$alias]->value[0];
        $order = commerce_order_load($order_id);
      }
    }
  }

  return isset($order) ? $order : FALSE;
}
