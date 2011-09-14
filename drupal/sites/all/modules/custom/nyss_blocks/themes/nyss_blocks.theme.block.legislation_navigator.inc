<?php
// $Id$

/**
 *  @file
 *  Theme functions for the 'Legislation Navigator' block for Senators' Blogs.
 */

/**
 *  Subject of the 'Legislation Navigator' block.
 *  @return
 *    The subject of that block.
 */
function theme_nyss_blocks_view_subject_legislation_navigator() {
  return t('Legislation Navigator');
}

/**
 *  Display the content of the 'Legislation Navigator' block.
 *
 */
function theme_nyss_blocks_view_content_legislation_navigator() {
  if (arg(0) == 'node' && is_numeric(arg(1)) && is_null(arg(2))) {
    $node = node_load(arg(1));

    $tree = menu_tree_all_data(book_menu_name($node->book['bid']));
    return '<div class="book-navigation-tree">'. menu_tree_output($tree) . '</div>';  
  }  
}
