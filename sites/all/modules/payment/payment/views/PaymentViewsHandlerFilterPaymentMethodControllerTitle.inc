<?php

/**
 * Contains class PaymentViewsHandlerFilterPaymentMethodControllerTitle.
 */

/**
 * Filter by specific payment method controller, but show users their titles.
 */
class PaymentViewsHandlerFilterPaymentMethodControllerTitle extends views_handler_filter_in_operator {

  /**
   * Implements views_handler_filter_in_operator::get_value_options().
   */
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_options = payment_method_controller_options();
    }
  }
}
