<?php

/*
 * Implements hook_entity_property_info_alter().
 */
function commerce_coupon_usage_entity_property_info_alter(&$info) {
  if (isset($info['commerce_coupon'])) {
    $info['commerce_coupon']['properties']['max_usage']  = array(
      'label' => t('Maximum number of uses'),
      'type' => 'integer',
      'getter callback' => 'commerce_coupon_usage_property_getter'
    );
    $info['commerce_coupon']['properties']['usage']  = array(
      'label' => t('Number of times used'),      
      'type' => 'integer',
      'getter callback' => 'commerce_coupon_usage_property_getter'
    );    
  }
}