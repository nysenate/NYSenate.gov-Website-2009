<?php

/**
 * @file
 *  Link webform functionalities to services module.
 */


module_load_include('inc', 'webform', 'includes/webform.submissions');

/**
 * Returns a list of webform nids.
 *
 * @return
 *   Array. An array of the nids of all webform nodes.
 */
function webform_service_list() {
  global $user;
  
  $db_result = db_query("SELECT nid FROM {node} WHERE type = 'webform'");
  
  $result = array();
  while ($row = db_fetch_array($db_result)) {
    $result[] = $row['nid'];
  }
  
  return $result;
}

/**
 * Returns a list of submission ids.
 *
 * @param $nid
 *   Number. The node id of the webform to retrieve submission ids from
 * @param $fromdate
 *   Number. The time of the oldest submission to query.
 * @return
 *   Array. An array of the sids of submissions since fromdate.
 */
function webform_service_get($nid, $fromdate = 0) {
  global $user;
  
  $db_result = db_query("SELECT sid FROM {webform_submissions} WHERE submitted >= '%d' AND nid = '%d'",$fromdate, $nid);
  
  $result = array();
  while ($row = db_fetch_array($db_result)) {
    $result[] = $row['sid'];
  }
  
  return $result;
}

/**
 * Returns a specified submission.
 *
 * @param $nid
 *   Number. The node ID.
 * @param $sid
 *   Number. The submission ID.
 * @return
 *   Object. The submission object with all wanted fields.
 */
function webform_service_view($nid,$sid) {
  
  //module_load_include('inc', 'webform', 'includes/webform.submissions');
  //$submissions = webform_get_submissions($nid);
  $submission = webform_get_submission($nid,$sid);
  _webform_service_populate_field_names($submission, $nid);

  if (!$submission) {
    return services_error(t("Could not find the submission."), 404);
  }

  return $submission;
}

/**
 * Returns an array of webform response submissions.
 *
 * @param $nid
 *   Number. The webform's node ID.
 * @param $limit
 *   Number. The maximum number of responses to return (default 100). 
 *   If a limit of "0" is specified, all responses will be returned. Warning: setting no limit could result in timeout or memory errors!
 * @param $start_date
 *   Number. An optional start date of the date range for which results are desired.
 * @param $end_date
 *   Number. An optional end date of the date range for which results are desired.
 * @param $start_sid
 *   Number. An optional start submission ID number for the range from which results are desired.
 * @param $end_sid
 *   Number. An optional end submission ID number for the range from which results are desired.
 * @return
 *   An array of the form:
 *     Array
 *         (
 *             'start_sid' => the lowest submission id in the returned set
 *             'end_sid' => the highest submission id in the return set
 *             'start_date' => the lowest submission date in the returned set
 *             'end_date' => the highest submission date in the returned set
 *             'nids' => Array(
 *                  [nid1] => [results1]
 *                  [nid2] => [results2]
 *                  ...
 *               )
 *         )
 *   where each instance of results1, results2, etc. is an array of the form:
 *     Array
 *         (
 *             'fields' => an array giving field definitions for the webform
 *             'sids' => Array(
 *                  [sid1] => [submission1]
 *                  [sid2] => [submission2]
 *                  ...
 *               )
 *         )
 *   and where each instance of submission1, submission2, etc. is an array of values from a single webform submission,
 *   as returned from function webform_service_submission_values().
 *
 * @see webform_service_submission_values()
 */
function webform_service_responses( $nid=NULL, $start_date=NULL, $end_date=NULL, $start_sid=NULL, $end_sid=NULL, $uid=NULL, $limit=100) {
  $filters = array();
  if ($nid) {
    $filters['nid'] = $nid;
  }
  if ($start_date) {
    $filters['start_date'] = $start_date;
  }
  if ($end_date) {
    $filters['end_date'] = $end_date;
  }
  if ($start_sid) {
    $filters['start_sid'] = $start_sid;
  }
  if ($end_sid) {
    $filters['end_sid'] = $end_sid;
  }
  if ($uid) {
    $filters['uid'] = $uid;
  }
  if ($limit) {
    $filters['limit'] = $limit;
  }

  $field_structures = array();
  $submissions = webform_service_get_submissions($filters);
  $results = array('nids' => array());
  foreach ($submissions as $submission) {
    $results['start_sid'] = isset($results['start_sid']) ? min($submission->sid, $results['start_sid']) : $submission->sid;
    $results['end_sid'] = isset($results['end_sid']) ? max($submission->sid, $results['end_sid']) : $submission->sid;
    $results['start_date'] = isset($results['start_date']) ? min($submission->submitted, $results['start_date']) : $submission->submitted;
    $results['end_date'] = isset($results['end_date']) ? max($submission->submitted, $results['end_date']) : $submission->submitted;
    if (!isset($results['nids'][$submission->nid])) {
      $results['nids'][$submission->nid] = array(
        'fields' => webform_service_fields($submission->nid),
        'sids' => array(),
      );
    }
    $results['nids'][$submission->nid]['sids'][$submission->sid] = webform_service_submission_values($submission, $results['nids'][$submission->nid]['fields'], 'text');
  }
  drupal_alter('webform_service_responses', $results); // hook_webform_service_responses_alter() lets other modules alter submission responses.
  return $results;
}

/**
 * Save a node. It creates a new one, in case the 'nid' field
 * is missing.
 *
 * @param $submission
 *   Array. The submission fields' values, just like created on
 *   submission edit form.
 * @return
 *   Number. The submission id.
 */
function webform_service_save($submission) {
  
  // save the submission here.
  
  return $submission->sid;
}

/**
 * Delete a submission. 
 *
 * @param $sid
 *   Array. The node fields' values, just like created on
 *   node edit form.
 * @return
 *   Number. The id of the deleted submission.
 */
function webform_service_delete($sid) {
  
  // delete the submission here.
  
  return $sid;
}

/**
 * Check if the user has the permission to get the
 * webform's data thru services.
 *
 * @param $fromdate
 *   Number. The date in seconds of the earliest webform submission to query.
 * @return
 *   Boolean. TRUE if the user has view access.
 */
function webform_service_list_access() {
  return TRUE; // hack so we don't have to do an extra authentication dance
  global $user;
  return user_access('access all webform results');
}

/**
 * Check if the user has the permission to get the
 * webform's data thru services.
 *
 * @param $fromdate
 *   Number. The date in seconds of the earliest webform submission to query.
 * @return
 *   Boolean. TRUE if the user has view access.
 */
function webform_service_get_access($nid, $fromdate) {
  return TRUE; // hack so we don't have to do an extra authentication dance
  global $user;
  return user_access('access all webform results');
}

/**
 * Check if the user has the permission to get the
 * node's formatted data thru services.
 *
 * @param $sid
 *   Number. The submission ID.
 * @return
 *   Boolean. TRUE if the user has the permission to get the
 *   submission's data thru services.
 */
function webform_service_view_access($sid) {
  return TRUE; // hack so we don't have to do an extra authentication dance
  global $user;
  return user_access('access all webform results');
}

/**
 * Check if the user has the permission to get the
 * node's formatted data thru services.
 *
 * @param $nid
 *   Number. The node ID.
 * @return
 *   Boolean. TRUE if the user has the permission to get the
 *   submission's data thru services.
 */
function webform_service_fields_access($nid=NULL) {
  return TRUE; // hack so we don't have to do an extra authentication dance
  global $user;
  return user_access('access all webform results');
}

/**
 * Check if the user has the permission to get the
 * node's formatted data thru services.
 *
 * @param $nid
 *   Number. The node ID.
 * @return
 *   Boolean. TRUE if the user has the permission to get the
 *   submission's data thru services.
 */
function webform_service_responses_access($nid=NULL) {
  return TRUE; // hack so we don't have to do an extra authentication dance
  global $user;
  return user_access('access all webform results');
}

/**
 * Check if the user has the permission to save a node.
 *
 * @param $node
 *   Object. The submission form object.
 * @return
 *   Boolean. TRUE if the user has the permission to save a submission.
 */
/*
function webform_service_save_access($submission) {
  
  return user_access('edit all webform submissions');
}
*/

/**
 * Check if the user has the permission to delete a node.
 *
 * @param $nid
 *   Number. The node ID.
 * @return
 *   Boolean. TRUE if the user has the permission to delete a submission.
 */
/*
function webform_service_delete_access($sid) {
  return user_access('delete all webform submissions');
}
*/

/**
 * Gets the name of each field and adds it to the object
 *
 * @param $submission
 *   Object. (passed by reference) The submission object.
 * @return
 *   Null. No return value
 */
function _webform_service_populate_field_names(&$submission, $nid){
  
  // get the field names
  static $fields = array();
  $result = db_query("SELECT `cid`,`form_key`,`type`,`name` FROM {webform_component} WHERE `nid` = '%d'",$nid);
  while ($row = db_fetch_array($result)) {
    $fields[$row['cid']] = array(
      'key'=>$row['form_key'], // the field's machine name, e.g., 'last_name'
      'type'=>$row['type'],    // the field type, e.g., textfield, grid, email, etc.
      'name'=>$row['name'],    // the field's display label, e.g., 'Last name'
    );
  }
  
  // loop through $submission->data and add field names to each
  if (is_array($submission->data)){
    foreach($submission->data as $key => $value){
      $submission->data[$key]['field_key'] = $fields[$key]['key'];
      $submission->data[$key]['field_type'] = $fields[$key]['type'];
      $submission->data[$key]['field_name'] = $fields[$key]['name'];
    }
  }
}
