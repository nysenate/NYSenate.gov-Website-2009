<?php
// $Id$

/**
 * @file
 * Common functionality for querying the OpenLeg API.
 */

define('OPENLEG_ROOT', 'http://open.nysenate.gov/legislation/api/1.0/xml/');
define('OPENLEG_STAGING', 'http://open-staging.nysenate.gov/legislation/api/1.0/xml/');

function openleg_curl_request($url) {
  $url .= '?filter=oid:s*+AND+stricken:false';
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, $url);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 15);
  $data = curl_exec($ch);
  curl_close($ch);
  return $data;
}

function openleg_retrieve($path, $source=OPENLEG_ROOT) {
  $xml = openleg_curl_request($source . str_replace("%2F", "/", urlencode($path)));
  $xml = str_replace("\0","",$xml);
  return @simplexml_load_string($xml);
}

function openleg_meeting($simplexml, $field = 'id') {
  switch ($field) {
    case 'date_time':
    case 'meetingDateTime':
      return (string)$simplexml->attributes()->meetingDateTime;
      break;
    case 'day_of_week':
    case 'meetday':
      return (string)$simplexml->attributes()->meetday;
      break;
    case 'location':
      return (string)$simplexml->attributes()->location;
      break;
    case 'committee_name':
    case 'committeeName':
      return (string)$simplexml->attributes()->committeeName;
      break;
    case 'committee_chair':
    case 'committeeChair':
      return (string)$simplexml->attributes()->committeeChair;
      break;
    case 'attendees':
      return $simplexml->attendees[0];
      break;
    case 'bills':
      return $simplexml->bills[0];
      break;
    case 'note':
    case 'notes':
      return (string)$simplexml->notes;
      break;
    case 'id':
    default:
      return (string)$simplexml->attributes()->id;
      break;
  }
}

function openleg_attribute($simplexml, $field = 'name') {
  return (string)$simplexml->attributes()->{$field};
}

function openleg_bill($simplexml, $field = 'sponsor') {
  switch ($field) {
    case 'year':
      return (string)$simplexml->attributes()->year;
      break;
    case 'id':
      return (string)$simplexml->attributes()->id;
      break;
    case 'current_committee':
    case 'currentCommittee':
      return (string)$simplexml->currentCommittee;
      break;
    case 'law_section':
    case 'lawSection':
      return (string)$simplexml->lawSection;
      break;
    case 'same_as':
    case 'sameAs':
      return (string)$simplexml->sameAs;
      break;
    case 'sponsor':
      return (string)$simplexml->sponsor->attributes()->fullname;
      break;
    case 'summary':
      return (string)$simplexml->summary;
      break;
    case 'title':
      return (string)$simplexml->title;
      break;
  }
}