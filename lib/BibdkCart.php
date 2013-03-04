<?php

class BibdkCart {

  private static $content = NULL;

  /**
   * Add pid to bibdk_cart
   *
   * @param BibdkCartElement $object
   * @internal param array|string $pids
   */
  public static function add(BibdkCartElement $object) {
    $key = $object->getElement();
    if (!self::checkInCart($key)){
      // TODO: Return ID and add to object
      _bibdk_cart_add_content_webservice($object->toService());
      $_SESSION['bibdk_cart'][$key] = $object;
    }
  }

  /**
   * Remove pid from cart
   *
   * @param $pids string|array
   */
  public static function remove($pids) {
    if ($element = BibdkCart::checkInCart($pids)){
      _bibdk_cart_remove_content_webservice($element->toService());
      unset($_SESSION['bibdk_cart'][$element->getElement()]);
    }
  }

  public static function update($object){
    $key = $object->getElement();
    if (self::checkInCart($key)){
      _bibdk_cart_update_content_webservice($object->toService());
      $_SESSION['bibdk_cart'][$key] = $object;
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

  /** Get Id's of all elements in cart
   * @return array
   */
  public static function getAllIds(){
    $cart = self::getAll();
    $ids = array();
    foreach($cart as $element){
      $ids[] = $element->getElementId();
    }
    return $ids;
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
   * @return bool|BibdkCartElement
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
    return isset($bibdk_cart[$pid]) ? $bibdk_cart[$pid] : FALSE;
  }

}
