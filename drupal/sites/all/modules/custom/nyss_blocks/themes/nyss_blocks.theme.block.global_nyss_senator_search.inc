<?php
// $Id$

/**
 *  @file
 *  Theme functions for the nyss_blocks 'Senator Search' block
 */

/**
 *  Subject of the 'Senator Search' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_subject_global_nyss_senator_search() {
  return t('Find My Senator:');
}

/**
 *  Display the content of the 'Senator Search' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_global_nyss_senator_search() {
  return theme('nyss_senator_search');
}