<?php

/**
 * Settings form callback
 */
function twitter_post_admin_settings() {
  $form['twitter_post_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Node types'),
    '#options' => node_get_types('names'),
    '#default_value' => variable_get('twitter_post_types', array('story' => 'story', 'blog' => 'blog')),
  );

  $form['twitter_post_default_format'] = array(
    '#type' => 'textfield',
    '#title' => t('Default format string'),
    '#maxlength' => 140,
    '#description' => t('The given text will be posted to twitter.com. You can use !url, !url-alias, !tinyurl, !title, and !user as replacement text.  If the token module is enabled, you may also choose from the tokens listed in the replacement patterns section.'),
    '#default_value' => variable_get('twitter_post_default_format', 'New post: !title !tinyurl'),
  );
  if (module_exists('token')) {
    $form['view']['token_help'] = array(
      '#title' => t('Replacement patterns'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#description' => t('Prefer raw-text replacements for text to avoid problems with HTML entities!'),
    );

    $form['view']['token_help']['help'] = array(
      '#value' => theme('token_help', 'node'),
    );
  }

  return system_settings_form($form);  
}
