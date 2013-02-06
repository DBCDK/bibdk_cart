<?php

function bibdk_cart_add_to_cart(){
  if(!isset($_REQUEST['pid'])){
    throw new Exception('pid has to be set');
  }

  $pid = $_REQUEST['pid'];

  //TODO test if pid already exsists in cart
  $data['saved'] = 1;
  $data['pid'] = $pid;

  drupal_json_output($data);
}
