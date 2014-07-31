<?php

/**
 * Filter by status code, but show users their human-readable titles.
 */
class PaymentViewsHandlerFilterPaymentStatusItemStatus extends views_handler_filter_in_operator {

  /**
   * Implements views_handler_filter_in_operator::get_value_options().
   */
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_options = payment_status_options();
    }
  }
}
