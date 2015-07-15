<?php

/**
 * @file
 * Drush integration for the Commerce Stripe module.
 */

/**
 * Implements hook_drush_command().
 */
function commerce_stripe_drush_command() {
  $items['stripe-download'] = array(
    'callback' => 'drush_commerce_stripe_stripe_download',
    'description' => dt('Downloads the Stripe PHP library from https://github.com/stripe/stripe-php.'),
  );
  return $items;
}

/**
 * A command callback.
 */
function drush_commerce_stripe_stripe_download() {

  if (!module_exists('libraries')) {
    drush_log(dt('Commerce Stripe requires the Libraries module (https://www.drupal.org/project/libraries) in order to install the Stripe PHP library.'), 'warning');
    return;
  }

  $args = func_get_args();
  if ($args[0]) {
    $path = $args[0];
  }
  else {
    $path = drush_get_context('DRUSH_DRUPAL_ROOT') . '/sites/all/libraries/stripe-php';
  }
  if (drush_shell_exec('git clone git://github.com/stripe/stripe-php.git ' . $path)) {
    drush_shell_exec('git --git-dir=' . $path . '/.git --work-tree=' . $path . ' checkout v1.18.0');
    drush_log(dt('Stripe PHP library has been cloned via git to @path.', array('@path' => $path)), 'success');
  }
  else {
    drush_log(dt('Drush was unable to clone Stripe PHP library to @path.', array('@path' => $path)), 'warning');
  }
}
