<?php
// $Id$

/**
 *  @file
 *  Theme functions for the 'Senate Video Services' block for any video pages.
 */

/**
 *  Subject of the 'Senate Video Services' block.
 *  @return
 *    The subject of that block.
 */
function theme_nyss_blocks_view_subject_sen_video() {
  return t('Senate Video Services');
}

/**
 *  Display the content of the 'Senate Video Services' block.
 *
 */
function theme_nyss_blocks_view_content_sen_video() {
  $output = t('Watch NY Senate video on the web!');
  
  $header = array(t('Service'), t('Channel'));
  $data = array(array(t('YouTube'), l(t('NY Senate'), 'http://www.youtube.com/nysenate')), array(t('YouTube'), l(t('NY Senate Uncut'), 'http://www.youtube.com/nysenateuncut')), array(t('Blip.tv'), l(t('NY Senate'), 'http://nysenate.blip.tv/')), array(t('Blip.tv'), l(t('NY Senate Uncut'), 'http://nysenateuncut.blip.tv/')), array(t('iTunes'), '<a href="itpc://nysenateuncut.blip.tv/rss/itunes/">'.t('NYS Podcast').'</a>'));
  
  $output .= theme_table($header, $data, array('width'=>'100%')); //. l('NY Senate', 'http://www.youtube.com/nysenate') . ' and ' . l('NY Senate Uncut', 'http://www.youtube.com/nysenateuncut') . ' on YouTube.');
//  $output .= t('Visit ' . l('NY Senate', 'http://www.youtube.com/nysenate') . ' and ' . l('NY Senate Uncut', 'http://www.youtube.com/nysenateuncut') . ' on YouTube.');
  return $output;
}
