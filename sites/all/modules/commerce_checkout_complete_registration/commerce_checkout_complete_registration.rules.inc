<?php

/**
 * @file
 * Rules integration for the checkout process.
 *
 * @addtogroup rules
 * @{
 */

/**
 * Implements hook_rules_event_info().
 */
function commerce_checkout_complete_registration_rules_event_info() {
  $events = array();

  $events['commerce_checkout_complete_registration'] = array(
    'label' => t('Create account for anonymous checkout'),
    'group' => t('Commerce Checkout'),
    'variables' => array(
      'user' => array(
        'type' => 'user',
        'label' => t('Created account', array(), array('context' => 'a drupal user account')),
      ),
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Completed order', array(), array('context' => 'a drupal commerce order')),
      ),
    ),
    'access callback' => 'commerce_order_rules_access',
  );

  return $events;
}
