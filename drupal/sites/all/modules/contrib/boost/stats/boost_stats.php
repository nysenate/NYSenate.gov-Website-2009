<?php
// $Id: boost_stats.php,v 1.1.2.3 2009/06/23 00:23:55 mikeytown2 Exp $

// Script should take under 1mb of memory to work.
// Prime php for background operations
ob_end_clean();
header("Connection: close");
ignore_user_abort();

// Output of 1 pixel transparent gif
ob_start();
header("Content-type: image/gif");
header("Expires: Wed, 11 Nov 1998 11:11:11 GMT");
header("Cache-Control: no-cache");
header("Cache-Control: must-revalidate");
header("Content-Length: 43");
header("Connection: close");
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",71,73,70,56,57,97,1,0,1,0,128,255,0,192,192,192,0,0,0,33,249,4,1,0,0,0,0,44,0,0,0,0,1,0,1,0,0,2,2,68,1,0,59);
ob_end_flush();
flush();

// Image returned and connection closed.
// Do background processing. Time taken below should not effect page load times.

// Exit script if nothing was passed to it.
if (   !isset($_GET['nid'])
    && !isset($_GET['title'])
    && !isset($_GET['q'])
    && !isset($_GET['referer'])
    ) {
  exit;
}

// Set variables passed via GET.
$nid = isset($_GET['nid']) ? $_GET['nid'] : NULL;
$title = isset($_GET['title']) ? urldecode($_GET['title']) : NULL;
$q = isset($_GET['q']) ? $_GET['q'] : NULL;
$referer = isset($_GET['referer']) ? $_GET['referer'] : NULL;

// Connect to DB.
include_once './includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_DATABASE);

// Get stat settings.
$count_views = db_fetch_array(db_query_range("SELECT value FROM {variable} WHERE name = '%s'", 'statistics_count_content_views', 0, 1));
$count_views = unserialize($count_views['value']);
$access_log = db_fetch_array(db_query_range("SELECT value FROM {variable} WHERE name = '%s'", 'statistics_enable_access_log', 0, 1));
$access_log = unserialize($access_log['value']);

// Set node counter.
if ($count_views) {
  // We are counting content views.
  if (isset($nid) && is_numeric($nid)) {
    // A node has been viewed, so update the node's counters.
    db_query('UPDATE {node_counter} SET daycount = daycount + 1, totalcount = totalcount + 1, timestamp = %d WHERE nid = %d', time(), $nid);
    // If we affected 0 rows, this is the first time viewing the node.
    if (!db_affected_rows()) {
      // We must create a new row to store counters for the new node.
      db_query('INSERT INTO {node_counter} (nid, daycount, totalcount, timestamp) VALUES (%d, 1, 1, %d)', $nid, time());
    }
  }
}

// Set access log.
if ($access_log && isset($title) && isset($q)) {
  $session_id = session_id();
  if (empty($session_id)) {
    $session_id = $_COOKIE[session_name()];
    if (empty($session_id)) {
      // This only goes in the access log; only used for stats, not creds.
      $session_id = md5($_SERVER['HTTP_USER_AGENT'] . ip_address());
    }
  }
  $uid = 0;
  db_query("INSERT INTO {accesslog} (title, path, url, hostname, uid, sid, timer, timestamp) values('%s', '%s', '%s', '%s', %d, '%s', %d, %d)", $title, $q, $referer, ip_address(), $uid, $session_id, timer_read('page'), time());
}
exit;