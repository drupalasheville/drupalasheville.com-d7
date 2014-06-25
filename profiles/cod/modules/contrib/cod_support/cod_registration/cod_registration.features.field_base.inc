<?php
/**
 * @file
 * cod_registration.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function cod_registration_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_event_tickets'
  $field_bases['field_event_tickets'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_event_tickets',
    'field_permissions' => array(
      'type' => 0,
    ),
    'foreign keys' => array(
      'ttid' => array(
        'columns' => array(
          'value' => 'ttid',
        ),
        'table' => 'ticket_type',
      ),
    ),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'ticket',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'ticket_type',
  );

  return $field_bases;
}
