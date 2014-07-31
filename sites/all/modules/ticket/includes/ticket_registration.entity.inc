<?php
/**
 * @file
 * Ticket Type entity class.
 */

/**
 * Provides an entity class Ticket Type.
 */
class TicketRegistration extends Entity {

  // Allow access to Ticket Type properties.
  public $trid;
  public $revision_id;
  // Essentially ttid is the bundle.
  public $bundle;
  public $user_uid;
  public $author_uid;
  public $created;
  public $changed;

  /**
   * Construct.
   */
  public function __construct(array $values = array()) {
    parent::__construct($values, 'ticket_registration');
  }

  /**
   * A helper function to get a registration's ticket type entity.
   */
  public function ticket_type() {
    return entity_load_single('ticket_type', $this->bundle);
  }

  /**
   * A helper function to get a registration's host entity.
   */
  public function host() {
    return entity_load_single($this->ticket_type()->entity_type, $this->ticket_type()->entity_id);
  }

  /**
   * A helper function to get a registration's author user.
   */
  public function registrant() {
    return entity_load_single('user', $this->author_uid);
  }

  /**
   * A helper function to get a registration's attendee user.
   */
  public function attendee() {
    return entity_load_single('user', $this->user_uid);
  }
}

class TicketRegistrationUIController extends EntityContentUIController {

  /**
   * Implements hook_menu().
   */
  public function hook_menu() {
    // Provide standard entity ui routes for registrations.
    $items = parent::hook_menu();

    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%entity_object';
    $plural_label = isset($this->entityInfo['plural label']) ? $this->entityInfo['plural label'] : $this->entityInfo['label'] . 's';

    // Remove any management links. We're defining some of these in
    // the ticket_type entity and field_ui will provide the rest.
    foreach (array_keys($items) as $path) {
      if (strpos($path, $this->path . '/manage/') === 0) {
        unset ($items[$path]);
      }
    }

    return $items;
  }

}

/**
 * @file
 *
 * Contains the controller for ticket_registration entities.
 */
class TicketRegistrationController extends EntityAPIController {

  /**
   * Saves a ticket registration entity.
   */
  public function save($registration, DatabaseTransaction $transaction = NULL) {
    $registration->changed = REQUEST_TIME;
    parent::save($registration, $transaction);
  }
}
