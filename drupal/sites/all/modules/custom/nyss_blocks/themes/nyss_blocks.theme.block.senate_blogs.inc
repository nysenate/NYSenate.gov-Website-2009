<?php
// $Id$

/**
 *  @file
 *  Theme functions for the nyss_blocks 'Senate Blogs' block
 */

/**
 *  Subject of the 'Senate Blogs' block.
 *
 *  @return
 *    The subject of this block.
 */
function theme_nyss_blocks_view_subject_senate_blogs() {
  return t('Senate Blogs');
}

/**
 *  Display the content of the 'Senate Blogs' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_senate_blogs() {
  $output = '<div id="happening_now_blogs">'. views_embed_view('flag_promote_to_front', 'default', 'blog') .'</div>';
  return $output;
}
