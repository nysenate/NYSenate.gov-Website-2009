<?php

/**
 * Implementation of hook_menu_default_menu_custom().
 */
function issues_page_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-taxonomy
  $menus['menu-taxonomy'] = array(
    'menu_name' => 'menu-taxonomy',
    'title' => 'Taxonomy',
    'description' => 'Taxonomy-based menus for the New York Senate website',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Taxonomy');
  t('Taxonomy-based menus for the New York Senate website');


  return $menus;
}
