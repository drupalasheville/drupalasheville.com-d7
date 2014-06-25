<?php

/**
 * @file
 * Entity related functions for the COD event module.
 */

/**
 * Provides an entity class for session rooms.
 */
class CodEventRoom extends Entity {

  /**
   * @var string
   */
  public $name;
  public $capacity;
  public $weight = 0;

  public function __construct($values = array()) {

    return parent::__construct($values, 'cod_event_room');
  }

  protected function defaultLabel() {
    return $this->name;
  }

  protected function defaultUri() {
    return array('path' => 'room/' . $this->identifier());
  }

  /**
   * Overrides Entity::save().
   */
  public function save() {
    parent::save();
    // Clear field info caches such that any changes to extra fields
    // get reflected.
    field_info_cache_clear();
  }

  /**
   * Returns whether the ingredient type is locked, thus may not be
   * deleted or renamed.
   *
   * Ingredient types provided in code are automatically treated as
   * locked, as well as any fixed ingredient type.
   */
   public function isLocked() {
     return isset($this->status) && empty($this->is_new)
     && (($this->status & ENTITY_IN_CODE)
         || ($this->status & ENTITY_FIXED));
   }
}

class CodEventRoomController extends EntityAPIControllerExportable {

  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $wrapper = entity_metadata_wrapper('cod_event_room', $entity);
    //$content['author'] = array('#markup' => t('Created by: !author', array('!author' => $wrapper->uid->name->value(array('sanitize' => TRUE)))));

    // Make Description and Status themed like default fields.
    $content['capacity'] = array(
      '#theme' => 'field',
      '#weight' => 0,
      '#title' =>t('Room Capacity'),
      '#access' => TRUE,
      '#label_display' => 'above',
      '#view_mode' => 'full',
      '#language' => LANGUAGE_NONE,
      '#field_name' => 'field_fake_description',
      '#field_type' => 'text',
      '#entity_type' => 'cod_event_room',
      '#bundle' => 'cod_event_room',
      '#items' => array(array('value' => $entity->capacity)),
      '#formatter' => 'text_default',
      0 => array('#markup' => check_plain($entity->capacity))
    );

    return parent::buildContent($entity, $view_mode, $langcode, $content);
  }
}

/**
 * UI controller.
 */
class CodEventRoomUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage rooms, including fields.';
    return $items;
  }
}

/**
 * Provides an entity class for session times.
 */
class CodEventTime extends Entity {

  /**
   * @var string
   */
  public $date_label;

  public function __construct($values = array()) {
    return parent::__construct($values, 'cod_event_time');
  }

  protected function defaultLabel() {
    return $this->date_label;
  }

  protected function defaultUri() {
    return array('path' => 'time/' . $this->identifier());
  }

  /**
   * Overrides Entity::save().
   */
  public function save() {
    $this->date_label = $this->setFullLabel();
    parent::save();
    // Clear field info caches such that any changes to extra fields
    // get reflected.
    field_info_cache_clear();
  }

  protected function setFullLabel() {

    $timezone = $this->field_evttime_date[LANGUAGE_NONE][0]['timezone'];
    $date_field1 = $this->field_evttime_date[LANGUAGE_NONE][0]['value'];
    $date_field1 = new DateTime($date_field1, new DateTimeZone('UTC'));
    $date_field1 = format_date($date_field1->getTimestamp(), $type = 'short');
    $date_field2 = $this->field_evttime_date[LANGUAGE_NONE][0]['value2'];
    $date_field2 = new DateTime($date_field2, new DateTimeZone('UTC'));
    $date_field2 = format_date($date_field2->getTimestamp(), $type = 'short');
    $date_label = $date_field1 . '-' . $date_field2;

    return $date_label;
  }

  public function getTimeLabel() {
    $timezone = $this->field_evttime_date[LANGUAGE_NONE][0]['timezone'];
    $date_field1 = $this->field_evttime_date[LANGUAGE_NONE][0]['value'];
    $date_field1 = new DateTime($date_field1, new DateTimeZone('UTC'));
    $date_field1 = format_date($date_field1->getTimestamp(), $type = 'cod_time');

    $date_field2 = $this->field_evttime_date[LANGUAGE_NONE][0]['value2'];
    $date_field2 = new DateTime($date_field2, new DateTimeZone('UTC'));
    $date_field2 = format_date($date_field2->getTimestamp(), $type = 'cod_time');

    return $date_field1 . '-' . $date_field2;
  }

  /**
   * Returns whether the ingredient type is locked, thus may not be
   * deleted or renamed.
   *
   * Ingredient types provided in code are automatically treated as
   * locked, as well as any fixed ingredient type.
   */
   public function isLocked() {
     return isset($this->status) && empty($this->is_new)
     && (($this->status & ENTITY_IN_CODE)
         || ($this->status & ENTITY_FIXED));
   }
}

class CodEventTimeController extends EntityAPIControllerExportable {

  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $wrapper = entity_metadata_wrapper('cod_event_time', $entity);
    //$content['author'] = array('#markup' => t('Created by: !author', array('!author' => $wrapper->uid->name->value(array('sanitize' => TRUE)))));

    return parent::buildContent($entity, $view_mode, $langcode, $content);
  }
}

/**
 * UI controller.
 */
class CodEventTimeUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage times, including fields.';
    return $items;
  }
}
