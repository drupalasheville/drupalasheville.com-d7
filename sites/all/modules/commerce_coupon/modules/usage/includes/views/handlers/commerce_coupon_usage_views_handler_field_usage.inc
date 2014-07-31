<?php

/*
 * Render a coupon usage summary.
 */
class commerce_coupon_usage_views_handler_field_usage extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['coupon_id'] = 'coupon_id';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }
  
  function render($values) {
    $coupon_id = $this->get_value($values, 'coupon_id');
    $variables = array(
      'coupon_id' => $coupon_id,
      'details_link_text' => t('Details')
    );

    return theme('commerce_coupon_usage_summary', $variables);    
  }
}
