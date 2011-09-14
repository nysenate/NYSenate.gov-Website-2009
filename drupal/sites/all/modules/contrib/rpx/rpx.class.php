<?php
/*
  Generic RPX Library
*/

define('RPX_LIBRARY_VERSION', '0.2');

class RPX {

  const create_api = 'https://rpxnow.com/plugin/create_rp';
  const lookup_api = 'https://rpxnow.com/plugin/lookup_rp';
  const auth_api = 'https://rpxnow.com/api/v2/auth_info';
  const status_api = 'https://rpxnow.com/api/v2/set_status';
    
  /* performs a lookup request for getting information about an RPX account */
  function lookup( $value, $type ) {
    $demographics = 'PHP RPX ' . RPX_LIBRARY_VERSION;
    
    if ( RPX_CLIENT_VERSION ) {
      $demographics .= " / " . RPX_CLIENT_VERSION;
    }
    
    $post_data = array(
        $type => $value,
        'demographics' => $demographics
      );

    $raw_result = RPX::http_post( RPX::lookup_api, $post_data );
    if(!$raw_result) { 
        return false;
    }
    
    return json_decode( $raw_result, true );
  }
  
  /* fetches authorization information from a token */
  function auth_info( $token, $api_key ) {
    $post_data = array(
        'token' => $token,
        'apiKey' => $api_key,
        'format' => 'json'
      );
      
      $raw_result = RPX::http_post( RPX::auth_api, $post_data );
      return json_decode( $raw_result, true );
  }

  /* Set user status */
  function set_status( $api_key, $identifier, $status ) {
    $post_data = array(
        'identifier' => $identifier,
        'apiKey' => $api_key,
        'status' => $status,
        'format' => 'json'
      );

      return RPX::http_post( RPX::status_api, $post_data );
  }

  /* get the list and order of providers */
  function get_enabled_providers($realm, $realm_scheme = 'http'){
    if (!in_array($realm_scheme, array('http', 'https'))) {
      $realm_scheme = 'http';
    }
    
    $url = $realm_scheme."://" . $realm . "/openid/ui_config";
    $context = stream_context_create();
    $raw_data = file_get_contents($url, 0, $context);

    $data = json_decode( $raw_data, true );
    return $data["enabled_providers"];
  }

  function locales() {
    return array('pt-BR', 'vi', 'zh', 'nl', 'sr', 'ko', 'ru', 'sv-SE', 'ro', 'pt', 'it', 'hu', 'fr', 'ja', 'en', 'bg', 'es', 'el', 'pl', 'de', 'cs', 'da');
  }
  
  /*
    Everything below is an internal utility function
  */


  /* builds the current URL for the page being looked at */
  function current_url() {
    if(isset($_SERVER['HTTPS']) && $_SERVER['HTTPS']=='on') {                    
      $proto = "https";
      $standard_port = '443';                                                 
    } else {                                                                    
      $proto = 'http';                                                        
      $standard_port = '80';                                                  
    }                                                                           

    $authority = $_SERVER['HTTP_HOST'];                                         
    if (strpos($authority, ':') === FALSE &&                                    
        $_SERVER['SERVER_PORT'] != $standard_port) {                            
      $authority .= ':' . $_SERVER['SERVER_PORT'];                            
    }                                                                           

    if (isset($_SERVER['REQUEST_URI'])) {                                       
      $request_uri = $_SERVER['REQUEST_URI'];                                 
    } else {                                                                    
      $request_uri = $_SERVER['SCRIPT_NAME'] . $_SERVER['PATH_INFO'];         
      $query = $_SERVER['QUERY_STRING'];                                      
      if (isset($query)) {                                                    
        $request_uri .= '?' . $query;                                       
      }                                                                       
    }                                                                           

    return $proto . '://' . $authority . $request_uri;                          
  }


  /* next three functions are for sending HTTP POST requests */
  function http_post($url, $post_data) {
    if (function_exists('curl_init')) {
      $curl_result = RPX::curl_http_post($url, $post_data);
      // if the curl call errors out, which can happen for a number of reasons,
      // try the other method.
      if (!$curl_result){
          $builtin_result = RPX::builtin_http_post($url, $post_data);
          return $builtin_result;
      }
      return $curl_result;
    } else {
      return RPX::builtin_http_post($url, $post_data);
    }
  }

  function curl_http_post($url, $post_data) {
    $curl = curl_init();
    curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($curl, CURLOPT_URL, $url);
    curl_setopt($curl, CURLOPT_POST, true);
    curl_setopt($curl, CURLOPT_POSTFIELDS, $post_data);
    curl_setopt($curl, CURLOPT_HEADER, false);
    curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, false);
    $raw_data = curl_exec($curl);
    curl_close($curl);
    return $raw_data;
  }


  function builtin_http_post($url, $post_data) {
    $content = http_build_query($post_data);
    $opts = array('http'=>array('method'=>"POST", 'content'=>$content));
    $context = stream_context_create($opts);
    /**
     * Silence warnings for this call
     */
    set_error_handler('errorHandler');
    $raw_data = file_get_contents($url, 0, $context);
    restore_error_handler();
    
    return $raw_data;
  }

}

function errorHandler($errno, $errstr, $errfile, $errline) {
    return;
}

