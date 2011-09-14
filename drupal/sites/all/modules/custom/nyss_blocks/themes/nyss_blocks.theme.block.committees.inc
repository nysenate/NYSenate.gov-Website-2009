<?php
// $Id$

/**
 *  @file
 *  Theme functions for the nyss_blocks 'Committee' block
 */

/**
 *  Subject of the 'Committee' block.
 *
 *  @return
 *    The subject of this block.
 */
function theme_nyss_blocks_view_subject_committees() {
  return t('Choose a committee');
}

/**
 *  Display the content of the 'Committee' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_committees() {
  return drupal_get_form('nyss_blocks_committees_form');
}

/**
 *  Build the form of the 'Committee' block.
 *
 *  @return
 *    The form for this block.
 */
function nyss_blocks_committees_form() {
  $form = array();
  $form['submit'] = array('#type' => 'submit', '#value' => t('Go'));
  $options = nyss_blocks_committees_get_commitees();
  $form['committee'] = array(
    '#type' => 'select',
    '#title' => t(''),
    '#options' => $options,
    '#prefix' => '<div class="clearfix">',
    '#suffix' => '</div>',  
  );
  return $form;
}

/**
 * Redirect the user to selected committee page.
 */
function nyss_blocks_committees_form_submit($form, $form_state) {
  drupal_goto('node/'. $form_state['values']['committee']);
}

/**
 *  Get committees for form.
 *
 *  @return
 *    Array of committees.
 */
function nyss_blocks_committees_get_commitees() {
  $view = views_get_view('committees');
  $view->execute_display('default');
  $committees = $view->result;
  $view->destroy();

  if (empty($committees)) return FALSE;

  $options = array();
  foreach ($committees as $committee) {
    $options[$committee->nid] = $committee->node_title;
  }
  return $options;
}