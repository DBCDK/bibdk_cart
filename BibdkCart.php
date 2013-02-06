<?php

class BibdkCart {

  /**
   * Add pid to bibdk_cart
   * @param $pids string|array
   */
  public static function add ($pids){
    if (!is_array($pids))
      $pids = array($pids);
    foreach($pids as $pid)
      $_SESSION['bibdk_cart'][$pid] = $pid;
  }

  /**
   * Remove pid from cart
   * @param $pids string|array
   */
  public static function remove ($pids){

    if (!is_array($pids))
      $pids = array($pids);

    foreach($pids as $pid){
      if (isset($_SESSION['bibdk_cart'][$pid]))
        unset($_SESSION['bibdk_cart'][$pid]);
    }
  }

  /**
   * Get all pids in cart
   * @return array
   */
  public static function getAll(){
    if(!isset($_SESSION['bibdk_cart']))
      return array();
    return $_SESSION['bibdk_cart'];
  }

  public static function emptyCart(){
    if (isset($_SESSION['bibdk_cart']))
      unset($_SESSION['bibdk_cart']);
  }

  /**
   * Check if pid is in cart
   * @param $pid
   * @return bool
   */
  public static function checkInCart($pid){
    if(!isset($_SESSION['bibdk_cart']))
      return false;
    if (in_array($pid, $_SESSION['bibdk_cart']))
        return true;
    return false;
  }

}
