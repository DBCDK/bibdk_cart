<?php

class BibdkCart {

  private static $content = NULL;

  /**
   * Add pid to bibdk_cart
   *
   * @param $pids string|array
   */
  public static function add($pids) {

    if (!is_array($pids)) {
      $pids = array($pids);
    }
    $key = implode(',', $pids);
    _bibdk_cart_add_content_webservice($pids);
    $_SESSION['bibdk_cart'][$key] = $key;
  }

  /**
   * Remove pid from cart
   *
   * @param $pids string|array
   */
  public static function remove($pids) {
    if (!is_array($pids)) {
      $pids = array($pids);
    }

    $key = implode(',', $pids);
    _bibdk_cart_remove_content_webservice($key);

    if (isset($_SESSION['bibdk_cart'][$key])) {
      unset($_SESSION['bibdk_cart'][$key]);
    }
  }

  /**
   * Get all pids in cart
   *
   * @return array
   */
  public static function getAll() {
    global $user;
    if (!isset($_SESSION['bibdk_cart'])){
      if ($user->uid && ding_user_is_provider_user($user)){
        $_SESSION['bibdk_cart'] = _bibdk_cart_get_cart_on_webservice();
      }
      else {
        $_SESSION['bibdk_cart'] = array();
    }
  }
    return $_SESSION['bibdk_cart'];
  }

  public static function emptyCart() {
    if (isset($_SESSION['bibdk_cart'])) {
      _bibdk_cart_remove_content_webservice($_SESSION['bibdk_cart']);
      unset($_SESSION['bibdk_cart']);
    }
  }

  /**
   * Check if pid is in cart
   *
   * @param $pid
   * @return bool
   */
  public static function checkInCart($pid) {
    $bibdk_cart = self::getAll();
    if (!isset($bibdk_cart)) {
      return FALSE;
    }
    if (!is_array($pid)) {
      $pid = array($pid);
    }
    $pid = implode(',', $pid);
    if (isset($bibdk_cart[$pid])) {
      return TRUE;
    }
    return FALSE;
  }

}
