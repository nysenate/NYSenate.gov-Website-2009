<?php
// $Id$

/**
 *  @file
 *  Theme functions for the 'Group Links' block
 */

/**
 *  Subject of the 'Group Links' block.
 *
 *  @return
 *    The subject of that block.
 */
function theme_nyss_blocks_view_subject_group_links() {
  $group = node_load(arg(1));
  
  if($group->og_groups) {
    foreach($group->og_groups as $groupnode) {
      $group = node_load($groupnode);      
    }
  }
  return t('@group_title Links', array('@group_title' => $group->title));
}

/**
 *  Display the content of the 'Group Links' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_group_links() {
  $node = node_load(arg(1));
  if($node->og_groups) {
    foreach($node->og_groups as $groupnode) {
      $node = node_load($groupnode);      
    }
  }
  $output = '';
  switch($node->nid) {
    case 23128:
      $output  = '<ul>';
      $output .= '<li>'.l(t('Team'),     'department/cio/team').'</li>';
      //$output .= '<li>'.l(t('Projects'), 'dept/'.arg(1).'/projects').'</li>';
      $output .= '<li>'.l(t('Twitter'),  'http://twitter.com/NYsenateCIO').'</li>';
      $output .= '<li>'.l(t('Facebook'), 'http://www.facebook.com/pages/New-York-NY/NY-Senate-CIOs-office/62313685063').'</li>';
      $output .= '</ul>';
      break;
  }
  return $output;
}
