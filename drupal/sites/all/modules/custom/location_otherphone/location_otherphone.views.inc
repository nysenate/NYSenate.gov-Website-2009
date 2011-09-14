<?php
// $Id$

/**
 * @file
 * Views 2 support for Location Other Phone.
 */

/**
 * Implementation of hook_views_data().
 */
function location_otherphone_views_data() {
  // ----------------------------------------------------------------
  // location_otherphone table -- basic table information.

  // Define the base group of this table. Fields that don't
  // have a group defined will go into this field by default.

  $data['location_otherphone']['table']['group'] = t('Location');

  // Location_fax joins only to location.
  $data['location_otherphone']['table']['join'] = array(
    'location' => array(
      'left_field' => 'lid',
      'field' => 'lid',
    ),
  );

  // ----------------------------------------------------------------
  // location_otherphone table -- fields

  $data['location_otherphone']['otherphone'] = array(
    'title' => t('Other phone'),
    'field' => array(
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
      'empty field name' => t('None'),
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
      'allow empty' => TRUE,
    ),
  );

  return $data;
}
