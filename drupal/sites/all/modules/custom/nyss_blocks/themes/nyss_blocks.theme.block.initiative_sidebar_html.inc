<?php
// $Id$

/**
 *  @file
 *  Theme functions for the 'Custom Sidebar HTML' block
 */

/**
 *  Subject of the 'Custom Sidebar HTML' block.
 *
 *  @return
 *    The subject of that block.
 */
function theme_nyss_blocks_view_subject_initiative_sidebar_html() {
  if(arg(0) == 'node' && is_numeric(arg(1))) {
    $node = node_load(arg(1));
  }
  if (isset($node->field_initiative) && $node->field_initiative[0]['nid']) {
    $node = node_load($node->field_initiative[0]['nid']);
  }
  if ($node->type == 'initiative') {
    return t('About @initiative_title', array('@initiative_title' => $node->title));
  }
}

/**
 *  Display the content of the 'Custom Sidebar HTML' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_initiative_sidebar_html() {
  if(arg(0) == 'node' && is_numeric(arg(1))) {
    $node = node_load(arg(1));
  }
  if (isset($node->field_initiative) && $node->field_initiative[0]['nid']) {
    $node = node_load($node->field_initiative[0]['nid']);
  }
  if (isset($node->field_sidebar_html) && $node->field_sidebar_html[0]['value']) {
    return $node->field_sidebar_html[0]['value'];
  }
  return '';
}
