<?php
/**
 * @file
 * Contains the ticket_registration display plugin.
 */

/**
 * A plugin to handle ticket_registration on a view.
 *
 * @ingroup views_display_plugins
 */
class ticket_views_plugin_display_ticket_registration extends views_plugin_display_default {
  /**
   * Override default to false.
   */
  function is_default_display() {
    return FALSE;
   }

  /**
   * Declare the option for ticket type.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['ticket_types'] = array('default' => array());
    return $options;
  }

  /**
   * Provide the summary for attachment options in the views UI.
   *
   * This output is returned as an array.
   */
  function options_summary(&$categories, &$options) {
    // It is very important to call the parent function here:
    parent::options_summary($categories, $options);

    $categories['ticket_registration'] = array(
      'title' => t('Ticket registration settings'),
      'column' => 'second',
      'build' => array(
        '#weight' => -10,
      ),
    );

    $ttids = $this->get_option('ticket_types');
    if ($num_tts = count($ttids)) {
      $label = ticket_get_ticket_type_names(reset($ttids));
      if ($num_tts > 1) {
        $num_tts--;
        $label = t('@name and @num more', array('@name' => $label, '@num' => $num_tts));
      }
    }
    else {
      $label = t('No ticket types selected.');
    }

    $options['ticket_types'] = array(
      'category' => 'ticket_registration',
      'title' => t('Ticket Types'),
      'value' => $label,
    );
  }

  /**
   * Provide a form to set the ticket type option.
   */
  function options_form(&$form, &$form_state) {
    // It is very important to call the parent function here:
    parent::options_form($form, $form_state);

    // Setup the types form.
    if ($form_state['section'] == 'ticket_types') {

      $form['#title'] = t('The types of ticket registrations to view');
      $form['ticket_types'] = array(
        '#type' => 'checkboxes',
        '#description' => t('Select the ticket types where this view will appear.'),
        '#options' => ticket_get_ticket_type_names(),
        '#default_value' => $this->get_option('ticket_types'),
      );
    }
  }

  /**
   * Save the display settings.
   */
  function options_submit(&$form, &$form_state) {
    // It is very important to call the parent function here:
    parent::options_submit($form, $form_state);

    if ($form_state['section'] == 'ticket_types') {
      $enabled_types = array();
      foreach ($form_state['values']['ticket_types'] as $val) {
        if ($val) {
          $enabled_types[$val] = $val;
        }
      }

      $this->set_option('ticket_types', $enabled_types);
    }
  }

}
