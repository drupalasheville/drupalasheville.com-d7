<?php

/**
 * @file
 * Rules integration.
 */

/**
 * Implements hook_rules_event_info().
 */
function payment_rules_event_info() {
  $event['payment_status_change'] = array(
    'label' => t("After changing a payment's status"),
    'group' => t('Payment'),
    'access callback' => 'payment_rules_access',
    'variables' => array(
      'payment' => array(
        'type' => 'payment',
        'label' => t('Payment'),
      ),
      'payment_old_status' => array(
        'type' => 'text',
        'label' => t("The payment's old status"),
      ),
    ),
  );
  $event['payment_pre_execute'] = array(
    'label' => t('Before executing a payment'),
    'group' => t('Payment'),
    'access callback' => 'payment_rules_access',
    'variables' => array(
      'payment' => array(
        'type' => 'payment',
        'label' => t('Payment'),
      ),
    ),
  );
  $event['payment_pre_finish'] = array(
    'label' => t("When resuming the user's work after finishing payment execution"),
    'group' => t('Payment'),
    'access callback' => 'payment_rules_access',
    'variables' => array(
      'payment' => array(
        'type' => 'payment',
        'label' => t('Payment'),
      ),
    ),
  );
  $event['payment_validate'] = array(
    'label' => t('When validating a payment against an arbitrary payment method'),
    'group' => t('Payment'),
    'access callback' => 'payment_rules_access',
    'variables' => array(
      'payment' => array(
        'type' => 'payment',
        'label' => t('Payment'),
      ),
      'payment_method' => array(
        'type' => 'payment_method',
        'label' => t('Payment method'),
        'description' => t('The payment method the variable is validated against.'),
      ),
      'strict' => array(
        'type' => 'boolean',
        'label' => t('Strict validation'),
        'description' => t('Whether to validate everything a payment method needs or to validate the most important things only. Useful when finding available payment methods, for instance, which does not require unimportant things to be a 100% valid.'),
      ),
    ),
  );

  return $event;
}

/**
 * Implements hook_rules_action_info().
 */
function payment_rules_action_info() {
  $actions['payment_rules_action_payment_set_status'] = array(
    'label' => t('Set payment status'),
    'access callback' => 'payment_rules_access',
    'parameter' => array(
      'payment' => array(
        'type' => 'payment',
        'label' => t('Label'),
      ),
      'status' => array(
        'type' => 'text',
        'label' => t('Status'),
        'options list' => 'payment_status_options',
      ),
    ),
    'group' => t('Payment'),
  );
  $actions['payment_rules_action_payment_line_item_delete'] = array(
    'label' => t('Delete a payment line item'),
    'access callback' => 'payment_rules_access',
    'group' => t('Payment'),
    'parameter' => array(
      'payment' => array(
        'type' => 'payment',
        'label' => t('Payment'),
      ),
      'name' => array(
        'type' => 'text',
        'label' => t('Machine name'),
      ),
    ),
  );
  $description = array(t('If the evaluated amount does not return a whole or fractional number, this action will do nothing.'));
  $description[] = module_exists('ctools') ? t('You can use mathematical expressions.') : t('Enable <a href="http://drupal.org/project/ctools">Chaos tool suite</a> in order to use mathematical expressions.');
  $description = implode(' ', $description);
  $actions['payment_rules_action_payment_line_item_add'] = array(
    'label' => t('Add a line item'),
    'access callback' => 'payment_rules_access',
    'group' => t('Payment'),
    'parameter' => array(
      'payment' => array(
        'type' => 'payment',
        'label' => t('Payment'),
      ),
      'name' => array(
        'type' => 'text',
        'label' => t('Machine name'),
      ),
      'description' => array(
        'type' => 'text',
        'label' => t('Description'),
        'translatable' => TRUE,
      ),
      'tax_rate' => array(
        'type' => 'decimal',
        'label' => t('Tax rate'),
        'description' => t('Enter a (fractional) number between 0 and 1.'),
        'default value' => 0,
      ),
      'quantity' => array(
        'type' => 'integer',
        'label' => t('Quantity'),
        'default value' => 1,
      ),
      'amount' => array(
        'type' => 'text',
        'label' => t('Amount'),
        'description' => $description,
      ),
    ),
  );
  $actions['payment_rules_action_payment_invalidate'] = array(
    'label' => t('Invalidate the combination of payment and payment method'),
    'access callback' => 'payment_rules_access',
    'group' => t('Payment'),
    'parameter' => array(
      'message' => array(
        'type' => 'text',
        'label' => t('Message'),
      ),
    ),
  );

  return $actions;
}

/**
 * Implements hook_rules_condition_info().
 */
function payment_rules_condition_info() {
  $conditions['payment_rules_condition_payment_status_is'] = array(
    'label' => t('Payment status is'),
    'access callback' => 'payment_rules_access',
    'parameter' => array(
      'payment' => array(
        'label' => t('Payment'),
        'type' => 'payment',
        'restriction' => 'selector',
      ),
      'payment_statuses' => array(
        'type' => 'list<text>',
        'label' => t('Payment status'),
        'options list' => 'payment_status_options',
        'restriction' => 'input',
      ),
    ),
    'group' => t('Payment'),
  );
  $conditions['payment_rules_condition_payment_status_has_ancestor'] = array(
    'label' => t('Payment status is derived from'),
    'access callback' => 'payment_rules_access',
    'parameter' => array(
      'payment' => array(
        'label' => t('Payment'),
        'type' => 'payment',
        'restriction' => 'selector',
      ),
      'payment_statuses' => array(
        'type' => 'list<text>',
        'label' => t('Payment status is derived from'),
        'options list' => 'payment_status_options',
        'restriction' => 'input',
      ),
    ),
    'group' => t('Payment'),
  );
  $conditions['payment_rules_condition_payment_uses_payment_method'] = array(
    'label' => t('Payment uses payment method (deprecated)'),
    'access callback' => 'payment_rules_access',
    'parameter' => array(
      'payment' => array(
        'label' => t('Payment'),
        'type' => 'payment',
        'restriction' => 'selector',
      ),
      'pmids' => array(
        'type' => 'list<text>',
        'label' => t('Payment methods'),
        'options list' => 'payment_method_options',
        'restriction' => 'input',
      ),
    ),
    'group' => t('Payment'),
  );
  $conditions['payment_rules_condition_payment_method_comparison'] = array(
    'label' => t('Payment method is'),
    'access callback' => 'payment_rules_access',
    'parameter' => array(
      'payment_method' => array(
        'label' => t('Payment method'),
        'type' => 'payment_method',
        'restriction' => 'selector',
      ),
      'pmids' => array(
        'type' => 'list<text>',
        'label' => t('Payment methods'),
        'options list' => 'payment_method_options',
        'restriction' => 'input',
      ),
    ),
    'group' => t('Payment'),
  );
  $conditions['payment_rules_condition_payment_uses_payment_method_type'] = array(
    'label' => t('Payment uses payment method of type (deprecated)'),
    'access callback' => 'payment_rules_access',
    'parameter' => array(
      'payment' => array(
        'label' => t('Payment'),
        'type' => 'payment',
        'restriction' => 'selector',
      ),
      'payment_method_controller_class_names' => array(
        'type' => 'list<text>',
        'label' => t('Payment method types'),
        'options list' => 'payment_method_controller_options',
        'restriction' => 'input',
      ),
    ),
    'group' => t('Payment'),
  );
  $conditions['payment_rules_condition_payment_method_type_comparison'] = array(
    'label' => t('Payment method is of type'),
    'access callback' => 'payment_rules_access',
    'parameter' => array(
      'payment_method' => array(
        'label' => t('Payment method'),
        'type' => 'payment_method',
        'restriction' => 'selector',
      ),
      'payment_method_controller_class_names' => array(
        'type' => 'list<text>',
        'label' => t('Payment method types'),
        'options list' => 'payment_method_controller_options',
        'restriction' => 'input',
      ),
    ),
    'group' => t('Payment'),
  );
  $conditions['payment_rules_condition_payment_method_controller_supports_currency'] = array(
    'label' => t('Payment uses payment method of a type that supports currency (deprecated)'),
    'access callback' => 'payment_rules_access',
    'parameter' => array(
      'payment' => array(
        'label' => t('Payment'),
        'type' => 'payment',
        'restriction' => 'selector',
      ),
      'currency' => array(
        'type' => 'text',
        'label' => t('Currency code'),
      ),
    ),
    'group' => t('Payment'),
  );
  $conditions['payment_rules_condition_payment_method_supports_currencies'] = array(
    'label' => t('Payment method supports currency'),
    'access callback' => 'payment_rules_access',
    'parameter' => array(
      'payment_method' => array(
        'label' => t('Payment method'),
        'type' => 'payment_method',
        'restriction' => 'selector',
      ),
      'currency' => array(
        'type' => 'list<text>',
        'label' => t('Currency code'),
      ),
    ),
    'group' => t('Payment'),
  );
  $conditions['payment_rules_condition_payment_amount_comparison'] = array(
    'label' => t('Payment amount comparison'),
    'access callback' => 'payment_rules_access',
    'parameter' => array(
      'payment' => array(
        'label' => t('Payment'),
        'type' => 'payment',
        'restriction' => 'selector',
      ),
      'operator' => array(
        'type' => 'text',
        'label' => t('Comparison operator'),
        'default value' => '<=',
        'options list' => 'payment_numeric_comparison_operator_options',
        'restriction' => 'input',
      ),
      'comparison_amount' => array(
        'type' => 'decimal',
        'label' => t('Amount'),
        'default value' => '0',
      ),
    ),
    'group' => t('Payment'),
  );

  return $conditions;
}

/**
 * Implements Rules condition callback: check whether a payment's status
 * is one of the selected statuses.
 *
 * @param Payment $payment
 *   The payment to check the condition for.
 * @param array $payment_statuses
 *   An array with payment statuses.
 *
 * @return boolean
 */
function payment_rules_condition_payment_status_is(Payment $payment, array $payment_statuses) {
  return in_array($payment->getStatus()->status, $payment_statuses);
}

/**
 * Implements Rules condition callback: check whether a payment's status
 * is a child of any of the selected statuses.
 *
 * @param Payment $payment
 *   The payment to check the condition for.
 * @param array $payment_statuses
 *   An array with payment statuses.
 *
 * @return boolean
 */
function payment_rules_condition_payment_status_has_ancestor(Payment $payment, array $payment_statuses) {
  foreach ($payment_statuses as $payment_status) {
    if (payment_status_has_ancestor($payment->getStatus()->status, $payment_status)) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Implements Rules action callback for payment_rules_payment_set_status.
 */
function payment_rules_action_payment_set_status(Payment $payment, $status_data) {
  $payment->setStatus(reset($status_data));
}

/**
 * Implements Rules action callback: add a line item.
 *
 * @param Payment $payment
 * @param string $name
 *   The line item's unique machine name.
 * @param string $description
 * @param float $tax_rate
 * The tax rate that applies to the amount. Should be a float between 0 and 1.
 * @param integer $quantity
 * @param integer|string $amount
 *   The amount of money, either as an integer or string that contains
 *   placeholders or a Ctools math expression.
 */
function payment_rules_action_payment_line_item_add(Payment $payment, $name, $description, $tax_rate, $quantity, $amount) {
  if (!is_numeric($amount)) {
    // Replace placeholders.
    $amount = token_replace($amount, array(
      'payment' => $payment,
    ));

    // Evaluate Ctools math expression.
    if (module_exists('ctools')) {
      $math = new ctools_math_expr;
      $amount = $math->evaluate($amount);
    }
  }
  if (is_numeric($amount)) {
    $payment->setLineItem(new PaymentLineItem(array(
      'name' => $name,
      'amount' => $amount,
      'description' => $description,
      'tax_rate' => $tax_rate,
      'quantity' => $quantity,
    )));
  }
}

/**
 * Implements Rules action callback: invalidate a combination of a payment and
 * a payment method.
 *
 * @throws PaymentValidatioNException
 *
 * @param $message
 *
 * @return NULL
 */
function payment_rules_action_payment_invalidate($message) {
  throw new PaymentValidationException($message);
}


/**
 * Implements Rules options list callback for
 * payment_rules_action_payment_line_item_set_calculated().
 */
function payment_rules_options_list_payment_line_item_name() {
  $options = array();
  foreach (payment_line_items_info() as $line_item_info) {
    $options[$line_item_info->name] = $line_item_info->title;
  }

  return $options;
}

/**
 * Implements Rules action callback: delete a line item.
 *
 * @param Payment $payment
 * @param string $name
 *   The machine name of the line item to delete.
 */
function payment_rules_action_payment_line_item_delete(Payment $payment, $name) {
  unset($payment->line_items[$name]);
}

/**
 * Implements Rules condition callback: check whether a payment uses one of the
 * selected payment methods.
 *
 * This function is deprecated. Use
 * payment_rules_condition_payment_method_comparison() instead.
 *
 * @see payment_rules_condition_payment_method_comparison()
 *
 * @param Payment $payment
 *   The payment to check the condition for.
 * @param array $pmids
 *   An array with payment method IDs.
 *
 * @return boolean
 */
function payment_rules_condition_payment_uses_payment_method(Payment $payment, array $pmids) {
  return $payment->method && payment_rules_condition_payment_method_comparison($payment->method, $pmids);
}

/**
 * Implements Rules condition callback: check whether a payment method is one
 * of the given payment methods.
 *
 * @param PaymentMethod $payment_method
 *   The payment method to check the condition for.
 * @param array $pmids
 *   An array with payment method IDs.
 *
 * @return boolean
 */
function payment_rules_condition_payment_method_comparison(PaymentMethod $payment_method, array $pmids) {
  return in_array($payment_method->pmid, $pmids);
}

/**
 * Implements Rules options list callback for
 * payment_rules_condition_payment_uses_payment_method_type.
 *
 * This function is deprecated. Use payment_method_controller_options()
 * instead.
 *
 * @todo Remove this function in Payment 2.
 */
function payment_rules_options_list_payment_uses_payment_method_type() {
  return payment_method_controller_options();
}

/**
 * Implements Rules condition callback: check whether a payment uses one of the
 * selected payment methods types.
 *
 * This function is deprecated. Use
 * payment_rules_condition_payment_method_type_comparison() instead.
 *
 * @see payment_rules_condition_payment_method_type_comparison()
 *
 * @param Payment $payment
 *   The payment to check the condition for.
 * @param array $payment_method_controller_class_names
 *   An array with class names of payment method controllers.
 *
 * @return boolean
 */
function payment_rules_condition_payment_uses_payment_method_type(Payment $payment, array $payment_method_controller_class_names) {
  return $payment->method && payment_rules_condition_payment_method_type_comparison($payment->method, $payment_method_controller_class_names);
}

/**
 * Implements Rules condition callback: check whether a payment method uses one
 * of the given controllers.
 *
 * @param PaymentMethod $payment_method
 *   The payment method to check the condition for.
 * @param array $payment_method_controller_class_names
 *   An array with class names of payment method controllers.
 *
 * @return boolean
 */
function payment_rules_condition_payment_method_type_comparison(PaymentMethod $payment_method, array $payment_method_controller_class_names) {
  return in_array($payment_method->controller->name, $payment_method_controller_class_names);
}

/**
 * Implements Rules condition callback: check whether a payment method
 * controller supports a currency.
 *
 * This function is deprecated. Use
 * payment_rules_condition_payment_method_supports_currencies() instead.
 *
 * @see payment_rules_condition_payment_method_supports_currencies()
 *
 * @param Payment $payment
 *   The payment to check the condition for.
 * @param string $currency_code
 *   The ISO 4217 currency code to check for.
 *
 * @return boolean
 */
function payment_rules_condition_payment_method_controller_supports_currency(Payment $payment, $currency_code) {
  return $payment->method && payment_rules_condition_payment_method_supports_currencies($payment->method, array($currency_code));
}

/**
 * Implements Rules condition callback: check whether a payment method supports
 * a currency.
 *
 * @param PaymentMethod $payment_method
 *   The payment method to check the condition for.
 * @param array $currency_codes
 *   The ISO 4217 currency codes to check for.
 *
 * @return boolean
 */
function payment_rules_condition_payment_method_supports_currencies(PaymentMethod $payment_method, array $currency_codes) {
  return empty($payment_method->controller->currencies) || (bool) array_intersect($currency_codes, array_keys($payment_method->controller->currencies));
}

/**
 * Implements Rules condition callback: compare the payment amount.
 *
 * @param Payment $payment
 *   The payment of which to compare the amount.
 * @param string $comparison_operator
 * @param string $comparison_amount
 *
 * @return boolean
 */
function payment_rules_condition_payment_amount_comparison(Payment $payment, $operator, $comparison_amount) {
  $payment_amount = $payment->totalAmount(TRUE);
  switch ($operator) {
    case '<':
      return $payment_amount < $comparison_amount;
    case '<=':
      return $payment_amount <= $comparison_amount;
    case '=':
      return $payment_amount == $comparison_amount;
    case '>=':
      return $payment_amount >= $comparison_amount;
    case '>':
      return $payment_amount > $comparison_amount;
  }
  return FALSE;
}
