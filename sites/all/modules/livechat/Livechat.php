<?php
// $Id$

/**
 * @file
 * LiveChat module for Drupal
 */
class Livechat
{
  /**
   * Singleton pattern
   */
  protected static $instance = NULL;

  /**
   * Module directory
   */
  protected $module_dir = NULL;

  /**
   * Singleton pattern
   */
  public static function get_instance()
  {
    if (is_null(self::$instance))
    {
      self::$instance = new Livechat();
    }

    return self::$instance;
  }

  /**
   * Constructor
   */
  protected function __construct()
  {
    $this->module_dir = drupal_get_path('module', 'livechat');
  }

  /**
   * Resets module settings
   */
  public function reset_settings()
  {
    variable_del('livechat_license');
  }

  /**
   * License number validation
   */
  public function validate_license($license)
  {
    $license = (int)$license;
	if ($license === 0) return false;

    return preg_match('/^[0-9]{1,20}$/', $license);
  }
  
  /**
   * Checks if Livechat settings are properly set up
   */
  public function is_installed()
  {
    $livechat_license = variable_get('livechat_license');

	if (is_null($livechat_license)) return FALSE;

    if ($this->validate_license($livechat_license) == FALSE) return FALSE;


    return TRUE;
  }

  /**
   * Checks if LiveChat tracking code is installed properly
   */
  public function tracking_code_installed()
  {
    if ($this->is_installed() == FALSE) return FALSE;

    return TRUE;
  }

  public function install_codes()
  {
	$this->add_tracking_code();
  }
  /**
   * Install tracking code
   */
  public function add_tracking_code()
  {
    if ($this->is_installed() == FALSE) return FALSE;

    $path = $this->module_dir . '/codes/tracking_code.txt';
    if (!file_exists($path)) return;

    $tracking_code = file_get_contents($path);

    $tracking_code = str_replace(
      array('{%LICENSE%}'),
      array(variable_get('livechat_license')),
    $tracking_code);

    // Install tracking code in footer
    drupal_add_js($tracking_code, 'inline');
  }

  /**
   * Includes admin CSS file
   */
  public function include_admin_css()
  {
    drupal_add_css($this->module_dir . '/css/livechat.css');
  }

  /**
   * Includes admin JS file
   */
  public function include_admin_js()
  {
    drupal_add_js($this->module_dir . '/js/livechat.js');
  }
}