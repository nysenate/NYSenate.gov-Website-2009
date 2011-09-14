<?php
// $Id: revision_deletion.admin.inc,v 1.1.2.9 2009/09/05 21:46:51 nancyw Exp $

/**
 * @file
 * Node Revision Deletion admin page.
 */

define('REV_DEL_PERM', 'mass delete revisions');

/**
 * Settings form.
 */
function revision_deletion_settings() {
  drupal_add_css(drupal_get_path('module', 'revision_deletion') .'/revision_deletion.css');
  $yesno = array(1 => t('Yes'), 0 => t('No'));
  // Intervals (in seconds).
  $minute = 60;
  $hour = 3600;
  $day = 86400;
  $week = 604800;

  $frequency = array(0 => t('Manual'));
  $frequency += drupal_map_assoc(array(1 * $day, 2 * $day, 4 * $day, 1 * $week, 2 * $week, 4 * $week, 8 * $week), 'format_interval');

  $current_age = array(0 => t('Always'));
  $current_age += drupal_map_assoc(array(1 * $hour, 2 * $hour, 4 * $hour, 12 * $hour, 1 * $day, 4 * $day, 1 * $week, 2 * $week, 4 * $week, 8 * $week, 26 * $week), 'format_interval');

  $age = drupal_map_assoc(array(15 * $minute, 30 * $minute, 1 * $hour, 2 * $hour, 1 * $day, 4 * $day, 1 * $week, 2 * $week, 4 * $week, 8 * $week, 16 * $week, 26 * $week, 52 * $week), 'format_interval');

  $form['rev_del'] = array(
    '#type' => 'fieldset',
    '#title' => t('Revision Mass Deletion Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    );

  // Set node types to be deleted. If not set yet, defaults to revision-enabled types.
  $default_types = variable_get('revision_delete', array());
  $set_default = empty($default_types);
  $node_types = node_get_types('names');
  foreach ($node_types as $type => $name) {
    $options = variable_get("node_options_$type", array());
    if (in_array('revision', $options)) {
      $node_types[$type] = '<strong>'. $name .'</strong>';
      if ($set_default) {
        $default_types[$type] = $type;
      }
    }
  }
  $form['rev_del']['revision_delete'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Content types'),
    '#default_value' => $default_types,
    '#multiple' => TRUE,
    '#required' => TRUE,
    '#options' => $node_types,
    '#description' => t('Select which content types are subject to revision deletion. Types in <strong>bold</strong> have revisions enabled by default. Multiple types may be selected.'),
    '#prefix' => '<div class="revision-deletion-options">',
    '#suffix' => '</div>',
    );

  // Set revision frequency interval.
  $form['rev_del']['revision_delete_freq'] = array(
    '#type' => 'radios',
    '#title' => t('Automatic deletion interval'),
    '#default_value' => variable_get('revision_delete_freq', 0),
    '#options' => $frequency,
    '#size' => 6,
    '#description' => t('Frequency of the scheduled mass revision deleton. Select "Manual" to disable the automatic deletion.'),
    '#prefix' => '<div class="revision-deletion-options">',
    '#suffix' => '</div>',
    );

  // Set revision age for deletion.
  $form['rev_del']['revision_delete_age'] = array(
    '#type' => 'radios',
    '#title' => t('Revision Age'),
    '#default_value' => variable_get('revision_delete_age', 2419200),
    '#options' => $age,
    '#description' => t('Age of revisions that should be deleted.'),
    '#prefix' => '<div class="revision-deletion-options">',
    '#suffix' => '</div>',
    );

  // Set age for current revision.
  $form['rev_del']['revision_delete_list_keep_current'] = array(
    '#type' => 'radios',
    '#title' => t('Current Revision Age'),
    '#default_value' => variable_get('revision_delete_list_keep_current', 1209600),
    '#options' => $current_age,
    '#description' => t('Age of current revision before the previous can be deleted. "Always" means the previous revision will be deleted regardless of how old the current one is.'),
    '#prefix' => '<div class="revision-deletion-options">',
    '#suffix' => '</div>',
    );

  // Settings for "list revisions".
  $form['list'] = array(
    '#type' => 'fieldset',
    '#title' => t('List settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('These options are used on revisions lists.'),
    );

  // Take over core list function.
  $takeover = variable_get('revision_delete_list_takeover', 0);
  $form['takeover_before'] = array('#type' => 'value', '#value' => $takeover);
  $form['list']['revision_delete_list_takeover'] = array(
    '#type' => 'radios',
    '#title' => t('Take over revisions list'),
    '#options' => $yesno,
    '#default_value' => $takeover,
    '#description' => t('This determines whether or not you wish to replace the core revisions list function.'),
    '#prefix' => '<div class="container-inline">',
    '#suffix' => '</div>',
    );

  // Number of revisions per page.
  $form['list']['revision_delete_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of Revisions per Page'),
    '#default_value' => variable_get('revision_delete_limit', 20),
    '#size' => 6,
    '#description' => t('This is the number of revisions that should be shown in the lists.'),
    ); /* */

  // Show conditional labels.
  $form['list']['revision_delete_list_show_conditional'] = array(
    '#type' => 'radios',
    '#title' => t('Show additional labels'),
    '#options' => $yesno,
    '#default_value' => variable_get('revision_delete_list_show_conditional', 1),
    '#description' => t('Should the additional labels (e.g "current" or "last for date") be shown? CSS classes are also set so those rows can be styled differently.'),
    '#prefix' => '<div class="container-inline">',
    '#suffix' => '</div>',
    );

  // Keep original.
  $form['list']['revision_delete_list_keep_original'] = array(
    '#type' => 'radios',
    '#title' => t('Keep original'),
    '#options' => $yesno,
    '#default_value' => variable_get('revision_delete_list_keep_original', 0),
    '#description' => t('Should the original version be unchecked?'),
    '#prefix' => '<div class="container-inline">',
    '#suffix' => '</div>',
    );

  // Keep last per date.
  $form['list']['revision_delete_list_keep_date_last'] = array(
    '#type' => 'radios',
    '#title' => t('Keep last revison per date'),
    '#options' => $yesno,
    '#default_value' => variable_get('revision_delete_list_keep_date_last', 0),
    '#description' => t('Should the last version for a date be unchecked? This probably should not be used at the same time as "Keep original" above.'),
    '#prefix' => '<div class="container-inline">',
    '#suffix' => '</div>',
    );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
    '#submit' => array('revision_deletion_settings_submit'),
    );

  $form['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset to defaults'),
    '#submit' => array('revision_deletion_settings_reset'),
    );

  return $form;
}

/**
 * Settings form reset.
 */
function revision_deletion_settings_reset($form, &$form_state) {
  variable_del('revision_delete');
  variable_del('revision_delete_freq');
  variable_del('revision_delete_age');
  variable_del('revision_delete_list_takeover');
  variable_del('revision_delete_list_limit');
  variable_del('revision_delete_list_show_conditional');
  variable_del('revision_delete_list_keep_original');
  variable_del('revision_delete_list_keep_date_last');
  cache_clear_all();
  drupal_set_message(t('Configuration options have been reset to defaults.'));
}

/**
 * Settings form submission.
 */
function revision_deletion_settings_submit($form, &$form_state) {
  variable_set('revision_delete', array_filter($form_state['values']['revision_delete']));
  variable_set('revision_delete_freq', $form_state['values']['revision_delete_freq']);
  variable_set('revision_delete_age', $form_state['values']['revision_delete_age']);
  variable_set('revision_delete_list_takeover', $form_state['values']['revision_delete_list_takeover']);
  variable_set('revision_delete_limit', $form_state['values']['revision_delete_limit']);
  variable_set('revision_delete_list_show_conditional', $form_state['values']['revision_delete_list_show_conditional']);
  variable_set('revision_delete_list_keep_original', $form_state['values']['revision_delete_list_keep_original']);
  variable_set('revision_delete_list_keep_date_last', $form_state['values']['revision_delete_list_keep_date_last']);
  variable_set('revision_delete_list_keep_current', $form_state['values']['revision_delete_list_keep_current']);

  // If the take over option has changed, rebuild the menu.
  if ($form_state['values']['takeover_before'] != $form_state['values']['revision_delete_list_takeover']) {
    menu_rebuild();
  }

  drupal_set_message(t('Configuration options have been saved.'));
}
