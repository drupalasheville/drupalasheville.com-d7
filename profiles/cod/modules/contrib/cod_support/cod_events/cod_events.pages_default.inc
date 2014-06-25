<?php
/**
 * @file
 * cod_events.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function cod_events_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'event_dashboard';
  $page->task = 'page';
  $page->admin_title = 'Event dashboard';
  $page->admin_description = 'Event dashboard';
  $page->path = 'node/%node/event/dashboard';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'entity_bundle:node',
        'settings' => array(
          'type' => array(
            'event' => 'event',
          ),
        ),
        'context' => 'argument_entity_id:node_1',
        'not' => FALSE,
      ),
      1 => array(
        'name' => 'og_member',
        'settings' => array(
          'state' => array(
            1 => '1',
          ),
        ),
        'context' => array(
          0 => 'logged-in-user',
          1 => 'argument_entity_id:node_1',
        ),
        'not' => FALSE,
      ),
      2 => array(
        'name' => 'og_perm',
        'settings' => array(
          'perm' => 'administer group',
        ),
        'context' => array(
          0 => 'logged-in-user',
          1 => 'argument_entity_id:node_1',
        ),
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array(
    'type' => 'default tab',
    'title' => 'Dashboard',
    'name' => 'navigation',
    'weight' => '-10',
    'parent' => array(
      'type' => 'tab',
      'title' => 'Manage Event',
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
    'admin_paths' => TRUE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_event_dashboard_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'event_dashboard';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Landing Page',
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
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'Event Dashboard';
  $display->uuid = '821a4c89-fbc6-4667-8a31-96d416c6c40c';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-953eed62-a7ab-4e14-a3c3-6b54bc9268d6';
    $pane->panel = 'middle';
    $pane->type = 'views_panes';
    $pane->subtype = 'ticket_registration-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '953eed62-a7ab-4e14-a3c3-6b54bc9268d6';
    $display->content['new-953eed62-a7ab-4e14-a3c3-6b54bc9268d6'] = $pane;
    $display->panels['middle'][0] = 'new-953eed62-a7ab-4e14-a3c3-6b54bc9268d6';
    $pane = new stdClass();
    $pane->pid = 'new-b3bf5ce8-48dd-4abe-a06f-c73772de5965';
    $pane->panel = 'middle';
    $pane->type = 'views_panes';
    $pane->subtype = 'cod_sponsors_admin-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'b3bf5ce8-48dd-4abe-a06f-c73772de5965';
    $display->content['new-b3bf5ce8-48dd-4abe-a06f-c73772de5965'] = $pane;
    $display->panels['middle'][1] = 'new-b3bf5ce8-48dd-4abe-a06f-c73772de5965';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['event_dashboard'] = $page;

  return $pages;

}
