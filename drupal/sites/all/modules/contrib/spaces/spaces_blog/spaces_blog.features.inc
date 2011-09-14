<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function spaces_blog_context_default_contexts() {
  module_load_include('inc', 'spaces_blog', 'spaces_blog.defaults');
  return _spaces_blog_context_default_contexts();
}

/**
 * Implementation of hook_menu_default_items().
 */
function spaces_blog_menu_default_items() {
  module_load_include('inc', 'spaces_blog', 'spaces_blog.defaults');
  return _spaces_blog_menu_default_items();
}

/**
 * Implementation of hook_views_default_views().
 */
function spaces_blog_views_default_views() {
  module_load_include('inc', 'spaces_blog', 'spaces_blog.defaults');
  return _spaces_blog_views_default_views();
}
