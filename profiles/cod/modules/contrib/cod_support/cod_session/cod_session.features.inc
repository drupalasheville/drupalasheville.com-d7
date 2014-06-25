<?php
/**
 * @file
 * cod_session.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cod_session_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "quicktabs" && $api == "quicktabs") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function cod_session_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_flag_default_flags().
 */
function cod_session_flag_default_flags() {
  $flags = array();
  // Exported flag: "Speaker confirmation flag".
  $flags['session_confirm'] = array(
    'entity_type' => 'node',
    'title' => 'Speaker confirmation flag',
    'global' => 0,
    'types' => array(
      0 => 'session',
    ),
    'flag_short' => 'I confirm that I can present this sesssion at the listed date and time.',
    'flag_long' => 'Once confirmed, you cannot unconfirm without contacting the session organizers.',
    'flag_message' => 'Thanks for confirming that you can present [node:title] at this date and time!',
    'unflag_short' => 'Cancel confirmation',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => 'You have confirmed that you will be presenting for this session.',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'teaser' => TRUE,
      'full' => TRUE,
    ),
    'show_as_field' => FALSE,
    'show_on_form' => 0,
    'access_author' => 'own',
    'show_contextual_link' => 0,
    'i18n' => 0,
    'module' => 'cod_session',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  // Exported flag: "Session Attending".
  $flags['session_schedule'] = array(
    'entity_type' => 'node',
    'title' => 'Session Attending',
    'global' => 0,
    'types' => array(
      0 => 'bof_session',
      1 => 'schedule_item',
      2 => 'session',
    ),
    'flag_short' => 'Add to my schedule',
    'flag_long' => 'Add this session to your personal session attendance.',
    'flag_message' => 'Session added',
    'unflag_short' => 'Remove from your schedule',
    'unflag_long' => 'Remove this session from your schedule',
    'unflag_message' => 'Session removed',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => TRUE,
    ),
    'show_as_field' => FALSE,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 0,
    'i18n' => 0,
    'module' => 'cod_session',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  // Exported flag: "Session Vote".
  $flags['session_vote'] = array(
    'entity_type' => 'node',
    'title' => 'Session Vote',
    'global' => 0,
    'types' => array(
      0 => 'session',
    ),
    'flag_short' => 'I\'d like to attend this session',
    'flag_long' => 'Express interest in this session',
    'flag_message' => 'Your vote has been recorded!',
    'unflag_short' => 'Retract interest in session',
    'unflag_long' => 'Retract your vote for this session.',
    'unflag_message' => 'Your vote has been retracted.',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(),
    'show_as_field' => FALSE,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 0,
    'i18n' => 0,
    'module' => 'cod_session',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  return $flags;

}

/**
 * Implements hook_node_info().
 */
function cod_session_node_info() {
  $items = array(
    'page' => array(
      'name' => t('Basic page'),
      'base' => 'node_content',
      'description' => t('Use <em>basic pages</em> for your static content, such as an \'About us\' page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'schedule_item' => array(
      'name' => t('Schedule Item'),
      'base' => 'node_content',
      'description' => t('Use schedule items for content you wish to have in the schedule but not be part of any session submission workflows. Examples include scheduling lunch or breaks.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'session' => array(
      'name' => t('Session'),
      'base' => 'node_content',
      'description' => t('Use this content type to propose sessions at the event. Users can vote on proposed sessions and add sessions to their individual session agendas.'),
      'has_title' => '1',
      'title_label' => t('Session Title'),
      'help' => '',
    ),
  );
  return $items;
}
