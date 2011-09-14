<?php

/**
 * Implementation of hook_feeds_importer_default().
 */
function cable_broadcast_import_feeds_importer_default() {
  $export = array();
  $feeds_importer = new stdClass;
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'cable_broadcast';
  $feeds_importer->config = array(
    'name' => 'Cable Broadcast',
    'description' => 'Upload en masse Cable Broadcast Info',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'direct' => FALSE,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => ',',
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'content_type' => 'cable_broadcast',
        'input_format' => '0',
        'update_existing' => '2',
        'expire' => '-1',
        'mappings' => array(
          0 => array(
            'source' => 'Entry',
            'target' => 'guid',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'Date Start',
            'target' => 'field_date:start',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'Date End',
            'target' => 'field_date:end',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'Original Event',
            'target' => 'field_original_event:nid',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'Live',
            'target' => 'field_live',
            'unique' => FALSE,
          ),
        ),
        'author' => 0,
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
  );

  $export['cable_broadcast'] = $feeds_importer;
  return $export;
}
