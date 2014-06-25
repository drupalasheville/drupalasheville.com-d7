<?php
/**
 * @file
 * cod_sponsors.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function cod_sponsors_user_default_roles() {
  $roles = array();

  // Exported role: sponsor organizer.
  $roles['sponsor organizer'] = array(
    'name' => 'sponsor organizer',
    'weight' => 3,
  );

  return $roles;
}
