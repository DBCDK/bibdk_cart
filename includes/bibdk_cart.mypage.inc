<?php

/**
 * Implements hook_bibdk_mypage_tabs().
 */
function bibdk_cart_bibdk_mypage_tabs($max_rows = 3) {

  global $user;

  $form['bibdk_cart'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#theme' => 'bibdk_mypage-form',
    '#attributes' => array('class' => array('element-wrapper', 'bibdk-mypage-wrapper')),
  );

  $form['bibdk_cart']['header'] = array(
    '#type' => 'markup',
    '#markup' => t('Cart'),
  );

  $form['bibdk_cart']['rows'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  $cart = BibdkCart::getAll();

  if (sizeof($cart) > 0) {
    $cart = array_slice($cart, 0, $max_rows);
    foreach ($cart as $id => $item) {
      $form['bibdk_cart']['rows'][$id] = array(
        'label_row' => array(
          '#type' => 'markup',
          '#markup' => isset($item->manifestation) ? $item->manifestation->getTitle() : '',
        ),
        'value_row' => array(
          '#type' => 'markup',
          '#markup' => '',
        ),
      );
    }
  }
  else {
    $form['bibdk_cart']['rows'][] = array(
      'item_row' => array(
        '#type' => 'markup',
        '#markup' => t('No items in cart'),
      ),
    );
  }

  $form['bibdk_cart']['link_profile2_tab'] = array(
    '#type' => 'link',
    '#title' => t('Go to cart'),
    '#title_display' => 'invisible',
    '#href' => 'user/' . $user->uid . '/edit/bibdk_cart_list',
    '#options' => array('attributes' => array('title' => t('Go to cart'))),
  );

  return $form;
}

