<?php

function bibdk_cart_add_to_cart() {
  if (!isset($_REQUEST['pid'])) {
    throw new Exception('pid has to be set');
  }

  $pids = $_REQUEST['pid'];
  if (BibdkCart::checkInCart($pids)) {
    BibdkCart::remove($pids);
    $saved = 0;
  }
  else {
    $object = new BibdkCartElement();
    $object->setElement($pids);
    BibdkCart::add($object);
    $saved = 1;
  }

  $data['saved'] = $saved;
  $data['pid'] = $pids;
  $data['classid'] = strtolower(strtr($pids, array(':' => '-')));
  $data['cartcount'] = (string)count(BibdkCart::getAll());

  drupal_json_output($data);
}

function bibdk_cart_empty_cart() {

}
