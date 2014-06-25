<?php
/**
 * @file
 * Ticket rules include.
 */

/**
 * Implements hook_rules_condition_info().
 */
function ticket_rules_rules_condition_info() {
  $conditions = array();

  $conditions['ticket_registration_check_state'] = array(
    'label' => t('Check ticket registration state'),
    'parameter' => array(
      'ticket_registration' => array(
        'type' => 'ticket_registration',
        'label' => t('Ticket registration'),
      ),
      'ticket_state' => array(
        'type' => 'list<text>',
        'label' => t('Ticket state'),
        'options list' => 'ticket_state_get_states_options',
      ),
    ),
    'group' => t('Ticket'),
    'callbacks' => array(
      'execute' => 'ticket_rules_get_registration_state',
    ),
  );

  return $conditions;
}

/**
 * Callback for ticket_registration_check_state.
 */
function ticket_rules_get_registration_state($ticket_registration, $ticket_state) {
  return in_array($ticket_registration->{TICKET_STATE_FIELD}[LANGUAGE_NONE][0]['target_id'], $ticket_state);
}

/**
 * Implements hook_rules_action_info().
 */
function ticket_rules_rules_action_info() {
  $actions = array();

  $actions['ticket_registration_set_state'] = array(
    'label' => t('Set ticket registration state'),
    'parameter' => array(
      'ticket_registration' => array(
        'type' => 'ticket_registration',
        'label' => t('Ticket registration'),
      ),
      'ticket_state' => array(
        'type' => 'list<text>',
        'label' => t('Ticket state'),
        'options list' => 'ticket_state_get_states_options',
      ),
    ),
    'group' => t('Ticket'),
    'callbacks' => array(
      'execute' => 'ticket_rules_set_regitration_state',
    ),
  );

  $actions['ticket_registration_advance_state'] = array(
    'label' => t('Advance ticket registration state'),
    'parameter' => array(
      'ticket_registration' => array(
        'type' => 'ticket_registration',
        'label' => t('Ticket registration'),
      ),
    ),
    'group' => t('Ticket'),
    'callbacks' => array(
      'execute' => 'ticket_rules_advance_regitration_state',
    ),
  );

  return $actions;
}

/**
 * Callback for ticket_registration_set_state.
 */
function ticket_rules_set_regitration_state($ticket_registration, $ticket_state) {
  $ticket_registration->{TICKET_STATE_FIELD}[LANGUAGE_NONE][0]['target_id'] = reset($ticket_state);
  $ticket_registration->save();
}

/**
 * Callback for ticket_rules_advance_registration_state.
 */
function ticket_rules_advance_regitration_state($ticket_registration) {
  $current_state = $ticket_registration->{TICKET_STATE_FIELD}[LANGUAGE_NONE][0]['target_id'];
  $states = ticket_state_get_active_states();
  $current_key = array_search($current_state, $states);
  if (isset($states[$current_key + 1])) {
    $ticket_registration->{TICKET_STATE_FIELD}[LANGUAGE_NONE][0]['target_id'] = $states[$current_key + 1];
    $ticket_registration->save();
  }
}
