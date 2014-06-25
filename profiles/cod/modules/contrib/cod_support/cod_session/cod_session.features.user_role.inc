<?php
/**
 * @file
 * cod_session.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function cod_session_user_default_roles() {
  $roles = array();

  // Exported role: session organizer.
  $roles['session organizer'] = array(
    'name' => 'session organizer',
    'weight' => 3,
  );

  return $roles;
}
