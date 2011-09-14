<?php

/**
 *  @file
 *  Theme functions for the 'Search All Blogs' block.
 */

/**
 *  Subject of the 'Search All Blogs' block.
 *
 *  @return
 *    The subject of that block.
 */
function theme_nyss_blocks_view_subject_search_blogs() {
  return t('Search All Blogs');
}

/**
 *  Display the content of the 'Search All Blogs' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_search_blogs() {
  $view = views_get_view('blog_search');
  $view->set_display('default');
  $view->init_handlers();
  $form_state = array(
    'view' => $view,
    'display' => $view->display_handler->display,
    'method' => 'get',
    'rerender' => TRUE,
    'no_redirect' => TRUE,
  );
  $output = drupal_build_form('views_exposed_form', $form_state);
  $output = str_replace('value="Apply"', 'value="Search"', $output);
  return $output;
}