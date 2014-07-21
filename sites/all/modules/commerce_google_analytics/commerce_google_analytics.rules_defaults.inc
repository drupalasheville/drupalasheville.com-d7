<?php

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_google_analytics_default_rules_configuration() {
  $rule = rules_reaction_rule();
  $rule->label = 'Send google analytics code on checkout completion';
  $rule->active = TRUE;
  $rule->event('commerce_checkout_complete')
          ->action('commerce_google_analytics_send_order', array('commerce_order:select' => 'commerce_order')
  );
  $configs['commerce_google_analytics_rule_ga'] = $rule;
  return $configs;
}