<?php

$page = new stdClass;
$page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
$page->api_version = 1;
$page->name = 'homepage';
$page->task = 'page';
$page->admin_title = 'Home page';
$page->admin_description = 'The home page of NYSenate.gov';
$page->path = 'front';
$page->access = array();
$page->menu = array();
$page->arguments = array();
$page->conf = array();
$page->default_handlers = array();
$handler = new stdClass;
$handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
$handler->api_version = 1;
$handler->name = 'page_homepage_panel_context';
$handler->task = 'page';
$handler->subtask = 'homepage';
$handler->handler = 'panel_context';
$handler->weight = 0;
$handler->conf = array(
  'title' => 'Home page',
  'no_blocks' => 0,
  'pipeline' => 'standard',
  'css_id' => 'homepage',
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
      ),
      'parent' => 'canvas',
    ),
    'main-row' => array(
      'type' => 'row',
      'contains' => 'region',
      'children' => array(
        0 => 'senate_blog',
      ),
      'parent' => 'main',
      'class' => 'front-two-column',
    ),
    'senate_blog' => array(
      'type' => 'region',
      'title' => 'Welcome message',
      'width' => 100,
      'width_type' => '%',
      'parent' => 'main-row',
      'class' => 'welcome-message',
    ),
  ),
);
$display->panel_settings = array(
  'style_settings' => array(
    'default' => NULL,
    'center' => NULL,
    'homepage_content' => NULL,
    'senators_col2' => NULL,
    'blog' => NULL,
    'happening_now' => NULL,
    'senate_video' => NULL,
    'senate_blog' => NULL,
    'featured_video' => NULL,
  ),
);
$display->cache = array();
$display->title = 'New York State Senate';
$display->content = array();
$display->panels = array();
  $pane = new stdClass;
  $pane->api_version = 1;
  $pane->pid = 'new-1';
  $pane->panel = 'senate_blog';
  $pane->type = 'block';
  $pane->subtype = 'nyss_blocks-senate_blogs';
  $pane->shown = FALSE;
  $pane->access = array();
  $pane->configuration = array(
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
  $display->panels['senate_blog'][0] = 'new-1';
  $pane = new stdClass;
  $pane->api_version = 1;
  $pane->pid = 'new-2';
  $pane->panel = 'senate_blog';
  $pane->type = 'block';
  $pane->subtype = 'views-5880aedbb982c2793ab700505b2bb051';
  $pane->shown = FALSE;
  $pane->access = array();
  $pane->configuration = array(
    'override_title' => 0,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $display->content['new-2'] = $pane;
  $display->panels['senate_blog'][1] = 'new-2';
  $pane = new stdClass;
  $pane->api_version = 1;
  $pane->pid = 'new-3';
  $pane->panel = 'senate_blog';
  $pane->type = 'custom';
  $pane->subtype = 'custom';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'admin_title' => 'Welcome message',
    'title' => 'Welcome to the official web site of the New York State Senate.',
    'body' => '<p>To All New Yorkers,</p>
<p>Welcome to the official web site of the New York State Senate. The new year of 2011 brings important changes and challenges to our State government, and to the State of New York as a whole.&nbsp;</p>
<p>The members of &nbsp;the State Senate will be working closely with our new Governor Andrew Cuomo and the members of the New York State Assembly to meet the significant challenges that lie ahead.</p>
<p>The people’s priorities must be our priorities. &nbsp;That means balancing the state budget, closing the deficit, easing the burden on taxpayers, and doing everything we can to strengthen our economy and create private sector jobs.</p>
<p>This web site provides extensive access to a wide array of Senate proceedings and legislative information, and enables members of the public to watch Senate sessions and committee meetings live. &nbsp;You can also use this site to find your State Senator and contact him or her to voice your concerns and priorities, ask questions, make recommendations or discuss issues that are important to you, your family and your community.</p>
<p>I\'d like to thank you for taking the time to visit the State Senate website, and I encourage you to stay informed and involved in our State government, as we work together to address the many challenges facing the people of New York.</p>
<p>Sincerely,</p>
<p>Senator Dean G. Skelos<br />
Temporary President and Majority Leader of the New York State Senate</p>',
    'format' => '2',
    'substitute' => TRUE,
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 2;
  $display->content['new-3'] = $pane;
  $display->panels['senate_blog'][2] = 'new-3';
$display->hide_title = PANELS_TITLE_PANE;
$display->title_pane = '0';
$handler->conf['display'] = $display;
$page->default_handlers[$handler->name] = $handler;
