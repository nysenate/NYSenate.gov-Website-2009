<?php
// $Id: spaces_plugin_access_spaces_feature.inc,v 1.1.2.3.2.2 2009/06/27 19:05:53 developmentseed Exp $

/**
 * Provides access control for views by checking against the current space's feature settings.
 * 
 * This access plugin delegates access control first to spaces_feature_access() which 
 * will check whether the user can first access content, then the active space type's 
 * 'feature_access' method will be called.  If implementing your own space type you have
 * the ability to define your own access control.  See 'space_og' class in Spaces OG
 * module for an example implementation.
 */
class spaces_plugin_access_spaces_feature extends views_plugin_access {
  function access($account) {
    return spaces_feature_access($this->options['spaces_feature']);
  }

  function get_access_callback() {
    return array('spaces_feature_access', $this->options['spaces_feature']);
  }

  function summary_title() {
    return $this->options['spaces_feature'];
  }

  function option_defaults(&$options) {
    $options['spaces_feature'] = '';
  }

  function options_form(&$form, &$form_state) {
    $options = array();
    foreach (spaces_features() as $feature) {
      $options[$feature->name] = $feature->info['name'];
    }
    $form['spaces_feature'] = array(
      '#type' => 'select',
      '#title' => t('Feature'),
      '#default_value' => $this->options['spaces_feature'],
      '#options' => $options,
      '#description' => t('Only allow access to this view if the user has access to the selected feature.'),
    );
  }

  function options_validate(&$form, &$form_state) {
  }

  function options_submit(&$form, &$form_state) {
  }
}
