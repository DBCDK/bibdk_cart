<?php

class BibdkCartElement {
  public $status;
  public  $element;
  public $manifestation;

  function __construct() {
  }

  public function setElement($pids) {
    if (!is_array($pids)) {
      $pids = array($pids);
    }
    $this->element = implode(',', $pids);
  }

  public function getElement() {
    return $this->element;
  }

  public function getElementArray() {
    return explode(',', $this->element);
  }


  public function setStatus($status) {
    $this->status = $status;
  }

  public function getStatus() {
    return $this->status;
  }

  public function setManifestation($manifestation) {
    $this->manifestation = $manifestation;
  }

  public function getManifestation() {
    return $this->manifestation;
  }



  public function toService(){
    return array(
      'oui:cartContentElement' => $this->getElement(),
      'oui:cartContentStatus' => $this->getStatus(),
    );
  }

  public function getId(){
    return reset( $this->getElementArray() );
  }




}
