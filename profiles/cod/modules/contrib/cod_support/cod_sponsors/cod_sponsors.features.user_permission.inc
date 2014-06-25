<?php
/**
 * @file
 * cod_sponsors.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cod_sponsors_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create sponsor content'.
  $permissions['create sponsor content'] = array(
    'name' => 'create sponsor content',
    'roles' => array(
      'administrator' => 'administrator',
      'sponsor organizer' => 'sponsor organizer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any sponsor content'.
  $permissions['delete any sponsor content'] = array(
    'name' => 'delete any sponsor content',
    'roles' => array(
      'administrator' => 'administrator',
      'sponsor organizer' => 'sponsor organizer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any sponsor content'.
  $permissions['edit any sponsor content'] = array(
    'name' => 'edit any sponsor content',
    'roles' => array(
      'administrator' => 'administrator',
      'sponsor organizer' => 'sponsor organizer',
    ),
    'module' => 'node',
  );

  return $permissions;
}
