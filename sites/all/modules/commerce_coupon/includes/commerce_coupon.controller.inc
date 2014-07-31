<?php

/**
 * @file
 * Coupon controller class.
 */

class CommerceCouponEntityController extends DrupalCommerceEntityController {

  public $code;

  public $created;

  public $bulk;

  public $type = 'discount_coupon';

  public $status;

  public $uid;

  /**
   * Create a default coupon.
   *
   * @param array $values
   *   An array of values to set, keyed by property name.
   *
   * @return object A product object with all default fields initialized.
   */
  public function create(array $values = array()) {
    $values += array(
      'coupon_id' => '',
      'code' => '',
      'bulk' => FALSE,
      'created' => '',
      'status' => TRUE,
      'uid' => 0
    );

    return parent::create($values);
  }

  /**
   * Saves a coupon.
   *
   * @param $entity
   *   The full coupon object to save
   * @param \DatabaseTransaction $transaction
   *   An optional transaction object.
   *
   * @return bool|int SAVED_NEW or SAVED_UPDATED depending on the operation performed.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    if (empty($entity->{$this->idKey}) || !empty($entity->is_new)) {
      // Set the creation timestamp if not set, for new entities.
      if (empty($entity->created)) {
        $entity->created = REQUEST_TIME;
      }    
    }
    
    // Set the "changed" field    
    $entity->changed = REQUEST_TIME;
    return parent::save($entity);
  }
}
