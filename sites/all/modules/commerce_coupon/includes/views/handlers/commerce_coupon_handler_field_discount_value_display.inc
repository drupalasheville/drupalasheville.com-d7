<?php

class commerce_coupon_handler_field_discount_value_display extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['coupon_id'] = 'coupon_id';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }
  
  function render($values) {        
    // Determine if there is an order id argument. If multiple are present, use 
    // the first found.
    $order = _commerce_coupon_load_argument_order($this);
    $coupon = commerce_coupon_load($this->get_value($values, 'coupon_id'));
    
    if ($order && $coupon) {
      $discounts = commerce_coupon_order_coupon_code_discounts($coupon->code, $order);
      $output = '';
      // Make sure that if the coupon grants free shipping, those discounts gets
      // added too.
      $free_shipping_discount = _commerce_coupon_free_shipping_single_discount($coupon, FALSE);
      if ($free_shipping_discount) {
        $discounts[] = $free_shipping_discount;
      }
      
      if ($discounts) {
        $items = array();       

        // Coupon codes may be linked to multiple discounts, so we have a hook that
        // lets discount type/offer modules define what value gets shown for each
        // coupon that has a discount  
        foreach ($discounts as $discount) {
          $display = '';
          drupal_alter('commerce_coupon_discount_value_display', $display, $discount, $order);
          if ($display) {
            $items[] = $display;
          }
        }
        $variables = array(
          'items' => $items,
          'type' => 'ul',
          'title' => '',
          'attributes' => array()
        );

        $output = theme_item_list($variables);
      }
      
      // Allow modules to alter the entire row.
      drupal_alter('commerce_coupon_value_display', $output, $coupon, $order);
      return $output;
    }
  }
}
