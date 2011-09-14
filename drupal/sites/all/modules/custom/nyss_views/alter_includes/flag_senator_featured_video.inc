<?php
/*
 * View 'flag_senator_featured_video'
 */
$view = new view;
$view->name = 'flag_senator_featured_video';
$view->description = 'View for flag: Feature video on the senator page';
$view->tag = 'flag';
$view->view_php = '';
$view->base_table = 'node';
$view->is_cacheable = FALSE;
$view->api_version = 2;
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->override_option('relationships', array(
  'field_senator_nid' => array(
    'label' => 'Senator',
    'required' => 0,
    'delta' => -1,
    'id' => 'field_senator_nid',
    'table' => 'node_data_field_senator',
    'field' => 'field_senator_nid',
    'relationship' => 'none',
  ),
  'flag_content_rel' => array(
    'label' => 'senator_featured_video',
    'required' => 1,
    'flag' => 'senator_featured_video',
    'user_scope' => 'any',
    'id' => 'flag_content_rel',
    'table' => 'node',
    'field' => 'flag_content_rel',
    'relationship' => 'none',
  ),
));
$handler->override_option('fields', array(
  'field_video_embed' => array(
    'label' => '',
    'link_to_node' => 0,
    'label_type' => 'none',
    'format' => 'video_preview',
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
  'title' => array(
    'label' => '',
    'link_to_node' => 1,
    'exclude' => 0,
    'id' => 'title',
    'table' => 'node',
    'field' => 'title',
    'override' => array(
      'button' => 'Override',
    ),
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
$handler->override_option('arguments', array(
  'title' => array(
    'default_action' => 'default',
    'style_plugin' => 'default_summary',
    'style_options' => array(),
    'wildcard' => 'all',
    'wildcard_substitution' => 'All',
    'title' => '',
    'breadcrumb' => '',
    'default_argument_type' => 'php',
    'default_argument' => '',
    'validate_type' => 'php',
    'validate_fail' => 'not found',
    'glossary' => 0,
    'limit' => '0',
    'case' => 'ucwords',
    'path_case' => 'none',
    'transform_dash' => 0,
    'id' => 'title',
    'table' => 'node',
    'field' => 'title',
    'relationship' => 'field_senator_nid',
    'default_options_div_prefix' => '',
    'default_argument_user' => 0,
    'default_argument_fixed' => '',
    'default_argument_php' => 'return nyss_views_related_argument(\'senator\');',
    'validate_argument_node_type' => array(
      'blog' => 0,
      'poll' => 0,
      'campaign' => 0,
      'initiative' => 0,
      'organization' => 0,
      'panel' => 0,
      'cable_broadcast' => 0,
      'committee' => 0,
      'community_project_fund' => 0,
      'district' => 0,
      'event' => 0,
      'expenditure_report' => 0,
      'feed' => 0,
      'group' => 0,
      'in_the_news' => 0,
      'legislation' => 0,
      'outline' => 0,
      'page' => 0,
      'payroll' => 0,
      'photo' => 0,
      'press_release' => 0,
      'report' => 0,
      'senator' => 0,
      'story' => 0,
      'testimony' => 0,
      'transcript' => 0,
      'video' => 0,
      'webform' => 0,
    ),
    'validate_argument_node_access' => 0,
    'validate_argument_nid_type' => 'nid',
    'validate_argument_vocabulary' => array(
      '4' => 0,
      '1' => 0,
      '3' => 0,
    ),
    'validate_argument_type' => 'tid',
    'validate_argument_node_flag_name' => '*relationship*',
    'validate_argument_node_flag_test' => 'flaggable',
    'validate_argument_node_flag_id_type' => 'id',
    'validate_argument_user_flag_name' => '*relationship*',
    'validate_argument_user_flag_test' => 'flaggable',
    'validate_argument_user_flag_id_type' => 'id',
    'validate_argument_php' => 'return nyss_views_related_argument_validate(\'senator\', $argument, $handler);',
    'override' => array(
      'button' => 'Override',
    ),
    'validate_user_argument_type' => 'uid',
    'validate_user_roles' => array(
      '2' => 0,
      '3' => 0,
      '9' => 0,
      '11' => 0,
      '4' => 0,
      '7' => 0,
      '8' => 0,
      '5' => 0,
      '10' => 0,
    ),
    'namespace' => '',
    'attribute' => '',
    'validate_argument_transform' => 0,
    'validate_user_restrict_roles' => 0,
    'validate_argument_is_member' => 'OG_VIEWS_DO_NOT_VALIDATE_MEMBERSHIP',
    'validate_argument_group_node_type' => array(
      'organization' => 0,
      'group' => 0,
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
$handler->override_option('title', 'Featured Video');
$handler->override_option('items_per_page', 1);
$handler->override_option('use_pager', '0');
$handler->override_option('style_plugin', 'list');
$handler->override_option('style_options', array(
  'grouping' => '',
  'type' => 'ul',
));
$handler = $view->new_display('block', 'Feature video on the senator page', 'block_1');
$handler->override_option('block_description', '');
$handler->override_option('block_caching', -1);
$handler = $view->new_display('feed', 'RSS', 'feed_1');
$handler->override_option('style_plugin', 'rss');
$handler->override_option('style_options', array(
  'mission_description' => FALSE,
  'description' => '',
));
$handler->override_option('row_plugin', 'node_rss');
$handler->override_option('path', 'senator/%/front_video/rss');
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
$handler->override_option('displays', array());
$handler->override_option('sitename_title', FALSE);
$views[$view->name] = $view;

