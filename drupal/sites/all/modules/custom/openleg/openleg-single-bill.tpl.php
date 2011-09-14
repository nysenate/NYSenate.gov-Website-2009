<?php
// $Id$

/**
 * @file openleg-single-bill.tpl.php
 * Default theme implementation to display a single bill.
 *
 * Available variables:
 * - $senate_id: The bill ID. (This variable should probably be renamed.)
 * - $sponsor: The bill's sponsor, e.g., "ADAMS".
 * - $title: The bill's title.
 * - $committee: The bill's committee.
 * - $summary: Whether bill summar.
 *
 * @see template_preprocess_field()
 */
?>
<?php
_pathauto_include();
?>
<div class="leginfo-bill-wrapper">
  <strong>
    <a href="http://open.nysenate.gov/legislation/bill/<?php print $senate_id; ?>" title="<?php echo t('View this bill on open.nysenate.gov'); ?>"><?php print $senate_id; ?></a>: 
    <?php echo $title; ?>
  </strong>
  <?php echo t('sponsored by'); ?>
  <strong> 
    <a href="http://open.nysenate.gov/legislation/sponsor/<?php echo $sponsor; ?>" title="<?php echo t('Search open legislation by sponsor'); ?>"><?php echo $sponsor; ?></a>
  </strong><br />
  <?php echo t('Committee: '); ?>
  <a href="/committee/<?php echo pathauto_cleanstring(strtolower(str_replace(' ', '-', $committee))); ?>" title="<?php echo t('Visit this committee page'); ?>"><?php echo $committee; ?></a>
  <span class="leginfo-committee-search"> |
    <a href="http://open.nysenate.gov/legislation/committee/<?php echo $committee; ?>" title="<?php echo t('Search open legislation by committee'); ?>"><?php echo t('Search'); ?></a>
  </span><br />
  <?php echo $summary; ?>
  <a href="http://open.nysenate.gov/legislation/bill/<?php echo $senate_id; ?>" title="<?php echo t('View this bill on open.nysenate.gov'); ?>"><?php echo t('Read more...'); ?></a>
</div>
