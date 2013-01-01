<?php

/**
 * @file
 * CommerceShopController class include file.
 */

class CommerceShopController extends EntityAPIController {
  public function __construct($entityType) {
    parent::__construct($entityType);
  }
  
  /**
   * Create a commerce_shop - we first set up the values that are specific
   * to our commerce_shop schema but then also go through the EntityAPIController
   * function.
   *
   * @param $type
   *   The machine-readable type of the commerce_shop.
   *
   * @return
   *   A commerce_shop object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our Model
    $values += array(
      'shop_id' => '',
      'name' => '',
      'is_new' => TRUE,
      'owner' => '',
      'title' => '',
      'sub_title' => '',
      'description' => '',
      'path' => '',
      'status' => '',
      'created' => '',
      'changed' => '',
      'data' => '',
    );
  
    $commerce_shop = parent::create($values);
    return $commerce_shop;
  }
}
