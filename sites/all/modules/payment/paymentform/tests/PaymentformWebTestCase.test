<?php

/**
 * @file
 * Contains class PaymentformWebTestCase.
 */

/**
 * Contains functionality shared by Paymentform test cases.
 */
class PaymentformWebTestCase extends PaymentWebTestCase {
  /**
   * Overrides parent::setUp().
   */

  /**
   * Overrides parent::setUp().
   */
  function setUp(array $modules = array()) {
    parent::setUp($modules + array('field', 'node', 'paymentform'));

    $this->content_type = $this->drupalCreateContentType();
    // Field configuration.
    $this->field_paymentform = field_create_field(array(
      'field_name' => 'field_paymentform',
      'type' => 'paymentform',
      'cardinality' => 2,
    ));
    $this->field_paymentform_instance = field_create_instance(array(
      'field_name' => 'field_paymentform',
      'entity_type' => 'node',
      'bundle' => $this->content_type->type,
      'widget' => array(
        'type' => 'paymentform_line_item',
      ),
    ));
    $this->PaymentLineItemData = array(
      'amount' => 1.0,
      'description' => 'foo',
      'name' => 'bar',
      'quantity' => 1,
      'tax_rate' => 0.0,
    );
  }

  /**
   * Checks if a FieldValidationException contains a specified error code.
   *
   * @param FieldValidationException $e
   * @param string $code
   *
   * @return boolean
   */
  function fieldValidationExceptionError(FieldValidationException $e, $code) {
    $codes = array();
    foreach ($e->errors['field_paymentform'][LANGUAGE_NONE][0] as $error) {
      if ($error['error'] == $code) {
        return TRUE;
      }
    }
    return FALSE;
  }
}
