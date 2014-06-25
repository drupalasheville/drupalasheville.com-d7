<?php
/**
 * @file
 * cod_session_pages.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function cod_session_pages_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'sessions';
  $page->task = 'page';
  $page->admin_title = 'Sessions';
  $page->admin_description = '';
  $page->path = 'node/%node/program/sessions';
  $page->access = array();
  $page->menu = array(
    'type' => 'tab',
    'title' => 'Sessions',
    'name' => 'navigation',
    'weight' => '0',
    'parent' => array(
      'type' => 'none',
      'title' => '',
      'name' => 'navigation',
      'weight' => '0',
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
  $handler->name = 'page_sessions_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'sessions';
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
  $display->layout = 'flexible';
  $display->layout_settings = array(
    'items' => array(
      'canvas' => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 'main',
          1 => 1,
        ),
        'parent' => NULL,
      ),
      'main' => array(
        'type' => 'column',
        'width' => '66.65375151243254',
        'width_type' => '%',
        'children' => array(
          0 => 'main-row',
        ),
        'parent' => 'canvas',
      ),
      'main-row' => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'center',
        ),
        'parent' => 'main',
      ),
      'center' => array(
        'type' => 'region',
        'title' => 'Center',
        'width' => 100,
        'width_type' => '%',
        'parent' => 'main-row',
      ),
      1 => array(
        'type' => 'column',
        'width' => '33.34624848756747',
        'width_type' => '%',
        'parent' => 'canvas',
        'children' => array(
          0 => 2,
        ),
        'class' => '',
      ),
      2 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'right_sidebar',
        ),
        'parent' => '1',
        'class' => '',
      ),
      'right_sidebar' => array(
        'type' => 'region',
        'title' => 'Right Sidebar',
        'width' => 100,
        'width_type' => '%',
        'parent' => '2',
        'class' => '',
      ),
    ),
  );
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'left' => NULL,
      'right' => NULL,
      'center' => NULL,
      'right_sidebar' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'Sessions';
  $display->uuid = '0eeda185-558c-46be-bee1-c6c1962556c5';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-6b94ff3f-2d4a-4452-b7ce-e90cda00f081';
    $pane->panel = 'center';
    $pane->type = 'block';
    $pane->subtype = 'quicktabs-sessions';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
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
    $pane->uuid = '6b94ff3f-2d4a-4452-b7ce-e90cda00f081';
    $display->content['new-6b94ff3f-2d4a-4452-b7ce-e90cda00f081'] = $pane;
    $display->panels['center'][0] = 'new-6b94ff3f-2d4a-4452-b7ce-e90cda00f081';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['sessions'] = $page;

  return $pages;

}
