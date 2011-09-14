<?php
// $Id: media_bliptv.variables.inc,v 1.1.2.2 2011/02/18 17:16:07 aaron Exp $

/**
 * @file media_bliptv/includes/media_bliptv.admin.inc
 * Contains the variables and defaults used by Media: YouTube.
 */

define('MEDIA_BLIPTV_NAMESPACE', 'media_bliptv__');

define('MEDIA_BLIPTV_MAIN_URL', 'http://blip.tv/');
define('MEDIA_BLIPTV_API_INFO', 'http://blip.tv/about/api/');
define('MEDIA_BLIPTV_DEFAULT_RSS_TYPE', 'flv');

/**
 *  This defines the version of the content data array that we serialize
 *  in emvideo_bliptv_data(). If we change the expected keys of that array,
 *  we must increment this value, which will allow older content to be updated
 *  to the new version automatically.
 */
define('MEDIA_BLIPTV_DATA_VERSION', 3);

/**
 * Wrapper for variable_get() that uses the Media: YouTube variable registry.
 *
 * @param string $name
 *  The variable name to retrieve. Note that it will be namespaced by
 *  pre-pending MEDIA_BLIPTV_NAMESPACE, as to avoid variable collisions
 *  with other modules.
 * @param unknown $default
 *  An optional default variable to return if the variable hasn't been set
 *  yet. Note that within this module, all variables should already be set
 *  in the media_bliptv_variable_default() function.
 * @return unknown
 *  Returns the stored variable or its default.
 *
 * @see media_bliptv_variable_set()
 * @see media_bliptv_variable_del()
 * @see media_bliptv_variable_default()
 */
function media_bliptv_variable_get($name, $default = NULL) {
  // Allow for an override of the default.
  // Useful when a variable is required (like $path), but namespacing still desired.
  if (!isset($default)) {
    $default = media_bliptv_variable_default($name);
  }
  // Namespace all variables
  $variable_name = MEDIA_BLIPTV_NAMESPACE . $name;
  return variable_get($variable_name, $default);
}

/**
 * Wrapper for variable_set() that uses the Media: YouTube variable registry.
 *
 * @param string $name
 *  The variable name to set. Note that it will be namespaced by
 *  pre-pending MEDIA_BLIPTV_NAMESPACE, as to avoid variable collisions with
 *  other modules.
 * @param unknown $value
 *  The value for which to set the variable.
 * @return unknown
 *  Returns the stored variable after setting.
 *
 * @see media_bliptv_variable_get()
 * @see media_bliptv_variable_del()
 * @see media_bliptv_variable_default()
 */
function media_bliptv_variable_set($name, $value) {
  $variable_name = MEDIA_BLIPTV_NAMESPACE . $name;
  return variable_set($variable_name, $value);
}

/**
 * Wrapper for variable_del() that uses the Media: YouTube variable registry.
 *
 * @param string $name
 *  The variable name to delete. Note that it will be namespaced by
 *  pre-pending MEDIA_BLIPTV_NAMESPACE, as to avoid variable collisions with
 *  other modules.
 *
 * @see media_bliptv_variable_get()
 * @see media_bliptv_variable_set()
 * @see media_bliptv_variable_default()
 */
function media_bliptv_variable_del($name) {
  $variable_name = MEDIA_BLIPTV_NAMESPACE . $name;
  variable_del($variable_name);
}

/**
 * The default variables within the Media: YouTube namespace.
 *
 * @param string $name
 *  Optional variable name to retrieve the default. Note that it has not yet
 *  been pre-pended with the MEDIA_BLIPTV_NAMESPACE namespace at this time.
 * @return unknown
 *  The default value of this variable, if it's been set, or NULL, unless
 *  $name is NULL, in which case we return an array of all default values.
 *
 * @see media_bliptv_variable_get()
 * @see media_bliptv_variable_set()
 * @see media_bliptv_variable_del()
 */
function media_bliptv_variable_default($name = NULL) {
  static $defaults;

  if (!isset($defaults)) {
    $defaults = array(
      'width' => 624,
      'height' => 380,
      'autoplay' => FALSE,
      'wmode' => 'opaque',
      'allowfullscreen' => 'true',
      'allowscriptaccess' => 'always',
      'quality' => 'high',
      'bgcolor' => '#FFFFFF',
      'use_embed' => TRUE,
      'src_url' => 'http://blip.tv/play/',
      'noflash' => 'You must have Flash installed to view this content.',
      'rss_tag' => MEDIA_BLIPTV_DEFAULT_RSS_TYPE,
      'rss_format' => MEDIA_BLIPTV_DEFAULT_RSS_TYPE,
    );
  }

  if (!isset($name)) {
    return $defaults;
  }

  if (isset($defaults[$name])) {
    return $defaults[$name];
  }
}

/**
 * Return the fully namespace variable name.
 *
 * @param string $name
 *  The variable name to retrieve the namespaced name.
 * @return string
 *  The fully namespace variable name, prepended with
 *  MEDIA_BLIPTV_NAMESPACE.
 */
function media_bliptv_variable_name($name) {
  return MEDIA_BLIPTV_NAMESPACE . $name;
}
