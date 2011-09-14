<?php
/*
 * View 'json_flag_feature_front_csl'
 */
$view = new view;
$view->name = 'json_flag_feature_front_csl';
$view->description = 'View for flag: Feature on front carousel';
$view->tag = 'flag';
$view->view_php = '';
$view->base_table = 'node';
$view->is_cacheable = FALSE;
$view->api_version = 2;
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->override_option('relationships', array(
  'flag_content_rel' => array(
    'label' => 'feature_on_front_carousel',
    'required' => 1,
    'flag' => 'feature_on_front_carousel',
    'user_scope' => 'any',
    'id' => 'flag_content_rel',
    'table' => 'node',
    'field' => 'flag_content_rel',
    'relationship' => 'none',
    'override' => array(
      'button' => 'Override',
    ),
  ),
  'field_feature_image_fid' => array(
    'label' => 'Feature image',
    'required' => 1,
    'delta' => -1,
    'id' => 'field_feature_image_fid',
    'table' => 'node_data_field_feature_image',
    'field' => 'field_feature_image_fid',
    'relationship' => 'none',
  ),
));
$handler->override_option('fields', array(
  'field_feature_image_fid' => array(
    'label' => '',
    'link_to_node' => 1,
    'label_type' => 'none',
    'format' => 'front_carousel_linked',
    'multiple' => array(
      'group' => TRUE,
      'multiple_number' => '',
      'multiple_from' => '',
      'multiple_reversed' => FALSE,
    ),
    'exclude' => 0,
    'id' => 'field_feature_image_fid',
    'table' => 'node_data_field_feature_image',
    'field' => 'field_feature_image_fid',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
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
    'table' => 'flag_content',
    'field' => 'timestamp',
    'relationship' => 'flag_content_rel',
    'override' => array(
      'button' => 'Override',
    ),
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
));
$handler->override_option('access', array(
  'type' => 'none',
));
$handler->override_option('cache', array(
  'type' => 'none',
));
$handler->override_option('title', 'Feature on front carousel');
$handler->override_option('items_per_page', 5);
$handler->override_option('use_pager', '0');
$handler->override_option('style_plugin', 'list');
$handler->override_option('style_options', array(
  'grouping' => '',
  'type' => 'ul',
));
$handler = $view->new_display('page', 'Carousel JSON', 'page_3');
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
  'filepath' => array(
    'label' => 'Path',
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
      'strip_tags' => 0,
      'html' => 0,
    ),
    'empty' => '',
    'hide_empty' => 0,
    'empty_zero' => 0,
    'link_to_file' => 0,
    'exclude' => 0,
    'id' => 'filepath',
    'table' => 'files',
    'field' => 'filepath',
    'relationship' => 'field_feature_image_fid',
    'override' => array(
      'button' => 'Use default',
    ),
  ),
  'filemime' => array(
    'label' => 'Mime type',
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
      'strip_tags' => 0,
      'html' => 0,
    ),
    'empty' => '',
    'hide_empty' => 0,
    'empty_zero' => 0,
    'link_to_file' => 0,
    'exclude' => 0,
    'id' => 'filemime',
    'table' => 'files',
    'field' => 'filemime',
    'relationship' => 'field_feature_image_fid',
    'override' => array(
      'button' => 'Use default',
    ),
  ),
  'filesize' => array(
    'label' => 'Size',
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
      'strip_tags' => 0,
      'html' => 0,
    ),
    'empty' => '',
    'hide_empty' => 0,
    'empty_zero' => 0,
    'file_size_display' => 'formatted',
    'exclude' => 0,
    'id' => 'filesize',
    'table' => 'files',
    'field' => 'filesize',
    'relationship' => 'field_feature_image_fid',
    'override' => array(
      'button' => 'Use default',
    ),
  ),
  'field_feature_image_fid' => array(
    'label' => '',
    'link_to_node' => 1,
    'label_type' => 'none',
    'format' => 'front_carousel_linked',
    'multiple' => array(
      'group' => TRUE,
      'multiple_number' => '',
      'multiple_from' => '',
      'multiple_reversed' => FALSE,
    ),
    'exclude' => 0,
    'id' => 'field_feature_image_fid',
    'table' => 'node_data_field_feature_image',
    'field' => 'field_feature_image_fid',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
  ),
));
$handler->override_option('style_plugin', 'views_json');
$handler->override_option('style_options', array(
  'format' => 'Simple',
));
$handler->override_option('path', 'front_carousel/json');
$handler->override_option('menu', array(
  'type' => 'none',
  'title' => 'Feature on front carousel',
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
$views[$view->name] = $view;
