<?php
  /*
   * View 'legislation_reports_senate'
   */
  $view = new view;
  $view->name = 'legislation_reports_senate';
  $view->description = 'Legislation and reports on senate page';
  $view->tag = 'legislation, reports, senate';
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
      'override' => array(
        'button' => 'Override',
      ),
    ),
  ));
  $handler->override_option('sorts', array(
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
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_is_member' => 'OG_VIEWS_DO_NOT_VALIDATE_MEMBERSHIP',
      'validate_argument_group_node_type' => array(
        'group' => 0,
      ),
    ),
  ));
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'legislation' => 'legislation',
        'report' => 'report',
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
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Legislation and Reports');
  $handler->override_option('empty_format', '1');
  $handler->override_option('items_per_page', 3);
  $handler->override_option('distinct', 1);
  $handler->override_option('style_plugin', 'list');
  $handler = $view->new_display('block', 'Legislation and Reports', 'block_1');
  $handler->override_option('title', 'Senator Reports');
  $handler->override_option('footer', '<div class="more">
  <?php
  $senator = nyss_senator();
  print l(\'View more reports\', $senator->path . \'/reports\');
  ?>
  </div>');
  $handler->override_option('footer_format', '3');
  $handler->override_option('footer_empty', 0);
  $handler->override_option('block_description', '');
  $handler->override_option('block_caching', -1);
  $views[$view->name] = $view;

