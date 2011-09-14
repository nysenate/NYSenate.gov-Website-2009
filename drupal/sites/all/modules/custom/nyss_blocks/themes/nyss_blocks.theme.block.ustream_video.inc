<?php
// $Id$

/**
 *  @file
 *  Theme functions for the nyss_blocks 'Live Stream' block
 */

/**
 *  Subject of the 'Live Stream' block.
 *
 *  @return
 *    The subject of this block.
 */
function theme_nyss_blocks_view_subject_ustream_video() {
  return t('Live Stream');
}

/**
 *  Display the content of the 'Live Stream' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_ustream_video() {
  $output .= '<object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" width="250" height="200" id="utv590305"><param name="flashvars" value="viewcount=true&amp;autoplay=false&amp;brand=embed"/><param name="allowfullscreen" value="true"/><param name="allowscriptaccess" value="always"/><param name="movie" value="http://www.ustream.tv/flash/live/1/513405"/><embed flashvars="viewcount=true&amp;autoplay=false&amp;brand=embed" width="250" height="200" allowfullscreen="true" allowscriptaccess="always" id="utv590305" name="utv_n_983437" src="http://www.ustream.tv/flash/live/1/513405" type="application/x-shockwave-flash" /></object><a href="http://www.ustream.tv/" style="padding:2px 0px 4px;width:250px;background:#FFFFFF;display:block;color:#000000;font-weight:normal;font-size:10px;text-decoration:underline;text-align:center;" target="_blank">Live video chat by Ustream</a><br/>';
  $output .= l(t('More media...'), 'media_reports');
  return $output;
}
