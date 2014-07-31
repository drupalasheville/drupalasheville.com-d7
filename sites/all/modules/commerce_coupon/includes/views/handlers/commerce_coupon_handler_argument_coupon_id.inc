<?php

class commerce_coupon_handler_argument_coupon_id extends views_handler_argument_numeric {
  /*
   * Override the behavior of title(). Get the coupon code.
   */
  function title_query() {
    $titles = array();

    $result = db_query("SELECT c.code FROM {commerce_coupon} c WHERE c.coupon_id IN (:coupon_ids)", array(':coupon_ids' => $this->value));

    foreach ($result as $coupon) {
      $titles[] = check_plain($coupon->code);
    }

    return $titles;
  }
}
