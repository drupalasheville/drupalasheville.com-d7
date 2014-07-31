<?php

/**
 * @file
 * A views field handler. See payment_views_data().
 */

/**
 * Views field handler for a payment status item's human-readable title.
 */
class PaymentViewsHandlerFieldPaymentStatusTitle extends views_handler_field {

  /**
   * Implements views_handler_field::render().
   */
  function render($values) {
    $status = payment_status_info($this->get_value($values), TRUE);

    return $status->title;
  }
}
