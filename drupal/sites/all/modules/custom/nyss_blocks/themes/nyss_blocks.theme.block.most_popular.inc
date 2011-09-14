<?php
// $Id$

/**
 *  @file
 *  Theme functions for the nyss_blocks 'Most Popular' block
 */

/**
 *  Subject of the 'Most Popular' block.
 *
 *  @return
 *    The subject of this block.
 */
function theme_nyss_blocks_view_subject_most_popular() {
  return t('Most Popular');
}

/**
 *  Display the content of the 'Most Popular' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_most_popular() {
  if (!module_exists('jquery_ui')) return t('You must have <em>jquery_ui</em> module enabled.');
  jquery_ui_add('ui.accordion');
  $js =<<<EOD
    $(document).ready(function(){
      $("#most_popular").accordion({header: "h4"});
    });
EOD;
  drupal_add_js($js, 'inline', 'header', FALSE, TRUE, FALSE);
  drupal_add_css(path_to_theme() .'/themes/css/nyss_blocks_accordion.css', 'theme', 'all', TRUE);
  $output = '';
  $output .= '<div id="most_popular" class="clear-block">';
  $output .= '<div class="most-popular most">';
  $output .= '<h4>'. t('Most Popular') .'</h4>';
  $output .= views_embed_view('most_popular_nodes', 'block_1');
  $output .= '</div>';
  $output .= '<div class="most-emailed most">';
  $output .= '<h4>'. t('Most Emailed') .'</h4>';
  $most_mailed = print_mail_block('view');
  $output .= $most_mailed['content'];
  $output .= '</div>';
  $output .= '<div class="most-commented most">';
  $output .= '<h4>'. t('Most Commented') .'</h4>';
  $output .= views_embed_view('most_popular_nodes', 'block_2');
  $output .= '</div>';
  $output .= '</div>';
  return $output;
}
