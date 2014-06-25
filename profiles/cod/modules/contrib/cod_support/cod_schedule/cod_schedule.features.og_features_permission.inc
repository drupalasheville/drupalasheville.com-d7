<?php
/**
 * @file
 * cod_schedule.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function cod_schedule_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:event:administer cod_event_room'
  $permissions['node:event:administer cod_event_room'] = array(
    'roles' => array(
      'session organizer' => 'session organizer',
    ),
  );

  // Exported og permission: 'node:event:administer cod_event_time'
  $permissions['node:event:administer cod_event_time'] = array(
    'roles' => array(
      'session organizer' => 'session organizer',
    ),
  );

  // Exported og permission: 'node:event:create cod_event_room'
  $permissions['node:event:create cod_event_room'] = array(
    'roles' => array(
      'session organizer' => 'session organizer',
    ),
  );

  // Exported og permission: 'node:event:create cod_event_time'
  $permissions['node:event:create cod_event_time'] = array(
    'roles' => array(
      'session organizer' => 'session organizer',
    ),
  );

  // Exported og permission: 'node:event:edit any cod_event_room'
  $permissions['node:event:edit any cod_event_room'] = array(
    'roles' => array(
      'session organizer' => 'session organizer',
    ),
  );

  // Exported og permission: 'node:event:edit any cod_event_time'
  $permissions['node:event:edit any cod_event_time'] = array(
    'roles' => array(
      'session organizer' => 'session organizer',
    ),
  );

  // Exported og permission: 'node:event:edit own cod_event_room'
  $permissions['node:event:edit own cod_event_room'] = array(
    'roles' => array(
      'session organizer' => 'session organizer',
    ),
  );

  // Exported og permission: 'node:event:edit own cod_event_time'
  $permissions['node:event:edit own cod_event_time'] = array(
    'roles' => array(
      'session organizer' => 'session organizer',
    ),
  );

  // Exported og permission: 'node:event:view cod_event_room'
  $permissions['node:event:view cod_event_room'] = array(
    'roles' => array(
      'session organizer' => 'session organizer',
    ),
  );

  // Exported og permission: 'node:event:view cod_event_time'
  $permissions['node:event:view cod_event_time'] = array(
    'roles' => array(
      'session organizer' => 'session organizer',
    ),
  );

  return $permissions;
}
