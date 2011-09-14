<?php
// $Id: media-bliptv.tpl.php,v 1.1.2.1 2011/02/18 17:16:07 aaron Exp $

/**
 * @file media_bliptv/themes/media-bliptv.tpl.php
 *
 * Theme file for theme('media_bliptv').
 *
 * Variables passed along here:
 *  'output' => The video to display.
 *  'id' => The unique count for the video.
 *  'code' => The video code.
 *  'width' => The width of the video to display.
 *  'height' => The height of the video to display.
 *  'field' => The field of the content.
 *  'item' => The item array returned by the emvideo field.
 *  'autoplay' => TRUE or FALSE, to automatically play the video on display.
 *  'flv' => The .flv file returned by blip.tv.
 *  'thumbnail' => The URL of the thumbnail to display.
 *  'options' => Any other overrides.
 */
?>
<div id="media-bliptv-<?php print $id; ?>" class="media-bliptv">
  <?php print $output; ?>
</div>
