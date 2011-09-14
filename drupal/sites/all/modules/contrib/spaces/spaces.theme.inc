<?php

/**
 * Form theming for the block customizer settings form.
 */
function theme_spaces_block_customizer_settings_form($form) {
  // Add draggable weights
  drupal_add_js('misc/tableheader.js');
  drupal_add_css(drupal_get_path('module', 'spaces') .'/spaces.css');
  $output = '';

  $contexts = element_children($form['contexts']);
  foreach ($contexts as $identifier) {
    $output .= "<div class='spaces-block-customizer clear-block'>";

    // Add a context heading if there is more than 1 context in this feature
    if (count($contexts) > 1) {
      $output .= "<h3>{$form['contexts'][$identifier]['#title']}</h3>";
    }

    // List of block regions that should force an empty display
    $force_empty = array('content');
    global $theme_key;
    init_theme();
    $regions = system_region_list($theme_key);
    foreach ($force_empty as $region) {
      if (empty($form['contexts'][$identifier][$region]) && !empty($regions[$region])) {
        $output .= "<div class='region-{$region}'>";
        $output .= "<strong class='region'>{$regions[$region]}</strong>";
        $output .= "<div class='spaces-empty'>". t('There are no options available for this region.') ."</div>";
        $output .= "</div>";
      }
    }

    foreach (element_children($form['contexts'][$identifier]) as $a) {
      drupal_add_tabledrag("spaces-customizer-blocks-{$identifier}-{$a}", 'order', 'sibling', 'block-weight');
      $rows = array();
      uasort($form['contexts'][$identifier][$a], 'element_sort');
      foreach (element_children($form['contexts'][$identifier][$a]) as $b) {
        $form['contexts'][$identifier][$a][$b]['weight']['#attributes'] = array('class' => 'block-weight');
        $row = array(
          'dummy' => '',
          'status' => drupal_render($form['contexts'][$identifier][$a][$b]['status']),
          'title' => array('data' => drupal_render($form['contexts'][$identifier][$a][$b]['subject']), 'class' => 'fill'),
          'weight' => drupal_render($form['contexts'][$identifier][$a][$b]['weight']),
        );
        $rows[] = array('data' => $row, 'class' => 'draggable');
      }
      $output .= "<div class='region-{$a}'>";
      $output .= "<strong class='region'>{$form['contexts'][$identifier][$a]['#title']}</strong>";
      $output .= theme('table', array(), $rows, array('id' => "spaces-customizer-blocks-{$identifier}-{$a}"));
      $output .= "</div>";
    }

    $output .= "</div>";
  }

  $output .= drupal_render($form);
  return $output;
}

/**
 * Form theme function for spaces presets.
 */
function theme_spaces_form_presets($form) {
  $output = '';
  // Render presets in a table
  $rows = array();
  foreach (element_children($form['info']) as $id) {
    unset($form['preset'][$id]['#title']);
    $row = array(
      drupal_render($form['preset'][$id]),
      drupal_render($form['info'][$id]),
    );
    $rows[] = $row;
  }
  $output .= theme('table', array(array('data' => $form['preset']['#title'], 'colspan' => 2)), $rows);
  drupal_render($form['preset']); // Throw out the rest of this element

  $output .= drupal_render($form);
  return $output;
}

/**
 * Theme function for spaces_preset_default_form().
 */
function theme_spaces_preset_default_form($form) {
  drupal_add_css(drupal_get_path('module', 'spaces') .'/spaces.css');
  $output = '';
  foreach (element_children($form['types']) as $type) {
    // Build table rows
    $rows = array();
    if (!empty($form['types'][$type]['info'])) {
      foreach (element_children($form['types'][$type]['info']) as $preset) {
        $rows[] = array(
          'data' => array(
            drupal_render($form['types'][$type]['default'][$preset]),
            drupal_render($form['types'][$type]['name'][$preset]),
            $form['types'][$type]['info'][$preset]['#value']['description'],
            $form['types'][$type]['info'][$preset]['#value']['links'],
          ),
          'class' => !empty($form['types'][$type]['info'][$preset]['#value']['disabled']) ? 'disabled' : '',
        );
      }
    }
    $rows[] = array(
      array(
        'data' => "<div class='buttons'>". l(t('Add preset'), 'admin/build/spaces/presets/add/'. $type, array('attributes' => array('class' => 'button'))) ."</div>",
        'colspan' => 4,
      )
    );

    // Add type heading and preset table to output
    $output .= "<h3>{$form['types'][$type]['#title']}</h3>";
    $output .= theme('table', array('', t('Preset'), t('Description'), ''), $rows, array('class' => 'spaces-admin'));
  }
  $output .= drupal_render($form['buttons']);
  $output .= drupal_render($form);
  return $output;
}

/**
 * Theme for spaces featuers/settings form.
 * @TODO: this could probably live in a preprocess/template file.
 */
function theme_spaces_features_form($form) {
  drupal_add_css(drupal_get_path('module', 'features') .'/features.css');
  drupal_add_css(drupal_get_path('module', 'spaces') .'/spaces.css');
  drupal_add_js(drupal_get_path('module', 'spaces') .'/spaces.js');

  // Add draggable weights
  drupal_add_js('misc/tableheader.js');
  drupal_add_tabledrag('spaces-features', 'order', 'sibling', 'feature-weight');

  $output = '';
  foreach (array('features', 'settings') as $type) {
    $header = array(
      t('Settings'),
      array('class' => 'action', 'data' => !isset($form['space']['#value']->sid) ? t('Locked') : ''),
      '');
    if ($type == 'features') {
      $header[0] = t('Features');
      $header[] = '';
    }
    $rows = array();
    foreach (element_children($form[$type]) as $element) {
      // Yank title & description fields off the form element for
      // rendering in their own cells.
      $feature_name = "<strong>{$form[$type][$element]['#title']}</strong>";
      $feature_name .= "<div class='description'>{$form[$type][$element]['#description']}</div>";
      $feature_name = "<div class='feature'>{$feature_name}</div>";

      unset($form[$type][$element]['#title']);
      unset($form[$type][$element]['#description']);

      $row = array(
        'name' => $feature_name,
        'action' => drupal_render($form['customize'][$element]) . drupal_render($form['locked'][$type][$element]),
        'option' => drupal_render($form[$type][$element]),
      );

      // Determine row classes
      $class = '';
      if ($type == 'features') {
        $class = $form[$type][$element]['#default_value'] ? 'enabled' : 'disabled';
      }
      $class .= !empty($form[$type][$element]['#locked']) ? ' locked' : '';

      // Add feature weighting
      if ($type == 'features') {
        $form['weights'][$element]['#attributes'] = array('class' => 'feature-weight');
        $row['weight'] = drupal_render($form['weights'][$element]);
        $class .= ' draggable';
      }

      // Collect data + classes & add to master array.
      foreach ($row as $key => $data) {
        $row[$key] = array('data' => $data, 'class' => $key);
      }
      $rows[] = array('data' => $row, 'class' => $class);
    }
    if (!empty($rows)) {
      $output .= theme('table', $header, $rows, array('id' => 'spaces-'. $type, 'class' => 'features spaces-'. $type));
    }

    // Prevent section from being rendered by drupal_render().
    unset($form[$type]);
  }

  $output .= drupal_render($form['buttons']);
  $output .= drupal_render($form);
  return $output;
}

/**
 * Form theme function for customization items.
 */
function theme_spaces_customize_item($form) {
  $output = '';
  $rows = array();
  foreach (element_children($form) as $element) {
    if ($form[$element]['#type'] == 'fieldset') {
      $title = $form[$element]['#title'];
      unset($form[$element]['#title']);
      unset($form[$element]['#type']);
      $rows[] = array(
        "<strong>$title</strong>",
        drupal_render($form[$element]),
      );
    }
  }
  $output .= theme('table', array(), $rows);
  return $output;
}
