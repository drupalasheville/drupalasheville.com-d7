<?php

/*
 * Implements hook_rules_condition_info().
 */
function commerce_coupon_usage_rules_condition_info() {
  $inline_conditions = inline_conditions_get_info();
  
  $conditions['commerce_coupon_usage_evaluate_usage'] = array(
    'label' => t('Coupon usage'),
    'description' => t('Enter the maximum number of times a coupon may be used.'),
    'parameter' => array(
      'commerce_coupon' => array(
        'type' => 'commerce_coupon',
        'label' => t('Coupon'),        
      ),
      'max_usage' => array(
        'type' => 'integer',
        'label' => t('Max usage')
      )
    ),
    'callbacks' => array(
      'execute' => $inline_conditions['commerce_coupon_usage_evaluate_usage']['callbacks']['build'],
    )
  );
  
  return $conditions;
}
