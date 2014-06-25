<?php
/**
 * @file
 * cod_community.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cod_community_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer contact forms'.
  $permissions['administer contact forms'] = array(
    'name' => 'administer contact forms',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'contact',
  );

  return $permissions;
}
