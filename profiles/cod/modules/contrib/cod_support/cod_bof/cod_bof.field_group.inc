<?php
/**
 * @file
 * cod_bof.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function cod_bof_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_bof_schedule|node|bof_session|form';
  $field_group->group_name = 'group_bof_schedule';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'bof_session';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Schedule Info',
    'weight' => '2',
    'children' => array(
      0 => 'field_session_timeslot',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Schedule Info',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_bof_schedule|node|bof_session|form'] = $field_group;

  return $export;
}
