<?php
// $Id$

/**
 *  @file
 *  Theme functions for the 'About this Group' block
 */

/**
 *  Subject of the 'About this Group' block.
 *
 *  @return
 *    The subject of that block.
 */
function theme_nyss_blocks_view_subject_group_twitter() {
  if(arg(0) == 'node' && is_numeric(arg(1))) {
    $node = node_load(arg(1));
  }
  if ($node->type == 'group' || $node->type == 'blog') {
    if($node->og_groups) {
      foreach($node->og_groups as $groupnode) {
        $node = node_load($groupnode);      
      }
    }
    return t('Follow the @feed_title on Twitter', array('@feed_title' => $node->title));
  }
  else if (isset($node->field_initiative) && $node->field_initiative[0]['nid']) {
    $node = node_load($node->field_initiative[0]['nid']);
  }
  if ($node->type == 'initiative') {
    return t('@feed_title on Twitter', array('@feed_title' => $node->title));
  }
}

/**
 *  Display the content of the 'About this Group' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_group_twitter() {
  $output = '';
  if(arg(0) == 'node' && is_numeric(arg(1))) {
    $node = node_load(arg(1));
    if (isset($node->field_initiative) && $node->field_initiative[0]['nid']) {
      $node = node_load($node->field_initiative[0]['nid']);
    }
    if ($node->type == 'initiative') {
      $file = $node->field_twitter_feed[0]['value'];
    }
    else {
      if($node->og_groups) {
        foreach($node->og_groups as $groupnode) {
          $node = node_load($groupnode);      
        }
      }
      switch($node->nid) {
        case 23128:
          $file = 'http://twitter.com/statuses/user_timeline/20419431.rss';
          break;
      }
    }
    
    if ($file) {
      @$feed = simplexml_load_file($file);
      if ($feed) {
        if (count($feed->channel) == 0) {
          foreach ($feed->entry as $item) {
            $name = substr($item->author->uri, 19);
            $output .= '<div style="padding-bottom: 8px;">';
            $output .= l('@'.$name.':', $item->link['href']);
            $output .= ' '. $item->title;
            $output .= '</div>';
          }
        }
        else {
          $name = substr($feed->channel->title, 10);
          foreach ($feed->channel->item as $item) {
            $output .= '<div style="padding-bottom: 8px;">';
            $output .= l($name.':', $item->link);
            $output .= substr($item->description, strlen($name)+1);
            $output .= '</div>';
          }
        }
      }
      else {
        watchdog('nyss', 'Twitter feed for ' .$node->nid. ' not loading.', array(), 3, $file);
      }
    }
  }
  return $output;
}
