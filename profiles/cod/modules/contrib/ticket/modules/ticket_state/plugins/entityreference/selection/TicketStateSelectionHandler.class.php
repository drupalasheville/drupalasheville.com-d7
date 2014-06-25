<?php
/**
 * @file
 * OG Commons groups selection handler.
 */

class TicketStateSelectionHandler extends EntityReference_SelectionHandler_Generic {

  public static function getInstance($field, $instance = NULL, $entity_type = NULL, $entity = NULL) {
    return new self($field, $instance, $entity_type, $entity);
  }

  /**
   * Overrides TicketStateSelectionHandler::buildEntityFieldQuery().
   */
  public function buildEntityFieldQuery($match = NULL, $match_operator = 'CONTAINS') {
    $group_type = $this->field['settings']['target_type'];

    if (empty($this->instance['field_mode']) || $group_type != 'node' || user_is_anonymous()) {
      return parent::buildEntityFieldQuery($match, $match_operator);
    }

    $handler = EntityReference_SelectionHandler_Generic::getInstance($this->field, $this->instance, $this->entity_type, $this->entity);
    $query = $handler->buildEntityFieldQuery($match, $match_operator);

    // Show only the entities that are active groups.
    $query->propertyCondition('active', 1);

    $query->addMetaData('entityreference_selection_handler', $this);

    $query->addTag('entity_field_access');

    return $query;
  }
}
