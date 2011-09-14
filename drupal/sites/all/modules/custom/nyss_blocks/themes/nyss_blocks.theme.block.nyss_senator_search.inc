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
 *    The subject of this block.
 */
function theme_nyss_blocks_view_subject_nyss_senator_search() {
  
}

/**
 *  Display the content of the 'Senator Search' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_nyss_senator_search() {
  return theme('nyss_senator_search');
}