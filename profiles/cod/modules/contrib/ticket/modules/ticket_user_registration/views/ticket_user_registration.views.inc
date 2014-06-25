<?php
/**
 * @file
 * Views include file.
 */

/**
 * Implements hook_views_default_views_alter().
 */
function ticket_user_registration_views_default_views_alter(&$views) {
  if (isset($views['ticket_user'])) {
    // Get the handler.
    $handler = & $views['ticket_user']->display['default']->handler;

    // Add the display style info.
    $handler->display->display_options['style_options']['columns']['name'] = 'name';
    $handler->display->display_options['style_options']['info']['name'] = array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    );

    // Add the data relationship.
    $handler->display->display_options['relationships']['user_uid']['id'] = 'user_uid';
    $handler->display->display_options['relationships']['user_uid']['table'] = 'ticket_registration';
    $handler->display->display_options['relationships']['user_uid']['field'] = 'user_uid';

    // Splice the field into the 3rd column.
    if ($fields = & $handler->display->display_options['fields']) {
      $fields = array_slice($fields, 0, 2, TRUE) +
        array(
          'name' => array(
            'id' => 'name',
            'table' => 'users',
            'field' => 'name',
            'relationship' => 'user_uid',
            'label' => 'Attendee',
          ),
        ) +
        array_slice($fields, 2);
    }
  }
}
