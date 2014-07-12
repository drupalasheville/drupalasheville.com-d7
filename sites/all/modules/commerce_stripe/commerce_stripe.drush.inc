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
    'description' => dt('Downloads the Stripe PHP library from https://github.com/stripe/stripe-php.'),
  );
  return $items;
}

/**
 * A command callback.
 */
function drush_commerce_stripe_download() {
  $path = drush_get_context('DRUSH_DRUPAL_ROOT');
  if (module_exists('libraries')) {
    $path .= '/' . libraries_get_path('stripe-php');
  }

  if (is_dir($path)) {
    drush_log('Stripe PHP library already present. No download required.', 'ok');
  }
  elseif (drush_shell_exec('git clone git://github.com/stripe/stripe-php.git ' . $path)) {
    drush_log(dt('Stripe PHP library has been cloned via git to @path.', array('@path' => $path)), 'success');
  }
  else {
    drush_log(dt('Drush was unable to clone Stripe PHP library to @path.', array('@path' => $path)), 'warning');
  }
}

/**
 * Implements drush_MODULE_post_COMMAND().
 */
function drush_commerce_stripe_post_pm_enable() {
  $extensions = func_get_args();
  // Deal with comma delimited extension list.
  if (strpos($extensions[0], ',') !== FALSE) {
    $extensions = explode(',', $extensions[0]);
  }

  if (in_array('commerce_stripe', $extensions) && !drush_get_option('skip')) {
    drush_commerce_stripe_download();
  }
}
