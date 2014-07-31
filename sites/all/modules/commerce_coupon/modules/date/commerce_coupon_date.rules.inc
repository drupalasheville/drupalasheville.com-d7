<?php

/*
 * Implements hook_rules_condition_info().
 */
function commerce_coupon_date_rules_condition_info() {
  $inline_conditions = inline_conditions_get_info();
  
  $conditions['commerce_coupon_date_evaluate_date'] = array(
    'label' => t('Coupon dates'),
    'description' => t('Enter a start and/or end date during which this coupon is valid.'),
    'parameter' => array(
      'commerce_coupon' => array(
        'type' => 'commerce_coupon',
        'label' => t('Coupon'),
      ),
      'start' => array(
        'type' => 'date',
        'label' => t('Start date'),
        'optional' => TRUE,
      ),
      'end' => array(
        'type' => 'date',
        'label' => t('End date'),
        'optional' => TRUE,          
      )        
    ),
    'callbacks' => array(
      'execute' => $inline_conditions['commerce_coupon_date_evaluate_date']['callbacks']['build'],
    )
  );
  
  return $conditions;
}