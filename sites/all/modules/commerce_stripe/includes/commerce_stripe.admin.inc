<?php

/**
 * @file
 * Provides admin forms and functions for commerce_stripe.
 */

/**
 * Form callback for processing refunds.
 */
function commerce_stripe_refund_form($form, &$form_state, $order, $transaction) {
  $form = array();
  $payment_method = commerce_payment_method_instance_load($transaction->instance_id);
  $form_state['order'] = $order;
  $form_state['transaction'] = $transaction;
  $form_state['payment_method'] = $payment_method;

   // Make sure the library is available.
  if (!commerce_stripe_load_library()) {
    drupal_set_message(t('Cannot load the Stripe PHP library'), 'error');
    return $form;
  }

  // Make sure we can load the original charge object.
  try {
    Stripe::setApiKey($payment_method['settings']['secret_key']);
    $charge = Stripe_Charge::retrieve($transaction->remote_id);
    $form_state['stripe_charge'] = $charge;
  }
  catch (Exception $e) {
    drupal_set_message(t('The original transaction could not be loaded. The error was: @error', array('@error' => $e->getMessage())), 'error');
    return $form;
  }

  // Calculate the amount left available for a refund.
  $amount_refunded = !empty($charge->amount_refunded) ? $charge->amount_refunded : 0;
  $remaining = $charge->amount - $amount_refunded;

  $form['amount'] = array(
    '#type' => 'textfield',
    '#title' => t('Refund amount'),
    '#description' => t('Enter any amount to refund up to @txn_amount', array('@txn_amount' => commerce_currency_format($remaining, $transaction->currency_code))),
    '#required' => TRUE,
    '#size' => 8,
  );

  $options = array(
    'requested_by_customer' => t('Requested by customer'),
    'duplicate' => t('Duplicate'),
    'fraudulent' => t('Fraduluent'),
  );

  $form['reason'] = array(
    '#type' => 'select',
    '#title' => t('Refund reason'),
    '#description' => t('Select the most appropriate reason for the refund.'),
    '#options' => $options,
  );

  $form['actions'] = array(
    '#type' => 'container',
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Process refund'),
  );

  $form['actions']['cancel'] = array(
    '#type' => 'button',
    '#value' => t('Cancel'),
  );
  return $form;
}

/**
 * Validation callback for submitting refunds to Stripe.
 */
function commerce_stripe_refund_form_validate($form, &$form_state) {
  $transaction = $form_state['transaction'];
  $amount = commerce_currency_decimal_to_amount($form_state['values']['amount'], $transaction->currency_code);

  // Calculate the amount left available for a refund.
  $amount_refunded = !empty($form_state['stripe_charge']->amount_refunded) ? $form_state['stripe_charge']->amount_refunded : 0;
  $remaining = $form_state['stripe_charge']->amount - $amount_refunded;

  // Make sure the refund amount is valid and available.
  if ($amount <= 0 || $amount > $remaining || !is_numeric($amount)) {
    form_set_error('amount', t('Please enter a valid return amount that is less than or equal to the remaining balance available for refund of @remaining.', array('@remaining' => commerce_currency_format($remaining, $transaction->currency_code))));
  }
}

/**
 * Submit callback for submitting refunds to Stripe.
 */
function commerce_stripe_refund_form_submit($form, &$form_state) {
  // Don't rely on form_state objects to be fresh.
  $order = commerce_order_load($form_state['order']->order_id);
  $transaction = commerce_payment_transaction_load($form_state['transaction']->transaction_id);
  $payment_method = $form_state['payment_method'];
  global $user;

  // Make sure the library is available.
  if (!commerce_stripe_load_library()) {
    drupal_set_message(t('Cannot load the Stripe PHP library'), 'error');
    return FALSE;
  }

  // Create the refund object.
  $data = array(
    'amount' => commerce_currency_decimal_to_amount($form_state['values']['amount'], $transaction->currency_code),
    'reason' => $form_state['values']['reason'],
  );

  try {
    Stripe::setApiKey($payment_method['settings']['secret_key']);
    $charge = Stripe_Charge::retrieve($transaction->remote_id);
    $refund = $charge->refunds->create($data);
  }
  catch (Exception $e) {
    drupal_set_message(t('The transaction could not be refunded. The error was: @error', array('@error' => $e->getMessage())), 'error');
  }

  if (is_object($refund)) {
    // Copy the refund object into our own payload so we don't save API keys
    // included in the response object.
    $payload = array(
      'id' => $refund->id,
      'amount' => $refund->amount,
      'currency' => $refund->currency,
      'created' => $refund->created,
      'object' => $refund->object,
      'balance_transaction' => $refund->balance_transaction,
      'charge' => $refund->charge,
      'receipt_number' => $refund->receipt_number,
      'reason' => $refund->reason,
    );

    // Create the new commerce payment transation and set appropriate values.
    $refund_transaction = commerce_payment_transaction_new($transaction->payment_method, $order->order_id);
    $refund_transaction->instance_id = $payment_method['instance_id'];
    $refund_transaction->payload[REQUEST_TIME] = print_r($payload, TRUE);
    $refund_transaction->status = COMMERCE_PAYMENT_STATUS_SUCCESS;
    $refund_transaction->remote_id = $refund->id;
    $refund_transaction->message = t('Refund issued.');

    // Save data on the initial charge and flag this transaction as a refund.
    $refund_transaction->data = array(
      'stripe' => array(
        'stripe_charge' => array(
          'id' => $refund->id,
          'balance_transaction' => $refund->balance_transaction,
          'amount_refunded' => $refund->amount,
        ),
        'stripe_refund' => TRUE,
      ),
    );

    // Save the amount as a negative integer.
    $refund_transaction->amount = $refund->amount * -1;
    $refund_transaction->currency_code = strtoupper($refund->currency);
    commerce_payment_transaction_save($refund_transaction);

    // Inform the user of the success and redirect them back to payments.
    drupal_set_message(t('Refund processed successfully'));
    $form_state['redirect'] = 'admin/commerce/orders/' . $order->order_id . '/payment';
    return;
  }

  // Inform the user that the refund was not successful.
  $mesasge = 'The payment transaction could not be refunded. Failure information, if provided is: @failure_code @failure_message';
  $message_variables = array(
    '@failure_code' => !empty($refund->failure_code) ? $refund->failure_code : NULL,
    '@failure_message' => !empty($refund->failure_message) ? $refund->failure_message : NULL,
  );
  drupal_set_message(t($message, $message_variables), 'error');
}
