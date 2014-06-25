<?php

function cod_events_views_pre_render(&$view) {
  if($view->name == 'cod_events_admin' && $default_event = variable_get('cod_events_default_event', 0)) {
    foreach($view->result AS $rid => $row) {
      if($row->nid == $default_event) {
        $view->result[$rid]->node_title = t('!event (default event)', array('!event' => $view->result[$rid]->node_title));
      }
    }
  }
}

/**
 * Implements hook_views_plugins().
 * TODO: Create a default
 */
function cod_events_views_plugins() {
  return array(
    'argument default' => array(
      'cod_events_default_event' => array(
        'title' => t("Default event"),
        'handler' => 'cod_events_plugin_argument_default_event',
        'path' => drupal_get_path('module', 'cod_events') . '/includes/views/handlers'
      ),
      'cod_events_default_type' => array(
        'title' => t("Default Content Type"),
        'handler' => 'cod_events_plugin_argument_default_type',
        'path' => drupal_get_path('module', 'cod_events') . '/includes/views/handlers'
      ),
    ),
  );
}
