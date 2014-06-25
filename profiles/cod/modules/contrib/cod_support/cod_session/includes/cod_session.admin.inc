<?php

/**
 * @file
 * Admin page callbacks for the cod_session module.
 */
function cod_session_admin_page($event) {

  // Generate the appropriate link for this timeslot.
  $content = l(
    t('Session Tracks Overview'),
    'admin/structure/taxonomy/session_tracks_'. $event->nid,
    array('query' => array('destination' => 'node/'.$event->nid.'/event/sessions'))
  );

  $form = drupal_get_form('cod_session_details_form', $event);
  $content .= drupal_render($form);

  $field = field_info_field('field_accepted');
  $allowed_values = list_allowed_values($field);

  $content_tabs = array();
  foreach ($allowed_values AS $key => $status) {
    $content_tabs[] = array(
      'title' => $status,
      'contents' => views_embed_view('cod_session_sessions_admin', 'page_1', $event->nid, $key),
      'weight' => $key,
    );
  }
  // Add the Scheduled tab
  $content_tabs[] = array(
    'title' => t('Scheduled'),
    'contents' => views_embed_view('cod_session_sessions_admin', 'page_4', $event->nid),
    'weight' => 10,
  );

  $overrides = array('ajax' => 1, 'style' => 'Zen'); // Override some of the settings for the QT instance.
  $quicktabs = quicktabs_build_quicktabs('cod_session_sessions_builder', $overrides, $content_tabs);
  $content .= drupal_render($quicktabs['content']);

  return $content;
}