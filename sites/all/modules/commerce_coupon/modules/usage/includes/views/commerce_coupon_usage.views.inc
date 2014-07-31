<?php

/**
 * Commerce discount entity Views definitions.
 */
class CommerceCouponUsageTransactionViewsController extends EntityDefaultViewsController {

  /**
   * Override EntityDefaultViewsController::views_data().
   */
  public function views_data() {
    $data = parent::views_data();
    
    // Make date a date field.
    $data['commerce_coupon_usage_transaction']['date'] = array(
      'title' => t('Date'),
      'help' => t('The date the transaction occurred.'),
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
    
    // Coupon relationship
    $data['commerce_coupon_usage_transaction']['coupon_id']['relationship'] = array(
      'handler' => 'views_handler_relationship',
      'base' => 'commerce_coupon',
      'field' => 'coupon_id',
      'label' => t('Coupon'),        
    );
    
    // Order relationship
    $data['commerce_coupon_usage_transaction']['order_id']['relationship'] = array(
      'handler' => 'views_handler_relationship',
      'base' => 'commerce_order',
      'field' => 'order_id',
      'label' => t('Coupon'),        
    );
    
    // Coupon argument type
    $data['commerce_coupon_usage_transaction']['coupon_id']['argument'] = array(
      'handler' => 'commerce_coupon_handler_argument_coupon_id'
    );
    
    $data['commerce_coupon_usage_transaction']['remove'] = array(
      'field' => array(
        'title' => t('Remove button'),
        'help' => t('Button to remove a coupon usage transaction.'),
        'handler' => 'commerce_coupon_usage_views_handler_field_remove',
      ),      
    );
    
    return $data;
  }
}

function commerce_coupon_usage_views_data_alter(&$data) {
  if (isset($data['commerce_coupon'])) {
    $data['commerce_coupon']['usage_summary_area'] = array(
      'title' => t('Coupon usage summary area'),
      'help' => t('Displays a summary of coupon usage and usage limits; requires a coupon id argument.'),
      'area' => array(
        'handler' => 'commerce_coupon_usage_views_handler_area_usage_summary'
      )
    );
    
    $data['commerce_coupon']['usage'] = array(
      'field' => array(
        'title' => t('Coupon usage_summary'),
        'help' => t('Displays a summary of coupon usage and usage limits.'),
        'handler' => 'commerce_coupon_usage_views_handler_field_usage',
      ),
    );
  }
}
