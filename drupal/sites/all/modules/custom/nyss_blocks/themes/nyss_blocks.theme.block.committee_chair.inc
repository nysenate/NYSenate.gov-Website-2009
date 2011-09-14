<?php
// $Id$

/**
 *  @file
 *  Theme functions for the 'Committee Chair' block
 */

/**
 *  Subject of the 'Committee Chair' block.
 *
 *  @return
 *    The subject of that block.
 */
function theme_nyss_blocks_view_subject_committee_chair() {
  $committee = context_get('nyss', 'committee');
  return format_plural(count($committee->field_chairs), t('Committee Chair'), t('Committee Chairs'));
}

/**
 *  Display the content of the 'Committee Chair' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_committee_chair() {
  $committee = context_get('nyss', 'committee');
  if($committee->field_pseudochair[0]['value'] != 1) {
    foreach ($committee->field_chairs as $field_chair) {
      $chair = node_load($field_chair['nid']);
      $district = db_result(db_query('SELECT n.title FROM {node} n WHERE n.nid = %d', $chair->field_senators_district[0]['nid']));
      $output .= '<div class="committee-chair">';
      $output .= '<a class="picture" href="'. url('node/'. $chair->nid) .'">';
      // <img src="' . base_path() . file_directory_path() . '/imagecache/senator_teaser/profile-pictures/' . $chair->field_profile_picture[0]['filename'] . '" alt="' . $chair->title . ' photo" />
      $output .= theme('imagecache', 'senator_teaser', $chair->field_profile_picture[0]['filepath'], $chair->title, $chair->title, NULL);
      $output .= '</a><a href="'. url('node/'. $chair->nid) .'">Sen. ' . $chair->title . '</a><br />';
      $output .= substr($chair->field_party_affiliation[0]['value'], 0, 1) . '-' . strip_tags($district);
      $output .= theme('nyss_blocks_view_content_social_buttons', $chair);
      $output .= '</div>';
    }
  }
  return $output;
}
