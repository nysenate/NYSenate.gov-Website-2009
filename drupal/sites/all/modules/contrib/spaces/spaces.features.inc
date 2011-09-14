<?php
// $Id: spaces.features.inc,v 1.1.2.2 2009/09/06 15:25:48 yhahn Exp $

/**
 * Implementation of hook_spaces_features_export().
 */
function spaces_features_export($data, &$export, $module_name = '') {
  // Presets do not imply any other hard dependencies for now.
  $export['dependencies']['spaces'] = 'spaces';

  foreach ($data as $preset) {
    $export['features']['spaces'][$preset] = $preset;
  }
  return array();
}

/**
 * Implementation of hook_spaces_features_export_render().
 */
function spaces_features_export_render($module = 'foo', $data) {
  $code = array();
  $code[] = '  $presets = array();';
  $code[] = '';

  $presets = spaces_presets();

  foreach ($data as $id) {
    // Get the preset definition
    $preset = NULL;
    $presets = spaces_presets();
    foreach (array_keys($presets) as $type) {
      if (isset($presets[$type][$id])) {
        $preset = $presets[$type][$id];
        break;
      }
    }
    if ($preset) {
      // Clear out extraneous flags
      unset($preset['disabled']);
      unset($preset['storage']);

      $code[] = '  // Exported preset: '. $id;
      $code[] = '  $presets[\''. $id .'\'] = '. features_var_export($preset, '  ') .';';
      $code[] = '';
    }
  }

  $code[] = '  return $presets;';
  $code = implode("\n", $code);
  return array('spaces_presets' => $code);
}

/**
 * Implementation of hook_spaces_features_revert().
 */
function spaces_features_revert($module = NULL) {
  if (module_hook($module, 'spaces_presets')){
    module_load_include('inc', 'spaces', 'spaces_admin');
    $presets = module_invoke($module, 'spaces_presets');
    foreach ($presets as $id => $preset) {
      spaces_preset_delete($preset['type'], $id);
    }
  }
  return TRUE;
}
