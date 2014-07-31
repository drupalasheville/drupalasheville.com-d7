<?php

/**
 * @file
 * Definition of ticket_views_handler_field_entity_link.
 */

/**
 * Field handler to present a link to the registered entity (event).
 *
 * @ingroup views_field_handlers
 */
class ticket_views_handler_field_entity_link extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['ttid'] = 'ttid';
  }

  function option_definition() {
    return parent::option_definition();
  }

  function access() {
    return true;
    return ticket_type_access('view', $bundle);
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    // Get the host (event) entity.
    $value = $this->get_value($values, 'ttid');
    $ticket_type = ticket_type_load($value);
    $entity = entity_metadata_wrapper($ticket_type->entity_type, $ticket_type->host());

    // Generate as link.
    $this->options['alter']['make_link'] = TRUE;
    $uri = entity_uri($ticket_type->entity_type, $ticket_type->host());
    $this->options['alter']['path'] = drupal_get_path_alias($uri['path']);

    // Return entity label.
    return $entity->label();
  }

}
