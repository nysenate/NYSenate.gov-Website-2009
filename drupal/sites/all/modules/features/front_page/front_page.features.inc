<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function front_page_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => 1);
  }
  elseif ($module == "panels_mini" && $api == "panels_default") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function front_page_imagecache_default_presets() {
  $items = array(
    'frontpage_senator_photo' => array(
      'presetname' => 'frontpage_senator_photo',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '90',
            'height' => '120',
          ),
        ),
      ),
    ),
  );
  return $items;
}
