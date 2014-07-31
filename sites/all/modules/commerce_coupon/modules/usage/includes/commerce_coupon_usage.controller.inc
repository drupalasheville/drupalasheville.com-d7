<?php

/**
 * @file
 * Coupon usage transaction controller class.
 */

class CommerceCouponUsageTransactionEntityController extends DrupalCommerceEntityController {
  
  public $transaction_id;
  
  public $coupon_id;
  
  public $order_id;
  
  public $uid;
  
  public $date;
  

  /**
   * Create a new usage transaction.
   *
   * @param array $values
   *   An array of values to set, keyed by property name.
   * @return
   *   A product object with all default fields initialized.
   */
  public function create(array $values = array()) {
    $values += array(
      'coupon_id' => '',
      'transaction_id' => '',
      'order_id' => '',
      'date' => '',
      'uid' => ''
    );

    return parent::create($values);
  }

  /**
   * Saves a usage transaction
   *
   * @param $commerce_coupon
   *   The full coupon object to save.
   * @param $transaction
   *   An optional transaction object.
   *
   * @return
   *   SAVED_NEW or SAVED_UPDATED depending on the operation performed.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    // Do a normal entity save if the entity is not new. Usage records are just
    // boolean counters. We do not need atomic transaction handling on updates 
    // since there is no "amount" field that can be changed.
    if (empty($entity->is_new)) {
      return parent::save($entity);
    }
    
    // Load the usage
    if (!$entity->coupon_id) {
      throw new Exception('Cannot save a usage transaction without a coupon id');
    }
    
    $max_usage = commerce_coupon_usage_get_max_usage($entity->coupon_id);    
    
    // If the entity is new, we have to use a transaction.
    if (!isset($transaction)) {
      $transaction = db_transaction();
    }
    
    // Lock the related coupon. Any future save operations will have to wait
    // until this lock is cleared before the following query will return in
    // their thread.
    try {
      db_select('commerce_coupon', 'c')     
        ->fields('c', array('coupon_id'))
        ->condition('c.coupon_id', $entity->coupon_id)
        ->forUpdate()              
        ->execute();

      // Load the usage.
      $usage = commerce_coupon_usage_get_usage($entity->coupon_id);

      // Only save if the coupon referenced will not exceed its maximum
      // usage settings. Zero max usage means unlimited.
      if ($max_usage > $usage || !$max_usage) {
        return parent::save($entity, $transaction);
      }
      
      // End the transaction if the allowed usage has been reached.
      $transaction->rollback();
    }
    catch (Exception $e) {
      // Cancel the transaction if the coupon has no more uses. This clears the
      // lock on the control commerce_coupon row so that future save processes
      // may run.
      $transaction->rollback();
      watchdog_exception($this->entityType, $e);
      throw $e;
    }
  }  
}
