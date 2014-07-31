<?php
/**
 * @file
 * Metadata controller class.
 */

/**
 * @see hook_entity_property_info()
 */
class TicketRegistrationMetadataController extends EntityDefaultMetadataController {

  /**
   * Define entity properties.
   */
  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];

    $properties['trid'] = array(
      'label' => t('Ticket Registration ID'),
      'type' => 'integer',
      'description' => t('The ticket registration ID.'),
      'schema field' => 'trid',
    );

    $properties['revision_id'] = array(
      'label' => t('Ticket Registration revision ID'),
      'type' => 'integer',
      'description' => t('The ticket registration revision ID.'),
      'schema field' => 'revision_id',
    );

    $properties['bundle'] = array(
      'label' => t('Ticket type ID (bundle)'),
      'type' => 'integer',
      'description' => t('The ticket registration ticket type.'),
      'schema field' => 'bundle',
    );

    $properties['ticket_type'] = array(
      'label' => t('Ticket type entity'),
      'type' => 'entity',
      'description' => t('The loaded ticket type entity.'),
      'getter callback' => 'ticket_registration_get_properties',
    );

    $properties['entity_type'] = array(
      'label' => t('Host entity type'),
      'type' => 'token',
      'description' => t('The entity type of the host entity.'),
      'getter callback' => 'ticket_registration_get_properties',

    );

    $properties['entity_id'] = array(
      'label' => t('Host entity ID'),
      'type' => 'integer',
      'description' => t('The entity ID of the host entity.'),
      'getter callback' => 'ticket_registration_get_properties',
    );

    $properties['entity'] = array(
      'label' => t('Host entity'),
      'type' => 'entity',
      'description' => t('The loaded host entity.'),
      'getter callback' => 'ticket_registration_get_properties',
    );

    $properties['user'] = array(
      'label' => t('User entity'),
      'type' => 'entity',
      'schema field' => 'user_uid',
      'description' => t('The entity for which the registration belongs to. Usually a user.'),
      'getter callback' => 'ticket_registration_get_properties',
    );

    $properties['author'] = array(
      'label' => t('Author entity'),
      'type' => 'user',
      'schema field' => 'author_uid',
      'description' => t('The user who created the registration.'),
      'getter callback' => 'ticket_registration_property_author_get',
    );

    $properties['created'] = array(
      'label' => t('Date created'),
      'type' => 'date',
      'schema field' => 'created',
      'description' => t('The ticket registration creation date.'),
    );

    $properties['changed'] = array(
      'label' => t('Date updated'),
      'type' => 'date',
      'schema field' => 'updated',
      'description' => t('The ticket registration last changed date.'),
    );

    return $info;
  }

}
