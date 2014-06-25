<?php
/**
 * @file
 * Ticket state admin file.
 */

/**
 * Implements ENTITY_TYPE_form().
 */
function ticket_state_form($form, &$form_state, $entity, $op = 'edit') {

  // Attach the fields for this ticket registration.
  field_attach_form('ticket_state', $entity, $form, $form_state);

  // Add the property form fields.
  $form['label'] = array(
    '#title' => t('State label'),
    '#description' => t('The name of this ticket registration state.'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => isset($entity->label) ? $entity->label : '',
  );

  $form['name'] = array(
    '#title' => t('State machine name'),
    '#description' => t('The unique machine name of this state. The machine name must only contain lowercase letters, numbers and underscores.'),
    '#type' => 'machine_name',
    '#required' => TRUE,
    '#default_value' => isset($entity->name) ? $entity->name : '',
    '#machine_name' => array(
      'exists' => 'ticket_state_name_exists',
      'source' => array('label'),
    ),
  );

  $form['description'] = array(
    '#title' => t('Description'),
    '#description' => t('A description of this ticket registration state.'),
    '#type' => 'textarea',
    '#required' => FALSE,
    '#default_value' => isset($entity->description) ? $entity->description : '',
  );

  $form['weight'] = array(
    '#title' => t('Weight'),
    '#description' => t('The weight determines the logical order of states.'),
    '#type' => 'weight',
    '#default_value' => isset($entity->weight) ? $entity->weight : 0,
    '#delta' => 10,
  );

  $form['active'] = array(
    '#title' => t('Active'),
    '#description' => t('Set the status to enable or disable this state.'),
    '#type' => 'checkbox',
    '#default_value' => isset($entity->active) ? $entity->active : 0,
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => ($op == 'edit') ? t('Update') : t('Save'),
    '#weight' => 40,
  );

  if ($op != 'add' && $op != 'clone') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('ticket_state_form_submit_delete'),
    );
  }

  return $form;
}

/**
 * Machine name exists callback.
 */
function ticket_state_name_exists($name) {
  return db_select('ticket_state')
    ->condition('name', $name)
    ->countQuery()
    ->execute()
    ->fetchField();
}

/**
 * ENTITY_TYPE_form() submit callback.
 */
function ticket_state_form_submit(&$form, &$form_state) {
  $ticket_state = entity_ui_form_submit_build_entity($form, $form_state);

  // Add info to new states.
  if (empty($ticket_state->tsid)) {
    $ticket_state->is_new = TRUE;
  }

  // Update and save.
  $ticket_state->save();

  drupal_set_message(t('The ticket registration state %state has been saved.', array('%state' => $ticket_state->label)));
  $form_state['redirect'] = array(ticket_get_admin_path('ticket_state'));
}

/**
 * ENTITY_TYPE_form() delete callback.
 */
function ticket_state_form_submit_delete($form, &$form_state) {
  $form_state['redirect'] = array(
    ticket_get_admin_path('ticket_state') . '/manage/' . $form_state['ticket_state']->tsid . '/delete',
  );
}


/**
 * Ticket states setting form.
 */
function ticket_state_overview_form($form, &$form_state) {
  $ticket_states = ticket_state_states();

  // Form elements for existing states .
  $form['state']['#tree'] = TRUE;
  if (!empty($ticket_states)) {

    foreach ($ticket_states as $tsid => $state) {
      $form['state'][$tsid]['tsid'] = array(
        '#type' => 'hidden',
        '#default_value' => $tsid,
      );
      $form['state'][$tsid]['label'] = array(
        '#title' => t('Label'),
        '#type' => 'textfield',
        '#default_value' => $state->label,
        '#maxlength' => 128,
        '#size' => 20,
        '#required' => TRUE,
      );
      $form['state'][$tsid]['weight'] = array(
        '#title' => t('Weight'),
        '#type' => 'weight',
        '#default_value' => $state->weight,
        '#delta' => 15,
        '#attributes' => array('class' => array('ticket-state-weight')),
      );
      $form['state'][$tsid]['description'] = array(
        '#title' => t('Description'),
        '#type' => 'textfield',
        '#default_value' => $state->description,
        '#maxlength' => 128,
        '#size' => 50,
      );
      $form['state'][$tsid]['active'] = array(
        '#title' => t('Active'),
        '#type' => 'checkbox',
        '#default_value' => $state->active,
      );
      $form['state'][$tsid]['delete'] = array(
        '#type' => 'item',
        '#markup' => l(t('delete'), 'admin/structure/ticket_state/manage/' . $state->identifier() . '/delete', array('query' => drupal_get_destination())),
      );
      $form['state'][$tsid]['export'] = array(
        '#type' => 'item',
        '#markup' => l(t('export'), 'admin/structure/ticket_state/manage/' . $state->identifier() . '/export'),
      );
    }
  }

  $form['help'] = array(
    '#type' => 'item',
    '#description' => t("Shows the current ticket states for the site. When no states are shown on form, the default is used."),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Submit handler for the ticket states form.
 */
function ticket_state_overview_form_submit($form, &$form_state) {

  foreach ($form_state['input']['state'] as $state) {
    $ticket_state = entity_load_single('ticket_state', $state['tsid']);
    $ticket_state->label = $state['label'];
    $ticket_state->active = isset($state['active']) ? $state['active'] : 0;
    $ticket_state->weight = $state['weight'];
    $ticket_state->description = $state['description'];

    $ticket_state->save();
  }

  drupal_set_message(t('Your ticket states have been saved.'));
}

/**
 * Theme handler for ticket states form.
 */
function theme_ticket_state_overview_form($variables) {
  $form = $variables['form'];

  drupal_add_tabledrag('ticket-state-admin-settings-table', 'order', 'self', 'ticket-state-weight');
  $header = array(
    array('data' => t('Label !required', array('!required' => '<span class="form-required" title="' . t('This field is required.') . '">*</span>'))),
    array('data' => t('Description')),
    array('data' => t('Active')),
    array('data' => t('Weight')),
    array('data' => t('Operations'), 'colspan' => 2),
  );

  foreach (element_children($form['state']) as $key) {
    $row = array();
    foreach (array(
               'label',
               'description',
               'active',
               'weight',
               'delete',
               'export',
             ) as $element) {
      // Since we're rendering these in a table, remove any #title attributes.
      if (!empty($form['state'][$key][$element]['#title'])) {
        unset($form['state'][$key][$element]['#title']);
      }
      $row[] = drupal_render($form['state'][$key][$element]);
    }

    $rows[] = array(
      'class' => array('draggable'),
      'data' => $row,
    );
  }

  $output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => 'ticket-state-admin-settings-table'),
  ));

  $output .= drupal_render_children($form);
  return $output;
}
