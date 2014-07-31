<?php

/**
 * @file
 * A views field handler. See payment_views_data().
 */

/**
 * Views field handler for a payment method's controller description.
 */
class PaymentViewsHandlerFieldPaymentMethodControllerDescription extends views_handler_field {

  /**
   * Implements views_handler_field::render().
   */
  function render($values) {
    return payment_method_controller_load($this->get_value($values))->description;
  }
}
