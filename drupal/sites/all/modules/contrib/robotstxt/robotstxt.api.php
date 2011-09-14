<?php
// $Id: robotstxt.api.php,v 1.1.2.1 2009/02/19 22:08:00 hass Exp $

/**
 * @file
 * Hooks provided by the robotstxt module.
 */

/**
 * Add additional lines to the site's robots.txt file.
 *
 * @return
 *   An array of strings to add to the robots.txt.
 */
function hook_robotstxt() {
  return array(
    'Disallow: /foo',
    'Disallow: /bar',
  );
}
