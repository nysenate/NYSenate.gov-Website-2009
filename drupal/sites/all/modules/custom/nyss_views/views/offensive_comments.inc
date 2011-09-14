<?php
  /*
   * View 'offensive_comments'
   */
  $view = new view;
  $view->name = 'offensive_comments';
  $view->description = 'This will list all the comments that have been flagged as offensive.';
  $view->tag = 'comments offensive';
  $view->view_php = '';
  $view->base_table = 'comments';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'flag_content_rel' => array(
      'label' => 'flag',
      'required' => 1,
      'flag' => 'offensive',
      'user_scope' => 'any',
      'id' => 'flag_content_rel',
      'table' => 'comments',
      'field' => 'flag_content_rel',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('fields', array(
    'name' => array(
      'label' => 'Author',
      'link_to_user' => 1,
      'exclude' => 0,
      'id' => 'name',
      'table' => 'comments',
      'field' => 'name',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'subject' => array(
      'label' => 'Title',
      'link_to_comment' => 1,
      'exclude' => 0,
      'id' => 'subject',
      'table' => 'comments',
      'field' => 'subject',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'edit_comment' => array(
      'label' => 'Edit',
      'text' => '',
      'exclude' => 0,
      'id' => 'edit_comment',
      'table' => 'comments',
      'field' => 'edit_comment',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'view_comment' => array(
      'label' => 'View',
      'text' => '',
      'exclude' => 0,
      'id' => 'view_comment',
      'table' => 'comments',
      'field' => 'view_comment',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'timestamp' => array(
      'label' => 'Flagged time',
      'date_format' => 'custom',
      'custom_date_format' => 'n/j/Y - H:i',
      'exclude' => 0,
      'id' => 'timestamp',
      'table' => 'flag_content',
      'field' => 'timestamp',
      'relationship' => 'flag_content_rel',
      'override' => array(
        'button' => 'Override',
      ),
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
  $handler->override_option('access', array(
    'type' => 'role',
    'role' => array(
      '3' => 3,
      '4' => 4,
      '5' => 5,
    ),
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Offensive comments');
  $handler->override_option('empty', 'There currently no comments that have been flagged as offensive.');
  $handler->override_option('empty_format', '1');
  $handler->override_option('items_per_page', 50);
  $handler->override_option('style_plugin', 'table');
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'admin/content/comment/offensive');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'Offensive comments',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
  ));
  $views[$view->name] = $view;

