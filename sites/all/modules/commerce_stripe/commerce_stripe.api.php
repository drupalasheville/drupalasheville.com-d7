<?php
/**
 * @file
 * This code is never called, it's just information about to use the hooks.
 */

/**
 * Add information to the metadata sent to Stripe.
 */
function hook_commerce_stripe_metadata($order) {
  return array(
    'order_number' => $order->order_number,
  );
}
