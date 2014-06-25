<?php
/**
 * @file
 * cod_bof.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cod_bof_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function cod_bof_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function cod_bof_node_info() {
  $items = array(
    'bof_session' => array(
      'name' => t('BoF Session'),
      'base' => 'node_content',
      'description' => t('A BoF, or birds-of-a-feather, is an informal session that is self-scheduled.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
