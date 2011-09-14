<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _nyss_organization_node_info() {
  $items = array(
    'initiative' => array(
      'name' => t('Initiative'),
      'module' => 'features',
      'description' => t('One-shot initiative pages.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'organization' => array(
      'name' => t('Organization'),
      'module' => 'features',
      'description' => t('An organization that has an ongoing relationship of some kind with the senate or an individual senator.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
