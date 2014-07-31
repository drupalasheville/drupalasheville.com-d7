#!/usr/bin/env php
<?php

/**
 * @file
 * Generates content for Payment 7.x-1.x.
 *
 * Run this script at the root of an existing Drupal 7 installation.
 * Steps to use this generation script:
 * - Install drupal 7.
 * - Run this script from your Drupal ROOT directory.
 * - Use ./scripts/dump-database-d7.sh to generate the database dump.
 */

// Define settings.
$cmd = 'index.php';
define('DRUPAL_ROOT', getcwd());
$_SERVER['HTTP_HOST']       = 'default';
$_SERVER['PHP_SELF']        = '/index.php';
$_SERVER['REMOTE_ADDR']     = '127.0.0.1';
$_SERVER['SERVER_SOFTWARE'] = NULL;
$_SERVER['REQUEST_METHOD']  = 'GET';
$_SERVER['QUERY_STRING']    = '';
$_SERVER['PHP_SELF']        = $_SERVER['REQUEST_URI'] = '/';
$_SERVER['HTTP_USER_AGENT'] = 'console';
$modules_to_enable          = array('payment', 'paymentform', 'paymentmethodbasic', 'paymentreference');

// Bootstrap Drupal.
include_once './includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

// Enable requested modules.
require_once DRUPAL_ROOT . '/' . variable_get('password_inc', 'includes/password.inc');
include_once './modules/system/system.admin.inc';
$form = system_modules();
foreach ($modules_to_enable as $module) {
  $form_state['values']['status'][$module] = TRUE;
}
$form_state['values']['disabled_modules'] = $form['disabled_modules'];
system_modules_submit(NULL, $form_state);
unset($form_state);

// Run cron after installing.
drupal_cron_run();

// Create two payment methods.
$payment_method_unavailable = PaymentGenerate::paymentMethod();
$payment_method_unavailable->enabled = FALSE;
entity_save('payment_method', $payment_method_unavailable);
$payment_method_basic = PaymentGenerate::paymentMethod('PaymentMethodBasicController');
entity_save('payment_method', $payment_method_basic);

// Create two payments
$payment_unavailable = PaymentGenerate::payment($payment_method_unavailable);
entity_save('payment', $payment_unavailable);
$payment_basic = PaymentGenerate::payment($payment_method_basic);
entity_save('payment', $payment_basic);