<?php
/**
 * @file
 * cod_session.quicktabs.inc
 */

/**
 * Implements hook_quicktabs_default_quicktabs().
 */
function cod_session_quicktabs_default_quicktabs() {
  $export = array();

  $quicktabs = new stdClass();
  $quicktabs->disabled = FALSE; /* Edit this to true to make a default quicktabs disabled initially */
  $quicktabs->api_version = 1;
  $quicktabs->machine_name = 'sessions';
  $quicktabs->ajax = 1;
  $quicktabs->hide_empty_tabs = FALSE;
  $quicktabs->default_tab = 999999;
  $quicktabs->title = 'Sessions';
  $quicktabs->tabs = array(
    0 => array(
      'vid' => 'cod_session_sessions',
      'display' => 'block_sessions',
      'args' => '%1/0+2',
      'title' => 'Proposed',
      'weight' => '-100',
      'type' => 'view',
    ),
    1 => array(
      'vid' => 'cod_session_sessions',
      'display' => 'block_sessions',
      'args' => '%1/1',
      'title' => 'Accepted',
      'weight' => '-99',
      'type' => 'view',
    ),
  );
  $quicktabs->renderer = 'quicktabs';
  $quicktabs->style = 'Zen';
  $quicktabs->options = array();

  // Translatables
  // Included for use with string extractors like potx.
  t('Accepted');
  t('Proposed');
  t('Sessions');

  $export['sessions'] = $quicktabs;

  return $export;
}
