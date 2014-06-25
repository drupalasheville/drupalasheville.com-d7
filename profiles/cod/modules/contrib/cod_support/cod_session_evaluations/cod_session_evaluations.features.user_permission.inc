<?php
/**
 * @file
 * cod_session_evaluations.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cod_session_evaluations_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create session_evaluation content'.
  $permissions['create session_evaluation content'] = array(
    'name' => 'create session_evaluation content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
