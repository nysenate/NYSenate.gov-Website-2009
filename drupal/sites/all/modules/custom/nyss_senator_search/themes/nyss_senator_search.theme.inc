<?php

function theme_nyss_senator_search() {
  $output .= drupal_get_form('nyss_senator_search_form');
  return $output;
}

function theme_nyss_senator_search_unavailable($nysboe) {
  $output = t(
    'This service is currently being updated. Please use the !lookup_link to verify your Senator. ' .
    'We apologize for any inconvenience.',
    array(
      '!lookup_link' => l(t('New York Board of Election look up tool'), $nysboe)
    )
  );
  return $output;
}