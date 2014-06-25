<?php

/**
 * @file
 * Admin page callbacks for the cod_schedule module.
 */

function cod_schedule_schedule_admin_page($node) {
  // Grab the days.
  $days = cod_schedule_days($node);
  if (empty($days)) {
    return t('Your event must have a start and end date.');
  }

  // Grab the Rooms attached to the event.
  $room_query = new EntityFieldQueryExtraFields();
  $rooms = $room_query->entityCondition('entity_type', 'cod_event_room')
    ->addExtraField('', 'name', 'name', 'cod_event_room')
    ->fieldCondition('og_group_ref', 'target_id', $node->nid)
    // TODO: Weight property isn't fully coded.
    // ->propertyOrderby('weight')
    ->execute();

  // Provide feedback to help administrators setup the site.
  if (empty($rooms)) {
    return t('You must add a room to view the schedule.');
  }

  // Create the table for each day.
  foreach ($days as $weight => $day) {
    $tz = new DateTimeZone($node->field_dates[LANGUAGE_NONE][0]['timezone']);
    $tz_db = new DateTimeZone($node->field_dates[LANGUAGE_NONE][0]['timezone_db']);

    $tz_time_db = new DateTime("now", $tz_db);
    $tz_time = new DateTime("now", $tz);

    // Get opposite of the offset.
    $offset = $tz->getOffset($tz_time_db) * -1;

    $day_start = strtotime($day . ' 00:00:00') + $offset;
    $day_end = strtotime('+1 day', $day_start);

    $time_query = new EntityFieldQueryExtraFields();
    $times = $time_query->entityCondition('entity_type', 'cod_event_time')
      ->addExtraField('', 'date_label', 'date_label', 'cod_event_time')
      ->fieldCondition('og_group_ref', 'target_id', $node->nid)
      ->fieldCondition('field_evttime_date', 'value', format_date($day_start, 'custom', 'Y-m-d H:i:s'), '>=')
      ->fieldCondition('field_evttime_date', 'value2', format_date($day_end, 'custom', 'Y-m-d H:i:s'), '<=')
      ->fieldOrderBy('field_evttime_date', 'value')
      ->execute();
    $header = array(t('Time'));
    $rows = array();

    if (isset($times['cod_event_time'])) {
      foreach ($times['cod_event_time'] as $evttid => $time) {
        $time_entity = entity_load('cod_event_time', array($evttid));
        $time_label = $time_entity[$evttid]->getTimeLabel();
        $time_edit_uri = 'admin/conference/times/manage/' . $evttid;
        $row = array(l($time_label, $time_edit_uri));

        foreach ($rooms['cod_event_room'] as $roomid => $room) {
          if (empty($rows)) {
            $room_label = $room->extraFields->name;
            $room_edit_uri = 'admin/conference/rooms/manage/' . $roomid;
            $header[] = l($room_label, $room_edit_uri);
          }

          $row[] = cod_schedule_schedule_grid_item($node, $evttid, $roomid);
        }
        $rows[] = $row;
      }
    }

    // Add help content to empty tabs.
    if (empty($rows)) {
      $contents =  t('Add a time to build a schedule for this day.');
    }
    else {
      $contents = theme('table', array('header' => $header, 'rows' => $rows));
    }

    $content_tabs[] = array(
      'title' => $day,
      'contents' => $contents,
      'weight' => $weight,
    );
  }

  ctools_include('modal');
  ctools_modal_add_js();
  $overrides = array('ajax' => 0, 'style' => 'Zen'); // Override some of the settings for the QT instance.
  $quicktabs = quicktabs_build_quicktabs('cod_schedule_schedule_builder', $overrides, $content_tabs);
  return drupal_render($quicktabs['content']);
}

/**
 * Helper function to generate a sceduler grid item.
 */
function cod_schedule_schedule_grid_item($event, $time, $room, $reset = FALSE) {
  $cid = 'cod_schedule:schedule_grid_item:' . $time . ':' . $room;
  $grid = cache_get($cid);

  if (!isset($grid->data) || $reset) {
    $items = array();
    if ($timeslot = cod_schedule_timeslot_load_by_info($time, $room)) {
      $op = 'edit';
      if (isset($timeslot->field_timeslot_allowed_types[LANGUAGE_NONE])) {
        foreach ($timeslot->field_timeslot_allowed_types[LANGUAGE_NONE] as $type) {
          $items[]['data'] = node_type_get_name($type['value']);
        }
      }
    }
    else {
      $op = 'add';
    }

    // Generate the appropriate link for this timeslot.
    $items[]['data'] = l(
      t('@op timeslot', array('@op' => ucwords($op))),
      'node/' . $event->nid . '/event/schedule/nojs/' . $op . '/' . $time .'/' . $room,
      array('attributes' => array('class' => 'ctools-use-modal'))
    );

    $data = theme('item_list',
      array(
        'items' => $items,
        'attributes' => array(
          'id' => 'cod-events-schedule-timeslot-' . $time . '-' . $room,
        ),
      )
    );

    cache_set($cid, $data);
    return $data;
  }

  return $grid->data;
}

/**
 * Form constructor for the COD session room form.
 */
function cod_event_room_form($form, &$form_state, CodEventRoom $cod_event_room, $op = 'update', $node = NULL) {
  $form_state['cod_event_room'] = $cod_event_room;
  if (!isset($form_state['wrapper_callback'])) {
    $form_state['wrapper_callback'] = 'entity_ui_main_form_defaults';
  }
  $form_state['entity_type'] = 'cod_event_room';
  $form_state['op'] = $op;

  if ($op == 'clone') {
    $cod_event_room->name .= ' (cloned)';
  }

  $form['name'] = array(
    '#title' => t('Room Name'),
    '#type' => 'textfield',
    '#default_value' => $cod_event_room->name,
    '#description' => t('Name of the room.'),
    '#required' => TRUE,
    '#size' => 30,
  );
  $form['capacity'] = array(
    '#title' => t('Capacity'),
    '#type' => 'textfield',
    '#default_value' => $cod_event_room->capacity,
    '#description' => t('Total person capacity of a room.'),
    '#required' => FALSE,
    '#size' => 5,
  );

  field_attach_form('cod_event_room', $cod_event_room, $form, $form_state);
  $submit = array();
  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save room'),
    '#submit' => $submit + array('cod_event_room_form_submit'),
    '#weight' => 40,
  );
  if (isset($node->nid)) {
    $form['actions']['submit']['#redirect'] = 'node/'.$node->nid.'/event/schedule';
  }
  $form['weight'] = array(
    '#type' => 'weight',
    '#title' => t('Weight'),
    '#default_value' => $cod_event_room->weight,
    '#description' => t('When showing rooms, those with lighter (smaller) weights get listed before rooms with heavier (larger) weights.'),
    '#weight' => 10,
  );
  if (!$cod_event_room->isLocked() && $op != 'add' && $op != 'clone') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete room'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('cod_event_room_form_submit_delete')
    );
  }

  return $form;
}

/**
 * Form API submit callback for the save button.
 */
function cod_event_room_form_submit(&$form, &$form_state) {
  $cod_event_room = entity_ui_form_submit_build_entity($form, $form_state);

  // Save and go back.
  $cod_event_room->save();
  if (isset($form_state['clicked_button']['#redirect'])) {
    $form_state['redirect'] = $form_state['clicked_button']['#redirect'];
  }
  else {
    $form_state['redirect'] = 'admin/conference/rooms';
  }

  drupal_set_message(t('The room %room was saved.', array('%room' => $cod_event_room->name)));
}

/**
* Form API submit callback for the delete button.
*/
function cod_event_room_form_submit_delete(&$form, &$form_state) {
  $evtrid = $form_state['cod_event_room']->evtrid;
  $form_state['redirect'] = "admin/conference/rooms/manage/$evtrid/delete";
}


/**
 * Form constructor for the COD session time form.
 */
function cod_event_time_form($form, &$form_state, CodEventTime $cod_event_time, $op = 'update', $node = NULL) {
  $form_state['cod_event_time'] = $cod_event_time;

  if (!isset($form_state['wrapper_callback'])) {
    $form_state['wrapper_callback'] = 'entity_ui_main_form_defaults';
  }
  $form_state['entity_type'] = 'cod_event_time';
  $form_state['op'] = $op;

  if ($op == 'clone') {
    $cod_event_time->date_label .= ' (cloned)';
  }

  $form['date_label'] = array(
    '#type' => 'value',
    '#value' => $cod_event_time->date_label,
  );

  field_attach_form('cod_event_time', $cod_event_time, $form, $form_state);
  if (isset($node->field_dates[LANGUAGE_NONE][0])) {
    //Set the default time to be closer to the event date.
    $form['field_evttime_date'][LANGUAGE_NONE][0]['#default_value']['value'] = $node->field_dates[LANGUAGE_NONE][0]['value'];
    $form['field_evttime_date'][LANGUAGE_NONE][0]['#default_value']['value2'] = $node->field_dates[LANGUAGE_NONE][0]['value']+3600;
    $form['field_evttime_date'][LANGUAGE_NONE][0]['timezone']['#type'] = 'value';
    $form['field_evttime_date'][LANGUAGE_NONE][0]['timezone']['#value'] = $node->field_dates[LANGUAGE_NONE][0]['timezone'];
  }

  $submit = array();
  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save time'),
    '#submit' => $submit + array('cod_event_time_form_submit'),
    '#weight' => 40,
  );
  if (isset($node->nid)) {
    $form['actions']['submit']['#redirect'] = 'node/'.$node->nid.'/event/schedule';
  }

  if (!$cod_event_time->isLocked() && $op != 'add' && $op != 'clone') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete time'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('cod_event_time_form_submit_delete')
    );
  }

  return $form;
}


/**
 * Form API submit callback for the save button.
 */
function cod_event_time_form_submit(&$form, &$form_state) {
  $cod_event_time = entity_ui_form_submit_build_entity($form, $form_state);

  // Save and go back.
  $cod_event_time->save();
  if (isset($form_state['clicked_button']['#redirect'])) {
    $form_state['redirect'] = $form_state['clicked_button']['#redirect'];
  }
  else {
    $form_state['redirect'] = 'admin/conference/times';
  }
}

/**
* Form API submit callback for the delete button.
*/
function cod_event_time_form_submit_delete(&$form, &$form_state) {
  $evttid = $form_state['cod_event_time']->evttid;
  $form_state['redirect'] = "admin/conference/times/manage/$evttid/delete";
}

// --------------------------------------------------------------------------
// Various subforms for editing the pieces of a view.
//NODEID/event/schedule/nojs/OPERATION/TIMEID/ROOMID
function cod_schedule_schedule_forms($key = NULL) {
  $forms = array(
    'edit' => array(
      'form_id' => 'cod_schedule_schedule_timeslot_form',
      'args' => array('fcid'),
    ),
    'add' => array(
      'form_id' => 'cod_schedule_add_form',
      'args' => array('nid', 'timeid', 'roomid'),
    ),
    'assign' => array(
      'form_id' => 'cod_schedule_timeslot_form',
      'args' => array('nid', 'fcid'),
    ),
  );

  if ($key) {
    return !empty($forms[$key]) ? $forms[$key] : NULL;
  }

  return $forms;
}

/**
 * COD Events modal form popup.
 */
function cod_schedule_schedule_timeslot_callback($js, $event, $key, $time, $room) {
  $field_name = 'field_event_timeslots';

  // Load the timeslot or stub a new one.
  if (!$timeslot = cod_schedule_timeslot_load_by_info($time, $room)) {
    $timeslot = cod_schedule_field_collection_item_add(str_replace('-', '_', $field_name), 'node', $event->nid, $time, $room);
    if (!is_object($timeslot) && ($timeslot == MENU_NOT_FOUND || $timeslot == MENU_ACCESS_DENIED)) {
      drupal_exit();
    }
  }

  // Check if js is enabled, this parameter will be loaded by ctools.
  if ($js) {
    module_load_include('inc', 'field_collection', 'field_collection.pages');
    // Include ctools ajax and modal, dont forget to set ajax TRUE.
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
      'title' => t('Scheduleable items'),
      'build_info' => array(
        'args' => array($timeslot),
      ),
    );

    // Arguments need to be loaded directly onto the build_info args array
    // because ctools_modal_form_wrapper will call drupal_build_form()
    // directly see from API for more.
    // The modal form wrapper is needed to make sure the form will allow
    // validating, you cannot use drupal_get_form directly it wont work.
    if ($key == 'add' || $key == 'edit') {
      $output = ctools_modal_form_wrapper('field_collection_item_form', $form_state);
    }
    elseif ($key == 'delete') {
      $output = ctools_modal_form_wrapper('field_collection_item_delete_confirm', $form_state);
    }
    else {
      drupal_exit();
    }

    // If the form is executed will need to dismiss the form and reload the page.
    if ($form_state['executed']) {
      $commands = array();

      // Set the updated schedule item and close the ctools modal.
      $commands[] = ajax_command_replace('#cod-events-schedule-timeslot-' . $time . '-' . $room, cod_schedule_schedule_grid_item($event, $time, $room, TRUE));
      $commands[] = ctools_modal_command_dismiss();

      $output = $commands;
    }

    // Render the output.
    print ajax_render($output);
    drupal_exit();
  }
  else {
    // No js found lets go to the default page.
    return drupal_get_form('field_collection_item_form', $timeslot);
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function cod_schedule_form_field_collection_item_form_alter(&$form, &$form_state) {
  if (isset($form_state['field_collection_item']->field_timeslot_time)) {
    $form['field_timeslot_time'][LANGUAGE_NONE][0]['#default_value'] = $form_state['field_collection_item']->field_timeslot_time;
    $form['field_timeslot_time']['#access'] = FALSE;
  }
  if (isset($form_state['field_collection_item']->field_timeslot_room)) {
    $form['field_timeslot_room'][LANGUAGE_NONE][0]['#default_value'] = $form_state['field_collection_item']->field_timeslot_room;
    $form['field_timeslot_room']['#access'] = FALSE;
  }
}

/**
 * Add a new field-collection item.
 *
 * We copied this function from the field collection module but instead of returning a form we return the object
 */
function cod_schedule_field_collection_item_add($field_name, $entity_type, $entity_id, $time, $room, $revision_id = NULL, $langcode = NULL) {
  $info = entity_get_info();
  if (!isset($info[$entity_type])) {
    return MENU_NOT_FOUND;
  }
  $result = entity_load($entity_type, array($entity_id));

  $entity = reset($result);

  if (!$entity) {
    return MENU_NOT_FOUND;
  }
  // Ensure the given entity is of a bundle that has an instance of the field.
  list($id, $rev_id, $bundle) = entity_extract_ids($entity_type, $entity);
  $instance = field_info_instance($entity_type, $field_name, $bundle);

  if (!$instance) {
    return MENU_NOT_FOUND;
  }

  // Check field cardinality.
  $field = field_info_field($field_name);
  $langcode = LANGUAGE_NONE;
  if (!($field['cardinality'] == FIELD_CARDINALITY_UNLIMITED || !isset($entity->{$field_name}[$langcode]) || count($entity->{$field_name}[$langcode]) < $field['cardinality'])) {
    drupal_set_message(t('Too many items.'), 'error');
    return '';
  }

  $title = ($field['cardinality'] == 1) ? $instance['label'] : t('Add new !instance_label', array('!instance_label' => drupal_strtolower($instance['label'])));

  drupal_set_title($title);

  $stub = array(
    'field_name' => $field_name,
    'field_timeslot_time' => array(LANGUAGE_NONE => array(array('target_id' => $time))),
    'field_timeslot_room' => array(LANGUAGE_NONE => array(array('target_id' => $room))),
  );

  $field_collection_item = entity_create('field_collection_item', $stub);
  // Do not link the field-collection item with the host entity at this point,
  // as during the form-workflow we have multiple field-collection item entity
  // instances, which we don't want link all with the host.
  // That way the link is going to be created when the item is saved.
  $field_collection_item->setHostEntity($entity_type, $entity, LANGUAGE_NONE, FALSE);
  // Make sure the current user has access to create a field collection item.
  if (!field_collection_item_access('create', $field_collection_item)) {
    return MENU_ACCESS_DENIED;
  }

  return $field_collection_item;
}

/**
 * Generic entry point to handle forms.
 *
 * We do this for consistency and to make it easy to chain forms
 * together.
 */
/*
// TODO: Is this function needed or called from anywhere? it appears to be a dupe of cod_schedule_schedule_timeslot_callback().
function cod_schedule_schedule_form($js, $event, $key, $time, $room) {
  // Reset the cache of IDs. Drupal rather aggressively prevents id duplication
  // but this causes it to remember IDs that are no longer even being used.
  if (isset($_POST['ajax_html_ids'])) {
    unset($_POST['ajax_html_ids']);
  }

  $form = cod_schedule_schedule_ajax_forms($key);
  if (empty($form)) {
    return MENU_NOT_FOUND;
  }

  ctools_include('ajax');
  ctools_include('modal');

  ctools_modal_render( 'Error', 'Error Message');

  $args = func_get_args();
  // Remove the known args
  array_splice($args, 0, 4);

  $form_state = views_ui_build_form_state($js, $key, $view, $display_id, $args);
  // check to see if this is the top form of the stack. If it is, pop
  // it off; if it isn't, the user clicked somewhere else and the stack is
  // now irrelevant.
  if (!empty($view->stack)) {
    $identifier = views_ui_build_identifier($key, $view, $display_id, $args);
    // Retrieve the first form from the stack without changing the integer keys,
    // as they're being used for the "2 of 3" progress indicator.
    reset($view->stack);
    list($key, $top) = each($view->stack);
    unset($view->stack[$key]);

    if (array_shift($top) != $identifier) {
      $view->stack = array();
    }
  }

  // Automatically remove the form cache if it is set and the key does
  // not match. This way navigating away from the form without hitting
  // update will work.
  if (isset($view->form_cache) && $view->form_cache['key'] != $key) {
    unset($view->form_cache);
  }

  // With the below logic, we may end up rendering a form twice (or two forms
  // each sharing the same element ids), potentially resulting in
  // drupal_add_js() being called twice to add the same setting. drupal_get_js()
  // is ok with that, but until ajax_render() is (http://drupal.org/node/208611),
  // reset the drupal_add_js() static before rendering the second time.
  $drupal_add_js_original = drupal_add_js();
  $drupal_add_js = &drupal_static('drupal_add_js');
  $output = views_ajax_form_wrapper($form_state['form_id'], $form_state);
  if ($form_state['submitted'] && empty($form_state['rerender'])) {
    // Sometimes we need to re-generate the form for multi-step type operations.
    $object = NULL;
    if (!empty($view->stack)) {
      $drupal_add_js = $drupal_add_js_original;
      $stack = $view->stack;
      $top = array_shift($stack);
      $top[0] = $js;
      $form_state = call_user_func_array('views_ui_build_form_state', $top);
      $form_state['input'] = array();
      $form_state['url'] = url(views_ui_build_form_url($form_state));
      if (!$js) {
        return drupal_goto(views_ui_build_form_url($form_state));
      }
      $output = views_ajax_form_wrapper($form_state['form_id'], $form_state);
    }
    elseif (!$js) {
      // if nothing on the stack, non-js forms just go back to the main view editor.
      return drupal_goto("admin/structure/views/view/$view->name/edit");
    }
    else {
      $output = array();
      $output[] = views_ajax_command_dismiss_form();
      $output[] = views_ajax_command_show_buttons();
      $output[] = views_ajax_command_trigger_preview();
      if (!empty($form_state['#page_title'])) {
        $output[] = views_ajax_command_replace_title($form_state['#page_title']);
      }
    }
    // If this form was for view-wide changes, there's no need to regenerate
    // the display section of the form.
    if ($display_id !== '') {
      views_ui_regenerate_tab($view, $output, $display_id);
    }
  }

  return $js ? array('#type' => 'ajax', '#commands' => $output) : $output;
}
*/
