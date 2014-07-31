<?php

class commerce_coupon_handler_field_coupon_order_remove extends commerce_coupon_handler_field_coupon_link {

  public function render($values) {
    $coupon_id = $this->get_value($values, 'coupon_id');
    $order = _commerce_coupon_load_argument_order($this);


    // If there's an ajax form in the page, get the right destination url.
    if (isset($_SERVER['HTTP_X_REQUESTED_WITH']) && $_SERVER['HTTP_X_REQUESTED_WITH'] == 'XMLHttpRequest')  {
      $dest = str_replace($GLOBALS['base_url'] . '/', '', $_SERVER['HTTP_REFERER']);
    }
    else {
      $dest = current_path();
    }
    
    $text = !empty($this->options['text']) ? $this->options['text'] : t('Remove');

    return l(
      $text,
      'commerce/coupons/order/remove/' . $coupon_id . '/' . $order->order_id,
      array('query' => array('destination' => $dest, 'token' => drupal_get_token('commerce_coupon_remove_checkout:' . $coupon_id . ':' . $order->order_id)))
    );
  }
}
