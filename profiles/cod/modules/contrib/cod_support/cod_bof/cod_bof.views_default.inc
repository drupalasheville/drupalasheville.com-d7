<?php
/**
 * @file
 * cod_bof.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function cod_bof_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'cod_bof_schedule';
  $view->description = 'Conference Organizing Scheduler Admin View';
  $view->tag = 'cod';
  $view->base_table = 'cod_event_time';
  $view->human_name = 'cod_bof_schedule';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'BoFs';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '60';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '60';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'quicktabs';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_evttime_date',
      'rendered' => 1,
      'rendered_strip' => 1,
    ),
  );
  $handler->display->display_options['style_options']['tab_style'] = 'Zen';
  $handler->display->display_options['style_options']['tab_title_field'] = 'field_evttime_date';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = 'BoFs are first come, first serve. To create a BoF, <a href="/user">login first</a> and then click \'create a bof\' at the time you want.';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  /* Field: Time: Date and time */
  $handler->display->display_options['fields']['field_evttime_date']['id'] = 'field_evttime_date';
  $handler->display->display_options['fields']['field_evttime_date']['table'] = 'field_data_field_evttime_date';
  $handler->display->display_options['fields']['field_evttime_date']['field'] = 'field_evttime_date';
  $handler->display->display_options['fields']['field_evttime_date']['label'] = 'Day Tab';
  $handler->display->display_options['fields']['field_evttime_date']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_evttime_date']['settings'] = array(
    'format_type' => 'date_no_time',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Time: Date and time */
  $handler->display->display_options['fields']['field_evttime_date_1']['id'] = 'field_evttime_date_1';
  $handler->display->display_options['fields']['field_evttime_date_1']['table'] = 'field_data_field_evttime_date';
  $handler->display->display_options['fields']['field_evttime_date_1']['field'] = 'field_evttime_date';
  $handler->display->display_options['fields']['field_evttime_date_1']['label'] = '';
  $handler->display->display_options['fields']['field_evttime_date_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_evttime_date_1']['settings'] = array(
    'format_type' => 'time_slot',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Time: Time ID */
  $handler->display->display_options['fields']['evttid']['id'] = 'evttid';
  $handler->display->display_options['fields']['evttid']['table'] = 'cod_event_time';
  $handler->display->display_options['fields']['evttid']['field'] = 'evttid';
  $handler->display->display_options['fields']['evttid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['evttid']['separator'] = '';
  /* Field: Global: View */
  $handler->display->display_options['fields']['view']['id'] = 'view';
  $handler->display->display_options['fields']['view']['table'] = 'views';
  $handler->display->display_options['fields']['view']['field'] = 'view';
  $handler->display->display_options['fields']['view']['label'] = '';
  $handler->display->display_options['fields']['view']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['view']['view'] = 'cod_bof_schedule_timeslots';
  $handler->display->display_options['fields']['view']['arguments'] = '[!evttid]/bof_session';
  /* Sort criterion: Time: Date and time -  start date (field_evttime_date) */
  $handler->display->display_options['sorts']['field_evttime_date_value']['id'] = 'field_evttime_date_value';
  $handler->display->display_options['sorts']['field_evttime_date_value']['table'] = 'field_data_field_evttime_date';
  $handler->display->display_options['sorts']['field_evttime_date_value']['field'] = 'field_evttime_date_value';
  /* Contextual filter: Field: Event (og_group_ref) */
  $handler->display->display_options['arguments']['og_group_ref_target_id']['id'] = 'og_group_ref_target_id';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['field'] = 'og_group_ref_target_id';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['og_group_ref_target_id']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['validate_options']['types'] = array(
    'event' => 'event',
  );
  $handler->display->display_options['arguments']['og_group_ref_target_id']['validate_options']['access'] = TRUE;
  /* Filter criterion: Field collection item: Allowed Types (field_timeslot_allowed_types) */
  $handler->display->display_options['filters']['field_timeslot_allowed_types_value']['id'] = 'field_timeslot_allowed_types_value';
  $handler->display->display_options['filters']['field_timeslot_allowed_types_value']['table'] = 'field_data_field_timeslot_allowed_types';
  $handler->display->display_options['filters']['field_timeslot_allowed_types_value']['field'] = 'field_timeslot_allowed_types_value';
  $handler->display->display_options['filters']['field_timeslot_allowed_types_value']['relationship'] = 'reverse_field_timeslot_time_field_collection_item';
  $handler->display->display_options['filters']['field_timeslot_allowed_types_value']['value'] = 'bof_session';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_timeslot_time_field_collection_item']['id'] = 'reverse_field_timeslot_time_field_collection_item';
  $handler->display->display_options['relationships']['reverse_field_timeslot_time_field_collection_item']['table'] = 'cod_event_time';
  $handler->display->display_options['relationships']['reverse_field_timeslot_time_field_collection_item']['field'] = 'reverse_field_timeslot_time_field_collection_item';
  $handler->display->display_options['relationships']['reverse_field_timeslot_time_field_collection_item']['required'] = TRUE;
  $handler->display->display_options['path'] = 'node/%/program/bofs';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'BoFs';
  $handler->display->display_options['menu']['description'] = 'Birds of a Feather Sessions';
  $handler->display->display_options['menu']['weight'] = '4';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['cod_bof_schedule'] = $view;

  $view = new view();
  $view->name = 'cod_bof_schedule_content';
  $view->description = 'Conference Organizing Scheduler BoF content';
  $view->tag = 'cod';
  $view->base_table = 'node';
  $view->human_name = 'cod_bof_schedule_content';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_session_timeslot_target_id']['id'] = 'field_session_timeslot_target_id';
  $handler->display->display_options['relationships']['field_session_timeslot_target_id']['table'] = 'field_data_field_session_timeslot';
  $handler->display->display_options['relationships']['field_session_timeslot_target_id']['field'] = 'field_session_timeslot_target_id';
  $handler->display->display_options['relationships']['field_session_timeslot_target_id']['label'] = 'Timeslot Entity';
  $handler->display->display_options['relationships']['field_session_timeslot_target_id']['required'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Contextual filter: Field collection item: Field collection item ID */
  $handler->display->display_options['arguments']['item_id']['id'] = 'item_id';
  $handler->display->display_options['arguments']['item_id']['table'] = 'field_collection_item';
  $handler->display->display_options['arguments']['item_id']['field'] = 'item_id';
  $handler->display->display_options['arguments']['item_id']['relationship'] = 'field_session_timeslot_target_id';
  $handler->display->display_options['arguments']['item_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['item_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['item_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['item_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['item_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['item_id']['break_phrase'] = TRUE;
  /* Contextual filter: Field collection item: Allowed Types (field_timeslot_allowed_types) */
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['id'] = 'field_timeslot_allowed_types_value';
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['table'] = 'field_data_field_timeslot_allowed_types';
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['field'] = 'field_timeslot_allowed_types_value';
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['relationship'] = 'field_session_timeslot_target_id';
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['limit'] = '0';
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null']['id'] = 'null';
  $handler->display->display_options['arguments']['null']['table'] = 'views';
  $handler->display->display_options['arguments']['null']['field'] = 'null';
  $handler->display->display_options['arguments']['null']['default_action'] = 'default';
  $handler->display->display_options['arguments']['null']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['null']['default_argument_options']['argument'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null_1']['id'] = 'null_1';
  $handler->display->display_options['arguments']['null_1']['table'] = 'views';
  $handler->display->display_options['arguments']['null_1']['field'] = 'null';
  $handler->display->display_options['arguments']['null_1']['default_action'] = 'default';
  $handler->display->display_options['arguments']['null_1']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['null_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null_1']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  $export['cod_bof_schedule_content'] = $view;

  $view = new view();
  $view->name = 'cod_bof_schedule_timeslots';
  $view->description = 'The scheduling entity that renders Timeslot Combos for BoFs';
  $view->tag = 'default';
  $view->base_table = 'field_collection_item';
  $view->human_name = 'cod_bof_schedule_timeslots';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'cod_bof_schedule_timeslots';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_timeslot_time_target_id']['id'] = 'field_timeslot_time_target_id';
  $handler->display->display_options['relationships']['field_timeslot_time_target_id']['table'] = 'field_data_field_timeslot_time';
  $handler->display->display_options['relationships']['field_timeslot_time_target_id']['field'] = 'field_timeslot_time_target_id';
  $handler->display->display_options['relationships']['field_timeslot_time_target_id']['label'] = 'Time entity';
  $handler->display->display_options['relationships']['field_timeslot_time_target_id']['required'] = TRUE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_timeslot_room_target_id']['id'] = 'field_timeslot_room_target_id';
  $handler->display->display_options['relationships']['field_timeslot_room_target_id']['table'] = 'field_data_field_timeslot_room';
  $handler->display->display_options['relationships']['field_timeslot_room_target_id']['field'] = 'field_timeslot_room_target_id';
  $handler->display->display_options['relationships']['field_timeslot_room_target_id']['label'] = 'Room entity';
  $handler->display->display_options['relationships']['field_timeslot_room_target_id']['required'] = TRUE;
  /* Relationship: Field collection item: Entity with the Scheduler (Time Slots) (field_event_timeslots) */
  $handler->display->display_options['relationships']['field_event_timeslots_node']['id'] = 'field_event_timeslots_node';
  $handler->display->display_options['relationships']['field_event_timeslots_node']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_event_timeslots_node']['field'] = 'field_event_timeslots_node';
  $handler->display->display_options['relationships']['field_event_timeslots_node']['required'] = TRUE;
  /* Field: Field collection item: Field collection item ID */
  $handler->display->display_options['fields']['item_id']['id'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['table'] = 'field_collection_item';
  $handler->display->display_options['fields']['item_id']['field'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['label'] = '';
  $handler->display->display_options['fields']['item_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['item_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['item_id']['separator'] = '';
  /* Field: Room: Label */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'cod_event_room';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'field_timeslot_room_target_id';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Room: Capacity */
  $handler->display->display_options['fields']['capacity']['id'] = 'capacity';
  $handler->display->display_options['fields']['capacity']['table'] = 'cod_event_room';
  $handler->display->display_options['fields']['capacity']['field'] = 'capacity';
  $handler->display->display_options['fields']['capacity']['relationship'] = 'field_timeslot_room_target_id';
  $handler->display->display_options['fields']['capacity']['label'] = '';
  $handler->display->display_options['fields']['capacity']['exclude'] = TRUE;
  $handler->display->display_options['fields']['capacity']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['capacity']['separator'] = '';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'field_event_timeslots_node';
  $handler->display->display_options['fields']['nid']['label'] = 'Event NID';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  /* Field: Global: View */
  $handler->display->display_options['fields']['view']['id'] = 'view';
  $handler->display->display_options['fields']['view']['table'] = 'views';
  $handler->display->display_options['fields']['view']['field'] = 'view';
  $handler->display->display_options['fields']['view']['label'] = '';
  $handler->display->display_options['fields']['view']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['view']['view'] = 'cod_bof_schedule_content';
  $handler->display->display_options['fields']['view']['arguments'] = '[!item_id]/!2/[!capacity]/[!nid]';
  /* Contextual filter: Time: Time ID */
  $handler->display->display_options['arguments']['evttid']['id'] = 'evttid';
  $handler->display->display_options['arguments']['evttid']['table'] = 'cod_event_time';
  $handler->display->display_options['arguments']['evttid']['field'] = 'evttid';
  $handler->display->display_options['arguments']['evttid']['relationship'] = 'field_timeslot_time_target_id';
  $handler->display->display_options['arguments']['evttid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['evttid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['evttid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['evttid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['evttid']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Field collection item: Allowed Types (field_timeslot_allowed_types) */
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['id'] = 'field_timeslot_allowed_types_value';
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['table'] = 'field_data_field_timeslot_allowed_types';
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['field'] = 'field_timeslot_allowed_types_value';
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['limit'] = '0';
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['break_phrase'] = TRUE;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;

  /* Display: Bof Grid Block */
  $handler = $view->new_display('block', 'Bof Grid Block', 'block_1');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $export['cod_bof_schedule_timeslots'] = $view;

  return $export;
}
