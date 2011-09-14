<?php
// $Id: views-view.tpl.php,v 1.11 2008/12/02 18:35:50 merlinofchaos Exp $
/**
 * @file views-view.tpl.php
 * Main view template
 *
 * Variables available:
 * - $css_name: A css-safe version of the view name.
 * - $header: The view header
 * - $footer: The view footer
 * - $rows: The results of the view query, if any
 * - $empty: The empty text to display if the view is empty
 * - $pager: The pager next/prev links to display, if any
 * - $exposed: Exposed widget form/info to display
 * - $feed_icon: Feed icon to display, if any
 * - $more: A link to view more, if any
 * - $admin_links: A rendered list of administrative links
 * - $admin_links_raw: A list of administrative links suitable for theme('links')
 *
 * @ingroup views_templates
 */
 
 if (module_exists('jq')) {
   // I'm using jq_add here. It assumes you have the jQuery Cycle plug-in
   // installed. That plug-in comes bundled with the jQuery Plugins module as
   // jq_add('cycle'), but you could also just drop it into a /plugins or
   // /sites/all/plugins folder (as done here) and call it with the same method.
   jq_add('cycle');
   // Here's the actual call for our cycle slide show plug-in.
   // I'm using the 'fade' effect, fading the image cycle, slowing it from the
   // default with 'timeout', and using 'pause' to allow a pause on mouse hover.
   // There are lots of cool effects; see the plug-in home at malsup.com/jquery/cycle/.
   $js = <<<js
   $('.view-senator-carousel ul').cycle({
     fx: 'fade',
     pause: 1,
     timeout: 10000
   });
js;
   // Make it degrade gracefully in non-javascript browsers.
   $js = "if (Drupal.jsEnabled) {  $(document).ready(function() { $js  });  }";
   drupal_add_js($js, 'inline');
 }
 
?>
<div class="view view-<?php print $css_name; ?> view-id-<?php print $name; ?> view-display-id-<?php print $display_id; ?> view-dom-id-<?php print $dom_id; ?>">
  <?php if ($admin_links): ?>
    <div class="views-admin-links views-hide">
      <?php print $admin_links; ?>
    </div>
  <?php endif; ?>
  <?php if ($header): ?>
    <div class="view-header">
      <?php print $header; ?>
    </div>
  <?php endif; ?>

  <?php if ($exposed): ?>
    <div class="view-filters">
      <?php print $exposed; ?>
    </div>
  <?php endif; ?>

  <?php if ($attachment_before): ?>
    <div class="attachment-before">
      <?php print $attachment_before; ?>
    </div>
  <?php endif; ?>

  <?php if ($rows): ?>
    <div class="view-content">
      <?php print $rows; ?>
    </div>
  <?php elseif ($empty): ?>
    <div class="view-empty">
      <?php print $empty; ?>
    </div>
  <?php endif; ?>

  <?php if ($pager): ?>
    <?php print $pager; ?>
  <?php endif; ?>

  <?php if ($attachment_after): ?>
    <div class="attachment-after">
      <?php print $attachment_after; ?>
    </div>
  <?php endif; ?>

  <?php if ($more): ?>
    <?php print $more; ?>
  <?php endif; ?>

  <?php if ($footer): ?>
    <div class="view-footer">
      <?php print $footer; ?>
    </div>
  <?php endif; ?>

  <?php if ($feed_icon): ?>
    <div class="feed-icon">
      <?php print $feed_icon; ?>
    </div>
  <?php endif; ?>

</div> <?php // class view ?>
