<?php
// $Id: views-view-list.tpl.php,v 1.3 2008/09/30 19:47:11 merlinofchaos Exp $
/**
 * @file views-view-list.tpl.php
 * Default simple view template to display a list of rows.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $options['type'] will either be ul or ol.
 * @ingroup views_templates
 */
/** Modified so it only prints the list if it actually has items with events,
  * as determined by the row theming.
  */
?><?php $has_items = FALSE; ?>
<?php foreach ($rows as $id => $row): ?><?php if ($row != '') {
  $items .= '<li class="' . $classes[$id] . '">' . $row . "</li>\n";
  $has_items = TRUE;
}
?><?php endforeach; ?>
<?php if ($has_items): ?>
  <div class="item-list">
    <?php if (!empty($title)) : ?>
      <h3><?php print $title; ?></h3>
    <?php endif; ?>
    <<?php print $options['type']; ?>>
      <?php print $items; ?>
    </<?php print $options['type']; ?>>
  </div>
<?php endif; ?>