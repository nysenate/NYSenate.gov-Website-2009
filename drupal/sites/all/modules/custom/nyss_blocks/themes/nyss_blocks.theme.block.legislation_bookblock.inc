<?php
// $Id$

/**
 *  @file
 *  Theme functions for the 'About this blog' block for Senators' Blogs.
 */

/**
 *  Subject of the 'About this blog' block.
 *  @return
 *    The subject of that block.
 */
function theme_nyss_blocks_view_subject_legislation_bookblock() {
  return t('Legislation Comments');
}

/**
 *  Display the content of the 'About this blog' block.
 *
 *  @TODO: we need to build the blog view and figure out the senator.
 *
 *  @param $node
 *    (optional) The senator's node.
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_legislation_bookblock() {
  if (arg(0) == 'node' && is_numeric(arg(1)) && is_null(arg(2))) {
    $node = node_load(arg(1));
    $toc = book_toc($node->book['bid'], array(), 100);
    if ($toc ) {    
      $in = '(';
      foreach($toc as $key => $chapter) {
        if ($in != '(') { $in .= ', '; }
        $in .= $key;      
      }
      $in .= ')';
      $query = sprintf('SELECT n.title, b.nid, c.cid, c.subject, c.name, c.uid FROM {book} AS b INNER JOIN {comments} AS c ON c.nid = b.nid INNER JOIN {node} AS n ON b.nid = n.nid WHERE b.nid IN (SELECT nid FROM {book} WHERE mlid IN %s) AND c.status = 0 ORDER BY cid DESC', $in);
      $results = db_query($query);
      $output = '<ul>';
      while ($comment = db_fetch_object($results)) {
		$commentoutput .= '<li>';
        $commentoutput .= l($comment->subject, 'node/'. $comment->nid, array('fragment'=>'comment-'.$comment->cid)) . ' in ' . l($comment->title, 'node/'.$comment->nid) . ' by ' . l($comment->name, 'user/'.$comment->uid); 
        $commentoutput .= '</li>';
      }
	  if (!$commentoutput) {
		$commentoutput .= '<li>' . t('No comments yet!') . '</li>';
	  }
      $output .= $commentoutput . '</ul>';
      return $output;
    }
  }  
}
