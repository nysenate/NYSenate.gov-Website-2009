<?php
// $Id$

/**
 *  @file
 *  Theme functions for the 'About this blog' block for Senators' Blogs.
 */

/**
 *  Subject of the 'About this blog' block.
 *  @return
 *    The subject of that block.
 */
function theme_nyss_blocks_view_subject_my_committees() {
  return t('My Committees');
}

/**
 *  Display the content of the 'About this blog' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_my_committees() {
  $committees = nyss_senator_get_committees();
  if (!empty($committees)) {
    $committee_links = array();
    foreach ($committees as $committee) {
      $committee_links[$committee['nid']] = l($committee['title'], 'node/' . $committee['nid']);
      if ($committee['chair']) {
        $committee_links[$committee['nid']] .= ' - <span class="committee-chair">' . t('Chair Person') . '</span>';
      }
    }
    return theme_item_list($committee_links);
  }
  else {
    return t('This senator is not on any committees.');
  }
}
