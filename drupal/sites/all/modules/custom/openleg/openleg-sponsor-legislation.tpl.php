<?php
// $Id$

/**
 * @file openleg-sponsor-legislation.tpl.php
 * Default theme implementation to the paged result for legislation sponsored by a single senator.
 * 'arguments' => array('sponsor' => NULL, 'page' => 1, 'numitems' => 20, 'source' => OPENLEG_ROOT),
 * Available variables:
 * - $sponsor: The bill's sponsor, e.g., "ADAMS".
 * - $page: The page of bill results, e.g, "1" means it's the first page.
 * - $numitems: The number of results per page.
 * - $source: Normally OPENLEG_ROOT, but can be OPENLEG_STAGING as well. (This variable is probably unnecessary.)
 *
 * @see template_preprocess_field()
 */
?>
<?php
  $results = openleg_sponsor_legislation($sponsor, $page, $numitems, $source);
  if ($results) {
    foreach ($results as $result) {
      $output .= theme('openleg_single_bill', $result['senateId'], $result['sponsor'], $result['title'], $result->committee, $result->summary);
      $count++;
    }
  }
  print $output;
?>