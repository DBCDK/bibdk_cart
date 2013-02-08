<?php

function bibdk_cart_add_to_cart() {
  if (!isset($_REQUEST['pid'])) {
    throw new Exception('pid has to be set');
  }

  $pid = $_REQUEST['pid'];

  if (BibdkCart::checkInCart($pid)) {
    BibdkCart::remove($pid);
    $saved = 0;
  }
  else {
    BibdkCart::add($pid);
    $saved = 1;
  }

  $data['saved'] = $saved;
  $data['pid'] = $pid;
  $data['classid'] = strtolower(strtr($pid, array(':' => '-')));
  $data['cartcount'] = (string)count(BibdkCart::getAll());

  drupal_json_output($data);
}
