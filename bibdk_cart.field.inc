<?php

/**
 * Implements hook_field_info().
 */
function bibdk_cart_field_info() {
  return array(
    'bibdk_cart_manifestation_link' => array(
      'label' => t('Add to cart'),
      'description' => t('Adds the manifestation to the cart'),
      'default_widget' => 'hidden',
      'default_formatter' => 'bibdk_cart_link_default',
      'no_ui' => TRUE,
    ),
  );
}

/**
 * Implements hook_field_load().
 */
function bibdk_cart_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  foreach ($entities as $id => $entity) {
    $items[$id][] = array(
      'id' => $id,
    );
  }
}

/**
 * Implements hook_field_formatter_info().
 */
function bibdk_cart_field_formatter_info() {
  return array(
    'bibdk_cart_link_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_cart_manifestation_link',
      ),
    )
  );
}

/**
 * Implements hook_field_formatter_view().
 */
function bibdk_cart_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  foreach ($items as $delta => $item) {
    $link = bibdk_cart_get_link($item['id']);
    $element[$delta]['#markup'] = theme('bibdk_cart_button', array('add_to_cart' => $link));
  }
  return $element;
}

function bibdk_cart_get_link($id) {
  if(!is_array($id)){
    $id = array($id);
  }

  if (BibdkCart::checkInCart($id)) {
    $title = t('remove_item_from_cart');
  } else {
    $title = t('add_item_to_cart');
  }
  $id = implode(',', $id);
  $link = array(
    '#href' => '#' . $id,
    '#title' => $title,
    '#data-pid' => $id,
  );
  drupal_add_js(drupal_get_path('module', 'bibdk_cart') . '/js/bibdk_cart.js');
  return $link;
}
