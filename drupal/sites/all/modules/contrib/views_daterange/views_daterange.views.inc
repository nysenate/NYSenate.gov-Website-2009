<?php
// $Id: views_daterange.views.inc,v 1.1 2009/03/18 19:35:22 crell Exp $

/**
 * Implementation of hook_views_data().
 */
function views_daterange_views_data() {
  $data = array();

  // The flexible date argument.
  $data['node']['daterange_argument'] = array(
    'group' => t('Date'),
    'title' => t('Date range'),
    'help' => t('Filter any Views date field by an arbitrarily defined range class.'),
    'argument' => array(
      'handler' => 'daterange_argument_handler',
      'empty name field' => t('Undated'),
    ),
  );

  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function views_daterange_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'views_daterange'),
    ),
    'handlers' => array(
      'daterange_argument_handler' => array(
        'parent' => 'date_api_argument_handler',
      ),
    ),
  );
}
