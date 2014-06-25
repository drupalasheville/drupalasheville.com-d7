<?php
/**
 * @file
 * cod_session_evaluations.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function cod_session_evaluations_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'cod_session_evaluations_report';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'cod_sessions_evaluations_report';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Evaluation Report';
  $handler->display->display_options['link_display'] = 'page';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'edit field_accepted';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_eval_session' => 'field_eval_session',
    'field_accepted' => 'field_accepted',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_eval_session' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_accepted' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = 0;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_eval_session_target_id']['id'] = 'field_eval_session_target_id';
  $handler->display->display_options['relationships']['field_eval_session_target_id']['table'] = 'field_data_field_eval_session';
  $handler->display->display_options['relationships']['field_eval_session_target_id']['field'] = 'field_eval_session_target_id';
  $handler->display->display_options['relationships']['field_eval_session_target_id']['required'] = 1;
  /* Field: Content: Session being evaluated */
  $handler->display->display_options['fields']['field_eval_session_1']['id'] = 'field_eval_session_1';
  $handler->display->display_options['fields']['field_eval_session_1']['table'] = 'field_data_field_eval_session';
  $handler->display->display_options['fields']['field_eval_session_1']['field'] = 'field_eval_session';
  $handler->display->display_options['fields']['field_eval_session_1']['label'] = '';
  $handler->display->display_options['fields']['field_eval_session_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_eval_session_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_eval_session_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_eval_session_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_eval_session_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_eval_session_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_eval_session_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_eval_session_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_eval_session_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_eval_session_1']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_eval_session_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_eval_session_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_eval_session_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_eval_session_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_eval_session_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_eval_session_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_eval_session_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_eval_session_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_eval_session_1']['type'] = 'entityreference_entity_id';
  $handler->display->display_options['fields']['field_eval_session_1']['field_api_classes'] = 0;
  /* Field: Evaluation link */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Evaluation link';
  $handler->display->display_options['fields']['nothing']['label'] = 'Evaluation Link';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Evaluations';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'sessions-eval/[field_eval_session_1]';
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['alt'] = 'Evaluation';
  $handler->display->display_options['fields']['nothing']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['nothing']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nothing']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nothing']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nothing']['hide_alter_empty'] = 0;
  /* Field: Content: Session being evaluated */
  $handler->display->display_options['fields']['field_eval_session']['id'] = 'field_eval_session';
  $handler->display->display_options['fields']['field_eval_session']['table'] = 'field_data_field_eval_session';
  $handler->display->display_options['fields']['field_eval_session']['field'] = 'field_eval_session';
  $handler->display->display_options['fields']['field_eval_session']['label'] = 'Session';
  $handler->display->display_options['fields']['field_eval_session']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_eval_session']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_eval_session']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_eval_session']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_eval_session']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_eval_session']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_eval_session']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_eval_session']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_eval_session']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_eval_session']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_eval_session']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_eval_session']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_eval_session']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_eval_session']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_eval_session']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_eval_session']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_eval_session']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_eval_session']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_eval_session']['type'] = 'entityreference_entity_view';
  $handler->display->display_options['fields']['field_eval_session']['settings'] = array(
    'view_mode' => 'listing',
  );
  $handler->display->display_options['fields']['field_eval_session']['field_api_classes'] = 0;
  /* Field: Content: Status */
  $handler->display->display_options['fields']['field_accepted']['id'] = 'field_accepted';
  $handler->display->display_options['fields']['field_accepted']['table'] = 'field_data_field_accepted';
  $handler->display->display_options['fields']['field_accepted']['field'] = 'field_accepted';
  $handler->display->display_options['fields']['field_accepted']['relationship'] = 'field_eval_session_target_id';
  $handler->display->display_options['fields']['field_accepted']['label'] = 'Session Status';
  $handler->display->display_options['fields']['field_accepted']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_accepted']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_accepted']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_accepted']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_accepted']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_accepted']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_accepted']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_accepted']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_accepted']['field_api_classes'] = 0;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'session_evaluation' => 'session_evaluation',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['relationship'] = 'field_eval_session_target_id';
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Session being evaluated';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['required'] = 0;
  $handler->display->display_options['filters']['title']['expose']['multiple'] = FALSE;

  /* Display: Admin Eval Report */
  $handler = $view->new_display('page', 'Admin Eval Report', 'page');
  $handler->display->display_options['path'] = 'conference-admin/sessions/evaluations';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Evaluations';
  $handler->display->display_options['menu']['weight'] = '30';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['style_options']['quote'] = 1;
  $handler->display->display_options['style_options']['trim'] = 0;
  $handler->display->display_options['style_options']['replace_newlines'] = 0;
  $handler->display->display_options['style_options']['header'] = 1;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Session being evaluated */
  $handler->display->display_options['fields']['field_eval_session_1']['id'] = 'field_eval_session_1';
  $handler->display->display_options['fields']['field_eval_session_1']['table'] = 'field_data_field_eval_session';
  $handler->display->display_options['fields']['field_eval_session_1']['field'] = 'field_eval_session';
  $handler->display->display_options['fields']['field_eval_session_1']['label'] = '';
  $handler->display->display_options['fields']['field_eval_session_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_eval_session_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_eval_session_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_eval_session_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_eval_session_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_eval_session_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_eval_session_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_eval_session_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_eval_session_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_eval_session_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_eval_session_1']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_eval_session_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_eval_session_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_eval_session_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_eval_session_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_eval_session_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_eval_session_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_eval_session_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_eval_session_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_eval_session_1']['type'] = 'node_reference_nid';
  $handler->display->display_options['fields']['field_eval_session_1']['field_api_classes'] = 0;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'Evaluator';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['name']['link_to_user'] = 1;
  $handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
  $handler->display->display_options['fields']['name']['format_username'] = 1;
  /* Field: Evaluation link */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Evaluation link';
  $handler->display->display_options['fields']['nothing']['label'] = 'Evaluation Link';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'sessions-eval/[field_eval_session_1]';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'sessions-eval/[field_eval_session_1]';
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['alt'] = 'Evaluation';
  $handler->display->display_options['fields']['nothing']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['nothing']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nothing']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nothing']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nothing']['hide_alter_empty'] = 0;
  /* Field: Content: Session being evaluated */
  $handler->display->display_options['fields']['field_eval_session']['id'] = 'field_eval_session';
  $handler->display->display_options['fields']['field_eval_session']['table'] = 'field_data_field_eval_session';
  $handler->display->display_options['fields']['field_eval_session']['field'] = 'field_eval_session';
  $handler->display->display_options['fields']['field_eval_session']['label'] = 'Session';
  $handler->display->display_options['fields']['field_eval_session']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_eval_session']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_eval_session']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_eval_session']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_eval_session']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_eval_session']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_eval_session']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_eval_session']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_eval_session']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_eval_session']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_eval_session']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_eval_session']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_eval_session']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_eval_session']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_eval_session']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_eval_session']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_eval_session']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_eval_session']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_eval_session']['field_api_classes'] = 0;
  /* Field: Content: Status */
  $handler->display->display_options['fields']['field_accepted']['id'] = 'field_accepted';
  $handler->display->display_options['fields']['field_accepted']['table'] = 'field_data_field_accepted';
  $handler->display->display_options['fields']['field_accepted']['field'] = 'field_accepted';
  $handler->display->display_options['fields']['field_accepted']['relationship'] = 'field_eval_session_nid';
  $handler->display->display_options['fields']['field_accepted']['label'] = 'Session Status';
  $handler->display->display_options['fields']['field_accepted']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_accepted']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_accepted']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_accepted']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_accepted']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_accepted']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_accepted']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_accepted']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_accepted']['field_api_classes'] = 0;
  $handler->display->display_options['path'] = 'conference-admin/sessions/evaluations/feed';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: User Eval Report */
  $handler = $view->new_display('page', 'User Eval Report', 'page_1');
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    2 => '2',
  );
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Session being evaluated (field_eval_session) */
  $handler->display->display_options['arguments']['field_eval_session_target_id']['id'] = 'field_eval_session_target_id';
  $handler->display->display_options['arguments']['field_eval_session_target_id']['table'] = 'field_data_field_eval_session';
  $handler->display->display_options['arguments']['field_eval_session_target_id']['field'] = 'field_eval_session_target_id';
  $handler->display->display_options['arguments']['field_eval_session_target_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_eval_session_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_eval_session_target_id']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_eval_session_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_eval_session_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_eval_session_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_eval_session_target_id']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_eval_session_target_id']['not'] = 0;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'session_evaluation' => 'session_evaluation',
  );
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['path'] = 'sessions-eval/%';
  $export['cod_session_evaluations_report'] = $view;

  $view = new view;
  $view->name = 'cod_session_evaluations_speaker_review';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'sessions_speaker_review';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Sessions';
  $handler->display->display_options['css_class'] = 'view-grouped-list sessions-list';
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    2 => '2',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = 0;
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = 1;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_accepted' => 'field_accepted',
    'field_speakers' => 'field_speakers',
    'field_experience' => 'field_experience',
    'field_track' => 'field_track',
    'edit_node' => 'edit_node',
  );
  $handler->display->display_options['style_options']['default'] = 'title';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'field_accepted' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'field_speakers' => array(
      'align' => '',
      'separator' => '',
    ),
    'field_experience' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'field_track' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'No sessions';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'There are no sessions with this status.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nid']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['nid']['link_to_node'] = 0;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Evaluations';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'sessions-eval/[nid]';
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['alt'] = 'Evaluations';
  $handler->display->display_options['fields']['nothing']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nothing']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nothing']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nothing']['hide_alter_empty'] = 0;
  /* Field: Content: Status */
  $handler->display->display_options['fields']['field_accepted']['id'] = 'field_accepted';
  $handler->display->display_options['fields']['field_accepted']['table'] = 'field_data_field_accepted';
  $handler->display->display_options['fields']['field_accepted']['field'] = 'field_accepted';
  $handler->display->display_options['fields']['field_accepted']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_accepted']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_accepted']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_accepted']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_accepted']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_accepted']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_accepted']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_accepted']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_accepted']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_accepted']['field_api_classes'] = 0;
  /* Contextual filter: User: Uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'users';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['relationship'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['uid']['title_enable'] = 1;
  $handler->display->display_options['arguments']['uid']['title'] = '%1 Sessions';
  $handler->display->display_options['arguments']['uid']['breadcrumb_enable'] = 1;
  $handler->display->display_options['arguments']['uid']['breadcrumb'] = 'Sessions';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['uid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['uid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['uid']['not'] = 0;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'session' => 'session',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Status (field_accepted) */
  $handler->display->display_options['filters']['field_accepted_value']['id'] = 'field_accepted_value';
  $handler->display->display_options['filters']['field_accepted_value']['table'] = 'field_data_field_accepted';
  $handler->display->display_options['filters']['field_accepted_value']['field'] = 'field_accepted_value';
  $handler->display->display_options['filters']['field_accepted_value']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['field_accepted_value']['group'] = 1;
  /* Filter criterion: Content: Track (field_track) */
  $handler->display->display_options['filters']['field_track_value']['id'] = 'field_track_value';
  $handler->display->display_options['filters']['field_track_value']['table'] = 'field_data_field_track';
  $handler->display->display_options['filters']['field_track_value']['field'] = 'field_track_value';
  $handler->display->display_options['filters']['field_track_value']['group'] = 1;
  $handler->display->display_options['filters']['field_track_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_track_value']['expose']['operator_id'] = 'field_track_value_op';
  $handler->display->display_options['filters']['field_track_value']['expose']['label'] = 'Track';
  $handler->display->display_options['filters']['field_track_value']['expose']['operator'] = 'field_track_value_op';
  $handler->display->display_options['filters']['field_track_value']['expose']['identifier'] = 'track';
  $handler->display->display_options['filters']['field_track_value']['expose']['multiple'] = 1;
  $handler->display->display_options['filters']['field_track_value']['expose']['reduce'] = 0;
  /* Filter criterion: Search: Search Terms */
  $handler->display->display_options['filters']['keys']['id'] = 'keys';
  $handler->display->display_options['filters']['keys']['table'] = 'search_index';
  $handler->display->display_options['filters']['keys']['field'] = 'keys';
  $handler->display->display_options['filters']['keys']['group'] = 1;
  $handler->display->display_options['filters']['keys']['exposed'] = TRUE;
  $handler->display->display_options['filters']['keys']['expose']['operator_id'] = 'keys_op';
  $handler->display->display_options['filters']['keys']['expose']['label'] = 'Filter by keywords:';
  $handler->display->display_options['filters']['keys']['expose']['operator'] = 'keys_op';
  $handler->display->display_options['filters']['keys']['expose']['identifier'] = 'keys';
  $handler->display->display_options['filters']['keys']['expose']['multiple'] = FALSE;
  /* Filter criterion: Content: Experience level (field_experience) */
  $handler->display->display_options['filters']['field_experience_value']['id'] = 'field_experience_value';
  $handler->display->display_options['filters']['field_experience_value']['table'] = 'field_data_field_experience';
  $handler->display->display_options['filters']['field_experience_value']['field'] = 'field_experience_value';
  $handler->display->display_options['filters']['field_experience_value']['group'] = 1;
  $handler->display->display_options['filters']['field_experience_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_experience_value']['expose']['operator_id'] = 'field_experience_value_op';
  $handler->display->display_options['filters']['field_experience_value']['expose']['label'] = 'Experience level';
  $handler->display->display_options['filters']['field_experience_value']['expose']['operator'] = 'field_experience_value_op';
  $handler->display->display_options['filters']['field_experience_value']['expose']['identifier'] = 'experience_level';
  $handler->display->display_options['filters']['field_experience_value']['expose']['remember'] = 1;
  $handler->display->display_options['filters']['field_experience_value']['expose']['multiple'] = 1;
  $handler->display->display_options['filters']['field_experience_value']['expose']['reduce'] = 0;

  /* Display: Page: My Sessions */
  $handler = $view->new_display('page', 'Page: My Sessions', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'My Sessions';
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'view-grouped-list sessions-list sessions-accepted';
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'No accepted sessions';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'No sessions have been accepted yet. When you accept unprocessed sessions, they will show up here.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'session' => 'session',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: User: Current */
  $handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['table'] = 'users';
  $handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid_current']['value'] = '1';
  $handler->display->display_options['filters']['uid_current']['group'] = 1;
  $handler->display->display_options['path'] = 'user/%/sessions';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'My Sessions';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-menu-quick-links';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Admin Sessions';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $export['cod_session_evaluations_speaker_review'] = $view;

  return $export;
}
