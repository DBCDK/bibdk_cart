<?php

class BibdkCart {

  /**
   * @return BibdkCartObject
   */
  public static function GetObject() {
    if(!isset($_SESSION['cartobject'])){
      BibdkCartObject::SetObject();
    }
    return $_SESSION['cartobject'];
  }

  /**
   * @return BibdkCartObject
   */
  public static function SetObject() {
    $_SESSION['orderobject'] = new BibdkCart();
  }
}
