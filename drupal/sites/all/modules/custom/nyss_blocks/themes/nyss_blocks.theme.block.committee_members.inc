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
function theme_nyss_blocks_view_subject_committee_members() {
  $committee = context_get('nyss', 'committee');
  
  if($committee->field_committee_members[0]['value']) {
    return '';
  }
  else {
    return t('Committee Members');
  }
}

/**
 *  Display the content of the 'Committee Members' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_committee_members() {
  $committee = context_get('nyss', 'committee');
  $output = '<h2 class="committee_name">' . $committee->title . '</h2>';
  $output .= '<h2 class="title block_title">' . t('Committee members') . '</h2>';
  // Add chair or chairpersons
  if($committee->field_pseudochair[0]['value'] != 1) {
    foreach ($committee->field_chairs as $field_chair) {
      $chair = node_load($field_chair['nid']);
      $district = db_result(db_query('SELECT n.title FROM {node} n WHERE n.nid = %d', $chair->field_senators_district[0]['nid']));
      $output .= '<div class="committee-chair">';
      $output .= '<a class="picture" href="'. url('node/'. $chair->nid) .'">';
      $output .= theme('imagecache', 'senator_teaser', $chair->field_profile_picture[0]['filepath'], $chair->title, $chair->title, NULL);
      $output .= '</a>' . '<label>' . t('Chair: ') . '</label>' . '<a href="'. url('node/'. $chair->nid) .'">Sen. ' . $chair->title . '</a><br />';
      $output .= substr($chair->field_party_affiliation[0]['value'], 0, 1) . '-' . strip_tags($district);
      
      // add chairperson contact link
      $contacturl = trim(preg_replace('#[^\p{L}\p{N}]+#u', ' ', $chair->title));
      $contacturl = str_replace(' ', '-', strtolower($contacturl));
      $contacturl = 'senator/'. $contacturl;
      $output .= '<span class="contact"> | '. l(t('Contact'), $contacturl . '/contact').'</span>';

      $output .= theme('nyss_blocks_view_content_social_buttons', $chair);
      $output .= '</div><div style="clear:both;"></div>';
    }
  }

  // add committee members
  $output .= '<div class="committee-members">';
  if($committee->field_committee_members[0]['value']) {
    $output .= $committee->field_committee_members[0]['value'];
  }
  else {
    $output .= views_embed_view('committee_members', 'default');
  }
  $output .= '</div>';
  return $output;
}
