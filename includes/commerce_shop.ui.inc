<?php

/**
 * @file
 * Commerce shop entity UI controller.
 */

class CommerceShopUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults. Main reason for doing this is that
   * parent class hook_menu() is optimized for entity type administration.
   */
  public function hook_menu() {
    $items = array();
    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%' . $this->entityType;

    $items[$this->path] = array(
      'title' => 'Commerce shops',
      'description' => 'Manage commerce shops.',
      'type' => MENU_LOCAL_TASK | MENU_NORMAL_ITEM,
      'page callback' => 'commerce_shop_admin_overview',
      'access arguments' => array('access administration pages'),
      'file' => 'commerce_shop.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module']),
    );

    // Overview.
    // @todo access control.
    $item[$this->path . '/list'] = array(
      'title' => 'Manage commerce shops',
      'description' => 'Manage commerce_shop entities.',
      'type' => MENU_DEFAULT_LOCAL_TASK,
    );
    
    /*
    $items[$this->path . '/manage'] = array(
      'title' => 'Configure shop',
      'description' => 'Configure shop settings.',
      'page callback'  => 'commerce_shop_admin_overview',
      'access arguments' => array('access administration pages'),
      'type' => MENU_LOCAL_TASK,
      'weight' => 20,
      'file' => 'commerce_shop.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module']),
    );
    */

    $items[$this->path . '/add'] = array(
      'title' => 'Add a shop',
      'description' => 'Add a new shop.',
      'page callback'  => 'commerce_shop_admin_edit',
      'page arguments' => array(commerce_shop_create(array('type' => 'shop'))),
      'access callback'  => 'commerce_shop_access',
      'access arguments' => array('edit'),
      'type' => MENU_LOCAL_ACTION | MENU_LOCAL_TASK,
      'weight' => 20,
      'file' => 'commerce_shop.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module']),
    );

    // Loading and editing project entities
    $items[$this->path . '/shop/' . $wildcard] = array(
      'page callback' => 'commerce_shop_admin_edit',
      'page arguments' => array($id_count + 1),
      'access callback' => 'project_access',
      'access arguments' => array('edit', $id_count + 1),
      'weight' => 0,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'file' => 'commerce_shop.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    $items[$this->path . '/shop/' . $wildcard . '/edit'] = array(
      'title' => 'Edit',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    );
    $items[$this->path . '/shop/' . $wildcard . '/delete'] = array(
      'title' => 'Delete',
      'page callback' => 'commerce_shop_admin_delete',
      'page arguments' => array($id_count + 1),
      'access callback' => 'commerce_shop_access',
      'access arguments' => array('edit', $id_count + 1),
      'file' => 'commerce_shop.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module']),
      'weight' => 10,
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
    );

    // Menu item for viewing commerce_shop.
    $items['shop/' . $wildcard] = array(
      'title callback' => 'commerce_shop_page_title',
      'title arguments' => array(1),
      'page callback' => 'commerce_shop_page_view',
      'page arguments' => array(1),
      'access callback' => 'commerce_shop_access',
      'access arguments' => array('view', 1),
      'file' => 'project.pages.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module']),
      'type' => MENU_CALLBACK,
    );

    return $items;
  }
}
