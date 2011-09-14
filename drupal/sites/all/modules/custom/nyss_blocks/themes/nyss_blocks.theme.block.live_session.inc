<?php
// $Id$

/**
 *  @file
 *  Theme functions for the nyss_blocks 'Live Session' block
 */

/**
 *  Subject of the 'Live Search' block.
 *
 *  @return
 *    The subject of this block.
 */
function theme_nyss_blocks_view_subject_live_session() {
  $status = nyss_session_get_status();
  return $status['headline'];
}

/**
 *  Display the content of the 'Live Session' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_live_session() {
  $status = nyss_session_get_status();
  if ($status['use_js']) {
    drupal_add_js(drupal_get_path('module', 'nyss_internalusers') .'/test_ip.js');
  } else if ($status['display_video']) {
    drupal_add_js(drupal_get_path('module', 'nyss_internalusers') .'/test_ip_no_lbdc_feed.js');
  }
  $output = '<div class="senate-status-message">' . $status['message'] . '</div>';
  if (nyss_videosettings_livestream_working()) {
    $output .= '<div id="conditional-livestream">';
    $output .= nyss_blocks_livestream_session_player();
  } else {
    $output .= '<div id="livestream-not-working">';
  }
  $output .= '</div>';
    // $output .= '<h2 class="title block_title">' . t('This Week in the Senate') . '</h2>';
    // $output .= views_embed_view('week_senate', 'block_1');
  $output .= '<h2 class="title block_title">' . t('This Month in the Senate') . '</h2>';
  $output .= views_embed_view('month_senate', 'block_1');

  return $output;
}

function nyss_blocks_livestream_session_player() {
  $current_channel = variable_get('nyss_videosettings_main_livestream_channel', 'nysenate');
  $output = '<script src="http://static.mogulus.com/scripts/playerv2.js?channel=' . $current_channel . '&amp;layout=playerEmbedDefault&amp;backgroundColor=0xffffff&amp;backgroundAlpha=1&amp;backgroundGradientStrength=0&amp;chromeColor=0x000000&amp;headerBarGlossEnabled=true&amp;controlBarGlossEnabled=true&amp;chatInputGlossEnabled=false&amp;uiWhite=true&amp;uiAlpha=0.5&amp;uiSelectedAlpha=1&amp;dropShadowEnabled=true&amp;dropShadowHorizontalDistance=10&amp;dropShadowVerticalDistance=10&amp;paddingLeft=0&amp;paddingRight=0&amp;paddingTop=0&amp;paddingBottom=0&amp;cornerRadius=3&amp;backToDirectoryURL=null&amp;bannerURL=null&amp;bannerText=null&amp;bannerWidth=320&amp;bannerHeight=50&amp;showViewers=true&amp;embedEnabled=true&amp;chatEnabled=false&amp;onDemandEnabled=true&amp;programGuideEnabled=false&amp;fullScreenEnabled=true&amp;reportAbuseEnabled=false&amp;gridEnabled=false&amp;initialIsOn=false&amp;initialIsMute=false&amp;initialVolume=10&amp;contentId=null&amp;initThumbUrl=null&amp;playeraspectwidth=4&amp;playeraspectheight=3&amp;mogulusLogoEnabled=false&amp;width=270&amp;height=211&amp;wmode=window" type="text/javascript"></script>
  ';
  $output .= '<p style="padding: 0; font-size: .8em;">';
  $windowlink = l(t('larger window.'), 'new-york-state-senate-live');
  $watch = t('Watch in a !windowlink', array('!windowlink' => $windowlink));
  $output .= "$watch<br />\n";
  $livestream = l(t('Livestream.com/nysenate'), "http://www.livestream.com/$current_channel");
  $stream = l(t('RealPlayer Stream.'), 'http://senreal3.senate.state.ny.us/ramgen/sennet_tv.smil');
  $trouble = t('Having trouble? Try viewing the video at !livestream. You can also try viewing with our !stream',
    array(
      '!livestream' => $livestream,
      '!stream' => $stream,
    ));
  $output .= "$trouble";
  $output .= '</p>';
  return $output;
}


