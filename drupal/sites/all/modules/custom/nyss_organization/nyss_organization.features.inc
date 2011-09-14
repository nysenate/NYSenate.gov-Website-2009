<?php

/**
 * Implementation of hook_content_default_fields().
 */
function nyss_organization_content_default_fields() {
  module_load_include('inc', 'nyss_organization', 'nyss_organization.defaults');
  $args = func_get_args();
  return call_user_func_array('_nyss_organization_content_default_fields', $args);
}

/**
 * Implementation of hook_fieldgroup_default_groups().
 */
function nyss_organization_fieldgroup_default_groups() {
  module_load_include('inc', 'nyss_organization', 'nyss_organization.defaults');
  $args = func_get_args();
  return call_user_func_array('_nyss_organization_fieldgroup_default_groups', $args);
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function nyss_organization_imagecache_default_presets() {
  module_load_include('inc', 'nyss_organization', 'nyss_organization.defaults');
  $args = func_get_args();
  return call_user_func_array('_nyss_organization_imagecache_default_presets', $args);
}

/**
 * Implementation of hook_node_info().
 */
function nyss_organization_node_info() {
  module_load_include('inc', 'nyss_organization', 'nyss_organization.features.node');
  $args = func_get_args();
  return call_user_func_array('_nyss_organization_node_info', $args);
}

/**
 * Implementation of hook_user_default_permissions().
 */
function nyss_organization_user_default_permissions() {
  module_load_include('inc', 'nyss_organization', 'nyss_organization.defaults');
  $args = func_get_args();
  return call_user_func_array('_nyss_organization_user_default_permissions', $args);
}

/**
 * Implementation of hook_views_default_views().
 */
function nyss_organization_views_default_views() {
  module_load_include('inc', 'nyss_organization', 'nyss_organization.features.views');
  $args = func_get_args();
  return call_user_func_array('_nyss_organization_views_default_views', $args);
}
