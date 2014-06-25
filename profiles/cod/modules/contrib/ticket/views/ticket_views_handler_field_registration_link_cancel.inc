<?php

/**
 * @file
 * Definition of ticket_views_handler_field_registration_link_cancel.
 */

/**
 * Field handler to present a link to registration cancel.
 *
 * @ingroup views_field_handlers
 */
class ticket_views_handler_field_registration_link_cancel extends ticket_views_handler_field_registration_link {

  function render_link($data, $values) {
    $text = !empty($this->options['text']) ? $this->options['text'] : t('Cancel');

    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['path'] = 'ticket_registration/' . $data . '/delete';
    $this->options['alter']['query'] = drupal_get_destination();

    return $text;
  }
}
