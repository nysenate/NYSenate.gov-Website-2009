<?php
// $Id$

/**
 *  @file
 *  Theme functions for the nyss_blocks 'Social buttons' block
 */

/**
 *  Subject of the 'Social buttons' block.
 *
 *  @return
 *    The subject of this block.
 */
function theme_nyss_blocks_view_subject_social_buttons() {
  $senator = nyss_senator();
  if (empty($senator)) {
    if (arg(0) == 'node' && is_numeric(arg(1))) {
      $senator = node_load(arg(1));
    }
  }
  // If we are on a senator page use senator title setting for block title.
  if (!empty($senator)) {
    // Replace the [senator] token with the senator's name.
    return str_replace('[senator]', strip_tags($senator->title), variable_get('nyss_blocks_social_buttons_senator', ''));
  }
  else {
    return variable_get('nyss_blocks_social_buttons_overall_title', '');
  }
}

/**
 *  Display the content of the 'Social buttons' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_social_buttons($senator = NULL) {
  if ($senator == NULL) {
    $senator = nyss_senator();
  }
  if (empty($senator)) {
    if (arg(0) == 'node' && is_numeric(arg(1))) {
      $senator = node_load(arg(1));
    }
  }
  $rss = $twitter = $facebook = $flickr =  $bliptv = $picasa = $youtube = $myspace = $output = '';
  // If not on a senator page then use the overall settings else use senator's.
  if (empty($senator)) {
    $overall_links = variable_get('nyss_blocks_social_buttons_overall_links', array());
    
    $text = t("RSS feed of all Senate content");
    $rss = l('RSS', 'rss', array('attributes' => array('class' => 'rss', 'title' => $text)));
    
    if (!empty($overall_links['facebook'])) {
      $text = t("New York Senates' Facebook profile");
      $facebook = l('Facebook', $overall_links['facebook'], array('attributes' => array('class' => 'facebook', 'title' => $text)));
    }
    if (!empty($overall_links['twitter'])) {
      $text = t("Follow the New York Senate on Twitter");
      $twitter = l('Twitter', $overall_links['twitter'], array('attributes' => array('class' => 'twitter', 'title' => $text)));
    }
    if (!empty($overall_links['myspace'])) {
      $text = t("Follow the New York Senate on MySpace");
      $myspace = l('MySpace', $overall_links['myspace'], array('attributes' => array('class' => 'myspace', 'title' => $text)));
    }
    if (!empty($overall_links['flickr'])) {
      $text = t("Follow the New York Senate on Flickr");
      $flickr = l('Flickr', $overall_links['flickr'], array('attributes' => array('class' => 'flickr', 'title' => $text)));
    }
    if (!empty($overall_links['youtube'])) {
      $text = t("Follow the New York Senate on YouTube");
      $youtube = l('YouTube', $overall_links['youtube'], array('attributes' => array('class' => 'youtube', 'title' => $text)));
    }
    if (!empty($overall_links['bliptv'])) {
      $text = t("Follow the New York Senate on blip.tv");
      $bliptv = l('blip.tv', $overall_links['bliptv'], array('attributes' => array('class' => 'bliptv', 'title' => $text)));
    }
  }
  else {
    $text = t("RSS feed of @senator's content", array('@senator' => $senator->title));
    $rss = l('RSS', $senator->path . '/content/feed', array('attributes' => array('class' => 'rss', 'title' => $text)));
    
    if ($senator->field_facebook_link[0]['url']) {
      $text = t("@senator's Facebook profile", array('@senator' => $senator->title));
      $facebook = l('Facebook', $senator->field_facebook_link[0]['url'], array('attributes' => array('class' => 'facebook', 'title' => $text)));
    }
    if ($senator->field_twitter_link[0]['url']) {
      $text = t("Follow @senator on Twitter", array('@senator' => $senator->title));
      $twitter = l('Twitter', $senator->field_twitter_link[0]['url'], array('attributes' => array('class' => 'twitter', 'title' => $text)));
    }
    if ($senator->field_myspace_link[0]['url']) {
      $text = t("Follow @senator on MySpace", array('@senator' => $senator->title));
      $myspace = l('MySpace', $senator->field_myspace_link[0]['url'], array('attributes' => array('class' => 'myspace', 'title' => $text)));
    }
    if ($senator->field_youtube_link[0]['url']) {
      $text = t("Follow @senator on YouTube", array('@senator' => $senator->title));
      $youtube = l('YouTube', $senator->field_youtube_link[0]['url'], array('attributes' => array('class' => 'youtube', 'title' => $text)));
    }
    if ($senator->field_flickr_link[0]['url']) {
      $text = t("Follow @senator on Flickr", array('@senator' => $senator->title));
      $flickr = l('Flickr', $senator->field_flickr_link[0]['url'], array('attributes' => array('class' => 'flickr', 'title' => $text)));
    }
    if ($senator->field_picasa_link[0]['url']) {
      $text = t("Follow @senator on Picasa", array('@senator' => $senator->title));
      $picasa = l('Picasa', $senator->field_picasa_link[0]['url'], array('attributes' => array('class' => 'picasa', 'title' => $text)));
    }
  }

  if ($facebook || $twitter || $rss || $myspace || $youtube || $flickr || $bliptv || $picasa) {
    $output .= '<div id="social_buttons">'. $rss . $twitter . $facebook . $flickr .  $bliptv . $picasa . $youtube . $myspace .'</div>';
  }
  return $output;
}

/**
 * Configurations for hook_block delta 'social_buttons'.
 *
 * @return array $form
 */
function nyss_blocks_configure_form_social_buttons() {
  $form['overall'] = array(
    '#type' => 'fieldset',
    '#title' => t('Overall block settings'),
    '#weight' => -9999,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('These are the settings that will be used when <strong>NOT</strong> on a senator page.'),
  );
  $form['overall']['overall_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Block title'),
    '#default_value' => variable_get('nyss_blocks_social_buttons_overall_title', ''),
    '#size' => 60,
    '#maxlength' => 128,
  );
  $overall_links = variable_get('nyss_blocks_social_buttons_overall_links', array());
  $form['overall']['facebook'] = array(
    '#type' => 'textfield',
    '#title' => t('Facebook link'),
    '#default_value' => $overall_links['facebook'],
    '#size' => 60,
    '#maxlength' => 128,
    '#description' => t("Please enter the URL to the senate's Facebook page, if it exists."),
  );
  $form['overall']['twitter'] = array(
    '#type' => 'textfield',
    '#title' => t('Twitter link'),
    '#default_value' => $overall_links['twitter'],
    '#size' => 60,
    '#maxlength' => 128,
    '#description' => t("Please enter the URL to the senate's Twitter page, if it exists."),
  );
  $form['overall']['youtube'] = array(
    '#type' => 'textfield',
    '#title' => t('YouTube link'),
    '#default_value' => $overall_links['youtube'],
    '#size' => 60,
    '#maxlength' => 128,
    '#description' => t("Please enter the URL to the senate's YouTube page, if it exists."),
  );
  $form['overall']['myspace'] = array(
    '#type' => 'textfield',
    '#title' => t('MySpace link'),
    '#default_value' => $overall_links['myspace'],
    '#size' => 60,
    '#maxlength' => 128,
    '#description' => t("Please enter the URL to the senate's MySpace page, if it exists."),
  );
  $form['overall']['flickr'] = array(
    '#type' => 'textfield',
    '#title' => t('Flickr link'),
    '#default_value' => $overall_links['flickr'],
    '#size' => 60,
    '#maxlength' => 128,
    '#description' => t("Please enter the URL to the senate's Flickr page, if it exists."),
  );
  $form['overall']['bliptv'] = array(
    '#type' => 'textfield',
    '#title' => t('blip.tv link'),
    '#default_value' => $overall_links['bliptv'],
    '#size' => 60,
    '#maxlength' => 128,
    '#description' => t("Please enter the URL to the senate's blip.tv page, if it exists."),
  );
  $form['senator'] = array(
    '#type' => 'fieldset',
    '#title' => t('Senator settings'),
    '#weight' => -9999,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('These are the settings that will be used when on a senator page.'),
  );
  $form['senator']['senator_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Block title'),
    '#default_value' => variable_get('nyss_blocks_social_buttons_senator', ''),
    '#size' => 60,
    '#maxlength' => 128,
    '#description' => t('You may use [senator] as a place holder for the senator name.')
  );
  return $form;
}

/**
 * Save for hook_block delta 'social_buttons'.
 *
 * @param array $edit
 */
function nyss_blocks_configure_form_save_social_buttons($edit) {
  variable_set('nyss_blocks_social_buttons_overall_title', $edit['overall_title']);
  variable_set('nyss_blocks_social_buttons_overall_links', array('facebook' => $edit['facebook'], 'twitter' => $edit['twitter'], 'myspace' => $edit['myspace'], 'flickr' => $edit['flickr'], 'youtube' => $edit['youtube'], 'bliptv' => $edit['bliptv'], ));
  variable_set('nyss_blocks_social_buttons_senator', $edit['senator_title']);
}
