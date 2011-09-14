<?php

$node = node_load($row->nid);
$toc = book_toc($node->book['bid'], array(), 100);
if ($toc ) {    
  $in = '(';
  foreach($toc as $key => $chapter) {
    if ($in != '(') { $in .= ', '; }
    $in .= $key;      
  }
  $in .= ')';
  $query = sprintf('SELECT COUNT(cid) as commcount FROM {book} AS b INNER JOIN {comments} AS c ON c.nid = b.nid INNER JOIN {node} AS n ON c.nid = n.nid WHERE b.nid IN (SELECT nid FROM {book} WHERE mlid IN %s) AND n.comment > 0 AND c.status = 0 ORDER BY cid DESC', $in);
  $results = db_query($query);

  while($comment = db_fetch_array($results)) {
    $comments = format_plural($comment['commcount'], '(1 comment)', '(@count comments)');
  }
}

print '<div class="legislation-outline';
global $currentTerm;
if($currentTerm != $row->term_data_name) {
  print ' legislation-section"><h2 class="title">'.l($row->term_data_name,'legislation/issue/'.$row->term_data_tid) .'</h2>';
  $currentTerm = $row->term_data_name;
}
else {
  print '">';
}
print '<div class="legislation-top"><h3 class="title legislation-title">'. l($row->node_title, 'node/'.$row->nid) . '<span class="legis-comments">' . l($comments, 'node/'.$row->nid, array('fragment'=>'comments')) . '</span></h3></div>';
print '</div>';
