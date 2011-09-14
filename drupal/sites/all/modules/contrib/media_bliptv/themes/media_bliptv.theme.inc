<?php
// $Id: media_bliptv.theme.inc,v 1.1.2.1 2011/02/18 17:16:07 aaron Exp $

/**
 * @file media_bliptv/themes/media_bliptv.theme.inc
 *
 * Theme preprocess functions for the Media: BlipTV module.
 */

/**
 * Template preprocess function for theme('media_bliptv').
 *
 * Variables accepted:
 *  'media_id' => The video code.
 *  'width' => The width of the video to display.
 *  'height' => The height of the video to display.
 *  'field' => The field of the content.
 *  'item' => The item array returned by the emvideo field.
 *  'autoplay' => TRUE or FALSE, to automatically play the video on display.
 *  'flv' => The .flv file returned by blip.tv.
 *  'thumbnail' => The URL of the thumbnail to display.
 */
function template_preprocess_media_bliptv(&$variables) {
  $variables = array_merge($variables, $variables['variables']);
  $variables['media_id'] = check_plain($variables['media_id']);

  if ($variables['media_id']) {
    $variables['autoplay'] = isset($variables['autoplay']) ? $variables['autoplay'] : media_bliptv_variable_get('autoplay');

    $variables['width'] = isset($variables['width']) ? check_plain($variables['width']) : media_bliptv_variable_get('width');
    $variables['height'] = isset($variables['height']) ? check_plain($variables['height']) : media_bliptv_variable_get('height');

    $variables['showpage'] = $variables['item']['data']['showpage'];
    $variables['post_id'] = $variables['item']['data']['post_id'];

    // @TODO: Use the following if/when we allow featured shows to be embedded.
    // $file = $variables['item']['data']['is_show'] ? "http://{$variables['media_id']}.blip.tv/rss/flash/" : 'http://blip.tv/rss/flash/'. $variables['post_id'];
    if (isset($variables['item']['data']['m4v']['embed_code']['0'])) {
      $variables['embed_code'] = $variables['item']['data']['m4v']['embed_code']['0'];
    }
    else if (isset($variables['item']['data']['flv']['embed_code']['0'])) {
      $variables['embed_code'] = $variables['item']['data']['flv']['embed_code']['0'];
    }

    if ($variables['embed_code']) {
      // This allows the player to optionally display with iPhone.
      $variables['embed_code'] .= '%2Em4v';

      $query = array(
        'file' => 'http://blip.tv/rss/flash/'. $variables['post_id'],
        'referrer' => 'blip.tv',
        'source' => 1,
        'use_direct' => 1,
        'use_documents' => 1,
        'enable_js' => 'true',
        'show_player_path' => 'http://a.blip.tv/scripts/flash/stratos.swf',
        'autostart' => $variables['autoplay'] ? 'true' : 'false',
        'playerUrl' => 'http://a.blip.tv/scripts/flash/stratos.swf',
        'staggeredLoad' => 'true',
        'showinfo' => 'false',
        'enableHtml5Player' => 'true',
      );
      if ($variables['item']['data']['rss']) {
        $query['feed_url'] = $variables['item']['data']['rss'];
      }
      else {
        $query['feed_url'] = $variables['showpage'] .'/rss';
      }
      $variables['query'] = isset($variables['query']) ? $variables['query'] : array();
      $variables['query'] = array_merge($variables['query'], $query);
      $variables['src'] = url(media_bliptv_variable_get('src_url') . $variables['embed_code'], array('query' => $variables['query']));

      $variables['quality'] = isset($variables['quality']) ? check_plain($variables['quality']) : check_plain(media_bliptv_variable_get('quality'));
      $variables['bgcolor'] = isset($variables['bgcolor']) ? check_plain($variables['bgcolor']) : check_plain(media_bliptv_variable_get('bgcolor'));
      $variables['wmode'] = isset($variables['mode']) ? check_plain($variables['wmode']) : check_plain(media_bliptv_variable_get('wmode'));
      $variables['allowfullscreen'] = isset($variables['allowfullscreen']) ? check_plain($variables['allowfullscreen']) : check_plain(media_bliptv_variable_get('allowfullscreen'));
      $variables['allowscriptaccess'] = isset($variables['allowscriptaccess']) ? check_plain($variables['allowscriptaccess']) : check_plain(media_bliptv_variable_get('allowscriptaccess'));

      $variables['noflash'] = isset($variables['noflash']) ? filter_xss($variables['noflash']) : filter_xss(media_bliptv_variable_get('noflash'));

      if (media_bliptv_variable_get('use_embed')) {
        $variables['output'] = theme('media_bliptv_flash_embed', $variables);
      }
      else {
        $variables['output'] = theme('media_bliptv_flash_object', $variables);
      }
    }
  }
}

function template_preprocess_media_bliptv_flash_object(&$variables) {
  $variables = array_merge($variables, $variables['variables']);
}

function template_preprocess_media_bliptv_flash_embed(&$variables) {
  $variables = array_merge($variables, $variables['variables']);
}
