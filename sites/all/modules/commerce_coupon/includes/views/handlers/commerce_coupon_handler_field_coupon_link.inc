<?php

abstract class commerce_coupon_handler_field_coupon_link extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['coupon_id'] = 'coupon_id';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $this->options['text'],
    );
  }

  function check_access($coupon_id, $op) {
    $coupon = commerce_coupon_create('discount');
    $coupon->coupon_id = $coupon_id;

    if (commerce_coupon_access($op, $coupon)) {
      return TRUE;
    }
  }
}