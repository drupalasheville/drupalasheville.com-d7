<?php

/*
 * Render a usage summary for a view with a coupon id as its argument.
 */
class commerce_coupon_usage_views_handler_area_usage_summary extends views_handler_area {
  function render($empty = FALSE) {
    if (!$empty || !empty($this->options['empty'])) {
      // First look for an order_id argument.
      foreach ($this->view->argument as $name => $argument) {
        if ($argument instanceof commerce_coupon_handler_argument_coupon_id) {
          // If it is single value:
          if (count($argument->value) == 1) {
            $coupon_id = reset($argument->value);
            if (is_numeric($coupon_id) && $coupon_id) {
              $variables = array(
                'coupon_id' => $coupon_id,
                'details_link_text' => FALSE
              );

              return theme('commerce_coupon_usage_summary', $variables);
            }
          } 
        }
      }
    }
  }
}
