<?php

class commerce_coupon_handler_field_coupon_edit extends commerce_coupon_handler_field_coupon_link {
  function render($values) {
    $coupon_id = $this->get_value($values, 'coupon_id');
    if (!$this->check_access($coupon_id, 'update')) {
      return;
    }

    $text = !empty($this->options['text']) ? $this->options['text'] : t('Edit');

    return l($text, 'admin/commerce/coupons/' . $coupon_id . '/edit', array('query' => drupal_get_destination()));
  }
}