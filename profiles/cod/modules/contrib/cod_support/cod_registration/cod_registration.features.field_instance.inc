<?php
/**
 * @file
 * cod_registration.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function cod_registration_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-event-field_event_tickets'
  $field_instances['node-event-field_event_tickets'] = array(
    'bundle' => 'event',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'ticket',
        'settings' => array(
          'show_unavailable' => 0,
          'submit_text' => 'Register',
        ),
        'type' => 'ticket_type',
        'weight' => 9,
      ),
      'listing' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_event_tickets',
    'label' => 'Tickets',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'ticket',
      'settings' => array(),
      'type' => 'ticket_type',
      'weight' => 10,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Tickets');

  return $field_instances;
}
