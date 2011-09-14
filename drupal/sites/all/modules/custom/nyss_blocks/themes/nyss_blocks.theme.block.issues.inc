<?php
// $Id$

/**
 *  @file
 *  Theme functions for the nyss_blocks 'Issues' block
 */

/**
 *  Subject of the 'Issues' block.
 *
 *  @return
 *    The subject of this block.
 */
function theme_nyss_blocks_view_subject_issues() {
  return t('Issues');
}

/**
 *  Display the content of the 'Issues' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_issues() {
  $output = t('Select an issue to see all the articles associated with it.');
  $output .= drupal_get_form('nyss_block_issues_form', $terms);
  return $output;
}

/**
 *  Get all terms from Issues that have a node associated with that term.
 *
 *  @return
 *    Array of terms.
 */
function nyss_block_issues_get_taxonomy() {
  $results = db_query('SELECT td.tid, td.name FROM {term_node} tn INNER JOIN {term_data} td ON tn.tid = td.tid WHERE td.vid = 1 ORDER BY td.name ASC');
  $terms = array();
  while ($term = db_fetch_object($results)) {
    $terms[$term->tid] = strip_tags($term->name);
  }

  return $terms;
}

/**
 *  Build the form of the 'Issue' block.
 *
 *  @return
 *    The form for this block.
 */
function nyss_block_issues_form($form_state, $terms) {
  $form = array();
  $form['submit'] = array('#type' => 'submit', '#value' => t('Go'));
  $options = nyss_block_issues_get_taxonomy();
  $form['issue'] = array(
    '#type' => 'select',
    '#title' => t(''),
    '#options' => $options,
    '#prefix' => '<div class="clearfix">',
    '#suffix' => '</div>',  
  );
  return $form;
}

/**
 * Redirect the user to selected issue page.
 */
function nyss_block_issues_form_submit($form, $form_state) {
  drupal_goto('taxonomy/term/' . $form_state['values']['issue']);
}
