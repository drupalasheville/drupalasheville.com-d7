<?php
/**
 * @file
 * UI Controller class.
 */

class TicketStatesUIController extends EntityDefaultUIController {

  /**
   * Implements hook_menu().
   */
  public function hook_menu() {
    $items = parent::hook_menu();

    // Simplify the ticket state permissions.
    foreach ($items as &$item) {
      if (isset($item['access callback'])) {
        unset($item['access callback']);
        $item['access arguments'] = array('administer ticket states');
      }
    }

    return $items;
  }

  /**
   * Returns the ticket status overview form.
   */
  public function overviewForm($form, &$form_state) {
    return drupal_get_form('ticket_states_overview_form');
  }

}
