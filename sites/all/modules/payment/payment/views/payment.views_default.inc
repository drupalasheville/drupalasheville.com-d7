<?php

/**
 * @file
 * Default views.
 */

/**
 * Implements hook_views_default_views().
 */
function payment_views_default_views() {
  $views = array();

  $view_payments = payment_view_payments();
  $views[$view_payments->name] = $view_payments;
  $view_payment_methods = payment_view_payment_methods();
  $views[$view_payment_methods->name] = $view_payment_methods;

  return $views;
}

/**
 * Return the payment overview view.
 *
 * @return view
 */
function payment_view_payments() {
  $view = new view();
  $view->name = 'payments';
  $view->description = 'List all payments made using Payment module.';
  $view->tag = 'payment';
  $view->base_table = 'payment';
  $view->human_name = 'Payments';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Payments';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'payment_own_payment_overview';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'created' => 'created',
    'title' => 'title',
    'currency_code' => 'currency_code',
    'amount_total' => 'amount_total',
    'title_specific' => 'title_specific',
    'operations' => 'operations',
  );
  $handler->display->display_options['style_options']['default'] = 'created';
  $handler->display->display_options['style_options']['info'] = array(
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'currency_code' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'amount_total' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title_specific' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['empty_table'] = TRUE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['content'] = 'There are no payments yet.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: Payment: Payment method */
  $handler->display->display_options['relationships']['pmid']['id'] = 'pmid';
  $handler->display->display_options['relationships']['pmid']['table'] = 'payment';
  $handler->display->display_options['relationships']['pmid']['field'] = 'pmid';
  /* Relationship: Payment: Line items */
  $handler->display->display_options['relationships']['pid_line_item']['id'] = 'pid_line_item';
  $handler->display->display_options['relationships']['pid_line_item']['table'] = 'payment';
  $handler->display->display_options['relationships']['pid_line_item']['field'] = 'pid_line_item';
  /* Relationship: Payment: Last status item */
  $handler->display->display_options['relationships']['psiid_last']['id'] = 'psiid_last';
  $handler->display->display_options['relationships']['psiid_last']['table'] = 'payment';
  $handler->display->display_options['relationships']['psiid_last']['field'] = 'psiid_last';
  $handler->display->display_options['relationships']['psiid_last']['required'] = TRUE;
  /* Relationship: Payment: User */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'payment';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Payment status item: Creation date and time */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'payment_status_item';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['relationship'] = 'psiid_last';
  $handler->display->display_options['fields']['created']['label'] = 'Last update';
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  /* Field: Payment status item: Status title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'payment_status_item';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'psiid_last';
  $handler->display->display_options['fields']['title']['label'] = 'Status';
  /* Field: Payment: Currency code */
  $handler->display->display_options['fields']['currency_code']['id'] = 'currency_code';
  $handler->display->display_options['fields']['currency_code']['table'] = 'payment';
  $handler->display->display_options['fields']['currency_code']['field'] = 'currency_code';
  $handler->display->display_options['fields']['currency_code']['label'] = '';
  $handler->display->display_options['fields']['currency_code']['exclude'] = TRUE;
  $handler->display->display_options['fields']['currency_code']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['currency_code']['hide_alter_empty'] = FALSE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['amount']['id'] = 'amount';
  $handler->display->display_options['fields']['amount']['table'] = 'payment';
  $handler->display->display_options['fields']['amount']['field'] = 'amount';
  $handler->display->display_options['fields']['amount']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['amount']['alter']['text'] = '[currency_code] [amount]';
  $handler->display->display_options['fields']['amount']['hide_alter_empty'] = FALSE;
  /* Field: Payment method: Title (specific) */
  $handler->display->display_options['fields']['title_specific']['id'] = 'title_specific';
  $handler->display->display_options['fields']['title_specific']['table'] = 'payment_method';
  $handler->display->display_options['fields']['title_specific']['field'] = 'title_specific';
  $handler->display->display_options['fields']['title_specific']['relationship'] = 'pmid';
  $handler->display->display_options['fields']['title_specific']['label'] = 'Payment method';
  $handler->display->display_options['fields']['title_specific']['hide_alter_empty'] = FALSE;
  /* Field: Payment method: Title (generic) */
  $handler->display->display_options['fields']['title_generic']['id'] = 'title_generic';
  $handler->display->display_options['fields']['title_generic']['table'] = 'payment_method';
  $handler->display->display_options['fields']['title_generic']['field'] = 'title_generic';
  $handler->display->display_options['fields']['title_generic']['relationship'] = 'pmid';
  /* Field: Payment: Operations */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'payment';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  /* Sort criterion: Payment status item: Creation date and time */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'payment_status_item';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['relationship'] = 'psiid_last';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';

  /* Display: Administration page */
  $handler = $view->new_display('page', 'Administration page', 'administration_page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'payment.payment.view.any';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Payment status item: Creation date and time */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'payment_status_item';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['relationship'] = 'psiid_last';
  $handler->display->display_options['fields']['created']['label'] = 'Last update';
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  /* Field: Payment status item: Status title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'payment_status_item';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'psiid_last';
  $handler->display->display_options['fields']['title']['label'] = 'Status';
  /* Field: Payment: Currency code */
  $handler->display->display_options['fields']['currency_code']['id'] = 'currency_code';
  $handler->display->display_options['fields']['currency_code']['table'] = 'payment';
  $handler->display->display_options['fields']['currency_code']['field'] = 'currency_code';
  $handler->display->display_options['fields']['currency_code']['label'] = '';
  $handler->display->display_options['fields']['currency_code']['exclude'] = TRUE;
  $handler->display->display_options['fields']['currency_code']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['currency_code']['hide_alter_empty'] = FALSE;
  /* Field: SUM(Payment line item: Total amount) */
  $handler->display->display_options['fields']['amount_total']['id'] = 'amount_total';
  $handler->display->display_options['fields']['amount_total']['table'] = 'payment_line_item';
  $handler->display->display_options['fields']['amount_total']['field'] = 'amount_total';
  $handler->display->display_options['fields']['amount_total']['relationship'] = 'pid_line_item';
  $handler->display->display_options['fields']['amount_total']['group_type'] = 'sum';
  $handler->display->display_options['fields']['amount_total']['label'] = 'Amount';
  /* Field: Payment method: Title (specific) */
  $handler->display->display_options['fields']['title_specific']['id'] = 'title_specific';
  $handler->display->display_options['fields']['title_specific']['table'] = 'payment_method';
  $handler->display->display_options['fields']['title_specific']['field'] = 'title_specific';
  $handler->display->display_options['fields']['title_specific']['relationship'] = 'pmid';
  $handler->display->display_options['fields']['title_specific']['label'] = 'Payment method';
  $handler->display->display_options['fields']['title_specific']['empty'] = 'Unavailable';
  $handler->display->display_options['fields']['title_specific']['hide_alter_empty'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'User';
  /* Field: Payment: Operations */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'payment';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Payment status item: Creation date and time */
  $handler->display->display_options['filters']['created']['id'] = 'created';
  $handler->display->display_options['filters']['created']['table'] = 'payment_status_item';
  $handler->display->display_options['filters']['created']['field'] = 'created';
  $handler->display->display_options['filters']['created']['relationship'] = 'psiid_last';
  $handler->display->display_options['filters']['created']['operator'] = 'between';
  $handler->display->display_options['filters']['created']['group'] = 1;
  $handler->display->display_options['filters']['created']['exposed'] = TRUE;
  $handler->display->display_options['filters']['created']['expose']['operator_id'] = 'created_op';
  $handler->display->display_options['filters']['created']['expose']['label'] = 'Last updated between';
  $handler->display->display_options['filters']['created']['expose']['operator'] = 'created_op';
  $handler->display->display_options['filters']['created']['expose']['identifier'] = 'updated';
  $handler->display->display_options['filters']['created']['expose']['remember'] = TRUE;
  /* Filter criterion: Payment status item: Status code */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'payment_status_item';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['relationship'] = 'psiid_last';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Current status';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['multiple'] = TRUE;
  /* Filter criterion: Payment line item: Total amount */
  $handler->display->display_options['filters']['amount_total_1']['id'] = 'amount_total_1';
  $handler->display->display_options['filters']['amount_total_1']['table'] = 'payment_line_item';
  $handler->display->display_options['filters']['amount_total_1']['field'] = 'amount_total';
  $handler->display->display_options['filters']['amount_total_1']['relationship'] = 'pid_line_item';
  $handler->display->display_options['filters']['amount_total_1']['operator'] = 'between';
  $handler->display->display_options['filters']['amount_total_1']['group'] = 1;
  $handler->display->display_options['filters']['amount_total_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['amount_total_1']['expose']['operator_id'] = 'amount_total_1_op';
  $handler->display->display_options['filters']['amount_total_1']['expose']['label'] = 'Total amount between';
  $handler->display->display_options['filters']['amount_total_1']['expose']['operator'] = 'amount_total_1_op';
  $handler->display->display_options['filters']['amount_total_1']['expose']['identifier'] = 'amount_total_1';
  $handler->display->display_options['filters']['amount_total_1']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Payment method: Payment method ID */
  $handler->display->display_options['filters']['pmid']['id'] = 'pmid';
  $handler->display->display_options['filters']['pmid']['table'] = 'payment_method';
  $handler->display->display_options['filters']['pmid']['field'] = 'pmid';
  $handler->display->display_options['filters']['pmid']['relationship'] = 'pmid';
  $handler->display->display_options['filters']['pmid']['group'] = 1;
  $handler->display->display_options['filters']['pmid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['pmid']['expose']['operator_id'] = 'pmid_op';
  $handler->display->display_options['filters']['pmid']['expose']['label'] = 'Payment method';
  $handler->display->display_options['filters']['pmid']['expose']['operator'] = 'pmid_op';
  $handler->display->display_options['filters']['pmid']['expose']['identifier'] = 'pmid';
  $handler->display->display_options['filters']['pmid']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['pmid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['pmid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid']['value'] = '';
  $handler->display->display_options['filters']['uid']['group'] = 1;
  $handler->display->display_options['filters']['uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'User';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
  $handler->display->display_options['filters']['uid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['path'] = 'admin/content/payment';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Payments';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: User's own payments */
  $handler = $view->new_display('page', 'User\'s own payments', 'user_page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'payment_own_payment_overview';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Payment status item: Creation date and time */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'payment_status_item';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['relationship'] = 'psiid_last';
  $handler->display->display_options['fields']['created']['label'] = 'Last update';
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  /* Field: Payment status item: Status title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'payment_status_item';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'psiid_last';
  $handler->display->display_options['fields']['title']['label'] = 'Status';
  /* Field: Payment: Currency code */
  $handler->display->display_options['fields']['currency_code']['id'] = 'currency_code';
  $handler->display->display_options['fields']['currency_code']['table'] = 'payment';
  $handler->display->display_options['fields']['currency_code']['field'] = 'currency_code';
  $handler->display->display_options['fields']['currency_code']['label'] = '';
  $handler->display->display_options['fields']['currency_code']['exclude'] = TRUE;
  $handler->display->display_options['fields']['currency_code']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['currency_code']['hide_alter_empty'] = FALSE;
  /* Field: SUM(Payment line item: Total amount) */
  $handler->display->display_options['fields']['amount_total']['id'] = 'amount_total';
  $handler->display->display_options['fields']['amount_total']['table'] = 'payment_line_item';
  $handler->display->display_options['fields']['amount_total']['field'] = 'amount_total';
  $handler->display->display_options['fields']['amount_total']['relationship'] = 'pid_line_item';
  $handler->display->display_options['fields']['amount_total']['group_type'] = 'sum';
  $handler->display->display_options['fields']['amount_total']['label'] = 'Amount';
  /* Field: Payment method: Title (generic) */
  $handler->display->display_options['fields']['title_generic']['id'] = 'title_generic';
  $handler->display->display_options['fields']['title_generic']['table'] = 'payment_method';
  $handler->display->display_options['fields']['title_generic']['field'] = 'title_generic';
  $handler->display->display_options['fields']['title_generic']['relationship'] = 'pmid';
  $handler->display->display_options['fields']['title_generic']['label'] = 'Payment method';
  $handler->display->display_options['fields']['title_generic']['empty'] = 'Unavailable';
  /* Field: Payment: Operations */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'payment';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Payment: User ID */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'payment';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['path'] = 'user/%/payment';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Payments';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'user-menu';
  $translatables['payments'] = array(
    t('Master'),
    t('Payments'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('There are no payments yet.'),
    t('Payment method'),
    t('Line items'),
    t('Last status item'),
    t('User'),
    t('Last update'),
    t('Status'),
    t('Broken handler payment.amount'),
    t('[currency_code] [amount]'),
    t('Title (generic)'),
    t('Operations'),
    t('Administration page'),
    t('Amount'),
    t('Unavailable'),
    t('Last updated between'),
    t('Current status'),
    t('Total amount between'),
    t('User\'s own payments'),
    t('All'),
  );

  // If Currency 1 is enabled, prefix the amount with the currency code. If
  // Currency 2 is enabled, the amount Views field handler takes care of amount
  // formatting.
  $version = payment_currency_version();
  foreach (array('administration_page', 'user_page') as $display_name) {
    if ($version == 1) {
      $view->display[$display_name]->display_options['fields']['amount_total'] += array(
        'alter' => array(),
      );
      $view->display[$display_name]->display_options['fields']['amount_total']['alter'] += array(
        'alter_text' => TRUE,
        'text' => '[currency_code] [amount_total]',
      );
      $translatables['payments'][] = t('[currency_code] [amount]');
    }
    elseif ($version == 2) {
      $view->display[$display_name]->display_options['fields']['amount_total']['currency_code_field'] = 'payment_currency_code';
    }
  }

  return $view;
}

/**
 * Return the payment method overview view.
 *
 * @return view
 */
function payment_view_payment_methods() {
  $view = new view();
  $view->name = 'payment_methods';
  $view->description = '';
  $view->tag = 'payment';
  $view->base_table = 'payment_method';
  $view->human_name = 'Payment methods';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Payment methods';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'payment.payment_method.view.any';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['row_class'] = 'payment-method-[enabled_machine_name]';
  $handler->display->display_options['style_options']['columns'] = array(
    'pmid' => 'pmid',
    'title_specific' => 'title_specific',
    'controller_title' => 'controller_title',
    'name' => 'name',
    'operations' => 'operations',
    'enabled_machine_name' => 'enabled_machine_name',
  );
  $handler->display->display_options['style_options']['default'] = 'title_specific';
  $handler->display->display_options['style_options']['info'] = array(
    'pmid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title_specific' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'controller_title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'enabled_machine_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['empty_table'] = TRUE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['content'] = 'There are no payment methods yet.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: Payment method: User */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'payment_method';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
  /* Field: Payment method: Payment method ID */
  $handler->display->display_options['fields']['pmid']['id'] = 'pmid';
  $handler->display->display_options['fields']['pmid']['table'] = 'payment_method';
  $handler->display->display_options['fields']['pmid']['field'] = 'pmid';
  $handler->display->display_options['fields']['pmid']['label'] = '';
  $handler->display->display_options['fields']['pmid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['pmid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['pmid']['hide_alter_empty'] = FALSE;
  /* Field: Payment method: Title (specific) */
  $handler->display->display_options['fields']['title_specific']['id'] = 'title_specific';
  $handler->display->display_options['fields']['title_specific']['table'] = 'payment_method';
  $handler->display->display_options['fields']['title_specific']['field'] = 'title_specific';
  $handler->display->display_options['fields']['title_specific']['label'] = 'Title';
  $handler->display->display_options['fields']['title_specific']['hide_alter_empty'] = FALSE;
  /* Field: Payment method: Payment method type title */
  $handler->display->display_options['fields']['controller_title']['id'] = 'controller_title';
  $handler->display->display_options['fields']['controller_title']['table'] = 'payment_method';
  $handler->display->display_options['fields']['controller_title']['field'] = 'controller_title';
  $handler->display->display_options['fields']['controller_title']['label'] = 'Type';
  $handler->display->display_options['fields']['controller_title']['empty'] = 'Unavailable';
  $handler->display->display_options['fields']['controller_title']['hide_alter_empty'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'Owner';
  /* Field: Payment method: Operations */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'payment_method';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['fields']['operations']['hide_alter_empty'] = FALSE;
  /* Field: Payment method: Enabled (machine name) */
  $handler->display->display_options['fields']['enabled_machine_name']['id'] = 'enabled_machine_name';
  $handler->display->display_options['fields']['enabled_machine_name']['table'] = 'payment_method';
  $handler->display->display_options['fields']['enabled_machine_name']['field'] = 'enabled_machine_name';
  $handler->display->display_options['fields']['enabled_machine_name']['exclude'] = TRUE;
  /* Sort criterion: Payment method: Title (specific) */
  $handler->display->display_options['sorts']['title_specific']['id'] = 'title_specific';
  $handler->display->display_options['sorts']['title_specific']['table'] = 'payment_method';
  $handler->display->display_options['sorts']['title_specific']['field'] = 'title_specific';

  /* Display: Administration page */
  $handler = $view->new_display('page', 'Administration page', 'administration_page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'admin/config/services/payment/method';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Payment methods';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Payment';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $translatables['payment_methods'] = array(
    t('Master'),
    t('Payment methods'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('There are no payment methods yet.'),
    t('User'),
    t('.'),
    t(','),
    t('Title'),
    t('Type'),
    t('Unavailable'),
    t('Owner'),
    t('Operations'),
    t('Enabled (machine name)'),
    t('Administration page'),
  );

  return $view;
}
