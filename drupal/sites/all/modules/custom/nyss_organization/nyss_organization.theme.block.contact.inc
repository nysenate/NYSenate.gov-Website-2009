<?php
// $Id$

/**
 *  @file
 *  Theme functions for the nyss_organization 'Social buttons' block
 */

/**
 *  Subject of the 'Social buttons' block.
 *
 *  @return
 *    The subject of this block.
 */
function theme_nyss_organization_view_subject_contact() {
  $organization = nyss_organization();
  // If we are on an organization page use organization title setting for block title.
  if (!empty($organization)) {
    // Replace the [organization] token with the organization's name.
    return str_replace('[organization]', strip_tags($organization->title), variable_get('nyss_organization_contact_organization', ''));
  }
}

/**
 *  Display the content of the 'Social buttons' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_organization_view_content_contact($organization = NULL) {
  if ($organization == NULL) {
    $organization = nyss_organization();
  }
  $output = $facebook = $twitter = $rss = $myspace = $youtube = $flickr = $bliptv = $picasa = '';
  if (!empty($organization)) {
    $output .=  content_format('field_location', $organization->field_location[0]);
    $text = t("RSS feed of @organization's content", array('@organization' => $organization->title));
    $rss = l('RSS', $organization->path . '/content/feed', array('attributes' => array('class' => 'rss', 'title' => $text)));
    
    if ($organization->field_facebook_link[0]['url']) {
      $text = t("@organization's Facebook profile", array('@organization' => $organization->title));
      $facebook = l('Facebook', $organization->field_facebook_link[0]['url'], array('attributes' => array('class' => 'facebook', 'title' => $text)));
    }
    if ($organization->field_twitter_link[0]['url']) {
      $text = t("Follow @organization on Twitter", array('@organization' => $organization->title));
      $twitter = l('Twitter', $organization->field_twitter_link[0]['url'], array('attributes' => array('class' => 'twitter', 'title' => $text)));
    }
    if ($organization->field_myspace_link[0]['url']) {
      $text = t("Follow @organization on MySpace", array('@organization' => $organization->title));
      $myspace = l('MySpace', $organization->field_myspace_link[0]['url'], array('attributes' => array('class' => 'myspace', 'title' => $text)));
    }
    if ($organization->field_youtube_link[0]['url']) {
      $text = t("Follow @organization on YouTube", array('@organization' => $organization->title));
      $youtube = l('YouTube', $organization->field_youtube_link[0]['url'], array('attributes' => array('class' => 'youtube', 'title' => $text)));
    }
    if ($organization->field_flickr_link[0]['url']) {
      $text = t("Follow @organization on Flickr", array('@organization' => $organization->title));
      $flickr = l('Flickr', $organization->field_flickr_link[0]['url'], array('attributes' => array('class' => 'flickr', 'title' => $text)));
    }
    if ($organization->field_picasa_link[0]['url']) {
      $text = t("Follow @organization on Picasa", array('@organization' => $organization->title));
      $picasa = l('Picasa', $organization->field_picasa_link[0]['url'], array('attributes' => array('class' => 'picasa', 'title' => $text)));
    }
  }

  if ($facebook || $twitter || $rss || $myspace || $youtube || $flickr || $bliptv || $picasa) {
    $output .= '<div id="social_buttons">'. $rss . $twitter . $facebook . $flickr .  $bliptv . $picasa . $youtube . $myspace .'</div>';
  }
  return $output;
}

/**
 * Configurations for hook_block delta 'contact'.
 *
 * @return array $form
 */
function nyss_organization_configure_form_contact() {
  $form['organization_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Block title'),
    '#default_value' => variable_get('nyss_organization_contact_organization', ''),
    '#size' => 60,
    '#maxlength' => 128,
    '#description' => t('You may use [organization] as a place holder for the organization name.')
  );
  return $form;
}

/**
 * Save for hook_block delta 'contact'.
 *
 * @param array $edit
 */
function nyss_organization_configure_form_save_contact($edit) {
  variable_set('nyss_organization_contact_organization', $edit['organization_title']);
}
