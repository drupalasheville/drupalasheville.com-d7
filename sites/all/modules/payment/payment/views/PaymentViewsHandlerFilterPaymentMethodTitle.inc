<?php

/**
 * Filter by specific payment method, but show users their specific titles.
 */
class PaymentViewsHandlerFilterPaymentMethodTitle extends views_handler_filter_in_operator {

  /**
   * Implements views_handler_filter_in_operator::get_value_options().
   */
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_options = payment_method_options();
    }
  }
}
