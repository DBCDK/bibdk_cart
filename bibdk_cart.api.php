<?php

/**
 * @file
 * API documentation for Bibdk_cart.
 */

/**
 * Documentation of hook_cart_actions().
 * A renderable form item should be returned as well as any submisssion functions should be provided
 * @return array $action
 */
function hook_cart_actions(){
  $action['action_name'] = array(
    '#type' => 'submit',
    '#value' => t('Value'),
    '#submit' => array('module_name_submit_function'),
    '#weight' => 0,
  );

  return $action;
}
