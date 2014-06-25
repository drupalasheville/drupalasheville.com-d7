<?php
/**
 * @file
 * cod_events.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function cod_events_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:event:add user'
  $permissions['node:event:add user'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:event:administer group'
  $permissions['node:event:administer group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:event:approve and deny subscription'
  $permissions['node:event:approve and deny subscription'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:event:manage members'
  $permissions['node:event:manage members'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:event:manage permissions'
  $permissions['node:event:manage permissions'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:event:manage roles'
  $permissions['node:event:manage roles'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:event:subscribe'
  $permissions['node:event:subscribe'] = array(
    'roles' => array(
      'non-member' => 'non-member',
    ),
  );

  // Exported og permission: 'node:event:subscribe without approval'
  $permissions['node:event:subscribe without approval'] = array(
    'roles' => array(
      'non-member' => 'non-member',
    ),
  );

  // Exported og permission: 'node:event:unsubscribe'
  $permissions['node:event:unsubscribe'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:event:update group'
  $permissions['node:event:update group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  return $permissions;
}
