<?php

/**
 * @file
 * Commerce shop admin UI.
 */

function commerce_shop_admin_overview() {
  return '';
}

function commerce_shop_admin_edit($commerce_shop) {
  return drupal_get_form('commerce_shop_form_edit', $commerce_shop);
}

function commerce_shop_form_edit($form, $form_state, $commerce_shop) {
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => isset($commerce_shop->title) ? $commerce_shop->title : '',
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -10,
  );
  $form['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($commerce_shop->name) ? $commerce_shop->name : '',
    '#maxlength' => 255,
    '#disabled' => !$commerce_shop->is_new,
    '#machine_name' => array(
      'exists' => 'commmerce_shop_name_exists',
      'source' => array('title'),
      'replace_pattern' => '[^a-z0-9-]+',
      'replace' => '-',
    ),
  );
  $form['sub_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Sub-title'),
    '#default_value' => isset($commerce_shop->sub_title) ? $commerce_shop->sub_title : '',
    '#maxlength' => 255,
    '#weight' => -5,
  );
  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => isset($commerce_shop->description) ? $commerce_shop->description : '',
    '#weight' => -3,
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

function commerce_shop_form_edit_submit(&$form, &$form_state) {
  $commerce_shop = entity_ui_controller('commerce_shop')->entityFormSubmitBuildEntity($form, $form_state);
  
  // Add in created and changed times.
  if ($commerce_shop->is_new = isset($commerce_shop->is_new) ? $commerce_shop->is_new : 0){
    $commerce_shop->created = time();
  }
  $commerce_shop->changed = time();
  $commerce_shop->save();
  
  $form_state['redirect'] = 'admin/commerce/shops';
}

function commerce_shop_form_delete($form, $form_state, $commerce_shop) {
  
}

function commerce_shop_form_delete_submit(&$form, &$form_state) {

}
