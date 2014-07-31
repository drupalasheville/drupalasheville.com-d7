<?php

/*
 * Checkout pane callback: coupon settings
 */
function commerce_coupon_pane_settings_form($checkout_pane) {
  $form = array();

  // Build an options array of Views available for the cart contents pane.
  $options = array();

  // Generate an option list from all user defined and module defined views.
  foreach (views_get_all_views() as $view_id => $view_value) {
    // Only include line item Views.
    if ($view_value->base_table == 'commerce_coupon') {
      foreach ($view_value->display as $display_id => $display_value) {
        $options[check_plain($view_id)][$view_id . '|' . $display_id] = check_plain($display_value->display_title);
      }
    }
  }

  $form['commerce_coupon_checkout_pane_view'] = array(
    '#type' => 'select',
    '#title' => t('Coupons Checkout Pane View'),
    '#description' => t('Specify the View to use in the checkout pane under the coupon form. Select \'none\' to not display anything.'),
    '#options' => array('none' => t('None')) + $options,
    '#default_value' => variable_get('commerce_coupon_checkout_pane_view', 'order_coupon_list|checkout'),
  );

  $form['commerce_coupon_review_pane_view'] = array(
    '#type' => 'select',
    '#title' => t('Coupons Review Pane View'),
    '#description' => t('Specify the View to use in the review pane to display the coupons.'),
    '#options' => $options,
    '#default_value' => variable_get('commerce_coupon_review_pane_view', 'order_coupon_list|checkout'),
  );

  return $form;
}

/*
 * Checkout pane callback: coupon checkout form
 */
function commerce_coupon_pane_checkout_form($form, &$form_state, $checkout_pane, $order) {
  // Allow to replace pane content with ajax calls.
  $pane_form = array(
    '#prefix' => '<div id="commerce-checkout-coupon-ajax-wrapper">',
    '#suffix' => '</div>',
  );

  // Store the payment methods in the form for validation purposes.
  $pane_form['coupon_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Coupon Code'),
    '#description' => t('Enter your coupon code here.'),
  );

  $pane_form['coupon_add'] = array(
    '#type' => 'button',
    '#value' => t('Add coupon'),
    '#name' => 'coupon_add',
    '#limit_validation_errors' => array(),
    '#ajax' => array(
      'callback' => 'commerce_coupon_add_coupon_callback',
      'wrapper' => 'commerce-checkout-coupon-ajax-wrapper',
    ),
  );
  
  $error = '';
  if (isset($form_state['triggering_element']) && $form_state['triggering_element']['#name'] == 'coupon_add') {
    $code = $form_state['input']['commerce_coupon']['coupon_code'];
    if (!empty($code)) {
      $coupon = commerce_coupon_redeem_coupon_code($code, $order, $error);
      
      if ($coupon) {
        // Clear the field value so that the coupon code does not get
        // resubmitted causing an error when user uses main "Continue to next
        // step" submit.
        $pane_form['coupon_code']['#value'] = '';
        
        // Reload the order so it is not out of date.
        $order = commerce_order_load($order->order_id);       

        // Recalculate discounts.
        commerce_cart_order_refresh($order);
      }
    }
    else {
      $error = t('Please enter a code.');
    }

    if (!$error) {
      // If a coupon was invalidated during the cart refresh (e.g. if its 
      // discounts failed their conditions), an error message will have been
      // set.
      $error = &drupal_static('commerce_coupon_error_' . strtolower($code));
    }
  
    if (!$error) {      
      // Allow modules/rules to act when a coupon has been successfully added
      // to the cart.
      rules_invoke_all('commerce_coupon_applied_to_cart', $coupon, $order);
    }
    else {
      drupal_set_message($error, 'error');
    }    
  }

  // Extract the View and display keys from the cart contents pane setting.
  $pane_view = variable_get('commerce_coupon_checkout_pane_view', 'order_coupon_list|checkout');
  if ($pane_view != 'none') {
    list($view_id, $display_id) = explode('|', $pane_view);
    if (!empty($view_id) && !empty($display_id) && views_get_view($view_id)) {
      $pane_form['redeemed_coupons'] = array(
        '#type' => 'markup',
        '#markup' => commerce_embed_view($view_id, $display_id, array($order->order_id)),
      );
    }
  }

  // Display any new status messages added by this pane within the pane's area.
  if (drupal_get_messages(NULL, FALSE)) {
    $pane_form['status_messages'] = array(
      '#type' => 'markup',
      '#markup' => theme('status_messages'),
      '#weight' => -1,
    );
  }

  return $pane_form;
}

/*
 * Ajax callback: coupon add button.
 */
function commerce_coupon_add_coupon_callback($form, &$form_state) {
  // Re-render the cart summary.
  list($view_id, $display_id) = explode('|', variable_get('commerce_cart_contents_pane_view', 'commerce_cart_summary|default'));
  $cart_summary = commerce_embed_view($view_id, $display_id, array($form_state['order']->order_id));
  $commands[] = ajax_command_replace('.view-commerce-cart-summary', $cart_summary);

  // Re-render coupon pane
  $coupon_pane = $form['commerce_coupon'];
  $commands[] = ajax_command_replace('#commerce-checkout-coupon-ajax-wrapper', drupal_render($coupon_pane));
  
  // Allow other modules to alter the commands
  drupal_alter('commerce_coupon_add_coupon_ajax', $commands, $form, $form_state);

  return array('#type' => 'ajax', '#commands' => $commands);
}

/*
 * Checkout pane callback: coupon checkout review
 */
function commerce_coupon_pane_review($form, $form_state, $checkout_pane, $order) {
  if (!empty($order->commerce_coupons)) {
    // Extract the View and display keys from the cart contents pane setting.
    list($view_id, $display_id) = explode('|', variable_get('commerce_coupon_review_pane_view', 'order_coupon_list|checkout'));

    return commerce_embed_view($view_id, $display_id, array($order->order_id));
  }
}
