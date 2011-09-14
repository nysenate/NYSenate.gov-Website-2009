<?php
/*
 * View 'json_flag_promote_to_front'
 */
$view = new view;
$view->name = 'json_flag_promote_to_front';
$view->description = 'View for flag: Promote to front';
$view->tag = 'flag';
$view->view_php = '';
$view->base_table = 'node';
$view->is_cacheable = FALSE;
$view->api_version = 2;
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->override_option('relationships', array(
  'flag_content_rel' => array(
    'label' => 'promote_to_senatewide_front',
    'required' => 1,
    'flag' => 'promote_to_senatewide_front',
    'user_scope' => 'any',
    'id' => 'flag_content_rel',
    'table' => 'node',
    'field' => 'flag_content_rel',
    'relationship' => 'none',
  ),
));
$handler->override_option('fields', array(
  'title' => array(
    'id' => 'title',
    'table' => 'node',
    'field' => 'title',
    'label' => 'Title',
    'link_to_node' => 1,
  ),
  'name' => array(
    'label' => 'Author',
    'link_to_user' => 1,
    'id' => 'name',
    'table' => 'users',
    'field' => 'name',
  ),
  'teaser' => array(
    'label' => 'Teaser',
    'exclude' => 0,
    'id' => 'teaser',
    'table' => 'node_revisions',
    'field' => 'teaser',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
  ),
  'edit_node' => array(
    'id' => 'edit_node',
    'table' => 'node',
    'field' => 'edit_node',
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
$handler->override_option('arguments', array(
  'type' => array(
    'default_action' => 'empty',
    'style_plugin' => 'default_summary',
    'style_options' => array(),
    'wildcard' => 'all',
    'wildcard_substitution' => 'All',
    'title' => '',
    'default_argument_type' => 'fixed',
    'default_argument' => '',
    'validate_type' => 'none',
    'validate_fail' => 'not found',
    'id' => 'type',
    'table' => 'node',
    'field' => 'type',
    'relationship' => 'none',
    'default_options_div_prefix' => '',
    'default_argument_user' => 0,
    'default_argument_fixed' => '',
    'default_argument_php' => '',
    'validate_argument_node_type' => array(
      'blog' => 0,
      'committee' => 0,
      'district' => 0,
      'event' => 0,
      'in_the_news' => 0,
      'legislation' => 0,
      'page' => 0,
      'press_release' => 0,
      'report' => 0,
      'senator' => 0,
      'testimony' => 0,
      'video' => 0,
    ),
    'validate_argument_node_access' => 0,
    'validate_argument_nid_type' => 'nid',
    'validate_argument_vocabulary' => array(
      '1' => 0,
      '2' => 0,
    ),
    'validate_argument_type' => 'tid',
    'validate_argument_node_flag_name' => '*relationship*',
    'validate_argument_node_flag_test' => 'flaggable',
    'validate_argument_node_flag_id_type' => 'id',
    'validate_argument_user_flag_name' => '*relationship*',
    'validate_argument_user_flag_test' => 'flaggable',
    'validate_argument_user_flag_id_type' => 'id',
    'validate_argument_php' => '',
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
$handler->override_option('title', 'Promote to senatewide front');
$handler->override_option('header_format', '3');
$handler->override_option('header_empty', 0);
$handler->override_option('footer_format', '2');
$handler->override_option('footer_empty', 0);
$handler->override_option('empty', 'There are currently no posts for this tab.');
$handler->override_option('empty_format', '1');
$handler->override_option('items_per_page', 1);
$handler->override_option('use_pager', '0');
$handler->override_option('style_plugin', 'list');
$handler->override_option('row_plugin', 'node');
$handler->override_option('row_options', array(
  'teaser' => 1,
  'links' => 1,
  'comments' => 0,
));
$handler = $view->new_display('page', 'Front content JSON', 'page_2');
$handler->override_option('relationships', array(
  'flag_content_rel' => array(
    'label' => 'promote_to_senatewide_front',
    'required' => 1,
    'flag' => 'promote_to_senatewide_front',
    'user_scope' => 'any',
    'id' => 'flag_content_rel',
    'table' => 'node',
    'field' => 'flag_content_rel',
    'relationship' => 'none',
    'override' => array(
      'button' => 'Use default',
    ),
  ),
  'field_feature_image_fid' => array(
    'label' => 'Feature image',
    'required' => 0,
    'delta' => -1,
    'id' => 'field_feature_image_fid',
    'table' => 'node_data_field_feature_image',
    'field' => 'field_feature_image_fid',
    'override' => array(
      'button' => 'Use default',
    ),
    'relationship' => 'none',
  ),
));
$handler->override_option('fields', array(
  'title' => array(
    'id' => 'title',
    'table' => 'node',
    'field' => 'title',
    'label' => 'Title',
    'link_to_node' => 1,
  ),
  'teaser' => array(
    'label' => 'Teaser',
    'exclude' => 0,
    'id' => 'teaser',
    'table' => 'node_revisions',
    'field' => 'teaser',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
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
  'filepath' => array(
    'id' => 'filepath',
    'table' => 'files',
    'field' => 'filepath',
    'relationship' => 'field_feature_image_fid',
  ),
  'filesize' => array(
    'id' => 'filesize',
    'table' => 'files',
    'field' => 'filesize',
    'relationship' => 'field_feature_image_fid',
  ),
));
$handler->override_option('style_plugin', 'views_json');
$handler->override_option('style_options', array(
  'format' => 'Simple',
));
$handler->override_option('row_plugin', 'fields');
$handler->override_option('row_options', array(
  'inline' => array(),
  'separator' => '',
  'hide_empty' => 0,
));
$handler->override_option('path', 'front_content/%/json');
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
  'name' => 'navigation',
));
$views[$view->name] = $view;

