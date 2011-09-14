<?php
/*
 * Batchs 'resave_nodes'
 */

/**
 * Form builder; Generate a form to add/edit feed sources.
 *
 * @ingroup forms
 * @see aggregator_form_feed_validate()
 * @see aggregator_form_feed_submit()
 */
function batches_resave_nodes() {
  $form['info'] = array(
    '#value' => '<div>' . t('Resaves all nodes of a specified type.') . '</div>',
    '#weight' => -5,
  );
  $types = node_get_types('names');
  $form['type'] = array('#type' => 'radios',
    '#title' => 'Node type',
    '#options' => $types,
    '#required' => TRUE,
  );
//  drupal_set_message('<pre>' . print_r(node_get_types('names'), TRUE) . '</pre>');
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
  $form['revisions'] = array('#type' => 'checkbox',
    '#title' => t('Create new revisions'),
    '#description' => t('Create a new revision for each saved node.'),
  );
  $form['submit'] = array('#type' => 'submit', '#value' => t('Submit'));
  return $form;
}

/**
 * Process resave_nodes form submissions.
 */
function batches_resave_nodes_submit($form, &$form_state) {
  $values = $form_state['values'];
  batches_resave_nodes_start($values['max'], $values['dry_run'], $values['verbose'], $values['type'], $values['revisions']);
}

function batches_resave_nodes_start($max = NULL, $dry_run = FALSE, $verbose = FALSE, $type = 'page', $revisions) {
  $batch = array(
    'operations' => array(
      array('batches_resave_nodes_process', array($max, $dry_run, $verbose, $type, $revisions)),
      ),
    'finished' => 'batches_resave_nodes_finished',
    'title' => t('Resaving nodes'),
    'init_message' => t('Updating nodes of content type "!type."', array('!type' => $type)),
    'progress_message' => t('Processed @current out of @total.'),
    'error_message' => t('Resave nodes has encountered an error.'),
    'file' => __FILE__, // drupal_get_path('module', 'batches') . '/includes/resave_nodes.inc',
  );
  batch_set($batch);
}

function batches_resave_nodes_process($max, $dry_run, $verbose, $type, $revisions, &$context) {
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_nid'] = 0;
    $context['sandbox']['max'] = db_result(db_query("SELECT COUNT(DISTINCT nid) FROM {node} WHERE type = '%s'", $type));
    if ($max && $max < $context['sandbox']['max']) {
      $context['sandbox']['max'] = $max;
    }
  }

  // We can safely process 10 nodes at a time without a timeout.
  $limit = 10;
  
  $result = db_query_range("SELECT nid FROM {node} WHERE type = '%s' AND nid > %d ORDER BY nid ASC", $type, $context['sandbox']['current_nid'], 0, $limit);
  while (($row = db_fetch_array($result)) && $context['sandbox']['progress'] < $context['sandbox']['max']) {

    // Here we actually perform our processing on the current node.
    $node = node_load($row);
    if ($revisions) {
      $node->revision = 1;
    }
    else {
      unset($node->revision);
    }
    if (!$dry_run) {
      node_save($node);
    }
    $context['results']['total_nodes']++;
    if ($verbose) {
      $context['results']['titles'][] = l($node->title, 'node/'.$node->nid) . ($node->revision ? t(': saved as new revision') : '');
    }
    // Update our progress information.
    $context['sandbox']['progress']++;
    $context['sandbox']['current_nid'] = $node->nid;
    $context['message'] = t('Now processing node %name', array('%name' => $node->title));
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
function batches_resave_nodes_finished($success, $results, $operations) {
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
}
