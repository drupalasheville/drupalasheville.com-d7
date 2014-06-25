<?php
/**
 * @file
 * cod_session_evaluations.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cod_session_evaluations_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function cod_session_evaluations_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function cod_session_evaluations_node_info() {
  $items = array(
    'session_evaluation' => array(
      'name' => t('Session evaluation'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
