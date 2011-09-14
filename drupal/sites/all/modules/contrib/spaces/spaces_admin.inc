<?php

/**
 * Page callback for generating a list of spaces presets.
 * (admin/build/spaces)
 */
function spaces_preset_default_form(&$form_state) {
  $default_presets = variable_get('spaces_default_presets', array());

  $form = array(
    '#theme' => 'spaces_preset_default_form',
    'types' => array('#tree' => TRUE),
  );

  foreach (spaces_types() as $type => $info) {
    $form['types'][$type] = array(
      '#tree' => TRUE,
      '#title' => $info['title'],
    );
    $presets = spaces_presets($type, TRUE);
    if (count($presets)) {
      $form['types'][$type]['default'] = array(
        '#type' => 'radios',
        '#options' => array(),
      );
      foreach ($presets as $id => $preset) {
        // Add radio for use when choosing default
        if (!$preset['disabled']) {
          $form['types'][$type]['default']['#options'][$id] = '';
        }

        // Add name for display via theme function
        $form['types'][$type]['name'][$id] = array('#type' => 'markup', '#value' => $preset['name']);

        // Set as default if it is
        if ($id == $default_presets[$type]) {
          $form['types'][$type]['default']['#default_value'] = $id;
        }

        // Build links for each preset
        $links = array();
        if (isset($preset['module'])) {
          $links[] = $preset['disabled'] ? l(t('Enable'), 'admin/build/spaces/presets/enable/'. $type .'/'. $id) : l(t('Disable'), 'admin/build/spaces/presets/disable/'. $type .'/'. $id);
        }
        else {
          if (empty($preset['disabled'])) {
            $links[] = l(t('Edit'), 'admin/build/spaces/presets/edit/'. $type .'/'. $id);
            $links[] = l(t('Export'), 'admin/build/spaces/presets/export/'. $type .'/'. $id);
            $links[] = l(t('Disable'), 'admin/build/spaces/presets/disable/'. $type .'/'. $id);
          }
          else {
            $links[] = l(t('Enable'), 'admin/build/spaces/presets/enable/'. $type .'/'. $id);
          }
          switch ($preset['storage']) {
            case SPACES_PRESET_NORMAL:
              $links[] = l(t('Delete'), 'admin/build/spaces/presets/delete/'. $type .'/'. $id);
              break;
            case SPACES_PRESET_OVERRIDDEN:
              $links[] = l(t('Revert'), 'admin/build/spaces/presets/delete/'. $type .'/'. $id);
              break;
          }
        }
        $links = implode(' | ', $links);

        // Store preset information to be passed to theme function
        $form['types'][$type]['info'][$id] = array(
          '#type' => 'value',
          '#value' => array(
            'name' => $preset['name'],
            'description' => $preset['description'],
            'links' => $links,
            'disabled' => $preset['disabled'],
          ),
        );
      }
    }
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save defaults'),
    '#submit' => array('spaces_preset_default_form_submit'),
  );
  return $form;
}

/**
 * Submit handler for spaces_preset_default_form().
 */
function spaces_preset_default_form_submit($form, &$form_state) {
  $default_presets = variable_get('spaces_default_presets', array());
  foreach (spaces_types() as $type => $dummy) {
    if (isset($form_state['values']['types'][$type]['default']) && !empty($form_state['values']['types'][$type]['default'])) {
      $default_presets[$type] = $form_state['values']['types'][$type]['default'];
    }
    else {
      unset($default_presets[$type]);
    }
  }
  variable_set('spaces_default_presets', $default_presets);
  drupal_set_message(t('Spaces preset defaults were saved successfully.'));
}

/**
 * Form for adding or editing a spaces preset.
 *
 * @param $op
 *   A string for the operation to perform. Either 'add' or 'edit'.
 * @param $type
 *   A space type string.
 * @param $preset_id
 *   The preset identifier for edit forms.
 *
 * @return
 *   A FormAPI array.
 */
function spaces_preset_form(&$form_state, $op = 'add', $type, $preset_id = NULL) {
  $form = array();
  $space = spaces_load($type);

  switch ($op) {
    case 'add':
      drupal_set_title(t('Add spaces preset'));
      break;
    case 'edit':
      if ($type && $preset_id) {
        drupal_set_title(t('Edit preset: !presetname', array('!presetname' => $preset_id)));

        // Enforce preset settings on space object
        $space->preset = $preset_id;
        spaces_preset_enforce($space);

        // Load preset for form info
        $presets = spaces_presets($type);
        $preset = $presets[$preset_id];
      }
      break;    
  }

  // Preset fields
  $form['preset'] = array(
    '#tree' => true,
  );
  $form['preset']['id'] = array(
    '#type' => 'textfield',
    '#title' => t('Preset id'),
    '#required' => true,
    '#maxlength' => 64,
    '#description' => t('Enter an id for your preset. It may only contain lowercase letters, numbers, and underscores or dashes. <strong>Example:</strong> private_space'),
  );
  $form['preset']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Preset name'),
    '#required' => true,
    '#maxlength' => 255,
    '#description' => t('Enter a name for your preset. It will be displayed to users in forms and messages.'),
  );
  $form['preset']['description'] = array(
    '#type' => 'textfield',
    '#title' => t('Description'),
    '#description' => t('Enter a description for your preset. It should help users understand what the preset provides.'),
  );  

  // Features/settings form
  $form['features_form'] = _spaces_features_form($space);
  $form['features_form']['#tree'] = FALSE;
  $form['features_form']['#theme'] = 'spaces_features_form';  

  // Add locks to features/settings
  $form['features_form']['locked'] = array(
    '#tree' => TRUE,
    'features' => array('#tree' => TRUE),
    'settings' => array('#tree' => TRUE),
  );
  foreach (element_children($form['features_form']['features']) as $id) {
    $form['features_form']['locked']['features'][$id] = array(
      '#type' => 'checkbox',
    );
  }
  foreach (element_children($form['features_form']['settings']) as $id) {
    $form['features_form']['locked']['settings'][$id] = array(
      '#type' => 'checkbox',
    );
  }

  // Type-specific form
  $form[$type] = $space->form('preset');

  // Set default values
  if ($op == 'edit') {
    $form['preset']['id']['#default_value'] =
    $form['preset']['id']['#value'] = $preset_id;
    $form['preset']['id']['#disabled'] = true;
    $form['preset']['name']['#default_value'] = $preset['name'];
    $form['preset']['description']['#default_value'] = $preset['description'];

    foreach (element_children($form['features_form']['features']) as $id) {      
      $form['features_form']['locked']['features'][$id]['#default_value'] = isset($preset['preset']['locked']['features'][$id]) ? $preset['preset']['locked']['features'][$id] : 0;
    }
    foreach (element_children($form['features_form']['settings']) as $id) {
      $form['features_form']['locked']['settings'][$id]['#default_value'] = isset($preset['preset']['locked']['settings'][$id]) ? $preset['preset']['locked']['settings'][$id] : 0;
    }
  }

  $form['buttons'] = array('#tree' => FALSE, '#theme' => 'features_form_buttons');
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#weight' => 10,
  );

  return $form;
}

/**
 * Validation for the preset form.
 */
function spaces_preset_form_validate($form, &$form_state) {
  $space = $form_state['values']['space'];

  // Validate preset info
  if ($form_state['values']['preset']['id'] && !preg_match('!^[a-z0-9_-]+$!', $form_state['values']['preset']['id'])) {
    form_set_error('preset][id', t('The preset name may only contain lowercase letters, numbers, underscores or dashes.'));
  }

  // Validate the features form
  spaces_features_form_validate($form, $form_state);

  // Allow the space type to run its own validations
  $space->validate($form_state['values']);  
}

/**
 * Submit handler for spaces preset form.
 */
function spaces_preset_form_submit($form, &$form_state) {
  // Retrieve the space object from the form
  $space = $form_state['values']['space'];

  $preset = array(
    'name' => '',
    'description' => '',
    'features' => array(),
    'settings' => array(),
    'locked' => array(),
  );

  // Set name / description
  $preset['name'] = $form_state['values']['preset']['name'];
  $preset['description'] = $form_state['values']['preset']['description'];

  // Setting features & locks is easy
  $preset['features'] = $form_state['values']['features'];
  $preset['weights'] = $form_state['values']['weights'];
  $preset['locked'] = $form_state['values']['locked'];

  // Set setting values
  $settings = spaces_settings();
  foreach ($form_state['values']['settings'] as $setting => $value) {
    $preset['settings'][$setting] = $settings[$setting]->submit($space, $value);
  }  

  // Allow space_type to have its own preset values
  $preset[$space->type] = $space->submit($form_state['values']);

  spaces_preset_save($space->type, $form_state['values']['preset']['id'], $preset);
  $form_state['redirect'] = 'admin/build/spaces';
}

/**
 * Form for exporting a spaces preset.
 */
function spaces_preset_export(&$form_state, $type, $id) {
  module_load_include('inc', 'features', 'features.export');
  // Get the preset definition
  $presets = spaces_presets($type);
  $preset = $presets[$id];

  // Clear out extraneous flags
  unset($preset['disabled']);
  unset($preset['storage']);

  // Do some niceties to the export
  $export = features_var_export($preset);
  $export = '$items[\''. $id .'\'] = '. $export .';';

  // Build the form
  $form = array();
  $form['export'] = array(
    '#type' => 'textarea',
    '#rows' => 20,
    '#default_value' => $export,
  );
  return $form;
}

/**
 * Saves a spaces preset.
 *
 * @param $type
 *   The space type for this preset.
 * @param $id
 *   The preset identifier string.
 * @param $values
 *   An array of values that define the preset settings.
 */
function spaces_preset_save($type, $id, $values) {
  $name = isset($values['name']) ? $values['name'] : '';
  $description = isset($values['description']) ? $values['description'] : '';
  unset($values['name']);
  unset($values['description']);

  $exists = db_result(db_query("SELECT count(id) FROM {spaces_presets} WHERE type = '%s' AND id = '%s'", $type, $id));
  $success = false;
  if ($exists) {
    $success = db_query("UPDATE {spaces_presets} SET name = '%s', description = '%s', value = '%s' WHERE type = '%s' AND id = '%s'", $name, $description, serialize($values), $type, $id);
  }
  else {
    $success = db_query("INSERT INTO {spaces_presets} (type, id, name, description, value) VALUES('%s', '%s', '%s', '%s', '%s')", $type, $id, $name, $description, serialize($values));
  }
  if ($success) {
    drupal_set_message(t('The preset !preset was saved successfully.', array('!preset' => $id)));
  }
  else {
    drupal_set_message(t('There was an error saving the preset !preset.', array('!preset' => $id)));
  }
}

/**
 * Load a spaces preset.
 *
 * @param $type
 *   The space type for this preset.
 * @param $id
 *   The preset identifier string.
 */
function spaces_preset_load($type, $id) {
  $value = db_result(db_query("SELECT value FROM {spaces_presets} WHERE type = '%s' AND id = '%s'", $type, $id));
  if ($value) {
    return unserialize($value);
  }
  else {
    drupal_set_message(t('An error occurred while trying to load !preset.'), array('!preset' => $id));
    return array();
  }
}

function spaces_preset_delete($type, $preset) {
  $success = db_query("DELETE FROM {spaces_presets} WHERE type = '%s' AND id = '%s'", $type, $preset);
  return $success;
}

function spaces_preset_disable($type, $preset) {
  $disabled = variable_get('spaces_disabled_presets', array());
  if (!isset($disabled[$type])) {
    $disabled[$type] = array();
  }
  if (!isset($disabled[$type][$preset])) {
    $disabled[$type][$preset] = 1;
    variable_set('spaces_disabled_presets', $disabled);
  }
}

function spaces_preset_enable($type, $preset) {
  $disabled = variable_get('spaces_disabled_presets', array());
  if (!isset($disabled[$type])) {
    $disabled[$type] = array();
  }
  if (isset($disabled[$type][$preset])) {
    unset($disabled[$type][$preset]);
    variable_set('spaces_disabled_presets', $disabled);
  }
}

/**
 * Page callback wrapper around spaces_preset_disable()
 */
function _spaces_preset_disable_page($type, $preset) {
  spaces_preset_disable($type, $preset);
  drupal_goto('admin/build/spaces');
}

/**
 * Page callback wrapper around spaces_preset_enable()
 */
function _spaces_preset_enable_page($type, $preset) {
  spaces_preset_enable($type, $preset);
  drupal_goto('admin/build/spaces');
}

function spaces_preset_delete_form(&$form, $type, $preset_id) {
  // @TODO: proper check for preset existence
  $presets = spaces_presets(null, TRUE);
  if (isset($presets[$type][$preset_id]) && $preset = $presets[$type][$preset_id]) {
    $form = array();
    $form['type'] = array(
      '#type' => 'hidden',
      '#value' => $type,
    );
    $form['preset'] = array(
      '#type' => 'hidden',
      '#value' => $preset_id,
    );
    $question = t('Are you sure you want to delete !preset?', array('!preset' => $preset['name']));
    $description = t('Any spaces using this preset will need to reset.');
    $form = confirm_form($form, $question, 'admin/build/spaces', $description);
    return $form;
  }
  return '';
}

function spaces_preset_delete_form_submit($form, &$form_state) {
  $type = $form_state['values']['type'];
  $preset = $form_state['values']['preset'];

  $success = spaces_preset_delete($type, $preset);
  $message = $success ? t('The preset !preset was deleted successfully.', array('!preset' => $preset)) : t('An error occurred while trying to delete !preset.', array('!preset' => $preset));
  drupal_set_message($message);

  $form_state['redirect'] = 'admin/build/spaces';
}

/**
 * BASIC FORM =========================================================
 */

function spaces_basic_form(&$form_state, $space = NULL) {
  // Attempt to get current space if not provided
  $space = !isset($space) ? spaces_get_space() : $space;

  $form = array();

  $form['space'] = array(
    '#type' => 'value',
    '#value' => $space,
  );

  // Add context prefix form
  $types = spaces_types();
  if (isset($types[$space->type]['custom prefixes']) && $types[$space->type]['custom prefixes'] != FALSE) {
    $form['purl'] = purl_form('spaces_'. $space->type, $space->sid, $space->purl);
  }

  // Add preset form
  if (count(spaces_presets($space->type))) {
    $form['preset'] = spaces_form_presets($space);
  }

  // Only add submit if one of the options are set.
  // Otherwise, add message.
  if (isset($form['purl']) || isset($form['preset'])) {
    $form['buttons'] = array('#tree' => FALSE, '#theme' => 'features_form_buttons');
    $form['buttons']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
      '#submit' => array('spaces_basic_form_submit'),
    );
  }
  else {
    $space->redirect('features');
  }

  return $form;
}

function spaces_basic_form_submit($form, &$form_state) {
  $space = $form_state['values']['space'];

  // Grab prefixes if space uses custom prefixes
  if (isset($form_state['values']['purl'])) {
    $space->purl = $form_state['values']['purl']['value'];
  }

  // Retrieve selected preset and enforce values
  $space->preset = $form_state['values']['preset'];
  spaces_preset_enforce($space);

  spaces_save($space);
}

/**
 * FEATURE SETTINGS ===================================================
 */

function spaces_features_form(&$form_state, $space = NULL) {
  // Attempt to get current space if not provided
  $space = !isset($space) ? spaces_get_space() : $space;

  // Set a wide layout for themes that support it
  context_set('theme', 'layout', 'wide');

  spaces_preset_enforce($space);

  $form = _spaces_features_form($space);

  // Generate base path for the given space
  $types = spaces_types();
  $type = $types[$space->type];
  $base_path = '';
  if (isset($type['base path'])) {
    $base_path = str_replace('%sid', $space->sid, $type['base path']) .'/';
  }

  // Add customization and/or settings link if feature is not disabled
  $form['customize'] = array('#tree' => TRUE);
  foreach (element_children($form['features']) as $id) {
    if (isset($space->features[$id]) && ($space->features[$id] != SPACES_FEATURE_DISABLED)) {
      $form['customize'][$id] = array(
        '#type' => 'markup',
        '#value' => l(t('Customize'), $base_path .'spaces/features/'. $id),
      );
    }
  }

  // Lock features and settings.
  if ($space->preset) {
    $presets = spaces_presets($space->type);
    $preset = $presets[$space->preset];
    foreach (array('features', 'settings') as $item) {
      if (isset($preset['preset']['locked'][$item])) {
        foreach ($preset['preset']['locked'][$item] as $id => $value) {
          if ($value && isset($form[$item][$id])) {
            $form[$item][$id]['#disabled'] = true;
            $form[$item][$id]['#locked'] = true; // attribute used in theme layer
          }
        }
      }
    }
  }

  $form['buttons'] = array('#tree' => FALSE, '#theme' => 'features_form_buttons');
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
  );
  $form['buttons']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset to defaults'),
    '#submit' => array('spaces_features_form_reset'),
  );

  return $form;
}

/**
 * Core form for controlling features / settings
 */
function _spaces_features_form($space) {
  $form = array();
  $form['#attributes'] = array('enctype' => 'multipart/form-data');

  $form['space'] = array(
    '#type' => 'value',
    '#value' => $space,
  );
  $form['features'] = array(
    '#type' => 'fieldset',
    '#title' => t('Features'),
    '#tree' => TRUE,
  );
  $form['weights'] = array(
    '#tree' => TRUE,
  );
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
    '#tree' => TRUE,
  );

  // Generate features form

  // Grab an ordered list of features from the current space.
  // Add any additional features that this space is missing to the end.
  $features = spaces_features($space->type, TRUE);
  $ordered = array();
  if (isset($space->features)) {
    $ordered = array_keys($space->features);
    // Sometimes the feature array can contain stale data --
    // we intersect it with the spaces_features() to make sure it
    // doesn't contain any dead features.
    $ordered = array_intersect($ordered, array_keys($features));
  }
  foreach (array_keys($features) as $feature) {
    if (!in_array($feature, $ordered)) {
      $ordered[] = $feature;
    }
  }

  // Iterate a second time to build the form. We assign weights in a
  // strictly ascending fashion.
  $weight = -10;
  foreach ($ordered as $id) {
    $options = $space->feature_options() ? $space->feature_options() : array();
    if (count($options) > 0) {
      $form['weights'][$id] = array(
        '#type' => 'weight',
        '#delta' => 10,
        '#default_value' => $weight,
      );
      $form['features'][$id] = array(
        '#type' => 'select',
        '#title' => $features[$id]->info['name'],
        '#description' => $features[$id]->info['description'],
        '#options' => $options,
        '#default_value' => isset($space->features[$id]) ? $space->features[$id] : SPACES_FEATURE_DISABLED,
      );
      $weight++;
    }
  }

  // Generate settings form
  foreach (spaces_settings($space->type, TRUE) as $setting) {
    $setting_value = isset($space->settings[$setting->id]) ? $space->settings[$setting->id] : NULL;
    $setting_form = $setting->form($space, $setting_value);
    if (!empty($setting_form)) {
      $form['settings'][$setting->id] = $setting_form;
    }
  }

  return $form;
}

/**
 * Validate handler for spaces features form
 */
function spaces_features_form_validate($form, &$form_state) {
  $space = $form_state['values']['space'];
  $settings = spaces_settings();
  if (is_array($form_state['values']['features'])) {
    if (isset($space->sid) && array_sum($form_state['values']['features']) == 0) {
      return form_set_error('', t('You must enable at least 1 feature for this space.'));
    }
  }
  if (is_array($form_state['values']['settings'])) {
    foreach ($form_state['values']['settings'] as $setting => $value) {
      $settings[$setting]->validate($space, $value);
    }
  }
}

/**
 * Submit handler for spaces features form
 */
function spaces_features_form_submit($form, &$form_state) {
  // Retrieve the space object from the form
  $space = $form_state['values']['space'];

  // Sort the weights array and rebuild feature values list in the
  // weighted order. When the features are saved, an ascending set of
  // weights will be assigned.
  $features = array();
  if (!empty($form_state['values']['features'])) {
    asort($form_state['values']['weights']);
    foreach (array_keys($form_state['values']['weights']) as $feature) {
      $features[$feature] = $form_state['values']['features'][$feature];
    }
  }
  $space->features = $features;

  // Set setting values
  $settings = spaces_settings();
  if (!empty($form_state['values']['settings'])) {
    foreach ($form_state['values']['settings'] as $setting => $value) {
      $space->settings[$setting] = $settings[$setting]->submit($space, $value);
    }
  }

  // Save the space
  spaces_save($space);
  drupal_set_message(t('The space configuration has been saved successfully.'));
}

/**
 * Reset submit handler for feature customization form.
 */
function spaces_features_form_reset($form, &$form_state) {
  $space = $form_state['values']['space'];
  unset($space->customizer);
  unset($space->settings);
  unset($space->features);
  spaces_save($space);
}

/**
 * FEATURE CUSTOMIZATION ==============================================
 */

/**
 * Feature customization form.
 */
function spaces_customize_form(&$form_state, $space = NULL, $feature) {
  // Attempt to get current space if not provided
  $space = !isset($space) ? spaces_get_space() : $space;

  $form = array();

  $form['space'] = array('#type' => 'value', '#value' => $space);
  $form['feature'] = array('#type' => 'value', '#value' => $feature);
  $form['settings'] = array('#tree' => TRUE);
  $form['customizers'] = array('#tree' => TRUE);

  $customizable = FALSE;

  $features = spaces_features();
  $f = $features[$feature];
  drupal_set_title(t('Customize: !feature', array('!feature' => $f->info['name'])));

  // Generate feature-specific settings form
  $settings = spaces_feature_settings($feature);
  if (!empty($settings)) {
    $form['settings']['#title'] = t('Settings');
    $form['settings']['#type'] = 'fieldset';
    $form['settings']['#collapsible'] = TRUE;
    foreach ($settings as $id => $setting) {
      $setting_value = isset($space->settings[$id]) ? $space->settings[$id] : NULL;
      $form['settings'][$id] = $setting->form($space, $setting_value);
    }
    $customizable = TRUE;
  }

  // Create a fieldset per customizer
  $customizers = spaces_customizers();
  foreach ($customizers as $id => $customizer) {
    $form['customizers'][$id] = array(
      '#title' => t($customizer->name),
      '#type' => 'fieldset',
      '#tree' => TRUE,
      '#theme' => 'spaces_customize_item',
      '#collapsible' => TRUE,
    );
    $customizer_form = $customizer->form($space, $feature);
    if ($customizer_form) {
      $form['customizers'][$id] = array_merge($form['customizers'][$id], $customizer_form);
      $customizable = TRUE;
    }
  }

  // If we have customizers and/or settings, add submit buttons
  if ($customizable) {
    $form['buttons'] = array('#tree' => FALSE, '#theme' => 'features_form_buttons');
    $form['buttons']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save settings'),
      '#submit' => array('spaces_customize_form_submit'),
    );
  }
  // Otherwise, display a message.
  else {
    drupal_set_message(t('This feature does not have any customizations or settings available.'));
  }

  return $form;
}

/**
 * Validate handler for spaces features form
 */
function spaces_customize_form_validate($form_id, &$form_state) {
  $space = $form_state['values']['space'];
  $feature = $form_state['values']['feature'];

  // Push each customizer value through the customizer's validator
  $customizers = spaces_customizers();
  foreach ($customizers as $id => $customizer) {
    $customizer->validate($space, $feature, $form_state['values']['customizers'][$id]);
  }

  // Push each feature setting through the setting's validator
  $settings = spaces_feature_settings($feature);
  if (!empty($settings)) {
    foreach ($settings as $id => $setting) {
      $setting->validate($space, $form_state['values']['settings'][$id]);
    }
  }
}

/**
 * Submit handler for feature customization form.
 */
function spaces_customize_form_submit($form, &$form_state) {
  $space = $form_state['values']['space'];
  $feature = $form_state['values']['feature'];

  // Retrieve customizer values
  $customizers = spaces_customizers();
  foreach ($customizers as $id => $customizer) {
    $space->customizer[$id] = $customizer->submit($space, $feature, $form_state['values']['customizers'][$id]);
  }

  // Retrieve setting values
  $settings = spaces_feature_settings($feature);
  if (!empty($settings)) {
    foreach ($settings as $id => $setting) {
      $space->settings[$id] = $setting->submit($space, $form_state['values']['settings'][$id]);
    }
  }

  // Save the space
  spaces_save($space);
  drupal_set_message(t('Customizations saved for space !title.', array('!title' => $space->title)));
}
