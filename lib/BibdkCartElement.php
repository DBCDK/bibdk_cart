<?php

class BibdkCartElement {
  public $status;
  public  $element;

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

  public function setStatus($status) {
    $this->status = $status;
  }

  public function getStatus() {
    return $this->status;
  }

  public function toService(){
    return array(
      'oui:cartContentElement' => $this->getElement(),
      'oui:cartContentStatus' => $this->getStatus(),
    );
  }




}
