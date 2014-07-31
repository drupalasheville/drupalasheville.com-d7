<?php

/**
 * Define coupon types
 */
function hook_commerce_coupon_type_info() {
  $types['example_coupon_type'] = array(
    'label' => t('Example coupon type')
  );
  
  return $types;
}

/**
 * Modules can invoke this hook to provide a different query for determining 
 * query access for coupon entities. If no modules implement this hook, Commerce
 * Coupon will run commerce_entity_access_query_alter() to determine query
 * access.
 * 
 * @param object $query
 *  The query that is asking for coupon access-control logic
 * 
 * @param string $coupon_alias
 *  The alias of the coupon table in the query
 */
function hook_commerce_coupon_access_query_substitute($query, $coupon_alias) {
  // See commerce_coupon_user_commerce_coupon_access_query_substitute().
}

/**
 * Provide a custom callback for access on a coupon by operation. Includes all
 * of the normal entity operations, plus "redeem".
 * 
 * @param type $coupon
 *  A coupon as its access is being checked
 * 
 * @param type $account
 *  The account being used for the access check
 */
function hook_commerce_coupon_access_OP($coupon, $account) {
  // Grant access for all operations unconditionally.
  switch ($op) {
    case 'view':
    case 'update':
    case 'create':
    case 'delete':
    case 'redeem':
      return TRUE;
  }
}

/**
 * Transaction related modules must implement a rollback hook to clean up 
 * transactions in the event that payment validation fails after the transaction
 * has been processed.
 * 
 * This hook fires when the review page rebuilds after a coupon-transaction
 * module has done transactions. This is not the perfect setup because it can
 * confuse off-site payment methods, but short of a split-payment API in
 * Commerce, it is about as good as we can get.
 * 
 * @see commerce_coupon_usage_commerce_coupon_final_checkout_transaction_rollback().
 * @see hook_commerce_coupon_final_checkout_validate().
 * 
 * @param int $transaction_id
 */
function hook_commerce_coupon_final_checkout_transaction_rollback($transaction_id) {
  mymodule_void_transaction($transaction_id);
}

/**
 * Transaction related modules, such as Usage and Giftcards, do their 
 * transactions in this hook, which fires before the payment validator that 
 * actually processes payments.
 * 
 * 
 * @see commerce_coupon_usage_commerce_coupon_final_checkout_validate().
 * 
 * @param array $form
 *  The checkout form
 * 
 * @param array $form_state
 *  The checkout form state
 * 
 * @param stdClass $order_wrapper
 *  The checkout order
 * 
 * @return $transaction_ids
 */
function hook_commerce_coupon_final_checkout_validate(&$form, &$form_state, $order_wrapper) {
  $transaction_ids = array();
  $transaction = mymodule_do_transaction($order_wrapper);
  if (!$transaction) {
    form_set_error('', t('Transaction failed'));
  }
  else {
    $transaction_ids[] = $transaction;
  }
  
  return $transaction_ids;
}

/**
 * Specifically alter the coupon entity form wherever it is attached.
 * 
 * @param array $form
 *  The coupon entity form or form fragment
 * 
 * @param array $form_state
 *  Typical form state
 * 
 * @param CommerceCoupon $coupon
 *  The coupon being edited
 */
function hook_commerce_coupon_coupon_entity_form_alter($form, $form_state, $coupon) {
  // Do not allow access to the status flag on discount coupons.
  if ($coupon->type == 'discount_coupon' && isset($form['status'])) {
    $form['status']['#access'] = 0;
  }
}

/**
 * Alter the outcome of whether a coupon applies to an order.
 * 
 * @param boolean $outcome
 *  The outcome of coupon condition check.
 * 
 * @param array $context
 *  An array containing:
 *  - order: the order that the coupon is being applied to.
 *  - coupon: the coupon
 *  - data: an arbitrary array of contextual data. Not currently used.
 */
function commerce_coupon_condition_outcome(&$outcome, $context) {
  if ($context['coupon']->type == 'mytype') {
    $outcome = FALSE;
  }
}

/**
 * Alter the commands, form and formstate at the point where the coupon module
 * is about return from its checkout pane ajax handler.
 * 
 * @param array $commands
 *  Any commands that have been set
 * 
 * @param array $form
 *  The checkout form
 * 
 * @param array $form_state
 *  The checkout form state
 */
function hook_commerce_coupon_add_coupon_ajax_alter($commands, &$form, &$form_state) {
  // Set a JS alert when the coupon checkout pane form is rebuilt via ajax.
  $commands[] = ajax_command_alert(t('Thank you for redeeming a coupon'));
}

/**
 * Alter the display of the description that of the discount that a coupon
 * confers, when that coupon is being shown in the checkout area. 
 * 
 * @see commerce_coupon_handler_field_discount_value_display::render().
 * 
 * @param string $display
 *  The text that will be displayed for a single discount that the coupon
 *  confers. This hook fires for each discount on each coupon attached to an
 *  order.
 * 
 * @param CommerceDiscount $discount
 *  Discount conferred by coupon
 * 
 * @param stdClass $order
 *  The order that the coupon is attached to
 */
function hook_commerce_coupon_discount_value_display_alter($display, $discount, $order) {
  // Change the discount display for coupons that confer an order discount
  if ($discount->type == 'order_discount') {
    $display = t('Order discount');
  }
}

/**
 * Alter the final output of the coupon value display views handler
 * 
 * @param string $output
 *  The field handler output
 * 
 * @param CommerceCoupon $coupon
 *  The coupon entity being displayed
 * 
 * @param stdClass $order
 *  The order that the coupon is attached to
 */
function hook_commerce_coupon_value_display_alter($output, $coupon, $order) {
  // Change the display for all discount coupons
  if ($coupon->type == 'discount_coupon') {
    $output = t('Discount coupon');
  }
}
