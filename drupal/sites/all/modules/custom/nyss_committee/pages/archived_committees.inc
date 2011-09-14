<?php

$page = new stdClass;
$page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
$page->api_version = 1;
$page->name = 'archive_committees';
$page->task = 'page';
$page->admin_title = 'Archived Committees';
$page->admin_description = 'Archive Listing page of Committees';
$page->path = 'archive/committees';
$page->access = array();
$page->menu = array();
$page->arguments = array();
$page->conf = array();
$page->default_handlers = array();
$handler = new stdClass;
$handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
$handler->api_version = 1;
$handler->name = 'page_archive_committees_panel_context';
$handler->task = 'page';
$handler->subtask = 'archive_committees';
$handler->handler = 'panel_context';
$handler->weight = 0;
$handler->conf = array(
  'title' => 'Panel',
  'no_blocks' => 0,
  'pipeline' => 'standard',
  'css_id' => '',
  'css' => '',
  'contexts' => array(),
  'relationships' => array(),
);
$display = new panels_display;
$display->api_version = 1;
$display->layout = 'flexible';
$display->layout_settings = array(
  'items' => array(
    'canvas' => array(
      'type' => 'row',
      'contains' => 'column',
      'children' => array(
        0 => 'main',
      ),
      'parent' => NULL,
    ),
    'main' => array(
      'type' => 'column',
      'width' => 100,
      'width_type' => '%',
      'children' => array(
        0 => 'main-row',
        1 => 1,
        2 => 2,
        3 => 3,
        4 => 4,
      ),
      'parent' => 'canvas',
    ),
    'main-row' => array(
      'type' => 'row',
      'contains' => 'region',
      'children' => array(
        0 => 'center',
      ),
      'parent' => 'main',
    ),
    'center' => array(
      'type' => 'region',
      'title' => 'Standing Committees',
      'width' => 100,
      'width_type' => '%',
      'parent' => 'main-row',
      'class' => '',
    ),
    1 => array(
      'type' => 'row',
      'contains' => 'region',
      'children' => array(
        0 => 'task_forces___other_entities_',
      ),
      'parent' => 'main',
    ),
    2 => array(
      'type' => 'row',
      'contains' => 'region',
      'children' => array(
        0 => 'task_forces___other_entities__',
      ),
      'parent' => 'main',
    ),
    3 => array(
      'type' => 'row',
      'contains' => 'region',
      'children' => array(
        0 => 'legislative_commissions',
      ),
      'parent' => 'main',
    ),
    4 => array(
      'type' => 'row',
      'contains' => 'region',
      'children' => array(
        0 => 'temporary_committees',
      ),
      'parent' => 'main',
    ),
    'task_forces___other_entities_' => array(
      'type' => 'region',
      'title' => 'Subcommittees',
      'width' => 100,
      'width_type' => '%',
      'parent' => '1',
      'class' => '',
    ),
    'task_forces___other_entities__' => array(
      'type' => 'region',
      'title' => 'Task Forces & Other Entities',
      'width' => 100,
      'width_type' => '%',
      'parent' => '2',
    ),
    'legislative_commissions' => array(
      'type' => 'region',
      'title' => 'Legislative Commissions',
      'width' => 100,
      'width_type' => '%',
      'parent' => '3',
    ),
    'temporary_committees' => array(
      'type' => 'region',
      'title' => 'Temporary Committees',
      'width' => 100,
      'width_type' => '%',
      'parent' => '4',
    ),
  ),
);
$display->panel_settings = array(
  'style_settings' => array(
    'default' => NULL,
    'center' => NULL,
    'task_forces___other_entities' => NULL,
    'task_forces___other_entities_' => NULL,
    'task_forces___other_entities__' => NULL,
    'legislative_commissions' => NULL,
    'temporary_committees' => NULL,
  ),
);
$display->cache = array();
$display->title = 'Archived Committees';
$display->content = array();
$display->panels = array();
  $pane = new stdClass;
  $pane->api_version = 1;
  $pane->pid = 'new-1';
  $pane->panel = 'center';
  $pane->type = 'views';
  $pane->subtype = 'archived_committees';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_pager_settings' => 0,
    'use_pager' => 0,
    'nodes_per_page' => '0',
    'pager_id' => '',
    'offset' => '0',
    'more_link' => 0,
    'feed_icons' => 0,
    'panel_args' => 0,
    'link_to_view' => 0,
    'args' => '',
    'url' => '',
    'display' => 'page_1',
    'override_title' => 0,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $display->content['new-1'] = $pane;
  $display->panels['center'][0] = 'new-1';
  $pane = new stdClass;
  $pane->api_version = 1;
  $pane->pid = 'new-2';
  $pane->panel = 'legislative_commissions';
  $pane->type = 'views';
  $pane->subtype = 'archived_committees';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_pager_settings' => 0,
    'use_pager' => 0,
    'nodes_per_page' => '0',
    'pager_id' => '',
    'offset' => '0',
    'more_link' => 0,
    'feed_icons' => 0,
    'panel_args' => 0,
    'link_to_view' => 0,
    'args' => '',
    'url' => '',
    'display' => 'page_5',
    'override_title' => 0,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $display->content['new-2'] = $pane;
  $display->panels['legislative_commissions'][0] = 'new-2';
  $pane = new stdClass;
  $pane->api_version = 1;
  $pane->pid = 'new-3';
  $pane->panel = 'task_forces___other_entities_';
  $pane->type = 'views';
  $pane->subtype = 'archived_committees';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_pager_settings' => 0,
    'use_pager' => 0,
    'nodes_per_page' => '0',
    'pager_id' => '',
    'offset' => '0',
    'more_link' => 0,
    'feed_icons' => 0,
    'panel_args' => 0,
    'link_to_view' => 0,
    'args' => '',
    'url' => '',
    'display' => 'page_4',
    'override_title' => 0,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $display->content['new-3'] = $pane;
  $display->panels['task_forces___other_entities_'][0] = 'new-3';
  $pane = new stdClass;
  $pane->api_version = 1;
  $pane->pid = 'new-4';
  $pane->panel = 'task_forces___other_entities__';
  $pane->type = 'views';
  $pane->subtype = 'archived_committees';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_pager_settings' => 0,
    'use_pager' => 0,
    'nodes_per_page' => '0',
    'pager_id' => '',
    'offset' => '0',
    'more_link' => 0,
    'feed_icons' => 0,
    'panel_args' => 0,
    'link_to_view' => 0,
    'args' => '',
    'url' => '',
    'display' => 'page_3',
    'override_title' => 0,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $display->content['new-4'] = $pane;
  $display->panels['task_forces___other_entities__'][0] = 'new-4';
  $pane = new stdClass;
  $pane->api_version = 1;
  $pane->pid = 'new-5';
  $pane->panel = 'temporary_committees';
  $pane->type = 'views';
  $pane->subtype = 'archived_committees';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_pager_settings' => 0,
    'use_pager' => 0,
    'nodes_per_page' => '0',
    'pager_id' => '',
    'offset' => '0',
    'more_link' => 0,
    'feed_icons' => 0,
    'panel_args' => 0,
    'link_to_view' => 0,
    'args' => '',
    'url' => '',
    'display' => 'page_2',
    'override_title' => 0,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $display->content['new-5'] = $pane;
  $display->panels['temporary_committees'][0] = 'new-5';
$display->hide_title = PANELS_TITLE_FIXED;
$display->title_pane = '0';
$handler->conf['display'] = $display;
$page->default_handlers[$handler->name] = $handler;
