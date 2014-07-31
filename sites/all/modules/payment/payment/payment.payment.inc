<?php

/**
 * @file
 * Payment hooks.
 */

/**
 * Implements hook_payment_status_info().
 */
function payment_payment_status_info() {
  return array(
    new PaymentStatusInfo(array(
      'status' => PAYMENT_STATUS_MONEY_TRANSFERRED,
      'title' => t('Money has been transferred'),
    )),
    new PaymentStatusInfo(array(
      'status' => PAYMENT_STATUS_MONEY_NOT_TRANSFERRED,
      'title' => t('No money has been transferred'),
    )),
    new PaymentStatusInfo(array(
      'description' => t('The payment status could not be automatically verified.'),
      'status' => PAYMENT_STATUS_UNKNOWN,
      'title' => t('Unknown'),
    )),
    new PaymentStatusInfo(array(
      'status' => PAYMENT_STATUS_PENDING,
      'title' => t('Pending'),
      'parent' => PAYMENT_STATUS_MONEY_NOT_TRANSFERRED,
    )),
    new PaymentStatusInfo(array(
      'status' => PAYMENT_STATUS_SUCCESS,
      'title' => t('Completed'),
      'parent' => PAYMENT_STATUS_MONEY_TRANSFERRED,
    )),
    new PaymentStatusInfo(array(
      'status' => PAYMENT_STATUS_FAILED,
      'title' => t('Failed'),
      'parent' => PAYMENT_STATUS_MONEY_NOT_TRANSFERRED,
    )),
    new PaymentStatusInfo(array(
      'status' => PAYMENT_STATUS_CANCELLED,
      'title' => t('Cancelled'),
      'parent' => PAYMENT_STATUS_FAILED,
    )),
    new PaymentStatusInfo(array(
      'status' => PAYMENT_STATUS_EXPIRED,
      'title' => t('Expired'),
      'parent' => PAYMENT_STATUS_FAILED,
    )),
    new PaymentStatusInfo(array(
      'status' => PAYMENT_STATUS_AUTHORIZATION_FAILED,
      'title' => t('Authorization failed'),
      'parent' => PAYMENT_STATUS_FAILED,
    )),
    new PaymentStatusInfo(array(
      'status' => PAYMENT_STATUS_NEW,
      'title' => t('Created'),
      'parent' => PAYMENT_STATUS_MONEY_NOT_TRANSFERRED,
    )),
  );
}

/**
 * Implements hook_payment_method_controller_info().
 */
function payment_payment_method_controller_info() {
  return array('PaymentMethodControllerUnavailable');
}

/**
 * Implements hook_payment_line_item_info().
 */
function payment_payment_line_item_info() {
  return array(
    new PaymentLineItemInfo(array(
      'callback' => 'payment_line_item_get_all',
      'name' => 'payment_all',
      'title' => t('All items'),
    )),
  );
}