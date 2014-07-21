<?php

/**
 * Implements hook_rules_action_info().
 */
function commerce_google_analytics_rules_action_info() {
  return array(
    // Add rules action which sends the analytics code
    'commerce_google_analytics_send_order' => array(
      'label' => t('Send order to google analytics'),
      'parameter' => array(
        'commerce_order' => array(
          'type' => 'commerce_order',
          'label' => t('Order in checkout'),
        ),
      ),
      'callback' => array(
        'execute' => 'commerce_google_analytics_send_order'
      ),
    ),
  );
}