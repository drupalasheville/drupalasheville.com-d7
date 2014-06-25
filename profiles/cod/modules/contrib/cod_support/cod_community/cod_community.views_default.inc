<?php
/**
 * @file
 * cod_community.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function cod_community_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'cod_community_attendees';
  $view->description = '';
  $view->tag = 'cod community';
  $view->base_table = 'users';
  $view->human_name = 'Attendees';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Community';
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'All Attendees';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '48';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'picture' => 'field_profile_last',
    'field_profile_first' => 'field_profile_last',
    'field_profile_last' => 'field_profile_last',
    'field_profile_org' => 'field_profile_org',
    'field_profile_org_1' => 'field_profile_org_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'picture' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'field_profile_first' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'field_profile_last' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'field_profile_org' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'field_profile_org_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['content'] = 'No one has signed up for this event. Attendees will appear as they sign up.';
  /* Relationship: OG membership: OG membership from User */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'users';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Field: User: Picture */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'users';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['label'] = '';
  $handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
  /* Field: Field: First name */
  $handler->display->display_options['fields']['field_profile_first']['id'] = 'field_profile_first';
  $handler->display->display_options['fields']['field_profile_first']['table'] = 'field_data_field_profile_first';
  $handler->display->display_options['fields']['field_profile_first']['field'] = 'field_profile_first';
  /* Field: Field: Last name */
  $handler->display->display_options['fields']['field_profile_last']['id'] = 'field_profile_last';
  $handler->display->display_options['fields']['field_profile_last']['table'] = 'field_data_field_profile_last';
  $handler->display->display_options['fields']['field_profile_last']['field'] = 'field_profile_last';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  /* Field: User: Organization */
  $handler->display->display_options['fields']['field_profile_org']['id'] = 'field_profile_org';
  $handler->display->display_options['fields']['field_profile_org']['table'] = 'field_data_field_profile_org';
  $handler->display->display_options['fields']['field_profile_org']['field'] = 'field_profile_org';
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['gid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['gid']['validate']['type'] = 'og';
  /* Filter criterion: Field: First name (field_profile_first) */
  $handler->display->display_options['filters']['field_profile_first_value']['id'] = 'field_profile_first_value';
  $handler->display->display_options['filters']['field_profile_first_value']['table'] = 'field_data_field_profile_first';
  $handler->display->display_options['filters']['field_profile_first_value']['field'] = 'field_profile_first_value';
  $handler->display->display_options['filters']['field_profile_first_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_profile_first_value']['expose']['operator_id'] = 'field_profile_first_value_op';
  $handler->display->display_options['filters']['field_profile_first_value']['expose']['label'] = 'First name';
  $handler->display->display_options['filters']['field_profile_first_value']['expose']['operator'] = 'field_profile_first_value_op';
  $handler->display->display_options['filters']['field_profile_first_value']['expose']['identifier'] = 'field_profile_first_value';
  /* Filter criterion: Field: Last name (field_profile_last) */
  $handler->display->display_options['filters']['field_profile_last_value']['id'] = 'field_profile_last_value';
  $handler->display->display_options['filters']['field_profile_last_value']['table'] = 'field_data_field_profile_last';
  $handler->display->display_options['filters']['field_profile_last_value']['field'] = 'field_profile_last_value';
  $handler->display->display_options['filters']['field_profile_last_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_profile_last_value']['expose']['operator_id'] = 'field_profile_last_value_op';
  $handler->display->display_options['filters']['field_profile_last_value']['expose']['label'] = 'Last name';
  $handler->display->display_options['filters']['field_profile_last_value']['expose']['operator'] = 'field_profile_last_value_op';
  $handler->display->display_options['filters']['field_profile_last_value']['expose']['identifier'] = 'field_profile_last_value';
  /* Filter criterion: User: Organization (field_profile_org) */
  $handler->display->display_options['filters']['field_profile_org_value']['id'] = 'field_profile_org_value';
  $handler->display->display_options['filters']['field_profile_org_value']['table'] = 'field_data_field_profile_org';
  $handler->display->display_options['filters']['field_profile_org_value']['field'] = 'field_profile_org_value';
  $handler->display->display_options['filters']['field_profile_org_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_profile_org_value']['expose']['operator_id'] = 'field_profile_org_value_op';
  $handler->display->display_options['filters']['field_profile_org_value']['expose']['label'] = 'Organization';
  $handler->display->display_options['filters']['field_profile_org_value']['expose']['operator'] = 'field_profile_org_value_op';
  $handler->display->display_options['filters']['field_profile_org_value']['expose']['identifier'] = 'field_profile_org_value';
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['operator'] = 'not in';
  $handler->display->display_options['filters']['uid']['value'] = array(
    0 => 0,
    1 => '1',
  );
  $handler->display->display_options['filters']['uid']['group'] = '0';
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'Name';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  /* Filter criterion: OG membership: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'og_membership';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['state']['value'] = array(
    1 => '1',
  );

  /* Display: Community Page (Main) */
  $handler = $view->new_display('page', 'Community Page (Main)', 'page');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'picture' => 'picture',
    'field_profile_first' => 'field_profile_first',
    'field_profile_last' => 'field_profile_last',
    'field_profile_org_1' => 'field_profile_org_1',
    'field_profile_job_title' => 'field_profile_job_title',
    'field_profile_interests' => 'field_profile_interests',
  );
  $handler->display->display_options['style_options']['default'] = 'field_profile_first';
  $handler->display->display_options['style_options']['info'] = array(
    'picture' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_profile_first' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_profile_last' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_profile_org_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_profile_job_title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_profile_interests' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Picture */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'users';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['label'] = '';
  $handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
  /* Field: Field: First name */
  $handler->display->display_options['fields']['field_profile_first']['id'] = 'field_profile_first';
  $handler->display->display_options['fields']['field_profile_first']['table'] = 'field_data_field_profile_first';
  $handler->display->display_options['fields']['field_profile_first']['field'] = 'field_profile_first';
  $handler->display->display_options['fields']['field_profile_first']['label'] = 'name';
  $handler->display->display_options['fields']['field_profile_first']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_profile_first']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_profile_first']['element_wrapper_type'] = 'span';
  /* Field: Field: Last name */
  $handler->display->display_options['fields']['field_profile_last']['id'] = 'field_profile_last';
  $handler->display->display_options['fields']['field_profile_last']['table'] = 'field_data_field_profile_last';
  $handler->display->display_options['fields']['field_profile_last']['field'] = 'field_profile_last';
  $handler->display->display_options['fields']['field_profile_last']['label'] = 'name';
  $handler->display->display_options['fields']['field_profile_last']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_profile_last']['alter']['text'] = '[field_profile_first] [field_profile_last]';
  $handler->display->display_options['fields']['field_profile_last']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_profile_last']['element_wrapper_type'] = 'span';
  /* Field: User: Organization */
  $handler->display->display_options['fields']['field_profile_org_1']['id'] = 'field_profile_org_1';
  $handler->display->display_options['fields']['field_profile_org_1']['table'] = 'field_data_field_profile_org';
  $handler->display->display_options['fields']['field_profile_org_1']['field'] = 'field_profile_org';
  $handler->display->display_options['fields']['field_profile_org_1']['element_label_colon'] = FALSE;
  /* Field: User: Job title */
  $handler->display->display_options['fields']['field_profile_job_title']['id'] = 'field_profile_job_title';
  $handler->display->display_options['fields']['field_profile_job_title']['table'] = 'field_data_field_profile_job_title';
  $handler->display->display_options['fields']['field_profile_job_title']['field'] = 'field_profile_job_title';
  /* Field: User: Interests */
  $handler->display->display_options['fields']['field_profile_interests']['id'] = 'field_profile_interests';
  $handler->display->display_options['fields']['field_profile_interests']['table'] = 'field_data_field_profile_interests';
  $handler->display->display_options['fields']['field_profile_interests']['field'] = 'field_profile_interests';
  $handler->display->display_options['fields']['field_profile_interests']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Field: First name (field_profile_first) */
  $handler->display->display_options['filters']['field_profile_first_value']['id'] = 'field_profile_first_value';
  $handler->display->display_options['filters']['field_profile_first_value']['table'] = 'field_data_field_profile_first';
  $handler->display->display_options['filters']['field_profile_first_value']['field'] = 'field_profile_first_value';
  $handler->display->display_options['filters']['field_profile_first_value']['group'] = 1;
  $handler->display->display_options['filters']['field_profile_first_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_profile_first_value']['expose']['operator_id'] = 'field_profile_first_value_op';
  $handler->display->display_options['filters']['field_profile_first_value']['expose']['label'] = 'First name';
  $handler->display->display_options['filters']['field_profile_first_value']['expose']['operator'] = 'field_profile_first_value_op';
  $handler->display->display_options['filters']['field_profile_first_value']['expose']['identifier'] = 'field_profile_first_value';
  /* Filter criterion: Field: Last name (field_profile_last) */
  $handler->display->display_options['filters']['field_profile_last_value']['id'] = 'field_profile_last_value';
  $handler->display->display_options['filters']['field_profile_last_value']['table'] = 'field_data_field_profile_last';
  $handler->display->display_options['filters']['field_profile_last_value']['field'] = 'field_profile_last_value';
  $handler->display->display_options['filters']['field_profile_last_value']['group'] = 1;
  $handler->display->display_options['filters']['field_profile_last_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_profile_last_value']['expose']['operator_id'] = 'field_profile_last_value_op';
  $handler->display->display_options['filters']['field_profile_last_value']['expose']['label'] = 'Last name';
  $handler->display->display_options['filters']['field_profile_last_value']['expose']['operator'] = 'field_profile_last_value_op';
  $handler->display->display_options['filters']['field_profile_last_value']['expose']['identifier'] = 'field_profile_last_value';
  /* Filter criterion: User: Organization (field_profile_org) */
  $handler->display->display_options['filters']['field_profile_org_value']['id'] = 'field_profile_org_value';
  $handler->display->display_options['filters']['field_profile_org_value']['table'] = 'field_data_field_profile_org';
  $handler->display->display_options['filters']['field_profile_org_value']['field'] = 'field_profile_org_value';
  $handler->display->display_options['filters']['field_profile_org_value']['group'] = 1;
  $handler->display->display_options['filters']['field_profile_org_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_profile_org_value']['expose']['operator_id'] = 'field_profile_org_value_op';
  $handler->display->display_options['filters']['field_profile_org_value']['expose']['label'] = 'Organization';
  $handler->display->display_options['filters']['field_profile_org_value']['expose']['operator'] = 'field_profile_org_value_op';
  $handler->display->display_options['filters']['field_profile_org_value']['expose']['identifier'] = 'field_profile_org_value';
  /* Filter criterion: User: Job title (field_profile_job_title) */
  $handler->display->display_options['filters']['field_profile_job_title_value']['id'] = 'field_profile_job_title_value';
  $handler->display->display_options['filters']['field_profile_job_title_value']['table'] = 'field_data_field_profile_job_title';
  $handler->display->display_options['filters']['field_profile_job_title_value']['field'] = 'field_profile_job_title_value';
  $handler->display->display_options['filters']['field_profile_job_title_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_profile_job_title_value']['expose']['operator_id'] = 'field_profile_job_title_value_op';
  $handler->display->display_options['filters']['field_profile_job_title_value']['expose']['label'] = 'Job title';
  $handler->display->display_options['filters']['field_profile_job_title_value']['expose']['operator'] = 'field_profile_job_title_value_op';
  $handler->display->display_options['filters']['field_profile_job_title_value']['expose']['identifier'] = 'field_profile_job_title_value';
  /* Filter criterion: User: Interests (field_profile_interests) */
  $handler->display->display_options['filters']['field_profile_interests_value']['id'] = 'field_profile_interests_value';
  $handler->display->display_options['filters']['field_profile_interests_value']['table'] = 'field_data_field_profile_interests';
  $handler->display->display_options['filters']['field_profile_interests_value']['field'] = 'field_profile_interests_value';
  $handler->display->display_options['filters']['field_profile_interests_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_profile_interests_value']['expose']['operator_id'] = 'field_profile_interests_value_op';
  $handler->display->display_options['filters']['field_profile_interests_value']['expose']['label'] = 'Interests';
  $handler->display->display_options['filters']['field_profile_interests_value']['expose']['operator'] = 'field_profile_interests_value_op';
  $handler->display->display_options['filters']['field_profile_interests_value']['expose']['identifier'] = 'field_profile_interests_value';
  $handler->display->display_options['path'] = 'node/%/community';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Community';
  $handler->display->display_options['menu']['name'] = 'main-menu';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '12';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: User: Picture */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'users';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['label'] = '';
  $handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
  /* Field: Field: First name */
  $handler->display->display_options['fields']['field_profile_first']['id'] = 'field_profile_first';
  $handler->display->display_options['fields']['field_profile_first']['table'] = 'field_data_field_profile_first';
  $handler->display->display_options['fields']['field_profile_first']['field'] = 'field_profile_first';
  $handler->display->display_options['fields']['field_profile_first']['label'] = '';
  $handler->display->display_options['fields']['field_profile_first']['exclude'] = TRUE;
  /* Field: Field: Last name */
  $handler->display->display_options['fields']['field_profile_last']['id'] = 'field_profile_last';
  $handler->display->display_options['fields']['field_profile_last']['table'] = 'field_data_field_profile_last';
  $handler->display->display_options['fields']['field_profile_last']['field'] = 'field_profile_last';
  $handler->display->display_options['fields']['field_profile_last']['label'] = '';
  $handler->display->display_options['fields']['field_profile_last']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_profile_last']['alter']['text'] = '[field_profile_first] [field_profile_last]';
  $handler->display->display_options['fields']['field_profile_last']['element_label_colon'] = FALSE;
  /* Field: User: Organization */
  $handler->display->display_options['fields']['field_profile_org']['id'] = 'field_profile_org';
  $handler->display->display_options['fields']['field_profile_org']['table'] = 'field_data_field_profile_org';
  $handler->display->display_options['fields']['field_profile_org']['field'] = 'field_profile_org';
  $handler->display->display_options['fields']['field_profile_org']['label'] = '';
  $handler->display->display_options['fields']['field_profile_org']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['operator'] = 'not in';
  $handler->display->display_options['filters']['uid']['value'] = array(
    0 => 0,
    1 => '1',
  );
  $handler->display->display_options['filters']['uid']['group'] = '0';
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'Name';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  /* Filter criterion: OG membership: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'og_membership';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['state']['value'] = array(
    1 => '1',
  );

  /* Display: Entity Reference */
  $handler = $view->new_display('entityreference', 'Entity Reference', 'entityreference_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'field_profile_first' => 'field_profile_first',
    'field_profile_last' => 'field_profile_last',
    'picture' => 0,
    'name' => 0,
    'field_profile_org' => 0,
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['row_options']['separator'] = '';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Picture */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'users';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['label'] = '';
  $handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
  /* Field: Field: First name */
  $handler->display->display_options['fields']['field_profile_first']['id'] = 'field_profile_first';
  $handler->display->display_options['fields']['field_profile_first']['table'] = 'field_data_field_profile_first';
  $handler->display->display_options['fields']['field_profile_first']['field'] = 'field_profile_first';
  $handler->display->display_options['fields']['field_profile_first']['label'] = '';
  $handler->display->display_options['fields']['field_profile_first']['element_label_colon'] = FALSE;
  /* Field: Field: Last name */
  $handler->display->display_options['fields']['field_profile_last']['id'] = 'field_profile_last';
  $handler->display->display_options['fields']['field_profile_last']['table'] = 'field_data_field_profile_last';
  $handler->display->display_options['fields']['field_profile_last']['field'] = 'field_profile_last';
  $handler->display->display_options['fields']['field_profile_last']['label'] = '';
  $handler->display->display_options['fields']['field_profile_last']['element_label_colon'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['text'] = '([name])';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* Field: User: Organization */
  $handler->display->display_options['fields']['field_profile_org']['id'] = 'field_profile_org';
  $handler->display->display_options['fields']['field_profile_org']['table'] = 'field_data_field_profile_org';
  $handler->display->display_options['fields']['field_profile_org']['field'] = 'field_profile_org';
  $handler->display->display_options['fields']['field_profile_org']['label'] = '';
  $handler->display->display_options['fields']['field_profile_org']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['gid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['gid']['validate']['type'] = 'og';
  $handler->display->display_options['arguments']['gid']['validate']['fail'] = 'ignore';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['operator'] = 'not in';
  $handler->display->display_options['filters']['uid']['value'] = array(
    0 => 0,
    1 => '1',
  );
  $handler->display->display_options['filters']['uid']['group'] = '0';
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'Name';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  /* Filter criterion: OG membership: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'og_membership';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['state']['value'] = array(
    1 => '1',
  );
  $export['cod_community_attendees'] = $view;

  return $export;
}
