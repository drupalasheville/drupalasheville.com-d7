<?php

/**
 * @file
 * Definition of ticket_views_handler_field_registration_link.
 */

/**
 * Field handler to present a link to the registration.
 *
 * @ingroup views_field_handlers
 */
class ticket_views_handler_field_registration_link extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['trid'] = 'trid';
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['text'] = array('default' => '', 'translatable' => TRUE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $this->options['text'],
    );
    parent::options_form($form, $form_state);
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $value = $this->get_value($values, 'trid');
    return $this->render_link($this->sanitize_value($value), $values);
  }

  function render_link($data, $values) {
    $text = !empty($this->options['text']) ? $this->options['text'] : t('View');

    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['path'] = 'ticket_registration/' . $data;

    return $text;
  }

}
