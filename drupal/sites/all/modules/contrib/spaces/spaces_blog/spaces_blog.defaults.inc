<?php

/**
 * Helper to implemetation of hook_context_default_contexts().
 */
function _spaces_blog_context_default_contexts() {
  $items = array();

  $items[] = array(
    'namespace' => 'spaces',
    'attribute' => 'feature',
    'value' => 'blog',
    'description' => '',
    'node' => array(
      '0' => 'blog',
    ),
    'views' => array(
      '0' => 'spaces_blog',
    ),
    'menu' => 'blog',
    'block' => array(
      'views_spaces_blog_comments-block_1' => array(
        'module' => 'views',
        'delta' => 'spaces_blog_comments-block_1',
        'weight' => 20,
        'region' => 'right',
        'status' => '0',
        'label' => 'spaces_blog_comments: Recent comments',
        'type' => 'context_ui',
      ),
      'views_spaces_blog-block_1' => array(
        'module' => 'views',
        'delta' => 'spaces_blog-block_1',
        'weight' => 21,
        'region' => 'right',
        'status' => '0',
        'label' => 'spaces_blog: Block',
        'type' => 'context_ui',
      ),
    ),
  );
  return $items;
}

/**
 * Helper to implemetation of hook_menu_default_items().
 */
function _spaces_blog_menu_default_items() {
  $items = array();

  $items[] = array(
    'title' => 'Blog',
    'path' => 'blog',
    'weight' => '0',
    'description' => 'A simple blog.',
  );

  return $items;
}

/**
 * Helper to implemetation of hook_views_default_views().
 */
function _spaces_blog_views_default_views() {
  $views = array();

  // Exported view: spaces_blog
  $view = new view;
  $view->name = 'spaces_blog';
  $view->description = 'Spaces > blog';
  $view->tag = 'spaces';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'nid' => array(
      'label' => 'Nid',
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
      'relationship' => 'none',
    ),
    'field_referenced_book_page_nid' => array(
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'id' => 'field_referenced_book_page_nid',
      'table' => 'node_data_field_referenced_book_page',
      'field' => 'field_referenced_book_page_nid',
    ),
  ));
  $handler->override_option('sorts', array(
    'sticky' => array(
      'order' => 'DESC',
      'id' => 'sticky',
      'table' => 'node',
      'field' => 'sticky',
      'relationship' => 'none',
    ),
    'created' => array(
      'order' => 'DESC',
      'granularity' => 'second',
      'id' => 'created',
      'table' => 'node',
      'field' => 'created',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'uid' => array(
      'default_action' => 'ignore',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '%1\'s blog',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'uid',
      'table' => 'users',
      'field' => 'uid',
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => 'all',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'blog' => 0,
        'shoutbox' => 0,
        'book' => 0,
        'event' => 0,
        'feedapi_node' => 0,
        'feed_ical' => 0,
        'feed_ical_item' => 0,
        'group' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(
        '1' => 0,
      ),
      'validate_argument_type' => 'tid',
      'validate_argument_is_member' => 0,
      'validate_argument_php' => '',
    ),
    'created_year_month' => array(
      'default_action' => 'ignore',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => 'Archive: %2',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'id' => 'created_year_month',
      'table' => 'node',
      'field' => 'created_year_month',
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'blog' => 0,
        'shoutbox' => 0,
        'book' => 0,
        'event' => 0,
        'feedapi_node' => 0,
        'feed_ical' => 0,
        'feed_ical_item' => 0,
        'group' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(
        '1' => 0,
      ),
      'validate_argument_type' => 'tid',
      'validate_argument_php' => '',
      'validate_argument_is_member' => 0,
    ),
  ));
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => 1,
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'blog' => 'blog',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
    ),
    'current' => array(
      'operator' => 'all',
      'value' => 'all',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'current',
      'table' => 'spaces',
      'field' => 'current',
      'relationship' => 'none',
    ),
    'created' => array(
      'operator' => '>',
      'value' => array(
        'type' => 'offset',
        'value' => '-12 months',
        'min' => '',
        'max' => '',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'created',
      'table' => 'node',
      'field' => 'created',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'spaces_feature',
    'spaces_feature' => 'spaces_blog',
  ));
  $handler->override_option('title', 'Blog');
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_options', NULL);
  $handler->override_option('row_plugin', 'node');
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'blog');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
  ));
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->override_option('arguments', array(
    'null' => array(
      'default_action' => 'default',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'must_not_be' => 0,
      'id' => 'null',
      'table' => 'views',
      'field' => 'null',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => 'all',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'blog' => 0,
        'shoutbox' => 0,
        'book' => 0,
        'event' => 0,
        'feedapi_node' => 0,
        'feed_ical' => 0,
        'feed_ical_item' => 0,
        'group' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(
        '1' => 0,
      ),
      'validate_argument_type' => 'tid',
      'validate_argument_is_member' => 0,
      'validate_argument_php' => '',
    ),
    'created_year_month' => array(
      'default_action' => 'summary desc',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'id' => 'created_year_month',
      'table' => 'node',
      'field' => 'created_year_month',
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'blog' => 0,
        'book' => 0,
        'page' => 0,
        'portfolio' => 0,
        'quote' => 0,
        'story' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(
        '12' => 0,
        '13' => 0,
        '8' => 0,
        '1' => 0,
      ),
      'validate_argument_type' => 'tid',
      'validate_argument_php' => '',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('title', 'Archive');
  $handler->override_option('items_per_page', 12);
  $handler->override_option('use_pager', '0');
  $handler->override_option('block_description', '');
  $handler->override_option('block_caching', -1);
  $handler = $view->new_display('feed', 'Feed', 'feed_1');
  $handler->override_option('style_plugin', 'rss');
  $handler->override_option('style_options', array(
    'mission_description' => FALSE,
    'description' => '',
  ));
  $handler->override_option('row_plugin', 'node_rss');
  $handler->override_option('row_options', array(
    'item_length' => 'default',
  ));
  $handler->override_option('path', 'blog/feed');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
  ));
  $handler->override_option('displays', array());
  $handler->override_option('sitename_title', 1);

  $views[$view->name] = $view;

  // Exported view: spaces_blog_comments
  $view = new view;
  $view->name = 'spaces_blog_comments';
  $view->description = 'Spaces > Blog comments';
  $view->tag = 'spaces';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'nid' => array(
      'label' => 'Node',
      'required' => 0,
      'id' => 'nid',
      'table' => 'comments',
      'field' => 'nid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('fields', array(
    'name' => array(
      'label' => '',
      'link_to_user' => 1,
      'exclude' => 0,
      'id' => 'name',
      'table' => 'comments',
      'field' => 'name',
      'relationship' => 'nid',
    ),
    'timestamp' => array(
      'label' => '',
      'date_format' => 'reldate',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'timestamp',
      'table' => 'comments',
      'field' => 'timestamp',
      'relationship' => 'nid',
    ),
    'comment' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 1,
        'max_length' => '100',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 1,
      ),
      'exclude' => 0,
      'truncate' => 100,
      'id' => 'comment',
      'table' => 'comments',
      'field' => 'comment',
      'relationship' => 'nid',
    ),
    'title' => array(
      'label' => '',
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'timestamp' => array(
      'order' => 'DESC',
      'granularity' => 'second',
      'id' => 'timestamp',
      'table' => 'comments',
      'field' => 'timestamp',
      'relationship' => 'nid',
    ),
  ));
  $handler->override_option('filters', array(
    'comment_count' => array(
      'operator' => '!=',
      'value' => array(
        'value' => '0',
        'min' => '',
        'max' => '',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'comment_count',
      'table' => 'node_comment_statistics',
      'field' => 'comment_count',
      'relationship' => 'none',
    ),
    'status' => array(
      'operator' => '=',
      'value' => 1,
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'current' => array(
      'operator' => 'all',
      'value' => 'all',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'current',
      'table' => 'spaces',
      'field' => 'current',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'spaces_feature',
    'spaces_feature' => 'spaces_blog',
  ));
  $handler->override_option('title', 'Recent comments');
  $handler->override_option('items_per_page', 5);
  $handler->override_option('style_plugin', 'list');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'type' => 'ul',
  ));
  $handler = $view->new_display('block', 'Recent comments', 'block_1');
  $handler->override_option('block_description', '');
  $handler->override_option('block_caching', -1);

  $views[$view->name] = $view;

  return $views;
}
