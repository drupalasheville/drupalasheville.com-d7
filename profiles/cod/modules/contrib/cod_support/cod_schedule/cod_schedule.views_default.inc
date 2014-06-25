<?php
/**
 * @file
 * cod_schedule.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function cod_schedule_views_default_views() {
  $export = array();

  // This is the POC from DyanneNova, keeping here for legacy reasons for now.
  $view = new view();
  $view->name = 'cod_event_rooms';
  $view->description = '';
  $view->tag = 'cod_schedule';
  $view->base_table = 'cod_event_room';
  $view->human_name = 'COD Event Rooms';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Rooms';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Room: Label */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'cod_event_room';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Sort criterion: Room: Label */
  $handler->display->display_options['sorts']['name']['id'] = 'name';
  $handler->display->display_options['sorts']['name']['table'] = 'cod_event_room';
  $handler->display->display_options['sorts']['name']['field'] = 'name';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['cod_event_rooms'] = $view;

  $view = new view();
  $view->name = 'cod_schedule';
  $view->description = 'Main Schedule View for Events';
  $view->tag = 'cod_schedule';
  $view->base_table = 'cod_event_time';
  $view->human_name = 'COD Event Schedule';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Schedule';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
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
  /* Field: Time: Time ID */
  $handler->display->display_options['fields']['evttid']['id'] = 'evttid';
  $handler->display->display_options['fields']['evttid']['table'] = 'cod_event_time';
  $handler->display->display_options['fields']['evttid']['field'] = 'evttid';
  $handler->display->display_options['fields']['evttid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['evttid']['separator'] = '';
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
  /* Field: Field: Event */
  $handler->display->display_options['fields']['og_group_ref']['id'] = 'og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['table'] = 'og_membership';
  $handler->display->display_options['fields']['og_group_ref']['field'] = 'og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['label'] = '';
  $handler->display->display_options['fields']['og_group_ref']['exclude'] = TRUE;
  $handler->display->display_options['fields']['og_group_ref']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['og_group_ref']['type'] = 'entityreference_entity_id';
  $handler->display->display_options['fields']['og_group_ref']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['og_group_ref']['delta_offset'] = '0';
  /* Field: Global: View */
  $handler->display->display_options['fields']['view']['id'] = 'view';
  $handler->display->display_options['fields']['view']['table'] = 'views';
  $handler->display->display_options['fields']['view']['field'] = 'view';
  $handler->display->display_options['fields']['view']['label'] = '';
  $handler->display->display_options['fields']['view']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['view']['view'] = 'cod_schedule_content';
  $handler->display->display_options['fields']['view']['arguments'] = '[!evttid]/session+schedule_item';
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

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'node/%/program/schedule/sessions';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Sessions';
  $handler->display->display_options['menu']['weight'] = '-10';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Schedule';
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: Schedule Sign */
  $handler = $view->new_display('page', 'Schedule Sign', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Schedule';
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '4';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Time: Time ID */
  $handler->display->display_options['fields']['evttid']['id'] = 'evttid';
  $handler->display->display_options['fields']['evttid']['table'] = 'cod_event_time';
  $handler->display->display_options['fields']['evttid']['field'] = 'evttid';
  $handler->display->display_options['fields']['evttid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['evttid']['separator'] = '';
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
  /* Field: Field: Event */
  $handler->display->display_options['fields']['og_group_ref']['id'] = 'og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['table'] = 'og_membership';
  $handler->display->display_options['fields']['og_group_ref']['field'] = 'og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['label'] = '';
  $handler->display->display_options['fields']['og_group_ref']['exclude'] = TRUE;
  $handler->display->display_options['fields']['og_group_ref']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['og_group_ref']['type'] = 'entityreference_entity_id';
  $handler->display->display_options['fields']['og_group_ref']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['og_group_ref']['delta_offset'] = '0';
  /* Field: Global: View */
  $handler->display->display_options['fields']['view']['id'] = 'view';
  $handler->display->display_options['fields']['view']['table'] = 'views';
  $handler->display->display_options['fields']['view']['field'] = 'view';
  $handler->display->display_options['fields']['view']['label'] = '';
  $handler->display->display_options['fields']['view']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['view']['view'] = 'cod_schedule_content';
  $handler->display->display_options['fields']['view']['display'] = 'block_2';
  $handler->display->display_options['fields']['view']['arguments'] = '[!evttid]/session+schedule_item';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Time: Date and time - end date (field_evttime_date:value2) */
  $handler->display->display_options['filters']['field_evttime_date_value2']['id'] = 'field_evttime_date_value2';
  $handler->display->display_options['filters']['field_evttime_date_value2']['table'] = 'field_data_field_evttime_date';
  $handler->display->display_options['filters']['field_evttime_date_value2']['field'] = 'field_evttime_date_value2';
  $handler->display->display_options['filters']['field_evttime_date_value2']['operator'] = '>=';
  $handler->display->display_options['filters']['field_evttime_date_value2']['granularity'] = 'minute';
  $handler->display->display_options['filters']['field_evttime_date_value2']['default_date'] = '10 minutes';
  $handler->display->display_options['filters']['field_evttime_date_value2']['year_range'] = '-1:+1';
  $handler->display->display_options['path'] = 'node/%/program/schedule/sessions/sign';
  $export['cod_schedule'] = $view;

  $view = new view();
  $view->name = 'cod_schedule_content';
  $view->description = '';
  $view->tag = 'cod_schedule';
  $view->base_table = 'node';
  $view->human_name = 'COD Event Sessions';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
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
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'Nothing for this time.';
  $handler->display->display_options['empty']['area']['format'] = 'wiki_filter';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_session_timeslot_target_id']['id'] = 'field_session_timeslot_target_id';
  $handler->display->display_options['relationships']['field_session_timeslot_target_id']['table'] = 'field_data_field_session_timeslot';
  $handler->display->display_options['relationships']['field_session_timeslot_target_id']['field'] = 'field_session_timeslot_target_id';
  $handler->display->display_options['relationships']['field_session_timeslot_target_id']['label'] = 'Timeslots';
  $handler->display->display_options['relationships']['field_session_timeslot_target_id']['required'] = TRUE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_timeslot_room_target_id']['id'] = 'field_timeslot_room_target_id';
  $handler->display->display_options['relationships']['field_timeslot_room_target_id']['table'] = 'field_data_field_timeslot_room';
  $handler->display->display_options['relationships']['field_timeslot_room_target_id']['field'] = 'field_timeslot_room_target_id';
  $handler->display->display_options['relationships']['field_timeslot_room_target_id']['relationship'] = 'field_session_timeslot_target_id';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_timeslot_time_target_id']['id'] = 'field_timeslot_time_target_id';
  $handler->display->display_options['relationships']['field_timeslot_time_target_id']['table'] = 'field_data_field_timeslot_time';
  $handler->display->display_options['relationships']['field_timeslot_time_target_id']['field'] = 'field_timeslot_time_target_id';
  $handler->display->display_options['relationships']['field_timeslot_time_target_id']['relationship'] = 'field_session_timeslot_target_id';
  $handler->display->display_options['relationships']['field_timeslot_time_target_id']['label'] = 'Time entity';
  $handler->display->display_options['relationships']['field_timeslot_time_target_id']['required'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Room: Label */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'cod_event_room';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'field_timeslot_room_target_id';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Content: Speaker(s) */
  $handler->display->display_options['fields']['field_speakers']['id'] = 'field_speakers';
  $handler->display->display_options['fields']['field_speakers']['table'] = 'field_data_field_speakers';
  $handler->display->display_options['fields']['field_speakers']['field'] = 'field_speakers';
  $handler->display->display_options['fields']['field_speakers']['label'] = '';
  $handler->display->display_options['fields']['field_speakers']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_speakers']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['fields']['field_speakers']['delta_offset'] = '0';
  /* Field: Content: Track */
  $handler->display->display_options['fields']['field_session_track']['id'] = 'field_session_track';
  $handler->display->display_options['fields']['field_session_track']['table'] = 'field_data_field_session_track';
  $handler->display->display_options['fields']['field_session_track']['field'] = 'field_session_track';
  $handler->display->display_options['fields']['field_session_track']['label'] = '';
  $handler->display->display_options['fields']['field_session_track']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_session_track']['type'] = 'taxonomy_term_reference_plain';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Sort criterion: Field collection item: Room (field_timeslot_room) */
  $handler->display->display_options['sorts']['field_timeslot_room_target_id']['id'] = 'field_timeslot_room_target_id';
  $handler->display->display_options['sorts']['field_timeslot_room_target_id']['table'] = 'field_data_field_timeslot_room';
  $handler->display->display_options['sorts']['field_timeslot_room_target_id']['field'] = 'field_timeslot_room_target_id';
  $handler->display->display_options['sorts']['field_timeslot_room_target_id']['relationship'] = 'field_session_timeslot_target_id';
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
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['relationship'] = 'field_session_timeslot_target_id';
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['limit'] = '0';
  $handler->display->display_options['arguments']['field_timeslot_allowed_types_value']['break_phrase'] = TRUE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'views_json';
  $handler->display->display_options['style_options']['plaintext_output'] = 1;
  $handler->display->display_options['style_options']['remove_newlines'] = 0;
  $handler->display->display_options['style_options']['jsonp_prefix'] = '';
  $handler->display->display_options['style_options']['using_views_api_mode'] = 0;
  $handler->display->display_options['style_options']['object_arrays'] = 0;
  $handler->display->display_options['style_options']['numeric_strings'] = 0;
  $handler->display->display_options['style_options']['bigint_string'] = 0;
  $handler->display->display_options['style_options']['pretty_print'] = 0;
  $handler->display->display_options['style_options']['unescaped_slashes'] = 0;
  $handler->display->display_options['style_options']['unescaped_unicode'] = 0;
  $handler->display->display_options['style_options']['char_encoding'] = array();
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Room: Label */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'cod_event_room';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'field_timeslot_room_target_id';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Time: Date and time */
  $handler->display->display_options['fields']['field_evttime_date_1']['id'] = 'field_evttime_date_1';
  $handler->display->display_options['fields']['field_evttime_date_1']['table'] = 'field_data_field_evttime_date';
  $handler->display->display_options['fields']['field_evttime_date_1']['field'] = 'field_evttime_date';
  $handler->display->display_options['fields']['field_evttime_date_1']['relationship'] = 'field_timeslot_time_target_id';
  $handler->display->display_options['fields']['field_evttime_date_1']['label'] = 'day';
  $handler->display->display_options['fields']['field_evttime_date_1']['settings'] = array(
    'format_type' => 'date_no_time',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Time: Date and time */
  $handler->display->display_options['fields']['field_evttime_date']['id'] = 'field_evttime_date';
  $handler->display->display_options['fields']['field_evttime_date']['table'] = 'field_data_field_evttime_date';
  $handler->display->display_options['fields']['field_evttime_date']['field'] = 'field_evttime_date';
  $handler->display->display_options['fields']['field_evttime_date']['relationship'] = 'field_timeslot_time_target_id';
  $handler->display->display_options['fields']['field_evttime_date']['label'] = 'time';
  $handler->display->display_options['fields']['field_evttime_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_evttime_date']['settings'] = array(
    'format_type' => 'time_slot',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Speaker(s) */
  $handler->display->display_options['fields']['field_speakers']['id'] = 'field_speakers';
  $handler->display->display_options['fields']['field_speakers']['table'] = 'field_data_field_speakers';
  $handler->display->display_options['fields']['field_speakers']['field'] = 'field_speakers';
  $handler->display->display_options['fields']['field_speakers']['label'] = '';
  $handler->display->display_options['fields']['field_speakers']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_speakers']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['fields']['field_speakers']['delta_offset'] = '0';
  /* Field: Content: Track */
  $handler->display->display_options['fields']['field_session_track']['id'] = 'field_session_track';
  $handler->display->display_options['fields']['field_session_track']['table'] = 'field_data_field_session_track';
  $handler->display->display_options['fields']['field_session_track']['field'] = 'field_session_track';
  $handler->display->display_options['fields']['field_session_track']['label'] = '';
  $handler->display->display_options['fields']['field_session_track']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_session_track']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Content: Experience level */
  $handler->display->display_options['fields']['field_experience']['id'] = 'field_experience';
  $handler->display->display_options['fields']['field_experience']['table'] = 'field_data_field_experience';
  $handler->display->display_options['fields']['field_experience']['field'] = 'field_experience';
  $handler->display->display_options['fields']['field_experience']['label'] = '';
  $handler->display->display_options['fields']['field_experience']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Time: Date and time -  start date (field_evttime_date) */
  $handler->display->display_options['sorts']['field_evttime_date_value']['id'] = 'field_evttime_date_value';
  $handler->display->display_options['sorts']['field_evttime_date_value']['table'] = 'field_data_field_evttime_date';
  $handler->display->display_options['sorts']['field_evttime_date_value']['field'] = 'field_evttime_date_value';
  $handler->display->display_options['sorts']['field_evttime_date_value']['relationship'] = 'field_timeslot_time_target_id';
  /* Sort criterion: Field collection item: Room (field_timeslot_room) */
  $handler->display->display_options['sorts']['field_timeslot_room_target_id']['id'] = 'field_timeslot_room_target_id';
  $handler->display->display_options['sorts']['field_timeslot_room_target_id']['table'] = 'field_data_field_timeslot_room';
  $handler->display->display_options['sorts']['field_timeslot_room_target_id']['field'] = 'field_timeslot_room_target_id';
  $handler->display->display_options['sorts']['field_timeslot_room_target_id']['relationship'] = 'field_session_timeslot_target_id';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Field: Event (og_group_ref) */
  $handler->display->display_options['arguments']['og_group_ref_target_id']['id'] = 'og_group_ref_target_id';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['field'] = 'og_group_ref_target_id';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['relationship'] = 'field_timeslot_time_target_id';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['default_argument_type'] = 'cod_events_default_event';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Field collection item: Allowed Types (field_timeslot_allowed_types) */
  $handler->display->display_options['filters']['field_timeslot_allowed_types_value']['id'] = 'field_timeslot_allowed_types_value';
  $handler->display->display_options['filters']['field_timeslot_allowed_types_value']['table'] = 'field_data_field_timeslot_allowed_types';
  $handler->display->display_options['filters']['field_timeslot_allowed_types_value']['field'] = 'field_timeslot_allowed_types_value';
  $handler->display->display_options['filters']['field_timeslot_allowed_types_value']['relationship'] = 'field_session_timeslot_target_id';
  $handler->display->display_options['filters']['field_timeslot_allowed_types_value']['operator'] = '!=';
  $handler->display->display_options['filters']['field_timeslot_allowed_types_value']['value'] = 'bof_session';
  $handler->display->display_options['path'] = 'node/%/program/schedule/sessions.json';

  /* Display: Schedule Sign */
  $handler = $view->new_display('block', 'Schedule Sign', 'block_2');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['style_options']['columns'] = '12';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $export['cod_schedule_content'] = $view;

  $view = new view();
  $view->name = 'cod_schedule_timeslot_widget';
  $view->description = 'View representing the select field for timeslot entity references in sessions, bofs, etc';
  $view->tag = 'cod_schedule';
  $view->base_table = 'field_collection_item';
  $view->human_name = 'Timeslot Select List';
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
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_timeslot_room_target_id']['id'] = 'field_timeslot_room_target_id';
  $handler->display->display_options['relationships']['field_timeslot_room_target_id']['table'] = 'field_data_field_timeslot_room';
  $handler->display->display_options['relationships']['field_timeslot_room_target_id']['field'] = 'field_timeslot_room_target_id';
  $handler->display->display_options['relationships']['field_timeslot_room_target_id']['required'] = TRUE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_timeslot_time_target_id']['id'] = 'field_timeslot_time_target_id';
  $handler->display->display_options['relationships']['field_timeslot_time_target_id']['table'] = 'field_data_field_timeslot_time';
  $handler->display->display_options['relationships']['field_timeslot_time_target_id']['field'] = 'field_timeslot_time_target_id';
  $handler->display->display_options['relationships']['field_timeslot_time_target_id']['label'] = 'Time';
  /* Relationship: Field collection item: Entity with the Scheduler (Time Slots) (field_event_timeslots) */
  $handler->display->display_options['relationships']['field_event_timeslots_node']['id'] = 'field_event_timeslots_node';
  $handler->display->display_options['relationships']['field_event_timeslots_node']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_event_timeslots_node']['field'] = 'field_event_timeslots_node';
  $handler->display->display_options['relationships']['field_event_timeslots_node']['label'] = 'Event';
  /* Field: Field collection item: Field collection item ID */
  $handler->display->display_options['fields']['item_id']['id'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['table'] = 'field_collection_item';
  $handler->display->display_options['fields']['item_id']['field'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['label'] = '';
  $handler->display->display_options['fields']['item_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['item_id']['element_label_colon'] = FALSE;
  /* Field: Room: Label */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'cod_event_room';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'field_timeslot_room_target_id';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Time: Label */
  $handler->display->display_options['fields']['date_label']['id'] = 'date_label';
  $handler->display->display_options['fields']['date_label']['table'] = 'cod_event_time';
  $handler->display->display_options['fields']['date_label']['field'] = 'date_label';
  $handler->display->display_options['fields']['date_label']['relationship'] = 'field_timeslot_time_target_id';
  $handler->display->display_options['fields']['date_label']['label'] = '';
  $handler->display->display_options['fields']['date_label']['element_label_colon'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'field_event_timeslots_node';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
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

  /* Display: Entity Reference */
  $handler = $view->new_display('entityreference', 'Entity Reference', 'entityreference_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'name' => 'name',
    'date_label' => 'date_label',
    'item_id' => 0,
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'name' => 'name',
    'date_label' => 'date_label',
  );
  $handler->display->display_options['row_options']['separator'] = ' at ';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $export['cod_schedule_timeslot_widget'] = $view;

  return $export;
}
