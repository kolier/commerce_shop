<?php

/**
 * @file
 * Commerce shop admin UI.
 */

function commerce_shop_admin_overview() {
  
}

function commerce_shop_admin_edit($commerce_shop) {
  return drupal_get_form('commerce_shop_form_edit', $commerce_shop);
}

function commerce_shop_form_edit($form, $form_state, $commerce_shop) {
  // Add the default field elements.
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Shop title'),
    '#default_value' => isset($commerce_shop->title) ? $commerce_shop->title : '',
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -5,
  );
  
  // Add the field related form elements.
  $form_state['commerce_shop'] = $commerce_shop;
  field_attach_form('commerce_shop', $commerce_shop, $form, $form_state);
  
  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 400,
  );
  
  // We add the form's #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();
  
  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }
  
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save shop'),
    '#submit' => $submit + array('commerce_shop_form_edit_submit'),
  );
  
  if (!empty($project->title)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete shop'),
      '#suffix' => l(t('Cancel'), 'admin/commerce/shops'),
      '#submit' => $submit + array('commerce_shop_form_delete_submit'),
      '#weight' => 45,
    );
  }
  
  // We append the validate handler to #validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  //$form['#validate'][] = 'model_edit_form_validate';
  return $form;
}

function commerce_shop_form_edit_submit(&$form, &$form_state, $commerce_shop) {
  
}

function commerce_shop_form_delete($form, $form_state, $commerce_shop) {
  
}

function commerce_shop_form_delete_submit(&$form, &$form_state, $commerce_shop) {

}
