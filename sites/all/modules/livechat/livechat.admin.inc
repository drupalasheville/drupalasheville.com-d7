<?php
// $Id$

/**
 * @file
 * LiveChat module admin panel
 */

function livechat_admin_settings_form($form_state) {
  global $base_url;

  $livechat = Livechat::get_instance();
  $livechat->include_admin_css();
  $livechat->include_admin_js();


  /**
   * Tracking code notification
   */
  if ($livechat->tracking_code_installed()) {
    $form['tracking_code'] = array
    (
      '#type' => 'item',
      '#markup' => t('<div class="messages installed_ok">LiveChat is now installed on your website.</div>')
    );
  }

  if ($livechat->is_installed()) {
    $form['download_app'] = array
    (
      '#type' => 'item',
      '#markup' => t(
	    '<p>Download LiveChat for your desktop/mobile and start chatting with your customers!</p>'.
	    '<p class="btn"><a href="http://www.livechatinc.com/product/" target="_blank">Download application</a></p>'
	  )
    );
  }

  if ($livechat->is_installed() == false) {

	  /**
	   * New account / Already have a license forms
	   */
	  $form['choose_form'] = array
	  (
		'#type' => 'item',
		'#markup' =>
		  '<fieldset>'.
		  '<div id="lc_logo"></div>'.
		  '<h3>Already have a LiveChat account?</h3>'.
		  '<ul id="choose_form">'.
		  '<li><input type="radio" name="choose_form" id="choose_form_1" checked="checked"> <label for="choose_form_1">Yes, I already have a LiveChat account</label></li>'.
		  '<li><input type="radio" name="choose_form" id="choose_form_0"> <label for="choose_form_0">No, I want to create one</label></li>'.
		  '</ul>'.
		  '</fieldset>'
	  );

	  // General Settings
	  $form['general'] = array
	  (
		'#type' => 'fieldset',
		'#collapsible' => FALSE,
		'#prefix' => '<div id="livechat_already_have"><h3>Account details</h3>',
		'#suffix' => '</div>'
	  );

	  $form['general']['livechat_login'] = array(
		'#type' => 'textfield',
		'#title' => t('LiveChat login'),
		'#default_value' => '',
		'#size' => 30,
		'#maxlength' => 100,
		'#required' => FALSE // handled by JavaScript validator
	  );
	  $form['general']['license_number'] = array
	  (
		'#type' => 'hidden',
		'#value' => '0'
	  );
	  $form['general']['ajax_message'] = array
	  (
		'#type' => 'item',
		'#markup' => '<p class="ajax_message"></p>'
	  );

	  // New account form
	  $form['new_account'] = array
	  (
		'#type' => 'fieldset',
		'#collapsible' => FALSE,
		'#prefix' => '<div id="livechat_new_account"><h3>Create a new LiveChat account</h3>',
		'#suffix' => '</div>'
	  );
	  $form['new_account']['name'] = array
	  (
		'#type' => 'textfield',
		'#title' => t('Full name'),
		'#size' => 30,
		'#maxlength' => 60,
		'#required' => FALSE // handled by JavaScript validator
	  );
	  $form['new_account']['email'] = array
	  (
		'#type' => 'textfield',
		'#title' => t('E-mail'),
		'#size' => 30,
		'#maxlength' => 70,
		'#required' => FALSE // handled by JavaScript validator
	  );
	  $form['new_account']['password'] = array
	  (
		'#type' => 'password',
		'#title' => t('Password'),
		'#size' => 30,
		'#maxlength' => 70,
		'#required' => FALSE // handled by JavaScript validator
	  );
	  $form['new_account']['password_retype'] = array
	  (
		'#type' => 'password',
		'#title' => t('Retype password'),
		'#size' => 30,
		'#maxlength' => 70,
		'#required' => FALSE // handled by JavaScript validator
	  );
	  $form['new_account']['ajax_message'] = array
	  (
		'#type' => 'item',
		'#markup' => '<p class="ajax_message"></p>'
	  );
  }

  return system_settings_form($form);
}

function livechat_admin_settings_form_validate($form, &$data) {
  $livechat = Livechat::get_instance();

  // Check if "Reset" button has been clicked
  if (isset($data['input']) && isset($data['input']['op']) && $data['input']['op'] === 'Reset settings')
  {
    $livechat->reset_settings();
  }
  else
  {
	  /**
	   * Form validation
	   */
	  if ($livechat->validate_license($data['input']['license_number']) == FALSE) {
		form_set_error('livechat_license_number', t('LiveChat license number is incorrect.'));
	  }

	  variable_set('livechat_license', $data['input']['license_number']);
  }
}