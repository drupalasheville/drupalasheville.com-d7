<?php
/**
 * @file
 * cod_base.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function cod_base_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'admin_toolbar';
  $strongarm->value = array(
    'layout' => 'vertical',
    'position' => 'nw',
    'behavior' => 'df',
    'blocks' => array(
      'admin-create' => -1,
      'admin-theme' => 1,
      'admin-account' => -1,
      'system-management' => -1,
    ),
  );
  $export['admin_toolbar'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_date_no_time';
  $strongarm->value = 'D, j M Y';
  $export['date_format_date_no_time'] = $strongarm;

  return $export;
}
