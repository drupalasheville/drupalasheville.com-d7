<?php

/**
 * @file
 * A views field handler. See payment_views_data().
 */

/**
 * Views field handler for a payment method's controller title.
 */
class PaymentViewsHandlerFieldPaymentMethodControllerTitle extends views_handler_field {

  /**
   * Implements views_handler_field::render().
   */
  function render($values) {
    if ($controller = payment_method_controller_load($this->get_value($values), TRUE)) {
      return $controller->title;
    }
  }
}
