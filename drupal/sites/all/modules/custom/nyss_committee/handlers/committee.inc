<?php

$handler = new stdClass;
$handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
$handler->api_version = 1;
$handler->name = 'node_view_panel_context_2';
$handler->task = 'node_view';
$handler->subtask = '';
$handler->handler = 'panel_context';
$handler->weight = -30;
$handler->conf = array(
  'title' => 'Committee Nodes',
  'no_blocks' => 0,
  'css_id' => 'committee-page',
  'css' => '',
  'contexts' => array(),
  'relationships' => array(),
  'access' => array(
    'logic' => 'and',
    'plugins' => array(
      0 => array(
        'name' => 'node_type',
        'settings' => array(
          'type' => array(
            'committee' => 'committee',
          ),
        ),
        'context' => 'argument_nid_1',
      ),
    ),
  ),
  'pipeline' => 'standard',
);
$display = new panels_display;
$display->api_version = 1;
$display->layout = 'twocol_bricks';
$display->layout_settings = array();
$display->panel_settings = array(
  'top' => array(
    'style' => '-1',
  ),
  'style_settings' => array(
    'default' => NULL,
    'top' => NULL,
    'left_above' => NULL,
    'middle' => NULL,
    'left_below' => NULL,
    'right_below' => NULL,
    'bottom' => NULL,
    'right_above' => NULL,
  ),
  'right_above' => array(
    'style' => '-1',
  ),
);
$display->cache = array();
$display->title = '%node:title';
$display->content = array();
$display->panels = array();
  $pane = new stdClass;
  $pane->api_version = 1;
  $pane->pid = 'new-1';
  $pane->panel = 'left_above';
  $pane->type = 'views';
  $pane->subtype = 'next_event';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_pager_settings' => 0,
    'use_pager' => 0,
    'nodes_per_page' => '1',
    'pager_id' => '',
    'offset' => '0',
    'more_link' => 0,
    'feed_icons' => 0,
    'panel_args' => 0,
    'link_to_view' => 0,
    'args' => '',
    'url' => '',
    'context' => array(
      0 => 'argument_nid_1.title',
    ),
    'override_title' => 0,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array(
    'css_id' => 'block-views-next_event-block_1',
    'css_class' => '',
  );
  $pane->extras = array();
  $pane->position = 0;
  $display->content['new-1'] = $pane;
  $display->panels['left_above'][0] = 'new-1';
  $pane = new stdClass;
  $pane->api_version = 1;
  $pane->pid = 'new-2';
  $pane->panel = 'middle';
  $pane->type = 'views';
  $pane->subtype = 'committee_updates';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_pager_settings' => 0,
    'use_pager' => 0,
    'nodes_per_page' => '10',
    'pager_id' => '',
    'offset' => '0',
    'more_link' => 0,
    'feed_icons' => 0,
    'panel_args' => 0,
    'link_to_view' => 0,
    'args' => '',
    'url' => '',
    'display' => 'block_1',
    'context' => array(
      0 => 'argument_nid_1.title',
    ),
    'override_title' => 0,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array(
    'css_id' => 'block-views-committee_updates-block_1',
    'css_class' => 'region region-content_bottom clearfix',
  );
  $pane->extras = array();
  $pane->position = 0;
  $display->content['new-2'] = $pane;
  $display->panels['middle'][0] = 'new-2';
  $pane = new stdClass;
  $pane->api_version = 1;
  $pane->pid = 'new-3';
  $pane->panel = 'right_above';
  $pane->type = 'views';
  $pane->subtype = 'flag_committee_featured_video2';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_pager_settings' => 0,
    'use_pager' => 0,
    'nodes_per_page' => '1',
    'pager_id' => '',
    'offset' => '0',
    'more_link' => 0,
    'feed_icons' => 0,
    'panel_args' => 0,
    'link_to_view' => 0,
    'args' => '',
    'url' => '',
    'display' => 'block_1',
    'context' => array(
      0 => 'argument_nid_1.title',
    ),
    'override_title' => 0,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array(
    'css_id' => 'block-views-53783ff7ee6066f059668f3e283749cb',
    'css_class' => 'content clearfix block block-views region-even odd region-count-2 count-9 with-block-editing',
  );
  $pane->extras = array();
  $pane->position = 0;
  $display->content['new-3'] = $pane;
  $display->panels['right_above'][0] = 'new-3';
  $pane = new stdClass;
  $pane->api_version = 1;
  $pane->pid = 'new-4';
  $pane->panel = 'top';
  $pane->type = 'page_title';
  $pane->subtype = 'page_title';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'markup' => 'h2',
    'class' => 'committee_name',
    'id' => '',
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
  $display->panels['top'][0] = 'new-4';
  $pane = new stdClass;
  $pane->api_version = 1;
  $pane->pid = 'new-5';
  $pane->panel = 'top';
  $pane->type = 'page_feed_icons';
  $pane->subtype = 'page_feed_icons';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $display->content['new-5'] = $pane;
  $display->panels['top'][1] = 'new-5';
$display->hide_title = PANELS_TITLE_FIXED;
$display->title_pane = '0';
$handler->conf['display'] = $display;
