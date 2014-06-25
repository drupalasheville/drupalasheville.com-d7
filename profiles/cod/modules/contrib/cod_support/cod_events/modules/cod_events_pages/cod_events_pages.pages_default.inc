<?php
/**
 * @file
 * cod_events_pages.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function cod_events_pages_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'program';
  $page->task = 'page';
  $page->admin_title = 'Program';
  $page->admin_description = 'Program overview page';
  $page->path = 'node/%node/program/overview';
  $page->access = array();
  $page->menu = array(
    'type' => 'default tab',
    'title' => 'Overview',
    'name' => 'navigation',
    'weight' => '-10',
    'parent' => array(
      'type' => 'tab',
      'title' => 'Program',
      'name' => 'navigation',
      'weight' => '-9',
    ),
  );
  $page->arguments = array(
    'node' => array(
      'id' => 1,
      'identifier' => 'Event',
      'name' => 'entity_id:node',
      'settings' => array(),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_program_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'program';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'threecol_25_50_25';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'left' => NULL,
      'middle' => NULL,
      'right' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'cfbea808-9a6a-47e9-a1c1-0003c5f90ac0';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-c12ed458-8f73-478d-8451-922949e90a37';
    $pane->panel = 'left';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_event_program';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'text_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 1,
      'override_title_text' => 'Program',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'c12ed458-8f73-478d-8451-922949e90a37';
    $display->content['new-c12ed458-8f73-478d-8451-922949e90a37'] = $pane;
    $display->panels['left'][0] = 'new-c12ed458-8f73-478d-8451-922949e90a37';
    $pane = new stdClass();
    $pane->pid = 'new-d40f2c1e-f917-4670-a77a-bbc9786f5b32';
    $pane->panel = 'middle';
    $pane->type = 'views';
    $pane->subtype = 'cod_session_sessions';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 1,
      'nodes_per_page' => '20',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 1,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'page_1',
      'context' => array(
        0 => 'argument_entity_id:node_1.nid',
      ),
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'd40f2c1e-f917-4670-a77a-bbc9786f5b32';
    $display->content['new-d40f2c1e-f917-4670-a77a-bbc9786f5b32'] = $pane;
    $display->panels['middle'][0] = 'new-d40f2c1e-f917-4670-a77a-bbc9786f5b32';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = 'new-d40f2c1e-f917-4670-a77a-bbc9786f5b32';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['program'] = $page;

  return $pages;

}
