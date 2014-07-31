<?php

/**
 * Implements hook_views_default_views_alter().
 */
function commerce_coupon_usage_views_default_views_alter(&$views) {
  $usage_field = _commerce_coupon_usage_views_get_view_delta();

  $view = &$views['coupons'];
  $handler = &$view->display['default']->handler;

  if (!is_array($handler->display->display_options['fields'])) {
    return;
  }

  // Overwrite the original fields array.
  $handler->display->display_options['fields'] += $usage_field;
}

/**
 * Helper function to get the Views import.
 */
function _commerce_coupon_usage_views_get_view_delta() {
  $handler = new stdClass();

  /* Field: Commerce Discount: Analytics */
  $handler->display->display_options['fields']['usage']['id'] = 'usage';
  $handler->display->display_options['fields']['usage']['table'] = 'commerce_coupon';
  $handler->display->display_options['fields']['usage']['field'] = 'usage';
  $handler->display->display_options['fields']['usage']['label'] = 'Usage';

  return $handler->display->display_options['fields'];
}

/**
 * Implements hook_views_default_views_alter().
 */
function commerce_coupon_usage_views_default_views() {
  $view = new view();
  $view->name = 'coupon_usage';
  $view->description = 'Summary of coupon usage';
  $view->tag = 'default';
  $view->base_table = 'commerce_coupon_usage_transaction';
  $view->human_name = 'Coupon usage';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Coupon usage';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer commerce_coupon entities';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Header: Commerce Coupon: Coupon usage summary area */
  $handler->display->display_options['header']['usage_summary_area']['id'] = 'usage_summary_area';
  $handler->display->display_options['header']['usage_summary_area']['table'] = 'commerce_coupon';
  $handler->display->display_options['header']['usage_summary_area']['field'] = 'usage_summary_area';
  /* Relationship: Commerce coupon usage transaction: Order_id */
  $handler->display->display_options['relationships']['order_id']['id'] = 'order_id';
  $handler->display->display_options['relationships']['order_id']['table'] = 'commerce_coupon_usage_transaction';
  $handler->display->display_options['relationships']['order_id']['field'] = 'order_id';
  $handler->display->display_options['relationships']['order_id']['required'] = TRUE;
  /* Relationship: Commerce coupon usage transaction: Coupon_id */
  $handler->display->display_options['relationships']['coupon_id']['id'] = 'coupon_id';
  $handler->display->display_options['relationships']['coupon_id']['table'] = 'commerce_coupon_usage_transaction';
  $handler->display->display_options['relationships']['coupon_id']['field'] = 'coupon_id';
  $handler->display->display_options['relationships']['coupon_id']['required'] = TRUE;
  /* Field: Commerce coupon usage transaction: Date */
  $handler->display->display_options['fields']['date']['id'] = 'date';
  $handler->display->display_options['fields']['date']['table'] = 'commerce_coupon_usage_transaction';
  $handler->display->display_options['fields']['date']['field'] = 'date';
  $handler->display->display_options['fields']['date']['date_format'] = 'medium';
  /* Field: Commerce Order: Order number */
  $handler->display->display_options['fields']['order_number']['id'] = 'order_number';
  $handler->display->display_options['fields']['order_number']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['order_number']['field'] = 'order_number';
  $handler->display->display_options['fields']['order_number']['relationship'] = 'order_id';
  $handler->display->display_options['fields']['order_number']['exclude'] = TRUE;
  $handler->display->display_options['fields']['order_number']['alter']['text'] = 'Order [order_number]';
  /* Field: Commerce Order: Link */
  $handler->display->display_options['fields']['view_order']['id'] = 'view_order';
  $handler->display->display_options['fields']['view_order']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['view_order']['field'] = 'view_order';
  $handler->display->display_options['fields']['view_order']['relationship'] = 'order_id';
  $handler->display->display_options['fields']['view_order']['label'] = 'Order number';
  $handler->display->display_options['fields']['view_order']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['view_order']['alter']['text'] = '[order_number] | [view_order]';
  $handler->display->display_options['fields']['view_order']['text'] = 'view order';
  /* Contextual filter: Commerce coupon usage transaction: Coupon_id */
  $handler->display->display_options['arguments']['coupon_id']['id'] = 'coupon_id';
  $handler->display->display_options['arguments']['coupon_id']['table'] = 'commerce_coupon_usage_transaction';
  $handler->display->display_options['arguments']['coupon_id']['field'] = 'coupon_id';
  $handler->display->display_options['arguments']['coupon_id']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['coupon_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['coupon_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['coupon_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['coupon_id']['summary_options']['items_per_page'] = '25';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/commerce/coupons/%/usage';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Usage';
  $handler->display->display_options['menu']['weight'] = '100';
  $handler->display->display_options['menu']['context'] = 1;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  $views['coupon_usage'] = $view;
  
  return $views;
}