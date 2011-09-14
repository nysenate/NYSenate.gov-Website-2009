<?php
/*
 * Batches 'delete_nodes'
 */

/**
 * Form builder; Generate a form to add/edit feed sources.
 *
 * @ingroup forms
 * @see aggregator_form_feed_validate()
 * @see aggregator_form_feed_submit()
 */
function batches_delete_nodes() {
  $form['info'] = array(
    '#value' => '<div>' . t('Deletes all nodes of a specified type.') . '</div>',
    '#weight' => -5,
  );
  // count how many nodes we have of each type
  $result = db_query("SELECT type, COUNT(*) AS num FROM {node} GROUP BY type");
  $count = array();
  while ($data = db_fetch_object($result)) {
    $count[$data->type] = $data->num;
  }
  
  // Add the types to the form. If there are no eligible types to delete,
  // we don't need to render the form.
//  $types = node_get_types('names');
  $types = array();
  foreach (node_get_types() as $type => $info) {
    if ($count[$type] > 0) {
      $types[$type] = $info->name .' ('. $count[$type] .')';
    }
  }
  natcasesort($types);
  $form['types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Node types'),
    '#options' => $types,
    '#description' => t('Select the types of content to delete'),
  );
  $form['max'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum'),
    '#size' => 10,
    '#description' => t('Enter the maximum number of nodes to be processed. Leave blank or enter zero to process all nodes.'),
  );
  $form['dry_run'] = array('#type' => 'checkbox',
    '#title' => t('Dry run'),
    '#description' => t('This is a dry run, so don\'t actually save anything.'),
  );
  $form['verbose'] = array('#type' => 'checkbox',
    '#title' => t('Verbose'),
    '#description' => t('Produce an item-by-item message at the end detailing what happened. Warning: This may produce errors when processing numerous nodes.'),
  );
  $form['submit'] = array('#type' => 'submit', '#value' => t('Submit'));
  return $form;
}

/**
 * Process delete_nodes form submissions.
 */
function batches_delete_nodes_submit($form, &$form_state) {
  $values = $form_state['values'];
  $types = array();
  foreach ($values['types'] as $type) {
    if ($type) {
      $types[] = $type;
    }
  }
  batches_delete_nodes_start($values['max'], $values['dry_run'], $values['verbose'], $types);
}

function batches_delete_nodes_start($max = NULL, $dry_run = FALSE, $verbose = FALSE, $types = array('page')) {
  $batch = array(
    'operations' => array(
      array('batches_delete_nodes_process', array($max, $dry_run, $verbose, $types)),
      ),
    'finished' => 'batches_delete_nodes_finished',
    'title' => t('Deleting nodes'),
    'init_message' => t('Deleting nodes of content type "!type."', array('!type' => implode(', ', $types))),
    'progress_message' => t('Processed @current out of @total.'),
    'error_message' => t('Delete nodes has encountered an error.'),
    'file' => __FILE__,
  );
  batch_set($batch);
}

function batches_delete_nodes_process($max, $dry_run, $verbose, $types, &$context) {
  $placeholders = implode(',', array_fill(0, count($types), "'%s'"));
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_nid'] = 0;
    $context['sandbox']['max'] = db_result(db_query("SELECT COUNT(DISTINCT nid) FROM {node} WHERE type IN ($placeholders)", $types));
    if ($max && $max < $context['sandbox']['max']) {
      $context['sandbox']['max'] = $max;
    }
  }

  // We can safely process 10 nodes at a time without a timeout.
  $limit = 10;
  
  $result = db_query_range("SELECT nid FROM {node} WHERE type IN ($placeholders) AND nid > %d ORDER BY nid ASC", $types, $context['sandbox']['current_nid'], 0, $limit);
  while (($row = db_fetch_array($result)) && $context['sandbox']['progress'] < $context['sandbox']['max']) {

    // Here we actually perform our processing on the current node.
    $title = node_load($row)->title;
    if (!$dry_run) {
      batches_delete_nodes_node_delete($row);
    }
    $context['results']['total_nodes']++;
    if ($verbose) {
      $context['results']['titles'][] = $title;
    }
    // Update our progress information.
    $context['sandbox']['progress']++;
    $context['sandbox']['current_nid'] = $row;
    $context['message'] = t('Now processing node %name', array('%name' => $title));
  }

  // Inform the batch engine that we are not finished,
  // and provide an estimation of the completion level we reached.
  if ($context['sandbox']['progress'] >= $context['sandbox']['max']) {
    $context['finished'] = 1;
  } else {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
* Batch 'finished' callback
*/
function batches_delete_nodes_finished($success, $results, $operations) {
  if ($success) {
    // Here we do something meaningful with the results.
    $message = $results['total_nodes'] .' processed. ';
    if ($results['titles']) {
      $message .= theme('item_list', $results['titles']);
    }
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments', array('%error_operation' => $error_operation[0], '@arguments' => print_r($error_operation[1], TRUE)));
  }
  drupal_set_message($message);
  cache_clear_all();
}


/**
* Performance-optimized version of the node_delete function from Drupal core.
*/
function batches_delete_nodes_node_delete($nid) {
  // Clear the cache before the load, so if multiple nodes are deleted, the
  // memory will not fill up with nodes (possibly) already removed.
  $node = node_load($nid, NULL, TRUE);

  if (node_access('delete', $node)) {
    db_query('DELETE FROM {node} WHERE nid = %d', $node->nid);
    db_query('DELETE FROM {node_revisions} WHERE nid = %d', $node->nid);

    // Call the node-specific callback (if any):
    node_invoke($node, 'delete');
    node_invoke_nodeapi($node, 'delete');
    if (function_exists('search_wipe')) {
      search_wipe($node->nid, 'node');
    }
  }
}
