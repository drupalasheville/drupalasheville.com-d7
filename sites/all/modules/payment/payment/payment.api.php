<?php

/**
 * @file
 * Hook documentation.
 */

/**
 * Defines payment statuses.
 *
 * @return array
 *   An array with PaymentStatusInfo objects.
 */
function hook_payment_status_info() {
  return array(
    new PaymentStatusInfo(array(
      'description' => t('Foo payments are still being processed by Bar to guarantee their authenticity.'),
      'status' => PAYMENT_STATUS_FOO,
      'parent' => PAYMENT_STATUS_PENDING,
      'title' => t('Pending (waiting for Bar authentication)'),
    )),
  );
}

/**
 * Alters payment statuses.
 *
 * @param array $statuses_info
 *   An array with PaymentStatusInfo objects.
 *
 * @return NULL
 */
function hook_payment_status_info_alter(array &$statuses_info) {
  $statuses_info[PAYMENT_STATUS_FAILED]->title = 'Something went wrong!';
}

/**
 * Defines payment method controllers.
 *
 * @return array
 *   An array with the names of payment method controller classes. Keys may
 *   either specific aliases for their values (the classes), or be numeric
 *   (left empty) to make them default to the controller class names they
 *   belong to. This allows hook_payment_method_controller_info_alter() to
 *   override payment method controller class by setting a different class name
 *   for an alias.
 */
function hook_payment_method_controller_info() {
  return array(
    'DummyPaymentMethodController',
    'CashOnDeliveryPaymentMethodController',
  );
}

/**
 * Alters payment method controllers.
 *
 * @param array $controllers_info
 *   Keys are payment controller aliases, values are actual payment method
 *   controller class names.
 */
function hook_payment_method_controller_info_alter(array &$controllers_info) {
  // Remvove a payment method controller.
  unset($controllers_info['FooPaymentMethodController']);

  // Replace PaymentMethodControllerUnavailable with another controller.
  $controllers_info['PaymentMethodControllerUnavailable'] = 'FooPaymentMethodControllerUnavailableAdvanced';
}

/**
 * Defines line item types.
 *
 * @see Payment::getLineItems()
 *
 * @return array
 *   An array with PaymentLineItemInfo objects.
 */
function hook_payment_line_item_info() {
  return array(
    new PaymentLineItemInfo(array(
      'name' => 'foo_fee_credit_card',
      'title' => t('Credit card fee'),
    )),
    new PaymentLineItemInfo(array(
      'name' => 'foo_fee_wire_transfer',
      'title' => t('Wire transfer fee'),
    )),
    new PaymentLineItemInfo(array(
      // Use a custom callback, so we can get any/all line items we need
      // simultaneously.
      'callback' => 'foo_payment_line_item_get_fee',
      'name' => 'foo_fee',
      'title' => t('Any payment method fee'),
    )),
  );
}

/**
 * Alters line item types.
 *
 * @param array $line_items_info
 *   An array with PaymentLineItemInfo objects, keyed by PaymentLineItemInfo::name.
 */
function hook_payment_line_item_info_alter(array &$line_items_info) {
  // Set a callback for a line item.
  $line_items_info['foo_fee_credit_card']['callback'] = 'foo_payment_line_item_get';
}

/**
 * Executes when a payment status is being set.
 *
 * @see Payment::setStatus()
 *
 * @param Payment $payment
 * @param PaymentStatusItem $previous_status_item
 *   The status the payment had before it was set.
 *
 * @return NULL
 */
function hook_payment_status_change(Payment $payment, PaymentStatusItem $previous_status_item) {
  // Notify the site administrator, for instance.
}

/**
 * Executes right before a payment is executed. This is the place to
 * programmatically alter payments.
 *
 * @see Payment::execute()
 *
 * @param Payment $payment
 *
 * @return NULL
 */
function hook_payment_pre_execute(Payment $payment) {
  // Add a payment method processing fee.
  $payment->setLineItem(new PaymentLineItem(array(
    'name' => 'foo_fee',
    'amount' => 5.50,
    'description' => 'Credit card fee',
    'tax_rate' => 0.19,
  )));
}

/**
 * Executes right before payment execution is finished.
 *
 * @see Payment::finish()
 *
 * @param Payment $payment
 *
 * @return NULL
 */
function hook_payment_pre_finish(Payment $payment) {
  if (payment_status_is_or_has_ancestor($payment->getStatus()->status, PAYMENT_STATUS_SUCCESS)) {
    drupal_set_message(t('Your payment was successfully completed.'));
  }
  else {
    drupal_set_message(t('Your payment was not completed.'));
  }
}

/**
 * Validate a payment against a payment method.
 *
 * This hook may be called multiple times for the exact same payment, but for
 * different payment methods, for example when looking for payment methods that
 * are capable of processing a payment.
 *
 * @param Payment $payment
 *   $payment->method contains the method currently configured, but NOT the
 *   method that $payment should be tested against, which is $payment_method.
 * @param PaymentMethod $payment_method
 * @param boolean $strict
 *   Whether to validate everything a payment method needs or to validate the
 *   most important things only. Useful when finding available payment methods,
 *   for instance, which does not require unimportant things to be a 100%
 *   valid.
 *
 * @return boolean
 *   Whether the payment and/or the payment method are valid.
 */
function hook_payment_validate(Payment $payment, PaymentMethod $payment_method, $strict) {}

/**
 * Alter the payment form.
 *
 * Because the payment form is not always used through drupal_get_form(), you
 * should use this hook, rather than hook_form_alter() or
 * hook_form_FORM_ID_alter() to make changes to the payment form.
 *
 * @param array $elements
 *   The array of form elements that are part of the payment form. Note that
 *   the top-level array is NOT a form.
 * @param array $form_state
 * @param array $submit
 *   An array with the names of form submit callbacks that should be called upon form submission.
 *
 * @return NULL
 */
function hook_payment_form_alter(array &$elements, array &$form_state, array &$submit) {}

/**
 * Alter the results of entity_view('payment', ...).
 *
 * @param $build
 *   A renderable array representing the payment content.
 */
function hook_payment_view_alter(&$build) {}
