<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function nyss_senator_context_context_default_contexts() {
  $items = array();

  $items['nyss-content_type-senator'] = array(
    'namespace' => 'nyss',
    'attribute' => 'content_type',
    'value' => 'senator',
    'description' => 'Does this page belong to a Senator?',
    'block' => array(
      'nyss_blocks_about_senator_blog' => array(
        'module' => 'nyss_blocks',
        'delta' => 'about_senator_blog',
        'weight' => -128,
        'region' => 'left',
        'status' => '0',
        'label' => 'About this blog',
        'type' => 'context_ui',
      ),
      'nyss_blocks_social_buttons' => array(
        'module' => 'nyss_blocks',
        'delta' => 'social_buttons',
        'weight' => -127,
        'region' => 'left',
        'status' => '0',
        'label' => 'Social buttons',
        'type' => 'context_ui',
      ),
      'views_e69db2e86c97b4e7a11ff445c81075a9' => array(
        'module' => 'views',
        'delta' => 'e69db2e86c97b4e7a11ff445c81075a9',
        'weight' => -126,
        'region' => 'left',
        'status' => '0',
        'label' => 'flag_senator_featured_video: Feature video on the senator page',
        'type' => 'context_ui',
      ),
      'views_district_map-block_1' => array(
        'module' => 'views',
        'delta' => 'district_map-block_1',
        'weight' => -125,
        'region' => 'left',
        'status' => '0',
        'label' => 'district_map: Block',
        'type' => 'context_ui',
      ),
      'views_upcoming_events_senate-block_1' => array(
        'module' => 'views',
        'delta' => 'upcoming_events_senate-block_1',
        'weight' => -124,
        'region' => 'left',
        'status' => '0',
        'label' => 'upcoming_events_senate: Upcoming events',
        'type' => 'context_ui',
      ),
      'nyss_blocks_my_committees' => array(
        'module' => 'nyss_blocks',
        'delta' => 'my_committees',
        'weight' => -123,
        'region' => 'left',
        'status' => '0',
        'label' => 'My Committees',
        'type' => 'context_ui',
      ),
      'views_Forms-block_1' => array(
        'module' => 'views',
        'delta' => 'Forms-block_1',
        'weight' => -122,
        'region' => 'left',
        'status' => '0',
        'label' => 'Senator\'s "Get Involved" block',
        'type' => 'context_ui',
      ),
      'views_senator_quickpoll-block' => array(
        'module' => 'views',
        'delta' => 'senator_quickpoll-block',
        'weight' => -121,
        'region' => 'left',
        'status' => '0',
        'label' => 'Senator Quickpoll',
        'type' => 'context_ui',
      ),
      'nyss_blocks_senator_carousel' => array(
        'module' => 'nyss_blocks',
        'delta' => 'senator_carousel',
        'weight' => 121,
        'region' => 'content_masthead',
        'status' => '0',
        'label' => 'Senator\'s Carousel',
        'type' => 'context_ui',
      ),
      'views_senate_updates-block_1' => array(
        'module' => 'views',
        'delta' => 'senate_updates-block_1',
        'weight' => -122,
        'region' => 'content_bottom',
        'status' => '0',
        'label' => 'Senator\'s individual front page',
        'type' => 'context_ui',
      ),
      'views_gallery-block_1' => array(
        'module' => 'views',
        'delta' => 'gallery-block_1',
        'weight' => -121,
        'region' => 'content_bottom',
        'status' => '0',
        'label' => 'gallery: Block: Senator Videos',
        'type' => 'context_ui',
      ),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function nyss_senator_context_views_api() {
  return array(
    'api' => '2',
  );
}
