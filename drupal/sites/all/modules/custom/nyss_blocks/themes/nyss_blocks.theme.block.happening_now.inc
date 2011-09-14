<?php
// $Id$

/**
 *  @file
 *  Theme functions for the nyss_blocks 'Happening now' block
 */

/**
 *  Subject of the 'Happening now' block.
 *
 *  @return
 *    The subject of this block.
 */
function theme_nyss_blocks_view_subject_happening_now() {
  return t('Happening Now...');
}

/**
 *  Display the content of the 'Happening now' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_happening_now() {
  if (!module_exists('jquery_ui')) return t('You must have <em>jquery_ui</em> module enabled.');
  jquery_ui_add('ui.tabs');
  $js =<<<EOD
    $(document).ready(function(){
       $("#happening_now > .ui-tabs-nav").tabs();
     });
EOD;
  drupal_add_js($js, 'inline', 'header', FALSE, TRUE, FALSE);
  drupal_add_css(path_to_theme() .'/themes/css/nyss_blocks_tabs.css', 'theme', 'all', FALSE);
  $output = '';
  $output .= '<div id="happening_now" class="ui-tabs">';
  $output .= '<ul class="ui-tabs-nav">';
  $output .= '<li class="press-release"><a href="#happening_now_press">'. t('Press Release') .'</a></li>';
  $output .= '<li class="news-clips"><a href="#happening_now_news">'. t('News Clip') .'</a></li>';
  $output .= '</ul>';
  $output .= '<div id="happening_now_press">'. views_embed_view('flag_promote_to_front', 'default', 'press_release') .'</div>';
  $output .= '<div id="happening_now_news">'. views_embed_view('flag_promote_to_front', 'default', 'in_the_news') .'</div>';
  $output .= '</div>';
  return $output;
}
