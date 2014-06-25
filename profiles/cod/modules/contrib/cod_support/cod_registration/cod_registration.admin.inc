<?php

/*
 * Registration page display settings form.
 */
function cod_registration_form_cod_base_admin_settings_alter(&$form, &$form_state, $form_id) {

  $form['registration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Registration Display Settings'),
  );

  $form['registration']['cod_registration_display_page'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display registration on event page'),
    '#default_value' => variable_get('cod_registration_display_page', FALSE),
    '#description' => t('For sites with a default event, you can choose whether to display the registration on the event page or globally'),
    '#disabled' => variable_get('cod_events_default_event', FALSE) ? FALSE : TRUE,
  );
}