<?php

/**
 * Add cart content to provider on webservice
 * @param $content string|array
 * @return array|bool
 */
function _bibdk_cart_add_content_webservice($content){
  if ($response = _bibdk_cart_call_webservice('add_cart_content', $content)){
    return $response;
  }
}

/**
 * Remove cart content from provider on webservice
 * @param $content string|array
 * @return array|bool
 */
function _bibdk_cart_remove_content_webservice($content){
  if ($response = _bibdk_cart_call_webservice('remove_cart_content', $content)){
    return $response;
  }
}

/**
 * Get cart content from provider on webservice
 * @return array|bool
 */
function _bibdk_cart_get_cart_on_webservice() {
  if ($response = _bibdk_cart_call_webservice('get_cart')){
    $xpath = bibdk_cart_webservice_responce_xpath($response['response']);
    $result = bibdk_cart_parse_cart_content($xpath);
    return $result;
  }
  return array();
}

/**
 * Check if user is provider user. And call provider service
 * @param $service
 * @param null $content
 * @return bool
 */
function _bibdk_cart_call_webservice($service, $content = null){
  global $user;
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
 * @param $xpath xpath object
 * @return array
 */
function bibdk_cart_parse_cart_content($xpath) {
  if (!isset($xpath)) {
    return array();
  }
// grap agencies
  $query = '//oui:cartContentElement';
  $nodelist = $xpath->query($query);

// check if empty
  if (empty($nodelist)) {
    return array();
  }

  $cart_content = array();
  foreach ($nodelist as $node) {
    if (!empty($node->childNodes)) {
      foreach ($node->childNodes as $child) {
        $cart_content[$child->nodeValue] = $child->nodeValue;
      }
    }
  }
  return $cart_content;
}
