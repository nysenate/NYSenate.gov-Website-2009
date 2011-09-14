<?php

/**
 * Implementation of hook_feeds_importer_default().
 */
function openleg_parser_feature_feeds_importer_default() {
  $export = array();
  $feeds_importer = new stdClass;
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'openleg';
  $feeds_importer->config = array(
    'name' => 'OpenLeg',
    'description' => 'Parses OpenLeg using the 1.6 RSS Feed',
    'fetcher' => array(
      'plugin_key' => 'FeedsHTTPFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
        'use_pubsubhubbub' => FALSE,
        'designated_hub' => '',
      ),
    ),
    'parser' => array(
      'plugin_key' => 'OpenLegFeedsSimplePieParser',
      'config' => array(),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'content_type' => 'event',
        'input_format' => '2',
        'update_existing' => '2',
        'expire' => '-1',
        'mappings' => array(
          0 => array(
            'source' => 'summary',
            'target' => 'body',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'guid',
            'target' => 'guid',
            'unique' => 1,
          ),
          2 => array(
            'source' => 'url',
            'target' => 'url',
            'unique' => 0,
          ),
          3 => array(
            'source' => 'street',
            'target' => 'field_location:street',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'city',
            'target' => 'field_location:city',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'state',
            'target' => 'field_location:province',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'zip',
            'target' => 'field_location:postal_code',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'committee',
            'target' => 'field_committee:title',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'date_start',
            'target' => 'field_date:start',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'date_end',
            'target' => 'field_date:end',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'committee',
            'target' => 'taxonomy:1',
            'unique' => FALSE,
          ),
          11 => array(
            'source' => 'chair',
            'target' => 'field_senator:title',
            'unique' => FALSE,
          ),
          12 => array(
            'source' => 'author_by',
            'target' => 'field_authored_by_senator',
            'unique' => FALSE,
          ),
          13 => array(
            'source' => 'event_type',
            'target' => 'field_public_hearing',
            'unique' => FALSE,
          ),
          14 => array(
            'source' => 'meeting_title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          15 => array(
            'source' => 'guid',
            'target' => 'field_openleg_id',
            'unique' => FALSE,
          ),
          16 => array(
            'source' => 'livestream',
            'target' => 'field_video',
            'unique' => FALSE,
          ),
        ),
        'author' => '1',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '1800',
    'expire_period' => 3600,
    'import_on_create' => 1,
  );

  $export['openleg'] = $feeds_importer;
  return $export;
}
