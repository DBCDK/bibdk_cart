<?php

/**
 * Implements hook_field_info().
 */
function bibdk_cart_field_info(){
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
      'link' => '', #bibdk_cart_generate_link($id),
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
  fb($items);
  foreach($items as $delta => $item){
    $element[$delta]['#markup'] = theme('bibdk_cart_button', array());
  }

  return $element;
}
