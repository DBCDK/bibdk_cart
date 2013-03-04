<?php

/**
 * Add cart content to provider on webservice
 *
 * @param $content string|array
 * @param null $user
 * @return array|bool
 */
function _bibdk_cart_add_content_webservice($content, $user = NULL) {

  if ($response = _bibdk_cart_call_webservice('add_cart_content', $content, $user)) {
    return $response;
  }
}

/**
 * Update cart content to provider on webservice
 *
 * @param $content string|array
 * @param null $user
 * @return array|bool
 */
function _bibdk_cart_update_content_webservice($content, $user = NULL){
  if ($response = _bibdk_cart_call_webservice('update_cart_content', $content, $user)) {
    return $response;
  }
}

/**
 * Remove cart content from provider on webservice
 *
 * @param $content string|array
 * @param null $user
 * @return array|bool
 */
function _bibdk_cart_remove_content_webservice($content, $user = NULL) {
  if ($response = _bibdk_cart_call_webservice('remove_cart_content', $content, $user)) {
    return $response;
  }
}

/**
 * Get cart content from provider on webservice
 *
 * @param null $user
 * @return array|bool
 */
function _bibdk_cart_get_cart_on_webservice($user = NULL) {
  if ($response = _bibdk_cart_call_webservice('get_cart', NULL, $user)) {
    $xpath = bibdk_cart_webservice_responce_xpath($response['response']);
    return bibdk_cart_parse_cart_content($xpath);
  }
  return array();
}

/**
 * Check if user is provider user. And call provider service
 *
 * @param $service
 * @param null $content
 * @param null $user
 * @return bool
 */
function _bibdk_cart_call_webservice($service, $content = NULL, $user = NULL) {
  if (!isset($user)) {
    global $user;
  }
  if (!ding_user_is_provider_user($user)) {
    return FALSE;
  }
  try {
    $creds = ding_user_get_creds($user);
  }
  catch (Exception $e) {
    return FALSE;
  }
  // Service implemented in bibdk_provider.user.inc
  return ding_provider_invoke('user', $service, $creds['name'], $content);
}

/**
 * convert xml to xpath
 *
 * @param $xml
 * @return array|DomXPATH
 */
function bibdk_cart_webservice_responce_xpath($xml) {
  $dom = new DomDocument();
  if (!@$dom->loadXML($xml)) {
    if (variable_get('bibdk_provider_enable_logging')) {
      watchdog('bibdk_cart', t('BIBDK cart could not load response: %xml', array('%xml' => var_export($xml, TRUE))), array(), WATCHDOG_ERROR);
    }
    return array();
  }
  $xpath = new DomXPATH($dom);
  $xpath->registerNamespace('oui', 'http://oss.dbc.dk/ns/openuserinfo');
  return $xpath;
}

/**
 * get elements from request from openuserinfo
 *
 * @param $xpath xpath object
 * @return array
 */
function bibdk_cart_parse_cart_content($xpath) {
  if (!isset($xpath)) {
    return array();
  }
// grap agencies
  $query = '//oui:cartContent';
  $nodelist = $xpath->query($query);

// check if empty
  if (empty($nodelist)) {
    return array();
  }

  $cart_content = array();
  foreach ($nodelist as $delta => $node) {
    if (!empty($node->childNodes)) {
      $element = new BibdkCartElement();
      foreach ($node->childNodes as $child) {
        switch ($child->nodeName) {
          case 'oui:cartContentId' :
            $element->setId($child->nodeValue);
            break;
         case 'oui:cartContentElement' :
            $element->setElement($child->nodeValue);
            break;
          case 'oui:cartContentStatus' :
            if (!empty($child->nodeValue))
              $element->setStatus($child->nodeValue);
            break;
        }
      }
      $cart_content[$element->getElement()] = $element;
    }
  }
  return $cart_content;
}
