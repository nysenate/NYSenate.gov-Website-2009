<?php
// $Id$

/**
 *  @file
 *  Theme functions for the 'Committee Members' block
 */

/**
 *  Subject of the 'Committee Members' block.
 *
 *  @return
 *    The subject of that block.
 */
function theme_nyss_blocks_view_subject_flickr_gallery() {
  return t('Photo Gallery');
}

/**
 *  Display the content of the 'Committee Members' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_flickr_gallery() {
  if (arg(1) == 21915 || arg(1) == 15) {
    $id = '72157620599320540';
  }

  $iframe = '<iframe align="center" src="http://www.flickr.com/slideShow/index.gne?set_id=' . $id . ' frameBorder="0" width="265" height="350" scrolling="no"></iframe>';
  return $iframe;
}
