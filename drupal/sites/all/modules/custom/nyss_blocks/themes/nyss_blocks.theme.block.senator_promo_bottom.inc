<?php
// $Id$

/**
 *  @file
 *  Theme functions for the 'Senator Bottom Promo' block
 */

/**
 *  Subject of the 'Senator Bottom Promo' block.
 *
 *  @return
 *    The subject of that block.
 */
function theme_nyss_blocks_view_subject_senator_promo_bottom() {
  return '';
}

/**
 *  Display the content of the 'Senator Bottom Promo' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_senator_promo_bottom() {
  $node = context_get('nyss', 'committee');
  if (!$node && context_isset('nyss', 'senator')) {
    $node = context_get('nyss', 'senator');
  }
  $img = theme('imagecache', 'senator_promo_bottom', $node->field_promo_bottom[0]['filepath']);
  return l($img, $node->field_promo_bottom[0]['data']['url'], array('html' => TRUE));
}
