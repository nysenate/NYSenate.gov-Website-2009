<?php
// $Id: livestream.inc,v 1.1 2010/10/21 00:21:27 alexua Exp $

/**
 * @file
 *   This include processes livestream.com media files for use by emfield.module.
 */

define('EMVIDEO_LIVESTREAM_MAIN_URL', 'http://www.livestream.com/');
define('EMVIDEO_LIVESTREAM_API_INFO', 'http://www.livestream.com/userguide/index.php/API_overview');
define('EMVIDEO_LIVESTREAM_API_APPLICATION_URL', 'http://securebeta.livestream.com/myaccount/api');
define('EMVIDEO_LIVESTREAM_REST_ENDPOINT', 'http://channel.api.livestream.com/1.0');

/* http://channel.api.livestream.com/1.0/embed?channel=proshowcase
 * returns the actual video HTML
 *
 * http://channel.api.livestream.com/1.0/livestatus?channel=proshowcase
 * returns a result indicating whether the channel is live or not
 */


/**
 * hook emvideo_PROVIDER_info
 * this returns information relevant to a specific 3rd party video provider
 * @return
 *   an array of strings requested by various admin and other forms
 *   'name' => the translated name of the provider
 *   'url' => the url to the main page for the provider
 *   'settings_description' => a description of the provider that will be posted in the admin settings form
 *   'supported_features' => an array of rows describing the state of certain supported features by the provider.
 *      These will be rendered in a table, with the columns being 'Feature', 'Supported', 'Notes'.
 */
function emvideo_livestream_info() {
  $features = array(
    array(t('Autoplay'), t('Yes'), ''),
    array(t('RSS Attachment'), t('No'), ''),
    array(t('Show related videos'), t('No'), ''),
    array(t('Thumbnails'), t('Yes'), t('')),
    array(t('Custom player colors'), t('No'), ''),
    array(t('Full screen mode'), t('Yes'), t('You may customize the player to enable or disable full screen playback. Full screen mode is enabled by default.')),
  );
  return array(
    'provider' => 'livestream',
    'name' => t('Livestream'),
    'url' => EMVIDEO_LIVESTREAM_MAIN_URL,
    'settings_description' => t('These settings specifically affect videos displayed from <a href="@livestream" target="_blank">Livestream</a>. You can learn more about its <a href="@api" target="_blank">API</a> here.', array('@livestream' => EMVIDEO_LIVESTREAM_MAIN_URL, '@api' => EMVIDEO_LIVESTREAM_API_INFO)),
    'supported_features' => $features,
  );
}

/**
 * hook emvideo_PROVIDER_settings
 * this should return a subform to be added to the emvideo_settings() admin settings page.
 * note that a form field will already be provided, at $form['PROVIDER'] (such as $form['livestream'])
 * so if you want specific provider settings within that field, you can add the elements to that form field.
 */
function emvideo_livestream_settings() {
  $form['livestream']['api'] = array(
    '#type' => 'fieldset',
    '#title' => t('Livestream API'),
    '#description' => t('You will first need to apply for an API Developer Key from the <a href="@livestream" target="_blank">Livestream Developer Profile page</a>. Note that you do not need this key to display Livestream videos or their thumbnails.', array('@livestream' => EMVIDEO_LIVESTREAM_API_APPLICATION_URL)),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['livestream']['api']['emvideo_livestream_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Livestream API Key'),
    '#default_value' => variable_get('emvideo_livestream_api_key', ''),
    '#description' => t('Please enter your Livestream Developer Key here.'),
  );

  $form['livestream']['player_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Embedded video player options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['livestream']['player_options']['emvideo_livestream_full_screen'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow fullscreen'),
    '#default_value' => variable_get('emvideo_livestream_full_screen', 1),
    '#description' => t('Allow users to view video using the entire computer screen.'),
  );
  $form['livestream']['player_options']['emvideo_livestream_autoplay'] = array(
    '#type' => 'checkbox',
    '#title' => t('Auto play'),
    '#default_value' => variable_get('emvideo_livestream_autoplay', 1),
    '#description' => t('Automatically play the video when users visit its page.'),
  );
  return $form;
}

/**
 * hook emfield_PROVIDER_data
 *
 * provides an array to be serialised and made available with $item elsewhere
 */
function emvideo_livestream_data($field, $item) {
	
  $data = array();
  
  // create some 'field' version control
  $data['emvideo_livestream_version'] = 1;
  
 // Thumbnail creation 
  
  // The links from the RSS 2.0 API contain ondemand in the video string
  // So we need to handle that seperatly
  
  if (strpos(strtolower($item['value']),'ondemand') !== false ) {

  	// Explodes mychannel/../videoID into parts
    $channelname = explode('/', $item['value']);
  	
    // Example API 2.0 call : http://xMYCHANNELNAMEx.channel-api.livestream-api.com/2.0/thumbnail?id=VIDEOID
    $api_url = 'http://x' . $channelname[0] . 'x.channel-api.livestream-api.com/2.0/thumbnail?id='. $channelname[2];

         
  } else {
  }; 

  // Get the thumbnail via an API 2.0 call
 
  $result = drupal_http_request($api_url); 
        
  if ($result->code == 200) {
    $parser = drupal_xml_parser_create($result->data);
    $vals = array();
    $index = array();
    xml_parse_into_struct($parser, $result->data, $vals);
    xml_parser_free($parser);
    if (count($vals)) {
      foreach ($vals as $val) {
        if ($val['tag'] == 'MEDIA:THUMBNAIL') {
          $data['thumbnail']['url'] = $val['attributes']['URL'];
          break;
        }
      }
    }
  }	
  
  // gather info about the item
  // RSS / MRSS feeds with the item would have enough info
  // alternative try getting the minimum from an http get
  $url = 'http://www.livestream.com/'. $item['value'];
  $response = emfield_request_header('livestream', $url);  

  if ($response->code == 200) {
    // probably shouldn't give the 303 path
    $data['flash']['url'] = $url;
    $data['flash']['size'] = $response->headers['Content-Length'];
    $data['flash']['mime'] = $response->headers['Content-Type'];
  }

  return $data;
}

/**
 *
 */
function emvideo_livestream_rss($item, $teaser = NULL) {
  if ($item['value']) {
    if (!empty($item['data']['emvideo_livestream_data_version']) && $item['data']['emvideo_livestream_data_version'] >= 1) {
      $data = $item['data'];
    }
    else {
      $data = emvideo_livestream_data(NULL, $item);
    }

    $file = array();
    if (is_array($data['flash'])) {
      $file['filepath'] = $data['flash']['url'];
      $file['filesize'] = $data['flash']['size'];
      $file['filemime'] = $data['flash']['mime'];
    }
    $file['thumbnail']['filepath'] = $data['thumbnail']['url'];

    return $file;
  }
}

/**
 * this is a wrapper for emvideo_request_xml that includes livestream's api key
 */
function emvideo_livestream_request($method, $args = array(), $cached = TRUE) {
  $args['dev_id'] = trim(variable_get('emvideo_livestream_api_key', ''));
  $args['method'] = $method;
  $request = module_invoke('emfield', 'request_xml', 'livestream', EMVIDEO_LIVESTREAM_REST_ENDPOINT, $args, $cached);
  return $request;
}

/**
 * hook emvideo_PROVIDER_extract
 * this is called to extract the video code from a pasted URL or embed code.
 * @param $embed
 *   an optional string with the pasted URL or embed code
 * @return
 *   either an array of regex expressions to be tested, or a string with the video code to be used
 *   if the hook tests the code itself, it should return either the string of the video code (if matched), or an empty array.
 *   otherwise, the calling function will handle testing the embed code against each regex string in the returned array.
 */
function emvideo_livestream_extract($embed = '') {
  // http://channel.api.livestream.com/1.0/embed?channel=proshowcase
  // http://www.livestream.com/proshowcase
  return array(
    '@livestream\.com/1.0/embed\?channel=([^"\&]+)@i',
    '@www\.livestream\.com/([^"\&]+)@i',
  );
}


/**
 * hook emvideo_PROVIDER_embedded_link($video_code)
 * returns a link to view the video at the provider's site
 *  @param $video_code
 *    the string containing the video to watch
 *  @return
 *    a string containing the URL to view the video at the original provider's site
 */
function emvideo_livestream_embedded_link($video_code) {
  return 'http://www.livestream.com/'. $video_code;
}

/**
 * The embedded flash displaying the livestream video.
 */
function theme_emvideo_livestream_flash($embed, $width, $height, $autoplay=TRUE, $options = array()) {
  static $count;
  $output = '';
  if ($embed) {
  	
    $fullscreen = isset($options['fullscreen']) ? $options['fullscreen'] : variable_get('emvideo_livestream_full_screen', 1);
    $fullscreen_value = $fullscreen ? "true" : "false";

    // This is a little funky. Essentially it ignores whatever is passed in to $autoplay and retrieves the setting or
    // takes a value from the options array. Also, don't I need to convert the & into &amp;?
    $autoplay = isset($options['autoplay']) ? $options['autoplay'] : variable_get('emvideo_livestream_autoplay', 1);
    $autoplay_value = $autoplay ? 'true' : 'false';

    // Micah's ugly hack.
    $embed = str_replace('?', '&amp;', $embed);
    $embed = str_replace('clipId', 'clip', $embed);   
    
    // Livestream URLs from the rss api contain /ondemand/ instead of ?clip=
    // So we fix it
    $embed = str_replace('/ondemand/', '&amp;clip=', $embed);
        
//    $id = isset($options['id']) ? $options['id'] : 'emvideo-livestream-flash-'. (++$count);
    $div_id = isset($options['div_id']) ? $options['div_id'] : 'emvideo-livestream-flash-wrapper-'. $count;

    $output .= <<<FLASH
      <div id="$div_id">
      
      <object width="$width" height="$height" id="lsplayer" classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000">
        <param name="movie" value="http://cdn.livestream.com/grid/LSPlayer.swf?channel=$embed&amp;autoPlay=$autoplay_value"></param>
        <param name="allowScriptAccess" value="always"></param>
        <param name="allowFullScreen" value="$fullscreen_value"></param>
        <embed name="lsplayer" 
          wmode="transparent"
          src="http://cdn.livestream.com/grid/LSPlayer.swf?channel=$embed&amp;autoPlay=$autoplay_value" 
          width="$width"
          height="$height"
          allowScriptAccess="always"
          allowFullScreen="$fullscreen_value"
          type="application/x-shockwave-flash">
        </embed>
        
      </object>
      </div>
FLASH;
    
  }
  return $output;
}

/**
 * hook emvideo_PROVIDER_thumbnail
 * returns the external url for a thumbnail of a specific video
 * TODO: make the args: ($embed, $field, $item), with $field/$item provided if we need it, but otherwise simplifying things
 *  @param $field
 *    the field of the requesting node
 *  @param $item
 *    the actual content of the field from the requesting node
 *  @return
 *    a URL pointing to the thumbnail
 */
function emvideo_livestream_thumbnail($field, $item, $formatter, $node, $width, $height) {
	
  global $base_url;
  global $base_path;
  global $theme;

  if ($item['data']['thumbnail']['url']) {
    return $item['data']['thumbnail']['url'];
  } else
  {
    return $base_url . $base_path . drupal_get_path('theme', $theme) . '/no-pre.png';
  }
  	
  // Always return the larger image, since we're storing images locally.
  // $tn = larger image
  // return $tn;
  
}

/**
 * hook emvideo_PROVIDER_video
 * this actually displays the full/normal-sized video we want, usually on the default page view
 *  @param $embed
 *    the video code for the video to embed
 *  @param $width
 *    the width to display the video
 *  @param $height
 *    the height to display the video
 *  @param $field
 *    the field info from the requesting node
 *  @param $item
 *    the actual content from the field
 *  @return
 *    the html of the embedded video
 */
function emvideo_livestream_video($embed, $width, $height, $field, $item, &$node, $autoplay) {
  $output = theme('emvideo_livestream_flash', $embed, $width, $height, $autoplay);
  return $output;
}

/**
 * hook emvideo_PROVIDER_preview
 * this actually displays the preview-sized video we want, commonly for the teaser
 *  @param $embed
 *    the video code for the video to embed
 *  @param $width
 *    the width to display the video
 *  @param $height
 *    the height to display the video
 *  @param $field
 *    the field info from the requesting node
 *  @param $item
 *    the actual content from the field
 *  @return
 *    the html of the embedded video
 */
function emvideo_livestream_preview($embed, $width, $height, $field, $item, &$node, $autoplay) {
  $output = theme('emvideo_livestream_flash', $embed, $width, $height, $autoplay);
  return $output;
}

/**
 * Implementation of hook_emfield_subtheme.
 */
function emvideo_livestream_emfield_subtheme() {
    return array(
        'emvideo_livestream_flash'  => array(
            'arguments' => array('embed' => NULL, 'width' => NULL, 'height' => NULL, 'autoplay' => NULL),
            'file' => 'providers/livestream.inc'
        )
    );
}
