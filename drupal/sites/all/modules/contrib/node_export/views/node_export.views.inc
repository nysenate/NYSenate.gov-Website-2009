<?php
// $Id: node_export.views.inc,v 1.1.2.6 2010/01/26 03:03:39 danielb Exp $

/**
 * @file
 * The Node Export views include.
 */

/**
 * Implementation of hook_views_handlers().
 */
function node_export_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'node_export') .'/views',
    ),
    'handlers' => array(
      'views_handler_field_node_link_export' => array(
        'parent' => 'views_handler_field_node_link',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_data_alter().
 */
function node_export_views_data_alter(&$views_data) {
  $views_data['node']['export_node'] = array(
    'field' => array(
      'title' => t('export link'),
      'help' => t('Provide a simple link to export the node.'),
      'handler' => 'views_handler_field_node_link_export',
    ),
  );
}

