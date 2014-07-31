<?php

/**
 * @file
 *   Token integration.
 */

/**
 * Implements hook_token_info().
 */
function payment_token_info() {
  // Fake a hierarchy, because payment:line_items has no direct contents and a
  // real hierarchy would not show up in Rules' token browser.
  $token = array();
  foreach (payment_line_items_info() as $info) {
    $token['payment'][PAYMENT_LINE_ITEM_TOKEN_PREFIX . $info->name] = array(
      'name' => $info->title,
      'description' => t('The total amount of all line items of this type.'),
    );
  }

  return array(
    'tokens' => $token,
  );
}

/**
 * Implements hook_tokens().
 */
function payment_tokens($type, array $tokens, array $data = array(), array $option = array()) {
  $replacements = array();

  if ($type == 'payment') {
    /** @var Payment $payment */
    $payment = $data['payment'];
    foreach ($tokens as $name => $token) {
      $pattern = '#^' . PAYMENT_LINE_ITEM_TOKEN_PREFIX . '#';
      if (preg_match($pattern, $name) && $line_items = $payment->getLineItems(preg_replace($pattern, '', $name))) {
        $replacements[$token] = $payment->totalAmount(TRUE, $line_items);
      }
    }
  }

  return $replacements;
}