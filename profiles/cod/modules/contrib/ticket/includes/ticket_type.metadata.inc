<?php
/**
 * @file
 * Ticket type metadata controller class.
 */

/**
 * @see hook_entity_property_info()
 */
class TicketTypeMetadataController extends EntityDefaultMetadataController {

  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];

    $properties['ttid'] = array(
      'label' => t('Ticket Type ID'),
      'type' => 'integer',
      'description' => t('The ticket type ID.'),
      'schema field' => 'ttid',
    );
    $properties['revision_id'] = array(
      'label' => t('Ticket Type Revision'),
      'type' => 'integer',
      'description' => t('The ticket type revision.'),
      'schema field' => 'revision_id',
    );
    $properties['entity_type'] = array(
      'label' => t('Entity Type'),
      'type' => 'text',
      'description' => t('The host entity type.'),
      'schema field' => 'entity_type',
    );
    $properties['entity_id'] = array(
      'label' => t('Entity ID'),
      'type' => 'integer',
      'description' => t('The host entity ID.'),
      'schema field' => 'entity_id',
    );
    $properties['entity'] = array(
      'label' => t('Entity'),
      'type' => 'entity',
      'description' => t('The loaded entity'),
      'getter callback' => 'ticket_type_get_properties',
    );
    $properties['field_name'] = array(
      'label' => t('Field Name'),
      'type' => 'text',
      'description' => t('The host entity field name.'),
      'schema field' => 'field_name',
    );
    $properties['status'] = array(
      'label' => t('Status'),
      'type' => 'boolean',
      'description' => t('The ticket type status.'),
      'schema field' => 'status',
    );
    $properties['created'] = array(
      'label' => t('Date Created'),
      'type' => 'date',
      'description' => t('The ticket type creation date.'),
      'schema field' => 'created',
    );
    $properties['changed'] = array(
      'label' => t('Date Changed'),
      'type' => 'date',
      'description' => t('The ticket type last changed date.'),
      'schema field' => 'changed',
    );

    return $info;
  }

}
