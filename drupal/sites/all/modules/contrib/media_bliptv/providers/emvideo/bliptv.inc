<?php
// $Id: bliptv.inc,v 1.1.2.8 2011/02/18 17:16:07 aaron Exp $

/**
 * @file media_bliptv/providers/emvideo/bliptv.inc
 * This include processes blip.tv media files for use by emfield.module.
 */

function emvideo_bliptv_info() {
  $features = array(
    array(t('Autoplay'), t('Yes'), ''),
    array(t('RSS attachment'), t('Yes'), t('When displaying in an RSS feed, these videos will be attached to the feed. (The feed reader or aggregator must support enclosure tags.)')),
    array(t('Thumbnails'), t('Yes'), ''),
  );
  return array(
    'provider' => 'bliptv',
    'name' => t('Blip.tv'),
    'url' => MEDIA_BLIPTV_MAIN_URL,
    'settings_description' => t('These settings specifically affect videos displayed from <a href="@provider" target="_blank">Blip.tv</a>.', array('@provider' => MEDIA_BLIPTV_MAIN_URL)),
    'supported_features' => $features,
  );
}

function emvideo_bliptv_settings() {
  module_load_include('inc', 'media_bliptv', 'includes/media_bliptv.admin');
  return media_bliptv_admin_form();
}

/**
 *  Implements emvideo_PROVIDER_validate hook.
 */
function emvideo_bliptv_validate($value, $error_field) {
  if ($value == 'BLIP_TV_ERROR_EMBED') {
    form_set_error($error_field, t('Please do not use the Embed Code from Blip.TV. You must instead paste the URL from the video page.'));
  }
}

/**
 *  Implement hook emvideo_PROVIDER_data_version().
 */
function emvideo_bliptv_data_version() {
  return MEDIA_BLIPTV_DATA_VERSION;
}

function emvideo_bliptv_data($field, $item) {
  return media_bliptv_metadata($item['value']);
}

function emvideo_bliptv_request($code, $cacheable = TRUE, $skin = 'rss', $show = FALSE) {
  $args = array();
  $file = $show ? "http://$code.blip.tv/file/?skin=" . $skin : "http://blip.tv/file/$code?skin=" . $skin;
  return module_invoke('emfield', 'request_xml', 'bliptv', $file, $args, $cacheable, FALSE, $code .':'. $skin . ($show ? ':show' : ':post'));
}

function emvideo_bliptv_extract($embed) {
  // @TODO: Until #293153 is resolved, don't allow pasting embed code from Blip.TV.
  preg_match('@blip\.tv/play/([^"\&\?/]+)@i', $embed, $matches);
  if ($matches[1]) {
    return 'BLIP_TV_ERROR_EMBED';
  }
  return array(
    '@blip\.tv/rss/flash/([^"\&\?/]+)@i',
    '@blip\.tv/file/view/([^"\&\?/]+)@i',
    '@blip\.tv/file/([^"\&\?/]+)@i',
  );
}

/**
 * hook emvideo_PROVIDER_duration($item)
 * Returns the duration of the video in seconds.
 *  @param $item
 *    The video item itself, which needs the $data array.
 *  @return
 *    The duration of the video in seconds.
 */
function emvideo_bliptv_duration($item) {
  if (!isset($item['data']['emvideo_bliptv_data_version']) || $item['data']['emvideo_bliptv_data_version'] < 2) {
    $item['data'] = emvideo_bliptv_data(NULL, $item);
  }
  return isset($item['data']['flv']['duration']) ? $item['data']['flv']['duration'] : 0;
}

/**
 * hook emvideo_PROVIDER_embedded_link($video_code)
 * returns a link to view the video at the provider's site.
 *  @param $video_code
 *    The string containing the video to watch.
 *  @return
 *    A string containing the URL to view the video at the original provider's site.
 */
function emvideo_bliptv_embedded_link($video_code) {
  return media_bliptv_video_url($video_code);
}

/**
 * Look for a file for an enclosure of the preferred tag.
 *
 * @param array $data
 *  The data from the provider video item.
 * @param string $preferred_tag
 *  The preferred tag from the data array, for instance 'web' or 'mov'.
 * @return mixed
 *  If the preferred tag is 'override' or 'none', the return that for possible
 *  later overriding. Otherwise, if we have a file in the data array for that
 *  tag, then return the file array. Otherwise return NULL, so we'll specify
 *  the fallback 'flv' tag, if it exists.
 */
function _media_bliptv_get_video_info_from_preferred_tag($data, $preferred_tag) {
  if (in_array($preferred_tag, array('override', 'none'))) {
    return $preferred_tag;
  }

  if ($data[$preferred_tag]['url']) {
    return $data[$preferred_tag];
  }
}

/**
 * Implementation of hook emvideo_PROVIDER_rss().
 *
 * Providers may supply an enclosure for rss feeds. This expects something in
 * a file format, so would be an object in the format of $file->filepath,
 * $file->filesize, and $file->filemime.
 */
function emvideo_bliptv_rss($item, $teaser = NULL) {
  if ($item['value']) {
    // If this item is of a really old version, we'll try to compensate.
    if ($item['data']['emvideo_bliptv_data_version'] >= 1) {
      $data = $item['data'];
    }
    else {
      $data = emvideo_bliptv_data(NULL, $item);
    }

    // Get the preferred type for the rss feed.
    $video_info = _media_bliptv_get_video_info_from_preferred_tag($data, media_bliptv_variable_get('rss_tag'));

    // Grab the preferred filetype rather than tag, so .mov rather than 'web'.
    if ($video_info == 'override') {
      $video_info = _media_bliptv_get_video_info_from_preferred_tag($data, media_bliptv_variable_get('rss_format'));
    }

    // Default to flv if there's no available clip format.
    if (is_null($video_info) || ($video_info == 'override')) {
      $video_info = $data['flv'];
    }

    // Begin building file object.
    if (is_array($video_info)) {
      $file = array();
      // Create temporary name/path for newly uploaded files.
      $file['filepath'] = $video_info['url'];
      $file['filesize'] = $video_info['size'];
      $file['filemime'] = $video_info['mime'];

      // Additional data for Y! MRSS.
      $file['thumbnail']['filepath'] = $data['thumbnail']['url'];
      $file['width'] = ($video_info['width']) ? $video_info['width'] : 0;
      $file['height'] = ($video_info['height']) ? $video_info['height'] : 0;
      $file['duration'] = ($video_info['duration']) ? $video_info['duration'] : FALSE;
      // @TODO Media:credit role="author" ...

      return $file;
    }
  }
}

function emvideo_bliptv_thumbnail($field, $item, $formatter, $node, $width, $height, $options = array()) {
  if (($item['data']['emvideo_bliptv_data_version'] >= 1) || isset($item['data']['thumbnail']['url'])) {
    $tn = $item['data']['thumbnail']['url'];
  }
  else {
    $tn = $item['data']['thumbnail'];
  }
  return $tn;
}

function emvideo_bliptv_video($code, $width, $height, $field, $item, $node, $autoplay, $options = array()) {
  if (($item['data']['emvideo_bliptv_data_version'] >= 1) || isset($item['data']['flv']['url'])) {
    $flv = $item['data']['flv']['url'];
  }
  else {
    $flv = $item['data']['flv'];
  }
  $thumbnail = emvideo_bliptv_thumbnail($field, $item, NULL, $node, $width, $height, $options);

  $output = theme('media_bliptv', array('media_id' => $code, 'width' => $width, 'height' => $height, 'field' => $field, 'item' => $item, 'autoplay' => $autoplay, 'flv' => $flv, 'thumbnail' => $thumbnail));
  return $output;
}

function emvideo_bliptv_preview($code, $width, $height, $field, $item, $node, $autoplay, $options = array()) {
  if ($item['data']['emvideo_bliptv_data_version'] >= 1) {
    $flv = $item['data']['flv']['url'];
    $thumbnail = $item['data']['thumbnail']['url'];
  }
  else {
    $flv = $item['data']['flv'];
    $thumbnail = $item['data']['thumbnail'];
  }
  $output = theme('media_bliptv', array('media_id' => $code, 'width' => $width, 'height' => $height, 'field' => $field, 'item' => $item, 'autoplay' => $autoplay, 'flv' => $flv, 'thumbnail' => $thumbnail));
  return $output;
}

/**
 * Implement hook_emvideo_PROVIDER_content_generate().
 */
function emvideo_bliptv_content_generate() {
  return array(
    'http://blip.tv/file/836041/',
    'http://blip.tv/file/1492835/',
    'http://blip.tv/file/2015750/',
    'http://blip.tv/file/2312026/',
  );
}
