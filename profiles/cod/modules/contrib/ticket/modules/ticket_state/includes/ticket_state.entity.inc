<?php
/**
 * @file
 * Ticket Type entity class.
 */

/**
 * Provides an entity class Ticket Type.
 */
class TicketStateEntity extends Entity {

  // Allow access to Ticket Type properties.
  public $tsid;
  public $label;
  public $name;
  public $description;
  public $weight;
  public $module;
  public $active;
  public $bundle = 'ticket_state';

  /**
   * Construct.
   */
  public function __construct(array $values = array()) {
    return parent::__construct($values, 'ticket_state');
  }

}
