<?php

/**
 * Implementation of hook_default_page_manager_pages().
 */
function front_page_default_page_manager_pages() {
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
          1 => 1,
        ),
        'parent' => 'canvas',
      ),
      'main-row' => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'senate_blog',
          1 => 'front_top_right',
        ),
        'parent' => 'main',
        'class' => 'front-two-column',
      ),
      'senate_blog' => array(
        'type' => 'region',
        'title' => 'Welcome message',
        'width' => 50,
        'width_type' => '%',
        'parent' => 'main-row',
        'class' => 'welcome-message',
      ),
      1 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'senator_spotlight',
        ),
        'parent' => 'main',
      ),
      'front_top_right' => array(
        'type' => 'region',
        'title' => 'front-top-right',
        'width' => 50,
        'width_type' => '%',
        'parent' => 'main-row',
        'class' => 'front-top-right',
      ),
      'senator_spotlight' => array(
        'type' => 'region',
        'title' => 'senator-spotlight',
        'width' => 100,
        'width_type' => '%',
        'parent' => '1',
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
      'front_top_right' => NULL,
      'senator_spotlight' => NULL,
      'senator_listing' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'New York State Senate';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass;
    $pane->api_version = 1;
    $pane->pid = 'new-1';
    $pane->panel = 'front_top_right';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'Front page right-column teaser',
      'title' => '',
      'body' => '<div><img src="http://www.nysenate.gov/files/users/u1088/budget_info.png" alt="2011-12 State Budget Information" height="129" width="265"></div>
<p>With our State facing serious fiscal and economic challenges, it’s important for all New Yorkers to get the facts about Governor Andrew Cuomo’s proposed Executive Budget for 2011-2012. The Senate has been carefully reviewing the proposed budget’s potential impact on taxpayers, our local communities, and New York’s economic future, and has also recently passed a fiscally responsible budget resolution to move the overall process forward. You can play a helpful role in this process by reviewing key budget briefing materials found on this website, and then providing feedback to your Senator.</p>',
      'format' => '2',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $display->content['new-1'] = $pane;
    $display->panels['front_top_right'][0] = 'new-1';
    $pane = new stdClass;
    $pane->api_version = 1;
    $pane->pid = 'new-2';
    $pane->panel = 'front_top_right';
    $pane->type = 'block';
    $pane->subtype = 'views-5880aedbb982c2793ab700505b2bb051';
    $pane->shown = TRUE;
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
    $display->panels['front_top_right'][1] = 'new-2';
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
      'title' => 'A MESSAGE FROM SENATE MAJORITY LEADER DEAN SKELOS',
      'body' => '<div style="float:right; width: 90px; margin: 0 0 10px 10px;">
  <img src="/files/imagecache/frontpage_senator_photo/profile-pictures/SD9_Skelos_4.jpg" alt="Dean Skelos" title="Dean Skelos"  align="left" />
</div>
<p>To All New Yorkers,</p>
<p>Welcome to the official web site of the New York State Senate. The new year of 2011 brings important changes and challenges to our State government, and to the State of New York as a whole.&nbsp;</p>
<p>The members of &nbsp;the State Senate will be working closely with our new Governor Andrew Cuomo and the members of the New York State Assembly to meet the significant challenges that lie ahead.</p>
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
    $pane->position = 0;
    $display->content['new-3'] = $pane;
    $display->panels['senate_blog'][0] = 'new-3';
    $pane = new stdClass;
    $pane->api_version = 1;
    $pane->pid = 'new-4';
    $pane->panel = 'senator_spotlight';
    $pane->type = 'block';
    $pane->subtype = 'nyss_senator-senator_spotlight';
    $pane->shown = TRUE;
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
    $display->content['new-4'] = $pane;
    $display->panels['senator_spotlight'][0] = 'new-4';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = 'new-1';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['homepage'] = $page;

 return $pages;

}
