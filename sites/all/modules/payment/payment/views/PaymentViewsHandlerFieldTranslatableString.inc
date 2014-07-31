<?php

/**
 * @file
 * Contains PaymentViewsHandlerFieldTranslatableString.
 */

/**
 * Views field handler for a translatable string that requires arguments from
 * the DB.
 */
class PaymentViewsHandlerFieldTranslatableString extends views_handler_field {

  function construct() {
    parent::construct();
    if (!empty($this->definition['string_arguments_field'])) {
      $this->additional_fields['string_arguments_field'] = $this->definition['string_arguments_field'];
    }
  }
  
  /**
   * Overrides views_handler_field::query().
   */
  function query() {
    parent::query();
    $this->add_additional_fields();
  }

  /**
   * Overrides views_handler_field::render().
   */
  function render($values) {
    $string = $this->get_value($values);
    $arguments = !empty($this->definition['string_arguments_field']) ? unserialize($this->get_value($values, $this->definition['string_arguments_field'])) : array();

    return t($string, $arguments);
  }
}
