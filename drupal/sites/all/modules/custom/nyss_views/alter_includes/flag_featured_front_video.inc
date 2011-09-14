<?php
/*
 * View 'flag_featured_front_video'
 */
$view = new view;
$view->name = 'flag_featured_front_video';
$view->description = 'View for flag: Feature video on front';
$view->tag = 'flag';
$view->view_php = '';
$view->base_table = 'node';
$view->is_cacheable = FALSE;
$view->api_version = 2;
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->override_option('relationships', array(
  'flag_content_rel' => array(
    'label' => 'featured_front_video',
    'required' => 1,
    'flag' => 'featured_front_video',
    'user_scope' => 'any',
    'id' => 'flag_content_rel',
    'table' => 'node',
    'field' => 'flag_content_rel',
    'relationship' => 'none',
    'override' => array(
      'button' => 'Override',
    ),
  ),
));
$handler->override_option('fields', array(
  'title' => array(
    'label' => '',
    'link_to_node' => 1,
    'exclude' => 0,
    'id' => 'title',
    'table' => 'node',
    'field' => 'title',
    'relationship' => 'none',
  ),
  'field_video_embed' => array(
    'label' => '',
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 0,
      'path' => '',
      'link_class' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'target' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'html' => 0,
      'strip_tags' => 0,
    ),
    'empty' => '',
    'hide_empty' => 0,
    'empty_zero' => 0,
    'link_to_node' => 0,
    'label_type' => 'none',
    'format' => 'lightbox2',
    'multiple' => array(
      'group' => TRUE,
      'multiple_number' => '',
      'multiple_from' => '',
      'multiple_reversed' => FALSE,
    ),
    'exclude' => 0,
    'id' => 'field_video_embed',
    'table' => 'node_data_field_video',
    'field' => 'field_video_embed',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
  ),
  'teaser' => array(
    'label' => '',
    'exclude' => 0,
    'id' => 'teaser',
    'table' => 'node_revisions',
    'field' => 'teaser',
    'relationship' => 'none',
  ),
));
$handler->override_option('sorts', array(
  'timestamp' => array(
    'order' => 'DESC',
    'granularity' => 'second',
    'id' => 'timestamp',
    'table' => 'flag_content',
    'field' => 'timestamp',
    'relationship' => 'flag_content_rel',
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
      'event' => 'event',
      'video' => 'video',
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
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
  ),
));
$handler->override_option('access', array(
  'type' => 'none',
));
$handler->override_option('cache', array(
  'type' => 'none',
));
$handler->override_option('title', 'Feature video on front');
$handler->override_option('items_per_page', 1);
$handler->override_option('use_pager', '0');
$handler->override_option('style_plugin', 'list');
$handler = $view->new_display('page', 'Featured video', 'page_1');
$handler->override_option('path', 'flags/featured_front_video');
$handler->override_option('menu', array(
  'type' => 'none',
  'title' => 'Feature video on front',
  'description' => '',
  'weight' => '0',
  'name' => 'navigation',
));
$handler->override_option('tab_options', array(
  'type' => 'none',
  'title' => NULL,
  'description' => '',
  'weight' => NULL,
  'name' => 'navigation',
));
$handler = $view->new_display('block', 'Featured video block', 'block_1');
$handler->override_option('title', 'Featured video');
$handler->override_option('block_description', '');
$handler->override_option('block_caching', -1);
$views[$view->name] = $view;

