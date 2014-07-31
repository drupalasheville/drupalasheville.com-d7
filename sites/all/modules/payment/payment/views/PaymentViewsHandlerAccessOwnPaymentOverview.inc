<?php

/**
 * Checks access for the payment view's "User's own payments" display.
 */
class PaymentViewsHandlerAccessOwnPaymentOverview extends views_plugin_access {

  /**
   * {@inheritdoc}
   */
  function summary_title() {
    return t('Restricted to people with the <em>View any payment</em> permission, or to people with the <em>View own payments</em> permission who access their own payments.');
  }

  /**
   * {@inheritdoc}
   */
  function access($account) {
    return _payment_own_overview_views_handler_access($account);
  }

  /**
   * {@inheritdoc}
   */
  function get_access_callback() {
    return array('_payment_own_overview_views_handler_access', array());
  }
}

