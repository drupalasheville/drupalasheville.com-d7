<?php

/**
 * @file
 * The API and related functions for executing and managing payments.
 */

/**
 * Base class with common functionality.
 */
class PaymentCommon {
  function __construct(array $properties = array()) {
    foreach ($properties as $property => $value) {
      $this->$property = $value;
    }
  }
}

/**
 * A single payment. Contains all payment-specific data.
 *
 * @see PaymentMethod
 * @see PaymentMethodController
 */
class Payment extends PaymentCommon {

  /**
   * The machine name of the context that created this Payment, such as the
   * webshop module.
   *
   * @var string
   */
  public $context = '';

  /**
   * Information about this payment that is specific to the context that
   * created it, such as the webshop module.
   *
   * @var mixed[]
   */
  public $context_data = array();

  /**
   * The ISO 4217 currency code of the payment amount.
   *
   * @var string
   */
  public $currency_code = 'XXX';

  /**
   * The general description of this payment. Not to be confused with line item
   * descriptions.
   *
   * @var string
   */
  public $description = '';

  /**
   * Arguments to pass on to t() when translating $this->description.
   *
   * @var string[]
   */
  public $description_arguments = array();

  /**
   * The name of a function to call when payment execution is completed,
   * regardless of the payment status. It receives one argument:
   * - $payment Payment
   *   The Payment object.
   * The callback does not need to return anything and is free to redirect the
   * user or display something.
   * Use Payment::context_data to pass on arbitrary data to the finish callback.
   *
   * @var string
   */
  public $finish_callback = '';

  /**
   * An array with PaymentLineItem objects.
   *
   * @see Payment::setLineItem()
   *
   * @var PaymentLineItem[]
   */
  public $line_items = array();

  /**
   * The payment method used for this payment.
   *
   * @var PaymentMethod
   */
  public $method = NULL;

  /**
   * Information about this payment that is specific to its payment method.
   *
   * @var mixed[]
   */
  public $method_data = array();

  /**
   * The internal ID of this payment.
   *
   * @var integer
   */
  public $pid = 0;

  /**
   * The status log. Contains PaymentStatusItem objects ordered by datetime. Do
   * not set directly, but use Payment::setStatus() instead.
   *
   * @see Payment::setStatus()
   *
   * @var PaymentStatusItem[]
   */
  public $statuses = array();

  /**
   * The UID of the user this payment belongs to.
   *
   * @var integer
   */
  public $uid = NULL;

  /**
   * Constructor.
   *
   * @param mixed[] $properties
   *   An associative array. Keys are property names and values are property
   *   values.
   */
  function __construct(array $properties = array()) {
    global $user;

    parent::__construct($properties);

    if (is_null($this->uid)) {
      $this->uid = $user->uid;
    }
    if (!$this->statuses) {
      // We purposefully avoid Payment::setStatus(), because this is the
      // payment's first status.
      $this->statuses[] = new PaymentStatusItem(PAYMENT_STATUS_NEW);
    }
  }

  /**
   * Execute the actual payment.
   */
  function execute() {
    // Preprocess the payment.
    module_invoke_all('payment_pre_execute', $this);
    if (module_exists('rules')) {
      rules_invoke_event('payment_pre_execute', $this);
    }
    // Execute the payment.
    if ($this->method) {
      try {
        $this->method->validate($this);
        $this->setStatus(new PaymentStatusItem(PAYMENT_STATUS_PENDING));
        $this->method->controller->execute($this);
      }
      // An exception was thrown during validation.
      catch (PaymentValidationException $e) {
        $this->setStatus(new PaymentStatusItem(PAYMENT_STATUS_FAILED));
      }
    }
    // There is no payment method.
    else {
      $this->setStatus(new PaymentStatusItem(PAYMENT_STATUS_FAILED));
    }
    // This is only called if the payment execution didn't redirect the user
    // offsite. Otherwise it's the payment method return page's responsibility.
    $this->finish();
  }

  /**
   * Finish the payment after its execution.
   */
  function finish() {
    entity_save('payment', $this);
    module_invoke_all('payment_pre_finish', $this);
    if (module_exists('rules')) {
      rules_invoke_event('payment_pre_finish', $this);
    }
    call_user_func($this->finish_callback, $this);
  }

  /**
   * Set a line item.
   *
   * @see Payment::getLineItems()
   *
   * @param PaymentLineItem $line_item
   *
   * @return static
   */
  function setLineItem(PaymentLineItem $line_item) {
    $this->line_items[$line_item->name] = $line_item;

    return $this;
  }

  /**
   * Get line items.
   *
   * @param string|null $name (optional)
   *   The requested line item(s)'s machine name, as possibly defined in
   *   hook_payment_line_item_info(). If $name is NULL, then all line items
   *   will be returned.
   *
   * @return PaymentLineItem[]
   *   An array with matching PaymentLineItem objects.
   */
  function getLineItems($name = NULL) {
    if (is_null($name)) {
      return payment_line_item_get_all($name, $this);
    }
    elseif ($line_item_info = payment_line_item_info($name)) {
      return call_user_func($line_item_info->callback, $name, $this);
    }
    else {
      return payment_line_item_get_specific($name, $this);
    }
  }

  /**
   * Get the total payment amount.
   *
   * @param boolean $tax
   *   Whether to include taxes or not.
   * @param PaymentLineItem[]|null $line_items
   *   An array with PaymentLineItem objects to calculate the total from.
   *   Leave empty to use $this->line_items.
   *
   * @return float
   */
  function totalAmount($tax, array $line_items = NULl) {
    $total = 0;
    if (is_null($line_items)) {
      $line_items = $this->line_items;
    }
    foreach ($line_items as $line_item) {
      $total += $line_item->totalAmount($tax);
    }

    return $total;
  }

  /**
   * Set the payment status.
   *
   * @param PaymentStatusItem $status_item
   *
   * @return static
   */
  function setStatus(PaymentStatusItem $status_item) {
    $previous_status_item = $this->getStatus();
    $status_item->pid = $this->pid;
    // Prevent duplicate status items.
    if ($this->getStatus()->status != $status_item->status) {
      $this->statuses[] = $status_item;
    }
    foreach (module_implements('payment_status_change') as $module_name) {
      call_user_func($module_name . '_payment_status_change', $this, $previous_status_item);
      // If a hook invocation has added another log item, a new loop with
      // invocations has already been executed and we don't need to continue
      // with this one.
      if ($this->getStatus()->status != $status_item->status) {
        return $this;
      }
    }
    if (module_exists('rules')) {
      rules_invoke_event('payment_status_change', $this, $previous_status_item);
    }

    return $this;
  }

  /**
   * Get the current payment status.
   *
   * @return PaymentStatusItem
   */
  function getStatus() {
    return end($this->statuses);
  }

  /**
   * Get available/valid payment methods for this payment.
   *
   * @param PaymentMethod[] $payment_methods
   *   Use an empty array to check the availability of all payment methods.
   *
   * @return PaymentMethod[]
   *   An array with payment methods usable for Payment in its current state,
   *   keyed by PMID.
   */
  function availablePaymentMethods(array $payment_methods = array()) {
    if (!$payment_methods) {
      $payment_methods = entity_load('payment_method', FALSE);
    }
    $available = array();
    foreach ($payment_methods as $payment_method) {
      try {
        $payment_method->validate($this, FALSE);
        $available[$payment_method->pmid] = $payment_method;
      }
      catch (PaymentValidationException $e) {
      }
    }

    return $available;
  }
}

/**
 * Entity API controller for payment entities.
 */
class PaymentEntityController extends EntityAPIController {

  /**
   * {@inheritdoc}
   */
  function load($ids = array(), $conditions = array()) {
    $entities = parent::load($ids, $conditions);
    foreach ($entities as $payment) {
      // Cast non-string scalars to their original types, because some backends
      // store/return all variables as strings.
      $payment->pid = (int) $payment->pid;
      $payment->uid = (int) $payment->uid;
    }

    return $entities;
  }

  /**
   * {@inheritdoc}
   */
  function attachLoad(&$queried_entities, $revision_id = FALSE) {
    $pids = array_keys($queried_entities);

    // Load the payments's payment methods.
    $pmids = array();
    foreach ($queried_entities as $payment) {
      $pmids[] = $payment->pmid;
    }
    $methods = entity_load('payment_method', $pmids);

    // Load line items.
    $result = db_select('payment_line_item')
      ->fields('payment_line_item')
      ->condition('pid', $pids)
      ->execute();
    $line_items = array();
    while ($line_item_data = $result->fetchAssoc('name', PDO::FETCH_ASSOC)) {
      $line_item_data['description_arguments'] = unserialize($line_item_data['description_arguments']);
      $line_item_data['amount'] = (float) $line_item_data['amount'];
      $line_item_data['tax_rate'] = (float) $line_item_data['tax_rate'];
      $line_item_data['quantity'] = (int) $line_item_data['quantity'];
      $line_items[$line_item_data['pid']][$line_item_data['name']] = new PaymentLineItem($line_item_data);
    }

    // Load the payments's status items.
    $result = db_select('payment_status_item')
      ->fields('payment_status_item')
      ->condition('pid', $pids)
      ->orderBy('psiid')
      ->execute();
    $status_items = array();
    while ($data = $result->fetchObject()) {
      $status_item = new PaymentStatusItem($data->status, $data->created, $data->pid, $data->psiid);
      $status_items[$status_item->pid][] = $status_item;
    }

    // Add all data to the payments.
    foreach ($queried_entities as $payment) {
      $payment->statuses = $status_items[$payment->pid];
      $payment->line_items = isset($line_items[$payment->pid]) ? $line_items[$payment->pid] : array();
      $payment->method = $methods[$payment->pmid];
      unset($payment->pmid);
    }

    parent::attachLoad($queried_entities, $revision_id);
  }

  /**
   * {@inheritdoc}
   */
  function save($entity, DatabaseTransaction $transaction = NULL) {
    $payment = $entity;

    // Save the payment.
    $payment->pmid = $payment->method->pmid;
    $return = parent::save($payment, $transaction);
    unset($payment->pmid);

    // Save line items.
    foreach ($payment->line_items as $line_item) {
      db_merge('payment_line_item')
        ->key(array(
          'name' => $line_item->name,
          'pid' => $payment->pid,
        ))
        ->fields(array(
          'amount' => $line_item->amount,
          'amount_total' => $line_item->amount * $line_item->quantity * ($line_item->tax_rate + 1),
          'description' => $line_item->description,
          'description_arguments' => serialize($line_item->description_arguments),
          'name' => $line_item->name,
          'pid' => $payment->pid,
          'quantity' => $line_item->quantity,
          'tax_rate' => $line_item->tax_rate,
        ))
        ->execute();
    }

    // Save the payment's status items.
    $update = empty(reset($payment->statuses)->psiid) || empty(end($payment->statuses)->psiid);
    foreach ($payment->statuses as $status_item) {
      // Statuses cannot be edited, so only save the ones without a PSIID set.
      if (!$status_item->psiid) {
        $status_item->pid = $payment->pid;
        drupal_write_record('payment_status_item', $status_item);
      }
    }
    if ($update) {
      $payment->psiid_first = reset($payment->statuses)->psiid;
      $payment->psiid_last = end($payment->statuses)->psiid;
      $query = db_update('payment')
        ->condition('pid', $payment->pid)
        ->fields(array(
          'psiid_first' => reset($payment->statuses)->psiid,
          'psiid_last' => end($payment->statuses)->psiid,
        ));
        $query->execute();
    }

    return $return;
  }

  /**
   * {@inheritdoc}
   */
  function view($entities, $view_mode = 'full', $langcode = NULL, $page = NULL) {
    $build = parent::view($entities, $view_mode, $langcode, $page);
    $type = 'payment';
    foreach ($build['payment'] as &$payment_build) {
      $payment = $payment_build['#entity'];
      $payment_build['payment_line_items'] = payment_line_items($payment);
      $payment_build['payment_status_items'] = payment_status_items($payment);
      $payment_build['payment_method'] = array(
        '#type' => 'item',
        '#title' => t('Payment method'),
        '#markup' => check_plain($payment->method->title_generic),
      );
      drupal_alter(array('payment_view', 'entity_view'), $payment_build, $type);
    }

    return $build;
  }

  /**
   * {@inheritdoc}
   */
  function delete($ids, DatabaseTransaction $transaction = NULL) {
    parent::delete($ids, $transaction);
    db_delete('payment_line_item')
      ->condition('pid', $ids)
      ->execute();
    db_delete('payment_status_item')
      ->condition('pid', $ids)
      ->execute();
  }
}

/**
 * Payment method configuration.
 *
 * @see Payment
 * @see PaymentMethodController
 */
class PaymentMethod extends PaymentCommon {

  /**
   * The payment method controller this merchant uses.
   *
   * @var PaymentMethodController
   */
  public $controller = NULL;

  /**
   * Information about this payment method that is specific to its controller.
   *
   * @var mixed[]
   */
  public $controller_data = array();

  /**
   * Whether this payment method is enabled and can be used.
   *
   * @var boolean
   */
  public $enabled = TRUE;

  /**
   * The entity's unique machine name.
   *
   * @var string
   */
  public $name = '';

  /**
   * The machine name of the module that created this payment method.
   *
   * @var string
   */
  public $module = 'payment';

  /**
   * The unique internal ID.
   *
   * @var integer
   */
  public $pmid = 0;

  /**
   * One of Entity API's ENTITY_* constants for exportable entities.
   *
   * @see entity_has_status()
   *
   * @var integer
   */
  public $status = ENTITY_CUSTOM;

  /**
   * The specific human-readable title, e.g. "Paypal WPS".
   *
   * @var string
   */
  public $title_specific = '';

  /**
   * The generic human-readable title, e.g. "Paypal".
   *
   * @var string
   */
  public $title_generic = '';

  /**
   * The UID of the user this payment method belongs to.
   *
   * @var integer
   */
  public $uid = NULL;

  /**
   * {@inheritdoc}
   */
  function __construct(array $properties = array()) {
    global $user;

    parent::__construct($properties);

    if (is_null($this->uid)) {
      // Cast non-string scalars to their original types, because some backends
      // store/return all variables as strings.
      $this->uid = (int) $user->uid;
    }
  }

  /**
   * Validate a payment against this payment method.
   *
   * @param Payment $payment
   * @param boolean $strict
   *   Whether to validate everything a payment method needs or to validate the
   *   most important things only. Useful when finding available payment methods,
   *   for instance, which does not require unimportant things to be a 100%
   *   valid.
   *
   * @throws PaymentValidationException
   */
  function validate(Payment $payment, $strict = TRUE) {
    $this->controller->validate($payment, $this, $strict);
    module_invoke_all('payment_validate', $payment, $this, $strict);
    if (module_exists('rules')) {
      rules_invoke_event('payment_validate', $payment, $this, $strict);
    }
  }
}

/**
 * A payment method that essentially disables payments.
 *
 * This is a 'placeholder' method that returns defaults and doesn't really do
 * anything else. It is used when no working payment method is available, so
 * other modules don't have to check for that.
 */
class PaymentMethodUnavailable extends PaymentMethod {

  public $enabled = FALSE;
  public $name = 'payment_method_unavailable';
  public $module = 'payment';
  // Use 0, so the payment method can be used for payments, but will never
  // collide with existing payment methods.
  public $pmid = 0;

  /**
   * {@inheritdoc}
   */
  function __construct() {
    $this->title_specific = $this->title_generic = t('Unavailable');
    $this->controller = payment_method_controller_load('PaymentMethodControllerUnavailable');
  }
}

/**
 * Entity API controller for payment_method entities.
 */
class PaymentMethodEntityController extends EntityAPIControllerExportable {

  /**
   * {@inheritdoc}
   */
  function load($ids = array(), $conditions = array()) {
    static $unavailable = NULL;

    $entities = parent::load($ids, $conditions);
    foreach ($entities as $payment_method) {
      // Cast non-string scalars to their original types, because some backends
      // store/return all variables as strings.
      $payment_method->enabled = (bool) $payment_method->enabled;
      $payment_method->pmid = (int) $payment_method->pmid;
      $payment_method->status = (int) $payment_method->status;
      $payment_method->uid = (int) $payment_method->uid;
    }
    // Load PaymentMethodUnavailable for all requested IDs that did not match
    // any existing payment methods.
    if (is_array($ids)) {
      // If the entities were loaded by PID.
      if (is_numeric(reset($ids))) {
        $diff = array_diff($ids, array_keys($entities));
      }
      // If the entities were loaded by name.
      else {
        $names = array();
        foreach ($entities as $entity) {
          $names[] = $entity->name;
        }
        $diff = array_diff($ids, $names);
      }

      if ($diff && is_null($unavailable)) {
        $unavailable = new PaymentMethodUnavailable;
      }
      foreach ($diff as $pmid) {
        $entities[$pmid] = $unavailable;
      }
      ksort($entities);
    }


    return $entities;
  }

  /**
   * {@inheritdoc}
   */
  function attachLoad(&$queries_entities, $revision_id = FALSE) {
    foreach ($queries_entities as $entity) {
      $entity->controller = payment_method_controller_load($entity->controller_class_name);
      if (!$entity->controller) {
        $entity->controller = payment_method_controller_load('PaymentMethodControllerUnavailable');
      }
      unset($entity->controller_class_name);
    }
    parent::attachLoad($queries_entities, $revision_id);
  }

  /**
   * {@inheritdoc}
   */
  function save($entity, DatabaseTransaction $transaction = NULL) {
    $entity->controller_class_name = $entity->controller->name;
    $return = parent::save($entity, $transaction);
    // Cast non-string scalars to their original types, because some backends
    // store/return all variables as strings.
    $entity->pmid = (int) $entity->pmid;
    unset($entity->controller_class_name);

    return $return;
  }

  /**
   * {@inheritdoc}
   */
  function export($entity, $prefix = '') {
    // The payment method controller should not be exported. Instead, we
    // temporarily replace it with a property that only stores its class name.
    $controller = $entity->controller;
    $entity->controller_class_name = $controller->name;
    unset($entity->controller);
    $export = parent::export($entity, $prefix);
    $entity->controller = $controller;
    unset($entity->controller_class_name);

    return $export;
  }

  /**
   * {@inheritdoc}
   */
  function import($export) {
    if ($payment = parent::import($export)) {
      $payment->controller = payment_method_controller_load($payment->controller_class_name);
      unset($payment->controller_class_name);
      return $payment;
    }
    return FALSE;
  }
}

/**
 * Features controller for payment_method entities.
 */
class PaymentMethodFeaturesController extends EntityDefaultFeaturesController {

  /**
   * {@inheritdoc}
   */
  function export($data, &$export, $module_name = '') {
    $pipe = parent::export($data, $export, $module_name);

    // Add dependencies for the payment method controller classes.
    $controller_class_names = array();
    foreach (entity_load_multiple_by_name($this->type, $data) as $method) {
      $controller_class_names[] = $method->controller->name;
    }
    $result = db_select('registry')
      ->fields('registry', array('module'))
      ->condition('name', $controller_class_names)
      ->condition('type', 'class')
      ->execute();
    while ($module = $result->fetchField()) {
      $export['dependencies'][$module] = $module;
    }

    return $pipe;
  }
}

/**
 * A payment method controller, e.g. the logic behind a payment method.
 *
 * @see payment_method_controller_load()
 * @see payment_method_controller_load_multiple()
 *
 * All other payment methods need to extend this class. This is a singleton
 * class. See payment_method_controller_load().
 *
 * @see Payment
 * @see PaymentMethod
 */
class PaymentMethodController {

  /**
   * Default values for the controller_data property of a PaymentMethod that
   * uses this controller.
   *
   * @var mixed[]
   */
  public $controller_data_defaults = array();

  /**
   * An array with ISO 4217 currency codes that this controller supports.
   *
   * Keys are ISO 4217 currency codes. Values are associative arrays with keys
   * "minimum" and "maximum", whose values are the minimum and maximum amount
   * supported for the specified currency. Leave empty to allow all currencies.
   *
   * @var array[]
   */
  public $currencies = array();

  /**
   * A human-readable plain text description of this payment method controller.
   *
   * @var string
   */
  public $description = '';

  /**
   * The machine name.
   *
   * This will be set by payment_method_controller_load_multiple() as a
   * shorthand for get_class($payment_method_controller).
   *
   * @see payment_method_controller_load_multiple()
   *
   * @var string
   */
  public $name = '';

  /**
   * The function name of the payment configuration form elements.
   *
   * Note that this is not a form ID and because the form will not be called
   * using drupal_get_form(), it can only be altered by altering the form
   * payment_form(). The validate callback is expected to be a function with
   * the same name, but suffixed with "_validate". If this function exists, it
   * will be called automatically. $form_state['payment'] contains the Payment
   * that is added or edited. All method-specific information should be added
   * to it in the validate callback. The payment will be saved automatically
   * using entity_save().
   *
   * The function accepts its parent form element and &$form_state as
   * parameters. It should return an array of form elements.
   *
   * @see payment_element_info()
   * @see payment_form_method_process()
   * @see payment_form_process_method_controller_payment_configuration()
   * @see paymentmethodbasic_payment_configuration_form_elements()
   *
   * @var string
   */
  public $payment_configuration_form_elements_callback = '';

  /**
   * The function name of the payment method configuration form elements.
   *
   * Note that this is not a form ID and because the form will not be called
   * using drupal_get_form(), it can only be altered by altering the form
   * payment_form_payment_method(). The validate callback is expected to be a
   * function with the same name, but suffixed with "_validate". If this
   * function exists, it will be called automatically.
   * $form_state['payment_method'] contains the PaymentMethod that is added or
   * edited. All controller-specific information should be added to it in the
   * validate callback. The payment method will be saved automatically using
   * entity_save().
   *
   * The function accepts its parent form element and &$form_state as
   * parameters. It should return an array of form elements.
   *
   * @see payment_form_payment_method()
   * @see paymentmethodbasic_payment_method_configuration_form_elements()
   *
   * @var string
   */
  public $payment_method_configuration_form_elements_callback = '';

  /**
   * The human-readable plain text title.
   *
   * @var string
   */
  public $title = '';

  /**
   * Execute a payment.
   *
   * Note that payments may be executed even if their owner is not logged into
   * the site. This means that if you need to do access control in your
   * execute() method, you cannot use global $user.
   *
   * @param Payment $payment
   *
   * @return boolean
   *   Whether the payment was successfully executed or not.
   */
  function execute(Payment $payment) {}

  /**
   * Validate a payment against a payment method and this controller. Don't
   * call directly. Use PaymentMethod::validate() instead.
   *
   * @see PaymentMethod::validate()
   *
   * @param Payment $payment
   * @param PaymentMethod $payment_method
   * @param boolean $strict
   *   Whether to validate everything a payment method needs or to validate the
   *   most important things only. Useful when finding available payment methods,
   *   for instance, which does not require unimportant things to be a 100%
   *   valid.
   *
   * @throws PaymentValidationException
   */
  function validate(Payment $payment, PaymentMethod $payment_method, $strict) {
    // Confirm the payment method is enabled, and thus available in general.
    if (!$payment_method->enabled) {
      throw new PaymentValidationPaymentMethodDisabledException(t('The payment method is disabled.'));
    }

    if (!$payment->currency_code) {
      throw new PaymentValidationMissingCurrencyException(t('The payment has no currency set.'));
    }

    $currencies = $payment_method->controller->currencies;

    // Confirm the payment's currency is supported.
    if (!empty($this->currencies) && !isset($this->currencies[$payment->currency_code])) {
      throw new PaymentValidationUnsupportedCurrencyException(t('The currency is not supported by this payment method.'));
    }

    // Confirm the payment's description is set and valid.
    if (empty($payment->description)) {
      throw new PaymentValidationDescriptionMissing(t('The payment description is not set.'));
    }
    elseif (drupal_strlen($payment->description) > 255) {
      throw new PaymentValidationDescriptionTooLong(t('The payment description exceeds 255 characters.'));
    }

    // Confirm the finish callback is set and the function exists.
    if (empty($payment->finish_callback) || !function_exists($payment->finish_callback)) {
      throw new PaymentValidationMissingFinishCallback(t('The finish callback is not set or not callable.'));
    }

    // Confirm the payment amount is higher than the supported minimum.
    $minimum = isset($currencies[$payment->currency_code]['minimum']) ? $currencies[$payment->currency_code]['minimum'] : PAYMENT_MINIMUM_AMOUNT;
    if ($payment->totalAmount(TRUE) < $minimum) {
      throw new PaymentValidationAmountBelowMinimumException(t('The amount should be higher than !minimum.', array(
        '!minimum' => payment_amount_human_readable($minimum, $payment->currency_code),
      )));
    }

    // Confirm the payment amount does not exceed the maximum.
    if (isset($currencies[$payment->currency_code]['maximum']) && $payment->totalAmount(TRUE) > $currencies[$payment->currency_code]['maximum']) {
      throw new PaymentValidationAmountExceedsMaximumException(t('The amount should be lower than !maximum.', array(
        '!maximum' => payment_amount_human_readable($currencies[$payment->currency_code]['maximum'], $payment->currency_code),
      )));
    }
  }

  /**
   * Returns an array with the names of all available payment method
   * controllers that inherit of this one.
   *
   * return string[]
   */
  static function descendants() {
    $descendants = array();
    foreach (payment_method_controllers_info() as $controller_name) {
      if (is_subclass_of($controller_name, get_called_class())) {
        $descendants[] = $controller_name;
      }
    }

    return $descendants;
  }
}

/**
 * A payment method controller that essentially disables payment methods.
 *
 * This is a 'placeholder' controller that returns defaults and doesn't really
 * do anything else. It is used when no working controller is available for a
 * payment method, so other modules don't have to check for that.
 */
class PaymentMethodControllerUnavailable extends PaymentMethodController {

  /**
   * {@inheritdoc}
   */
  function __construct() {
    $this->title = t('Unavailable');
  }

  /**
   * {@inheritdoc}
   */
  function execute(Payment $payment) {
    $payment->setStatus(new PaymentStatusItem(PAYMENT_STATUS_UNKNOWN));
  }

  /**
   * {@inheritdoc}
   */
  function validate(Payment $payment, PaymentMethod $payment_method, $strict) {
    throw new PaymentValidationException(t('This payment method type is unavailable.'));
  }
}

/**
 * Payment status information.
 */
class PaymentStatusInfo extends PaymentCommon {

  /**
   * A US English human-readable plain text description.
   *
   * @var string
   */
  public $description = '';

  /**
   * This status's parent status.
   *
   * @var string
   */
  public $parent = NULL;

  /**
   * The status itself.
   *
   * @var string
   */
  public $status = '';

  /**
   * A US English human-readable plain text title.
   *
   * @var string
   */
  public $title = '';

  /**
   * Get this payment status's ancestors.
   *
   * @return string[]
   *   The machine names of this status's ancestors.
   */
  function ancestors() {
    $ancestors = array($this->parent);
    if ($this->parent) {
      $ancestors = array_merge($ancestors, payment_status_info($this->parent)->ancestors());
    }

    return array_unique($ancestors);
  }

  /**
   * Get this payment status's children.
   *
   * @return string[]
   *   The machine names of this status's children.
   */
  function children() {
    $children = array();
    foreach (payment_statuses_info() as $status_info) {
      if ($status_info->parent == $this->status) {
        $children[] = $status_info->status;
      }
    }

    return $children;
  }

  /**
   * Get this payment status's descendants.
   *
   * @return string[]
   *   The machine names of this status's descendants.
   */
  function descendants() {
    $children = $this->children();
    $descendants = $children;
    foreach ($children as $child) {
      $descendants = array_merge($descendants, payment_status_info($child)->descendants());
    }

    return array_unique($descendants);
  }
}

/**
 * A payment line item.
 *
 * @see Payment::setLineItem()
 */
class PaymentLineItem extends PaymentCommon {

  /**
   * The payment amount, excluding tax. The number of decimals depends on the
   * ISO 4217 currency used.
   *
   * @var float
   */
  public $amount = 0.0;

  /**
   * A US English human-readable description for this line item. May contain
   * HTML.
   *
   * @var string
   */
  public $description = '';

  /**
   * Arguments to pass on to t() when translating $this->description.
   *
   * @var string[]
   */
  public $description_arguments = array();

  /**
   * The unique machine name (for a certain payment).
   *
   * @var string
   */
  public $name = '';

  /**
   * The tax rate that applies to PaymentLineItem::amount. Should be a float
   * between 0 and 1.
   *
   * @var float
   */
  public $tax_rate = 0.0;

  /**
   * Quantity.
   *
   * @var integer
   */
  public $quantity = 1;

  /**
   * Return this line item's unit amount.
   *
   * @param boolean $tax
   *   Whether to include taxes or not.
   *
   * @return float
   */
  function unitAmount($tax) {
    return $this->amount * ($tax ? $this->tax_rate + 1 : 1);
  }

  /**
   * Return this line item's total amount.
   *
   * @param boolean $tax
   *   Whether to include taxes or not.
   *
   * @return float
   */
  function totalAmount($tax) {
    return $this->amount * $this->quantity * ($tax ? $this->tax_rate + 1 : 1);
  }
}
/**
 * A payment status line item.
 */
class PaymentStatusItem {

  /**
   * The status itself.
   *
   * @var string
   */
  public $status = '';

  /**
   * The Unix datetime this status was set.
   *
   * @var integer
   */
  public $created = 0;

  /**
   * The PID of the payment this status item belongs to.
   *
   * @var integer
   */
  public $pid = 0;

  /**
   * The unique internal ID of this payment status item.
   *
   * @var integer
   */
  public $psiid = 0;

  function __construct($status, $created = 0, $pid = 0, $psiid = 0) {
    $this->status = $status;
    $this->created = $created ? $created : time();
    $this->pid = $pid;
    $this->psiid = $psiid;
  }
}

/**
 * Information about a line item type.
 */
class PaymentLineItemInfo extends PaymentCommon {

  /**
   * The callback function to get this line item from the Payment.
   *
   * The function accepts the machine name of the line item to get and the
   * Payment object to get it from as parameters. It should return an array,
   * optionally filled with PaymentLineItem objects.
   *
   * @see Payment::getLineItems()
   * @see payment_line_item_get_all()
   *
   * @var string
   */
  public $callback = 'payment_line_item_get_specific';

  /**
   * The unique (for this payment) machine name.
   *
   * @var string
   */
  public $name = '';

  /**
   * The human-readable plain text title.
   *
   * @var string
   */
  public $title = '';
}

/**
 * A Payment-related exception.
 */
class PaymentException extends Exception {

  /**
   * {@inheritdoc}
   */
  function __construct($message = '', $code = 0, Exception $previous = NULL) {
    parent::__construct($message, $code, $previous);
    payment_debug($this->getMessage(), $this->getFile(), $this->getLine());
  }
}

/**
 * Exception thrown if a payment is not valid.
 */
class PaymentValidationException extends PaymentException {}

/**
 * Exception thrown if a payment's total amount is below the required minimum.
 */
class PaymentValidationAmountBelowMinimumException extends PaymentValidationException {}

/**
 * Exception thrown if a payment's total amount exceeds the supported maximum.
 */
class PaymentValidationAmountExceedsMaximumException extends PaymentValidationException {}

/**
 * Exception thrown if a payment has no currency set.
 */
class PaymentValidationMissingCurrencyException extends PaymentValidationException {}

/**
 * Exception thrown if a payment uses a currency that is unsupported by a
 * payment method.
 */
class PaymentValidationUnsupportedCurrencyException extends PaymentValidationException {}

/**
 * Exception thrown if a payment's finish callback is not set or the function
 * does not exist.
 */
class PaymentValidationMissingFinishCallback extends PaymentValidationException {}

/**
 * Exception thrown if a payment's description is missing.
 */
class PaymentValidationDescriptionMissing extends PaymentValidationException {}

/**
 * Exception thrown if a payment's description is too long.
 */
class PaymentValidationDescriptionTooLong extends PaymentValidationException {}

/**
 * Exception thrown if a payment method is disabled.
 */
class PaymentValidationPaymentMethodDisabledException extends PaymentValidationException {}