<?php
/**
 * @file
 * cod_bof.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cod_bof_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create bof_session content'.
  $permissions['create bof_session content'] = array(
    'name' => 'create bof_session content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any bof_session content'.
  $permissions['delete any bof_session content'] = array(
    'name' => 'delete any bof_session content',
    'roles' => array(
      'administrator' => 'administrator',
      'session organizer' => 'session organizer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own bof_session content'.
  $permissions['delete own bof_session content'] = array(
    'name' => 'delete own bof_session content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any bof_session content'.
  $permissions['edit any bof_session content'] = array(
    'name' => 'edit any bof_session content',
    'roles' => array(
      'administrator' => 'administrator',
      'session organizer' => 'session organizer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own bof_session content'.
  $permissions['edit own bof_session content'] = array(
    'name' => 'edit own bof_session content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
