<?php

/**
 * @file
 * API documentation for Bibdk_cart.
 */

/**
 * Documentation of hook_cart_actions().
 * A renderable form item should be returned as well as any submisssion functions
 * should be provided
 *
 * Including cart-action-btn as class in attributes array will ensure that the
 * button will only by enabled when at least one item in the cart view is checked.
 *
 * @return array $action
 */
function hook_cart_actions(){
  $action['action_name'] = array(
    '#type' => 'submit',
    '#value' => t('Value'),
    '#submit' => array('module_name_submit_function'),
    '#weight' => 0,
    '#attributes' => array(
      'class' => array(
        'cart-action-btn', 'disabled'
      ),
    ),
  );

  return $action;
}
