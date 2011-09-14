<?php
  /*
   * View 'senate_updates'
   */
 $view = new view;
 $view->name = 'senate_updates';
 $view->description = 'Senate news content';
 $view->tag = 'newsroom';
 $view->view_php = '';
 $view->base_table = 'node';
 $view->is_cacheable = FALSE;
 $view->api_version = 2;
 $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
 $handler = $view->new_display('default', 'Defaults', 'default');
 $handler->override_option('relationships', array(
   'flag_content_rel' => array(
     'label' => 'flag',
     'required' => 1,
     'flag' => 'promote_to_front',
     'user_scope' => 'any',
     'id' => 'flag_content_rel',
     'table' => 'node',
     'field' => 'flag_content_rel',
     'relationship' => 'none',
   ),
 ));
 $handler->override_option('sorts', array(
   'created' => array(
     'order' => 'DESC',
     'granularity' => 'second',
     'id' => 'created',
     'table' => 'node',
     'field' => 'created',
     'override' => array(
       'button' => 'Override',
     ),
     'relationship' => 'none',
   ),
 ));
 $handler->override_option('filters', array(
   'status' => array(
     'operator' => '=',
     'value' => '1',
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
       'poll' => 'poll',
       'campaign' => 'campaign',
       'event' => 'event',
       'in_the_news' => 'in_the_news',
       'page' => 'page',
       'photo' => 'photo',
       'press_release' => 'press_release',
       'report' => 'report',
       'story' => 'story',
       'testimony' => 'testimony',
       'video' => 'video',
       'webform' => 'webform',
     ),
     'group' => '0',
     'exposed' => TRUE,
     'expose' => array(
       'use_operator' => 0,
       'operator' => 'type_op',
       'identifier' => 'newstype',
       'label' => 'Filter by content',
       'optional' => 1,
       'single' => 1,
       'remember' => 0,
       'reduce' => 1,
     ),
     'id' => 'type',
     'table' => 'node',
     'field' => 'type',
     'override' => array(
       'button' => 'Override',
     ),
     'relationship' => 'none',
   ),
   'type_1' => array(
     'operator' => 'not in',
     'value' => array(
       'initiative' => 'initiative',
       'organization' => 'organization',
       'panel' => 'panel',
       'cable_broadcast' => 'cable_broadcast',
       'committee' => 'committee',
       'community_project_fund' => 'community_project_fund',
       'district' => 'district',
       'expenditure_report' => 'expenditure_report',
       'feed' => 'feed',
       'group' => 'group',
       'legislation' => 'legislation',
       'outline' => 'outline',
       'payroll' => 'payroll',
       'senator' => 'senator',
       'transcript' => 'transcript',
     ),
     'group' => '0',
     'exposed' => FALSE,
     'expose' => array(
       'operator' => FALSE,
       'label' => '',
     ),
     'id' => 'type_1',
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
 $handler->override_option('title', 'Newsroom');
 $handler->override_option('header_format', '3');
 $handler->override_option('header_empty', 0);
 $handler->override_option('footer_format', '3');
 $handler->override_option('footer_empty', 0);
 $handler->override_option('empty', 'No content exists for this content type.');
 $handler->override_option('empty_format', '1');
 $handler->override_option('use_ajax', TRUE);
 $handler->override_option('items_per_page', 20);
 $handler->override_option('use_pager', '1');
 $handler->override_option('link_display', 'feed_1');
 $handler->override_option('distinct', 1);
 $handler->override_option('row_plugin', 'node');
 $handler->override_option('row_options', array(
   'relationship' => 'none',
   'build_mode' => 'teaser',
   'links' => 0,
   'comments' => 0,
 ));
 $handler = $view->new_display('page', 'Senate-wide newsroom', 'page_2');
 $handler->override_option('path', 'newsroom');
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
 $handler = $view->new_display('block', 'Senator\'s individual front page', 'block_1');
 $handler->override_option('relationships', array(
   'flag_content_rel' => array(
     'label' => 'flag',
     'required' => 1,
     'flag' => 'senator_tabs',
     'user_scope' => 'any',
     'id' => 'flag_content_rel',
     'table' => 'node',
     'field' => 'flag_content_rel',
     'relationship' => 'none',
     'override' => array(
       'button' => 'Use default',
     ),
   ),
   'field_senator_nid' => array(
     'label' => 'Senator',
     'required' => 1,
     'delta' => -1,
     'id' => 'field_senator_nid',
     'table' => 'node_data_field_senator',
     'field' => 'field_senator_nid',
     'override' => array(
       'button' => 'Use default',
     ),
     'relationship' => 'none',
   ),
 ));
 $handler->override_option('sorts', array(
   'sticky' => array(
     'order' => 'DESC',
     'id' => 'sticky',
     'table' => 'node',
     'field' => 'sticky',
     'override' => array(
       'button' => 'Use default',
     ),
     'relationship' => 'none',
   ),
   'created' => array(
     'order' => 'DESC',
     'granularity' => 'second',
     'id' => 'created',
     'table' => 'node',
     'field' => 'created',
     'override' => array(
       'button' => 'Override',
     ),
     'relationship' => 'none',
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
     'case' => 'none',
     'path_case' => 'none',
     'transform_dash' => 0,
     'id' => 'title',
     'table' => 'node',
     'field' => 'title',
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
     'override' => array(
       'button' => 'Use default',
     ),
     'relationship' => 'field_senator_nid',
     'default_options_div_prefix' => '',
     'default_argument_fixed' => '',
     'default_argument_user' => 0,
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
     'validate_argument_transform' => 0,
     'validate_user_restrict_roles' => 0,
     'validate_argument_node_flag_name' => '*relationship*',
     'validate_argument_node_flag_test' => 'flaggable',
     'validate_argument_node_flag_id_type' => 'id',
     'validate_argument_user_flag_name' => '*relationship*',
     'validate_argument_user_flag_test' => 'flaggable',
     'validate_argument_user_flag_id_type' => 'id',
     'validate_argument_is_member' => 'OG_VIEWS_DO_NOT_VALIDATE_MEMBERSHIP',
     'validate_argument_group_node_type' => array(
       'organization' => 0,
       'group' => 0,
     ),
     'validate_argument_php' => 'return nyss_views_related_argument_validate(\'senator\', $argument, $handler);',
     'namespace' => '',
     'attribute' => '',
   ),
 ));
 $handler->override_option('title', 'Top News');
 $handler->override_option('block_description', 'Senator\'s individual front page');
 $handler->override_option('block_caching', -1);
 $handler = $view->new_display('feed', 'Newsroom RSS', 'feed_1');
 $handler->override_option('relationships', array(
   'flag_content_rel' => array(
     'label' => 'flag',
     'required' => 0,
     'flag' => 'senator_exclude_newsroom',
     'user_scope' => 'any',
     'id' => 'flag_content_rel',
     'table' => 'node',
     'field' => 'flag_content_rel',
     'override' => array(
       'button' => 'Use default',
     ),
     'relationship' => 'none',
   ),
   'field_senator_nid' => array(
     'label' => 'Senator',
     'required' => 1,
     'delta' => -1,
     'id' => 'field_senator_nid',
     'table' => 'node_data_field_senator',
     'field' => 'field_senator_nid',
     'override' => array(
       'button' => 'Use default',
     ),
     'relationship' => 'none',
   ),
 ));
 $handler->override_option('sorts', array(
   'sticky' => array(
     'order' => 'DESC',
     'id' => 'sticky',
     'table' => 'node',
     'field' => 'sticky',
     'override' => array(
       'button' => 'Use default',
     ),
     'relationship' => 'none',
   ),
   'created' => array(
     'order' => 'DESC',
     'granularity' => 'second',
     'id' => 'created',
     'table' => 'node',
     'field' => 'created',
     'override' => array(
       'button' => 'Override',
     ),
     'relationship' => 'none',
   ),
 ));
 $handler->override_option('arguments', array(
   'title' => array(
     'default_action' => 'default',
     'style_plugin' => 'default_summary',
     'style_options' => array(),
     'wildcard' => 'all',
     'wildcard_substitution' => 'All',
     'title' => '%1\'s Newsroom',
     'breadcrumb' => '',
     'default_argument_type' => 'php',
     'default_argument' => '',
     'validate_type' => 'php',
     'validate_fail' => 'not found',
     'glossary' => 0,
     'limit' => '0',
     'case' => 'none',
     'path_case' => 'none',
     'transform_dash' => 0,
     'id' => 'title',
     'table' => 'node',
     'field' => 'title',
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
     'override' => array(
       'button' => 'Use default',
     ),
     'relationship' => 'field_senator_nid',
     'default_options_div_prefix' => '',
     'default_argument_fixed' => '',
     'default_argument_user' => 0,
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
       'feed_item' => 0,
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
     'validate_argument_transform' => 0,
     'validate_user_restrict_roles' => 0,
     'validate_argument_node_flag_name' => '*relationship*',
     'validate_argument_node_flag_test' => 'flaggable',
     'validate_argument_node_flag_id_type' => 'id',
     'validate_argument_user_flag_name' => '*relationship*',
     'validate_argument_user_flag_test' => 'flaggable',
     'validate_argument_user_flag_id_type' => 'id',
     'validate_argument_is_member' => 'OG_VIEWS_DO_NOT_VALIDATE_MEMBERSHIP',
     'validate_argument_group_node_type' => array(
       'organization' => 0,
       'group' => 0,
     ),
     'validate_argument_php' => 'return nyss_views_related_argument_validate(\'senator\', $argument, $handler);',
     'namespace' => '',
     'attribute' => '',
   ),
   'type' => array(
     'default_action' => 'ignore',
     'style_plugin' => 'default_summary',
     'style_options' => array(),
     'wildcard' => 'All',
     'wildcard_substitution' => 'All',
     'title' => '',
     'breadcrumb' => '',
     'default_argument_type' => 'fixed',
     'default_argument' => '',
     'validate_type' => 'none',
     'validate_fail' => 'not found',
     'id' => 'type',
     'table' => 'node',
     'field' => 'type',
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
     'override' => array(
       'button' => 'Use default',
     ),
     'relationship' => 'none',
     'default_options_div_prefix' => '',
     'default_argument_fixed' => '',
     'default_argument_user' => 0,
     'namespace' => '',
     'attribute' => '',
     'default_argument_php' => '',
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
     'validate_argument_transform' => 0,
     'validate_user_restrict_roles' => 0,
     'validate_argument_node_flag_name' => '*relationship*',
     'validate_argument_node_flag_test' => 'flaggable',
     'validate_argument_node_flag_id_type' => 'id',
     'validate_argument_user_flag_name' => '*relationship*',
     'validate_argument_user_flag_test' => 'flaggable',
     'validate_argument_user_flag_id_type' => 'id',
     'validate_argument_is_member' => 'OG_VIEWS_DO_NOT_VALIDATE_MEMBERSHIP',
     'validate_argument_group_node_type' => array(
       'organization' => 0,
       'group' => 0,
     ),
     'validate_argument_php' => '',
   ),
 ));
 $handler->override_option('filters', array(
   'status' => array(
     'operator' => '=',
     'value' => '1',
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
   'type_1' => array(
     'operator' => 'in',
     'value' => array(
       'blog' => 'blog',
       'poll' => 'poll',
       'campaign' => 'campaign',
       'event' => 'event',
       'in_the_news' => 'in_the_news',
       'page' => 'page',
       'photo' => 'photo',
       'press_release' => 'press_release',
       'report' => 'report',
       'story' => 'story',
       'testimony' => 'testimony',
       'video' => 'video',
       'webform' => 'webform',
     ),
     'group' => '0',
     'exposed' => FALSE,
     'expose' => array(
       'operator' => FALSE,
       'label' => '',
     ),
     'id' => 'type_1',
     'table' => 'node',
     'field' => 'type',
     'override' => array(
       'button' => 'Use default',
     ),
     'relationship' => 'none',
   ),
   'flagged' => array(
     'operator' => '=',
     'value' => '0',
     'group' => '0',
     'exposed' => FALSE,
     'expose' => array(
       'operator' => FALSE,
       'label' => '',
     ),
     'id' => 'flagged',
     'table' => 'flag_content',
     'field' => 'flagged',
     'relationship' => 'flag_content_rel',
     'override' => array(
       'button' => 'Use default',
     ),
   ),
 ));
 $handler->override_option('style_plugin', 'rss');
 $handler->override_option('style_options', array(
   'mission_description' => FALSE,
   'description' => '',
 ));
 $handler->override_option('row_plugin', 'node_rss');
 $handler->override_option('row_options', array(
   'relationship' => 'none',
   'item_length' => 'default',
 ));
 $handler->override_option('path', 'senator/%/newsroom/%/rss');
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
 $handler = $view->new_display('feed', 'Feed', 'feed_2');
 $handler->override_option('title', 'NY Senate Newsroom');
 $handler->override_option('items_per_page', 25);
 $handler->override_option('style_plugin', 'rss');
 $handler->override_option('style_options', array(
   'mission_description' => FALSE,
   'description' => '',
 ));
 $handler->override_option('row_plugin', 'node_rss');
 $handler->override_option('row_options', array());
 $handler->override_option('path', 'rss');
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
 $handler->override_option('sitename_title', 0);
 $views[$view->name] = $view;
