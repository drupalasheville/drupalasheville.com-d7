<?php

/*
 * Implements hook_views_default_views().
 */
function commerce_coupon_views_default_views() {

  /*
   * Administrative coupons list
   */

  $view = new view();
  $view->name = 'coupons';
  $view->description = 'List of coupons';
  $view->tag = 'default';
  $view->base_table = 'commerce_coupon';
  $view->human_name = 'Coupons';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Coupons';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer commerce_coupon entities';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: Commerce Coupon: Commerce coupon ID */
  $handler->display->display_options['fields']['coupon_id']['id'] = 'coupon_id';
  $handler->display->display_options['fields']['coupon_id']['table'] = 'commerce_coupon';
  $handler->display->display_options['fields']['coupon_id']['field'] = 'coupon_id';
  /* Field: Commerce Coupon: Label */
  $handler->display->display_options['fields']['code']['id'] = 'code';
  $handler->display->display_options['fields']['code']['table'] = 'commerce_coupon';
  $handler->display->display_options['fields']['code']['field'] = 'code';
  $handler->display->display_options['fields']['code']['label'] = 'Code';
  /* Field: Commerce Coupon: Delete coupon */
  $handler->display->display_options['fields']['delete']['id'] = 'delete';
  $handler->display->display_options['fields']['delete']['table'] = 'commerce_coupon';
  $handler->display->display_options['fields']['delete']['field'] = 'delete';
  $handler->display->display_options['fields']['delete']['label'] = '';
  $handler->display->display_options['fields']['delete']['element_label_colon'] = FALSE;
  /* Field: Commerce Coupon: Edit coupon */
  $handler->display->display_options['fields']['edit']['id'] = 'edit';
  $handler->display->display_options['fields']['edit']['table'] = 'commerce_coupon';
  $handler->display->display_options['fields']['edit']['field'] = 'edit';
  $handler->display->display_options['fields']['edit']['label'] = '';
  $handler->display->display_options['fields']['edit']['element_label_colon'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/commerce/coupons/list';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'List';
  $handler->display->display_options['menu']['description'] = 'List of coupons';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Coupons';
  $handler->display->display_options['tab_options']['description'] = 'Manage coupons';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'management';

  $views['coupons'] = $view;

  /*
   * Order coupons list
   */

  $view = new view();
  $view->name = 'order_coupon_list';
  $view->description = 'List of coupons in an order';
  $view->tag = 'default';
  $view->base_table = 'commerce_coupon';
  $view->human_name = 'Order coupon list';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Checkout';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_commerce_coupons_commerce_order']['id'] = 'reverse_commerce_coupons_commerce_order';
  $handler->display->display_options['relationships']['reverse_commerce_coupons_commerce_order']['table'] = 'commerce_coupon';
  $handler->display->display_options['relationships']['reverse_commerce_coupons_commerce_order']['field'] = 'reverse_commerce_coupons_commerce_order';
  $handler->display->display_options['relationships']['reverse_commerce_coupons_commerce_order']['required'] = TRUE;
  /* Field: Commerce Coupon: Label */
  $handler->display->display_options['fields']['code']['id'] = 'code';
  $handler->display->display_options['fields']['code']['table'] = 'commerce_coupon';
  $handler->display->display_options['fields']['code']['field'] = 'code';
  $handler->display->display_options['fields']['code']['label'] = 'Code';
  /* Field: Commerce Coupon: Discount value display */
  $handler->display->display_options['fields']['discount_value_display']['id'] = 'discount_value_display';
  $handler->display->display_options['fields']['discount_value_display']['table'] = 'commerce_coupon';
  $handler->display->display_options['fields']['discount_value_display']['field'] = 'discount_value_display';
  $handler->display->display_options['fields']['discount_value_display']['label'] = 'Value';
  /* Field: Commerce Coupon: Remove from Order */
  $handler->display->display_options['fields']['remove_from_order']['id'] = 'remove_from_order';
  $handler->display->display_options['fields']['remove_from_order']['table'] = 'commerce_coupon';
  $handler->display->display_options['fields']['remove_from_order']['field'] = 'remove_from_order';
  $handler->display->display_options['fields']['remove_from_order']['label'] = '';
  $handler->display->display_options['fields']['remove_from_order']['element_label_colon'] = FALSE;
  /* Contextual filter: Commerce Order: Order ID */
  $handler->display->display_options['arguments']['order_id']['id'] = 'order_id';
  $handler->display->display_options['arguments']['order_id']['table'] = 'commerce_order';
  $handler->display->display_options['arguments']['order_id']['field'] = 'order_id';
  $handler->display->display_options['arguments']['order_id']['relationship'] = 'reverse_commerce_coupons_commerce_order';
  $handler->display->display_options['arguments']['order_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['order_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['order_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['order_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['order_id']['summary_options']['items_per_page'] = '25';

  /* Display: Checkout */
  $handler = $view->new_display('block', 'Checkout', 'checkout');
  $handler->display->display_options['block_description'] = 'Order coupon list: checkout';

  $views['order_coupons_list'] = $view;

  return $views;

}
