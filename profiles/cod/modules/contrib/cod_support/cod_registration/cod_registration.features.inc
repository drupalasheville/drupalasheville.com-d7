<?php
/**
 * @file
 * cod_registration.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cod_registration_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function cod_registration_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_ticket_state().
 */
function cod_registration_default_ticket_state() {
  $items = array();
  $items['cancelled'] = entity_import('ticket_state', '{
    "label" : "Cancelled",
    "name" : "cancelled",
    "description" : "People who\\u0027ve cancelled",
    "weight" : "0",
    "active" : "0",
    "bundle" : "ticket_state"
  }');
  $items['checked_in'] = entity_import('ticket_state', '{
    "label" : "Checked-In",
    "name" : "checked_in",
    "description" : "Registered users who\\u0027ve checked-in.",
    "weight" : "0",
    "active" : "0",
    "bundle" : "ticket_state"
  }');
  $items['completed'] = entity_import('ticket_state', '{
    "label" : "Completed",
    "name" : "completed",
    "description" : "Completed Registrations",
    "weight" : "-9",
    "active" : "0",
    "bundle" : "ticket_state"
  }');
  $items['pending'] = entity_import('ticket_state', '{
    "label" : "Pending",
    "name" : "pending",
    "description" : "Registrations that are pending",
    "weight" : "-10",
    "active" : "1",
    "bundle" : "ticket_state"
  }');
  return $items;
}
