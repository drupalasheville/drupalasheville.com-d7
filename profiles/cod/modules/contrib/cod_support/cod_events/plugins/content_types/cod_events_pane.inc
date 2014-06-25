<?php
/**
* This plugin array is more or less self documenting
*/
$plugin = array(
  // the title in the admin
  'title' => t('Event Allowed Types Pane'),
  // no one knows if "single" defaults to FALSE...
  'single' => TRUE,
  // oh joy, I get my own section of panel panes
  'category' => array(t('Conference Organizing'), -9),
  //'edit form' => 'cod_events_pane_content_type_edit_form',
  'render callback' => 'cod_events_pane_content_type_render'
);


/**
* Run-time rendering of the body of the block (content type)
* See ctools_plugin_examples for more advanced info
*/
function cod_events_pane_content_type_render($subtype, $conf, $context = NULL) {
  // our output is generate by js. Any markup or theme functions
  // could go here.
  // that private js function is so bad that fixing it will be the
  // basis of the next tutorial
  $block->title = t('Room/Timeslot Scheduler');

  if($node = node_load(array_shift($context))) {
    $block->content = cod_events_timeslots_page($node);
  } else {
    $block->content = t('Invalid Event Type');
  }
  return $block;
}


/**
* 'Edit form' callback for the content type.

function cod_events_pane_content_type_edit_form(&$form, &$form_state) {
  $conf = $form_state['conf'];
  $form['twitter_username'] = array(
    '#type' => 'textfield',
    '#title' => t('twitter username'),
    '#size' => 50,
    '#description' => t('A valid twitter username.'),
    '#default_value' => !empty($conf['twitter_username']) ? $conf['twitter_username'] : 'nicklewisatx',
  );
  // no submit
  return $form;
}
*/

/**
* Submit function, note anything in the formstate[conf] automatically gets saved

function cod_events_pane_content_type_edit_form_submit(&$form, &$form_state) {
  $form_state['conf']['twitter_username'] = $form_state['values']['twitter_username'];
}
*/

/* this file works on the global scheduling system, which populates the field collection within the room CT.
 * its needed for allocating what timeslots/room combos are allowed to host what
 * This file is self_contained for the most part, and probably could use cleanup/merging with the session module
 * to consolidating helper functions.
 */

function cod_events_timeslots_page($event) {
  //put quicktabs here
  $days = cod_events_days($event->nid);
  if (!empty($days)) {
    $tabs = array();
    $weight = 0;
    foreach($days AS $day_format => $day) {
      $date = new DateObject($day_format, NULL, 'l F, d Y');
      if(count($days) == 1) {
        return drupal_get_form('cod_events_timeslots_form', $event, date_format_date($date, 'custom', 'Y-m-d'));
      }
      $tabs[date_format_date($date, 'custom', 'Y-m-d')] = array(
        'title' => date_format_date($date, 'custom', 'l F, d Y'),
        'contents' => drupal_get_form('cod_events_timeslots_'.$day.'_form', $event, date_format_date($date, 'custom', 'Y-m-d')),
        'weight' => $weight,
      );
      if(!isset($default_tab))
        $default_tab = date_format_date($date, 'custom', 'Y-m-d');

      $weight++;
    }
    $qtname = 'cod_events_timeslots';
    $qtoptions = array(
      'style' => 'basic',
      'ajax' => 0,
      'default_tab' => $default_tab,
    );
    return quicktabs_build_quicktabs($qtname, $qtoptions, $tabs);
  }
  else {
    return 'Please create timeslots first';
  }
}

/**
 * Custom schedule form.
 * This will build a schedule grid where you can select which rooms should have what items in it
 * Basically this is an empty theme callback that renders the children. When someone wants to take on theming, they can do it here
 */
function theme_cod_events_timeslots_form($variables) {

  // Isolate the form definition form the $variables array
  $form = $variables['form'];
  $output = '';
  // Pass the remaining form elements through drupal_render_children()
  $output .= drupal_render_children($form);
  // return the output
  return $output;

}

/*
 * The main form shown to users wishing to make the master schedule grid. This loops through rooms and timeslots, showing the user
 * rendered form elements from the field_collection field info.
 */
function cod_events_timeslots_form($form, &$form_state, $event, $day) {
  $days = cod_events_days($event->nid);
  // TODO: Workaround for the default schedule page, lets just redirect to the first day. Someday make this a listing page instead. See cod_session.module for details
  $form['instructions']['#markup'] = t('This form allows you to specify which
    kinds of schedulable items may be scheduled in each room during a particular timeslot.');

  // For single day events:
  if ($day == 'timeslots') {
    foreach($days AS $day_format => $day) {
      $date = new DateObject($day_format, NULL, 'l F, d Y');
      $day =  date_format_date($date, 'custom', 'Y-m-d');
    }
  }

  $time_slots = _cod_session_get_timeslots($day, $event->nid);
  $room_slots = _cod_session_get_rooms($event->nid);

  //this stores the room form elements
  $room_array = array();

  //iterate through the timeslots and generate forms for each room
  foreach($time_slots AS $time_slot) {
    $time_slot = node_load($time_slot->nid);

    $form[$time_slot->nid] = array(
      '#type' => 'fieldset',
      '#title' => t('Timeslot: @time_slot-title', array('@time_slot-title' => $time_slot->title)),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
    );

    //Don't want this to be called every time within the foreach, so lets set it here.
    $slot_types_field = field_info_field('field_slot_types_allowed');

    //Loop through each room slot and give us ths slot_types allowed and capacity.
    foreach($room_slots AS $room) {
      $room = node_load($room->nid);
      $key = cod_events_get_collection_entity($room->nid, $time_slot->nid, $event->nid) ? cod_events_get_collection_entity ($room->nid, $time_slot->nid, $event->nid) :  $room->nid .'-'. $time_slot->nid;
      $form[$time_slot->nid][$key.'_room_name'] = array(
        '#markup' => t('Room: @room-title', array('@room-title' => $room->title)),
      );
      $form[$time_slot->nid][$room->nid][$key.'-field_slot_types_allowed'] = array(
        '#title' => t('Allowed types'),
        '#type' => 'checkboxes',
        '#options' => $slot_types_field['settings']['allowed_values'],
        '#default_value' => _cod_session_get_room_slots_types_allowed($room->nid, $time_slot->nid, $event->nid),
        '#required' => FALSE,
        '#multiple' => TRUE,
      );
      $form[$time_slot->nid][$room->nid][$key.'-field_slot_types_capacity'] = array(
        '#title' => t('Room Capacity'),
        '#type' => 'textfield',
        '#maxlength' => 4,
        '#size' => 4,
        '#default_value' => _cod_session_get_room_slots_types_capacity($room->nid, $time_slot->nid, $event->nid),
        '#required' => FALSE,
        '#description' => t('The maximum number of simultaneous sessions of all types that are permitted in %room-title during the timeslot %time_slot_title.', array('%room-title' => $room->title, '%time_slot_title' => $time_slot->title)),
      );
    }
  }
  $form['event_id'] = array(
    '#type' => 'value',
    '#value' => $event->nid,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Confirm this time slot for day ' . $day),
  );
  //custom submit functions for some sanity checking. Probably could use some more sanity
  //nothing we really need to validate at this point
  $form['#submit'][] = 'cod_events_timeslots_form_submit';
  //todo: add a redirect so the ajax tab ends up in the same place

  return $form;

}

/**
 * Submit handler for scheduling form.
 */
function cod_events_timeslots_form_submit($form, $form_state) {
  module_load_include('inc', 'node', 'node.pages');
  //grab our key again
  //parse the form to see if its an entity already or if we need to create it
  foreach($form_state['complete form'] AS $time_nid => $element) {
    if(is_array($element) && is_numeric($time_nid)) { //we have a nid array
     foreach($element AS $room_nid => $fields) {
       if(is_array($fields) && is_numeric($room_nid)) { //we have a nid array
       $entity = FALSE;
       $key = '';
       //error_log(print_r($form_state['values'],true));
       if(cod_events_get_collection_entity($room_nid, $time_nid, $form_state['values']['event_id'])) {
         $key = cod_events_get_collection_entity($room_nid, $time_nid, $form_state['values']['event_id']);
         $entity = TRUE;
       }
       else {
         $key = $room_nid .'-'. $time_nid;
       }

       //check to see if the fields are set, that means this array is the correct one we're looking for
       if(is_numeric($room_nid) && isset($fields[$key.'-field_slot_types_allowed']) && isset($fields[$key.'-field_slot_types_capacity'])) {
         //check for empty values
          if(empty($fields[$key.'-field_slot_types_allowed']['#value'])) {
            //if the entity already exists, we don't want to destroy it, rather we want to unset the keys.
            //By doing this, the form will override the default values supplied by the field collection.
            if($entity == TRUE) {
              $field_collection_item = field_collection_item_load($key); // Load that field collection item.
              $field_collection_item->field_slot_types_allowed = array();
              $field_collection_item->field_slot_types_capacity = array();
              $field_collection_item->save(); // Save field-collection item.
              continue;
            }
            else {
              continue;
            }
          }
          $node = node_load($room_nid);
          //we have good data, and its been saved before (entity exists) lets resave it
          if($entity == TRUE) {
            // Get field collection item value.
            $field_collection_item = field_collection_item_load($key); // Load that field collection item.
            //unset the old values, otherwise the data won't save properly.
            $field_collection_item->field_slot_types_allowed = array();
            $field_collection_item->field_slot_types_capacity = array();
            $delta = 0;
            foreach($fields[$key.'-field_slot_types_allowed']['#value'] AS $element) {
              $field_collection_item->field_slot_types_allowed[LANGUAGE_NONE][$delta]['value'] = $element;
              $delta++;
            }
            $field_collection_item->field_slot_types_capacity[LANGUAGE_NONE][0]['value'] = $fields[$key.'-field_slot_types_capacity']['#value'] ? $fields[$key.'-field_slot_types_capacity']['#value'] : 1;
            $field_collection_item->save(); // Save field-collection item.
          }

          else {
            $values = array();
            $values['field_name'] = 'field_room_slots_types_allowed';
            $values['field_slot_types_time_slot'][LANGUAGE_NONE][0]['target_id'] = $time_nid;
            foreach($fields[$key.'-field_slot_types_allowed']['#value'] AS $element) {
              $values['field_slot_types_allowed'][LANGUAGE_NONE][]['value'] = $element;
            }
            $values['field_slot_types_capacity'][LANGUAGE_NONE][0]['value'] = $fields[$key.'-field_slot_types_capacity']['#value'] ? $fields[$key.'-field_slot_types_capacity']['#value'] : 1;
            $field_collection_item = entity_create('field_collection_item', $values);
            $field_collection_item->setHostEntity('node', $node);
            $field_collection_item->save();
          }
       }
     }
     }
    }
  }
}

function _cod_session_get_timeslots($day = NULL, $event_id) {
  $time_slots = array();

  // No view so default to all time slots within this day.
  $sql = "SELECT n.nid
    FROM {node} n
    INNER JOIN {field_data_field_slot_datetime} s ON n.nid = s.entity_id AND n.vid = s.revision_id
    INNER JOIN {og_membership} om ON s.entity_id = om.etid
    WHERE n.type = 'time_slot' AND n.status = 1 AND om.gid = :event_id";
  if ($day) {
    $sql .= " AND DATE_FORMAT(s.field_slot_datetime_value, '%Y-%m-%d') = :day";
  }
  $sql .= " ORDER BY s.field_slot_datetime_value ASC";
  $result = db_query($sql, array(':day' => $day, ':event_id' => $event_id));
  foreach ($result as $record) {
    $time_slots[] = $record;
  }
  return $time_slots;
}

function _cod_session_get_rooms($event_id) {
  $rooms = array();

  $sql = "SELECT n.nid FROM {node} n, {og_membership} om WHERE n.type = 'room' AND n.nid = om.etid AND om.gid = :event_id";
  $result = db_query($sql, array(':event_id' => $event_id));
  foreach ($result as $record) {
    $rooms[] = $record;
  }
  return $rooms;
}

/*
 * Get the Entity field collection that contains the room/timeslot/allowed types combo
 *
 * @return false if there is none found, entity ID if found
 */
function _cod_session_get_room_slots_types_allowed($room_nid, $time_nid, $event_id) {

  $entity_id = cod_events_get_collection_entity($room_nid, $time_nid, $event_id);
  if(!empty($entity_id)) {
    $sql = "SELECT sa.field_slot_types_allowed_value
      FROM {field_data_field_slot_types_allowed} sa, {field_data_field_slot_types_time_slot} st
      WHERE sa.entity_id = :entity_id AND st.entity_id = :entity_id AND st.field_slot_types_time_slot_target_id = :time_nid";
    $result = db_query($sql, array('entity_id' => $entity_id, ':time_nid' => $time_nid));
    $return = array();
    foreach($result as $record) {
      $return[$record->field_slot_types_allowed_value] = $record->field_slot_types_allowed_value;
    }
    return $return;
  }
  else {
    //get the default for the field
    $info = field_info_instances('field_collection_item','field_room_slots_types_allowed');
    if(!empty($info['field_slot_types_allowed']['default_value'])) {
      $return[$info['field_slot_types_allowed']['default_value'][0]['value']] = $info['field_slot_types_allowed']['default_value'][0]['value'];
      return $return;
    }
    else {
      return array();
    }
  }
}

function _cod_session_get_room_slots_types_capacity($room_nid, $time_nid, $event_id) {
  $entity_id = cod_events_get_collection_entity($room_nid, $time_nid, $event_id);
  //second it looks like we do, lets make sure it has some data, and return it!
  if(!empty($entity_id)) {
    $sql = "SELECT sa.field_slot_types_capacity_value
      FROM {field_data_field_slot_types_capacity} sa, {field_data_field_slot_types_time_slot} st
      WHERE sa.entity_id = :entity_id AND st.entity_id = :entity_id AND st.field_slot_types_time_slot_target_id = :time_nid";
    $result = db_query($sql, array('entity_id' => $entity_id, ':time_nid' => $time_nid));
    foreach($result as $record) {
      $return = $record->field_slot_types_capacity_value;
      return $return;
    }
  }
  else {
    return '1'; //by default we return a 1
  }
}

function cod_events_get_collection_entity($room_nid, $time_nid, $event_id) {
  //first, do we have an entity?
  $sql = "SELECT s.field_room_slots_types_allowed_value
    FROM {field_data_field_room_slots_types_allowed} s
    INNER JOIN {field_data_field_slot_types_time_slot} st ON s.field_room_slots_types_allowed_value = st.entity_id
    INNER JOIN {og_membership} om ON st.entity_id = om.etid
    WHERE s.entity_id = :nid AND st.field_slot_types_time_slot_target_id = :time_nid AND om.gid = :event_id";
  $entity_id = db_query($sql, array(':nid' => $room_nid, ':time_nid' => $time_nid, ':event_id' => $event_id))->fetchField();

  return $entity_id;
}