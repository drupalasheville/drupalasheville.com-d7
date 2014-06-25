<?php

/**
 * Room view callback.
 */
function cod_schedule_room_view($room) {
  drupal_set_title(entity_label('cod_event_room', $room));
  return entity_view('cod_event_room', array(entity_id('cod_event_room', $room) => $room), 'default');
}

/**
 * Time view callback.
 */
function cod_schedule_time_view($time) {
  drupal_set_title(entity_label('cod_event_time', $time));
  return entity_view('cod_event_time', array(entity_id('cod_event_time', $time) => $time), 'default');
}