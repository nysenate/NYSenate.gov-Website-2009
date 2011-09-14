<?php
// $Id$

/**
 *  @file
 *  Theme functions for the nyss_blocks 'Senator Carousel' block
 */

/**
 *  Subject of the 'Front Carousel' block.
 *
 *  @return
 *    The subject for this block.
 */
function theme_nyss_blocks_view_subject_senator_carousel() {
  return '';
}

/**
 *  Display the content of the 'Senator Carousel' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_senator_carousel() {
  if (module_exists('jq')) {
    // I'm using jq_add here. It assumes you have the jQuery Cycle plug-in
    // installed. That plug-in comes bundled with the jQuery Plugins module as
    // jq_add('cycle'), but you could also just drop it into a /plugins or
    // /sites/all/plugins folder (as done here) and call it with the same method.
    jq_add('cycle');
    // Here's the actual call for our cycle slide show plug-in.
    // I'm using the 'fade' effect, fading the image cycle, slowing it from the
    // default with 'timeout', and using 'pause' to allow a pause on mouse hover.
    // There are lots of cool effects; see the plug-in home at malsup.com/jquery/cycle/.
    $js = <<<js
    $('#unique_id ul').cycle({
      fx: 'fade',
      pause: 1,
      timeout: 10000
    });
js;
    // Make it degrade gracefully in non-javascript browsers.
    $js = "if (Drupal.jsEnabled) {  $(document).ready(function() { $js  });  }";
    drupal_add_js($js, 'inline');
  }
//   if (!module_exists('jcarousel')) return t('You must have <em>jcarousel</em> module enabled.');
  $output = '';
  $view = views_get_view('senator_carousel');
  $view->execute('block_1');
  if (count($view->result)) {
    $output .= '<div id="unique_id">';
    $output .= $view->preview('block_1');
    $output .= l('More stories', 'senator/'. nyss_senator_title_to_url() .'/news', array('attributes' => array('class' => 'more_bar')));
    $output .= '</div>';
//     jcarousel_add('#unique_id .item-list', array('scroll' => '1', 'visible' => '1', 'auto' => '3', 'wrap' => 'last', 'animation' => 'slow'));
  }
  return $output;
}