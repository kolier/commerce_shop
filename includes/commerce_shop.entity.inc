<?php

/**
 * @file
 * CommerceShop Entity class include file.
 */

class CommerceShop extends Entity {
  public function __construct($values = array()) {
    parent::__construct($values, 'commerce_shop');
  }
  
  protected function defaultLabel() {
    return $this->title;
  }
  
  protected function defaultUri() {
    return array('path' => 'shop/' . $this->shop_id);
  }
}
