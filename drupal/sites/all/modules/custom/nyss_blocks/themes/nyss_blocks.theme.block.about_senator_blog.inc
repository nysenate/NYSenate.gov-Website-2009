<?php
// $Id$

/**
 *  @file
 *  Theme functions for the 'About this blog' block for Senators' Blogs.
 */

/**
 *  Subject of the 'About this blog' block.
 *  @return
 *    The subject of that block.
 */
function theme_nyss_blocks_view_subject_about_senator_blog() {
  if (context_isset('nyss', 'senator')) {
    return t('What my senator can do for me');
  }
  else if (arg(0) == 'node' && is_numeric(arg(1))){
    $node = node_load(arg(1));
    if ($node->type == 'group') {
      return t('About the ' . $node->title);
    }
  }
  else {
    return t('About this blog');
  }
}

/**
 *  Display the content of the 'About this blog' block.
 *
 *  @TODO: we need to build the blog view and figure out the senator.
 *
 *  @param $node
 *    (optional) The senator's node.
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_about_senator_blog() {
  if (context_isset('nyss', 'senator')) {
    $senator = context_get('nyss', 'senator');
    if($senator->field_about_block[0]['value']) {
      return $senator->field_about_block[0]['value'];
    }
    else {
      $para1 = t('Your state senator works for the citizens of your district. ' .
               'Your senator talks with constituents about how <strong>proposed laws</strong> will affect their lives. ' .
               'Your senator can relay information on bill status, committee hearings, resolutions and floor activity.');
      $para2 = t(
        'Contact !name if you have concerns about issues affecting your community.', 
        array('!name' => l($senator->title, 'senator/'.nyss_senator_title_to_url($senator).'/contact'))
      );
      return "<p>$para1</p>\n<p>$para2</p>";
    }
  }
  else if(arg(0) == 'node' && is_numeric(arg(1))) {
    $node = node_load(arg(1));
    if($node->field_about_block[0]['value']) {
      return $node->field_about_block[0]['value'];
    }
  }
  else {
    return '<p>' . t(
      'This blog is maintained by the Senate Communications Department. Please direct all questions to <strong>!majority.</strong>', 
      array('!majority' => l(t('Majority Communications'),'contact_form'))
    ) . '</p>';
  }
}
