<?php
  /*
   * View 'Report_List'
   */
   $view = new view;
   $view->name = 'Report_List';
   $view->description = 'List of all the reports on the site';
   $view->tag = '';
   $view->view_php = '';
   $view->base_table = 'node';
   $view->is_cacheable = FALSE;
   $view->api_version = 2;
   $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
   $handler = $view->new_display('default', 'Defaults', 'default');
   $handler->override_option('sorts', array(
     'changed' => array(
       'order' => 'DESC',
       'granularity' => 'second',
       'id' => 'changed',
       'table' => 'node',
       'field' => 'changed',
       'relationship' => 'none',
     ),
   ));
   $handler->override_option('filters', array(
     'type' => array(
       'operator' => 'in',
       'value' => array(
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
   $handler->override_option('row_plugin', 'node');
   $handler->override_option('row_options', array(
     'relationship' => 'none',
     'build_mode' => 'teaser',
     'links' => 1,
     'comments' => 0,
   ));
   $handler = $view->new_display('page', 'Page', 'page_2');
   $handler->override_option('path', 'all_reports');
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
   $views[$view->name] = $view;

