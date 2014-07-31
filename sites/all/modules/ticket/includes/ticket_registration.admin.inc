<?php
/**
 * @file
 * Admin functions and callbacks.
 */

/**
 * Ticket registration view page.
 *
 * We can't use the Views page menu system because it doesn't know about
 * our host entities. So we attach the view in hook_menu() then use
 * this callback to get the view.
 *
 * $arg object
 *   This is the ticket type.
 */
function ticket_registration_view_page($ticket_type) {
  $view = views_get_view('ticket_registration');

  // If there's a display that's been tagged for this ticket type, use it.
  $dname = 'default';
  foreach ($view->display as $display_name => $display) {
    if ($display->display_plugin == 'ticket_registration' && in_array($ticket_type->ttid, $display->display_options['ticket_types'])) {
      $dname = $display_name;
      break;
    }
  }

  // Default back to the default display.
  return $view->preview($dname, array($ticket_type->ttid));
}

/**
 * Display tickets on a user's page.
 */
function ticket_registration_user_tickets($account) {
  $content = module_invoke_all('ticket_user_registrations', $account);
  return implode('', $content);
}

/**
 * Implements hook_ticket_user_registrations().
 */
function ticket_ticket_user_registrations($account) {
  $view = views_get_view('ticket_user');
  $display = 'block';
  $user = $account->uid == $GLOBALS['user']->uid ? t('Your') : t('@name\'s', array('@name' => $account->name));

  return theme('ticket_user_tickets', array(
    'title' => t('@user ticket registrations', array('@user' => $user)),
    'data' => $view->preview($display, array($account->uid)),
  ));
}

/**
 * View callback. This just arrayifies things for entity_view().
 */
function ticket_registration_view($entity_type, $entity) {
  return $entity->view('default');
}

/**
 * Implements ENTITY_TYPE_form().
 */
function ticket_registration_form($form, &$form_state, $entity, $op = 'edit') {

  // Attach the fields for this ticket registration.
  field_attach_form('ticket_registration', $entity, $form, $form_state);

  // TODO: Need to add the status checkbox here, but it should probably
  // have some additional access control and such. Also need to determine
  // the use cases for keeping it.
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
    '#weight' => 40,
  );

  if ($op != 'add' && $op != 'clone') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('ticket_registration_form_submit_delete'),
    );
  }
  return $form;
}

/**
 * ENTITY_TYPE_form() submit callback.
 */
function ticket_registration_form_submit($form, &$form_state) {
  $ticket_registration = entity_ui_form_submit_build_entity($form, $form_state);

  // Set the properties.
  if (empty($ticket_registration->trid)) {
    $ticket_registration->is_new = TRUE;
    $ticket_registration->created = REQUEST_TIME;
    if (empty($ticket_registration->author_uid)) {
      $ticket_registration->author_uid = $GLOBALS['user']->uid;
    }
  }
  if (empty($ticket_registration->user_uid)) {
    $ticket_registration->user_uid = $GLOBALS['user']->uid;
  }
  $ticket_registration->changed = REQUEST_TIME;

  // TODO: Set status here if entity_ui_form_submit_build_entity()
  // doesnt already.
  // Perform revisioning work.
  $ticket_registration->revision = TRUE;
  $ticket_registration->default_revision = TRUE;

  if (!isset($ticket_registration->is_new) || !$ticket_registration->is_new) {
    $ticket_registration->is_new = FALSE;
    $ticket_registration->is_new_revision = TRUE;
  }

  $ticket_registration->save();
}

/**
 * ENTITY_TYPE_form() delete callback.
 */
function ticket_registration_form_submit_delete($form, &$form_state) {
  // Redirect to the event registration list page if accessible, otherwise
  // redirect to the host entity page.
  $ticket_registration = entity_ui_form_submit_build_entity($form, $form_state);
  $ticket_type = $ticket_registration->ticket_type();
  $host = $ticket_type->host();

  $dest = ticket_get_entity_uri_pattern($ticket_type->entity_type);
  $dest = str_replace('%', $ticket_type->entity_id, $dest);
  if (ticket_type_access('update', $ticket_type)) {
    $dest .= '/tickets/' . $ticket_type->ttid . '/manage';
  }

  $form_state['redirect'] = array(
    ticket_get_admin_path('ticket_registration') . '/' . $ticket_registration->trid . '/delete',
    array(
      'query' => array(
        'destination' => $dest,
      ),
    ),
  );
}

/**
 * Ticket register page callback.
 *
 * This function builds the form of forms.
 */
function ticket_register_form($form, &$form_state) {
  $form = array();
  $entity_data = array();
  $schema = drupal_get_schema('ticket_registration');

  foreach ($_SESSION['ticket']['build_forms'] as $ttid => $quantity) {
    $ticket_type = entity_load_single('ticket_type', $ttid);
    $tt = entity_metadata_wrapper('ticket_type', $ticket_type);
    $label = $tt->ticket_type_label->value();

    for ($i = 1; $i <= $quantity; $i++) {
      $title = ($quantity > 1) ? t('@label: Ticket @num', array('@label' => $label, '@num' => $i)) : $label;

      // Create a stub entity for our form.
      $values = array('bundle' => $ttid);
      $ticket_registration = entity_create('ticket_registration', $values);

      // Generate some entity_data for the multiple entity form.
      $entity_data[] = array(
        'entity_type' => 'ticket_registration',
        'entity' => $ticket_registration,
        'fieldset' => $title,
      );
    }
  }

  if (!empty($entity_data)) {
    $entity_form = multiple_entity_form($form, $form_state, $entity_data);

    $form += $entity_form;
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => isset($_SESSION['ticket']['submit_text']) ? check_plain($_SESSION['ticket']['submit_text']) : 'Next',
    );
  }

  return $form;
}

/**
 * Implements hook_form_alter().
 */
function ticket_form_alter(&$form, &$form_state, $form_id) {
  // Disable registration forms from showing the ticket state.
  if (isset($form['#entity_form_keys'])) {
    foreach ($form['#entity_form_keys'] as $entity_form) {
      if (isset($form[$entity_form]['ticket_state']) && !user_access('administer ticket')) {
        $form[$entity_form]['ticket_state']['#access'] = FALSE;
      }
    }
  }

  // Disable the user registration edit page from showing ticket state.
  elseif (isset($form['ticket_state']) && !user_access('administer ticket')) {
    $form['ticket_state']['#access'] = FALSE;
  }
}

/**
 * Ticket register form validation.
 */
function ticket_register_form_validate($form, &$form_state) {
  multiple_entity_form_validate($form, $form_state);
}

/**
 * Tikcet register page form submit.
 */
function ticket_register_form_submit($form, &$form_state) {
  multiple_entity_form_submit($form, $form_state);

  $registrations = array();

  foreach ($form['#entity_form_keys'] as $form_key) {
    // Use the form_state version so that entity properties may be modified.
    $entity = $form_state['complete form'][$form_key]['#entity'];

    // Update the entity with some properties.
    if (empty($entity->author_uid)) {
      $entity->author_uid = $GLOBALS['user']->uid;
    }
    $entity->created = REQUEST_TIME;
    $entity->changed = REQUEST_TIME;
    $entity->revision = TRUE;
    $entity->default_revision = TRUE;

    // Set the default registrant uid if not set.
    if (empty($entity->user_uid)) {
      $entity->user_uid = $GLOBALS['user']->uid;
    }

    // TODO: We should probably do this in hook_entity insert or something.
    if (module_exists('ticket_state')) {
      $ticket_type = $entity->ticket_type();
      if (!empty($ticket_type->ticket_type_default_tsid)) {
        $ts = ticket_state_load($ticket_type->ticket_type_default_tsid[LANGUAGE_NONE][0]['target_id']);
        $entity->state = $ts->name;
      }
    }

    $entity->save();

    $registrations[$entity->trid] = $entity;

    drupal_set_message(t('Registration created - !label', array('!label' => $form[$form_key]['#title'])));
  }

  // Provide external module access, so they can react to the registrations.
  module_invoke_all('ticket_registered', $registrations);

  // Return back to the event entity, but let others modify that.
  // Note that hook_ticket_registered_redirect_alter() may return an array. see:
  // https://api.drupal.org/api/drupal/includes!form.inc/function/drupal_redirect_form/7
  $redirect = $_SESSION['ticket']['return_url'] ? $_SESSION['ticket']['return_url'] : '';
  drupal_alter('ticket_registered_redirect', $redirect, $registrations);

  if ($redirect) {
    $form_state['redirect'] = $redirect;
  }
  // Successful checkout, Clear the session.
  unset($_SESSION['ticket']);
}
