<?php

// code from one-time fix of event types; keeping here for reference purposes only

/**
 * Implementation of hook_menu().
 */
function nyss_batch_menu() {
  $items = array();
  $items['admin/content/batch/resave_videos'] = array(
    'title' => t('Batch resave nodes'),
    'page callback' => 'nyss_batch_update_videos',
    'access arguments' => array('administer nodes'),
    'type' => MENU_CALLBACK,
  );
  return $items;
}

function nyss_batch_update_videos() {
  $batch = array(
    'operations' => array(
      array('nyss_batch_update_some_videos', array()),
      ),
    'finished' => 'nyss_batch_video_updates_finished',
    'title' => t('Updating videos'),
    'init_message' => t('Updating video batch links.'),
    'progress_message' => t('Processed @current out of @total.'),
    'error_message' => t('Video update has encountered an error.'),
  );
  batch_set($batch);

  // If this function was called from a form submit handler, stop here,
  // FAPI will handle calling batch_process().

  // If not called from a submit handler, add the following,
  // noting the url the video should be sent to once the batch
  // is finished.
  batch_process('node');
}

function nyss_batch_update_some_videos(&$context) {
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_nid'] = 0;
    $context['sandbox']['max'] = db_result(db_query("SELECT COUNT(DISTINCT nid) FROM {node} WHERE type = 'video'"));
  }

  // We can safely process 5 videos at a time without a timeout.
  $limit = 5;
  $types = nyss_event_types();

  // With each pass through the callback, retrieve the next group of nids.
  $result = db_query_range("SELECT nid FROM {node} WHERE type = 'video' AND nid > %d ORDER BY nid ASC", $context['sandbox']['current_nid'], 0, $limit);
  while ($row = db_fetch_array($result)) {

    // Here we actually perform our processing on the current video.
    $video = node_load($row);
    if (count(taxonomy_node_get_terms_by_vocabulary($video, 1)) == 0) {
      if ($video->field_committee[0]['nid']) {
        $committee = node_load($video->field_committee[0]['nid']);
        if (count(taxonomy_node_get_terms_by_vocabulary($committee, 1)) == 0) {
          $video->taxonomy[117] = taxonomy_get_term(117); // assign miscellaneous
        }
        else {
          $video->taxonomy = array_merge($video->taxonomy, taxonomy_node_get_terms_by_vocabulary($committee, 1));
        }
      }
    }
    if (!$video->field_program_type[0]['value']) {
      $video->field_program_type[0]['value'] = 0;
    }
    if ($video->field_video_type[0]['value'] === 0) {
      $video->field_video_type[0]['value'] = 5;
    }
    else if ($video->field_video_type[0]['value']) {
      $before = $video->field_video_type[0]['value'];
      switch ($video->field_video_type[0]['value']) {
        case 1:
          $video->field_video_type[0]['value'] = 3;
          break;
        case 2:
          $video->field_video_type[0]['value'] = 6;
          break;
        case 10:
          $video->field_video_type[0]['value'] = 11;
          break;
        case 3:
          $video->field_video_type[0]['value'] = 7;
          break;
        case 8:
          $video->field_video_type[0]['value'] = 9;
          break;
        case 9:
          $video->field_video_type[0]['value'] = 10;
          break;
        case 4:
          $video->field_video_type[0]['value'] = 4;
          break;
        case 5:
          $video->field_video_type[0]['value'] = 1;
          break;
        case 7:
          $video->field_video_type[0]['value'] = 8;
          break;
        case 6:
          $video->field_video_type[0]['value'] = 2;
          break;
      }
      drupal_set_message("BEFORE: $before; AFTER: " . $video->field_video_type[0]['value'] . l($video->title, 'node/'.$video->nid));
      node_save($video);
    }
    else if ($video->field_event[0]['nid']) {
      $event = node_load($video->field_event[0]['nid']);
      $video->field_video_type[0]['value'] = $event->field_public_hearing[0]['value'];
      drupal_set_message(print_r($event->field_public_hearing, TRUE) . l($video->title, 'node/'.$video->nid));
      node_save($video);
    }
    $context['results']['total_videos']++;
//    $context['results']['titles'][] = $video->title;
    
    // Update our progress information.
    $context['sandbox']['progress']++;
    $context['sandbox']['current_nid'] = $video->nid;
    $context['message'] = t('Now processing video %name', array('%name' => $video->title));
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
function nyss_batch_video_updates_finished($success, $results, $operations) {
  if ($success) {
    // Here we do something meaningful with the results.
    $message = $results['total_videos'] .' processed. ';
//    $message .= theme('item_list', $results['titles']);
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments', array('%error_operation' => $error_operation[0], '@arguments' => print_r($error_operation[1], TRUE)));
  }
  drupal_set_message($message);
}
