<?php
// $Id$

/**
 *  @file
 *  xml-rpc-test.php
 *
 *  This file provides examples of retrieving information from NYSenate.gov using the node.get and views.get methods.
 *
 *  Project: NYSenate.gov
 *  Author: Sheldon Rampton
 *  Organization: New York State Senate
 *  Date: 2010-10-25
 *  Revised: 2010-10-25
 *
 *  For documentation, see the README file that accompanies this code as well as the developer documentation for
 *  NYSenate.gov at http://www.nysenate.gov/developers/apis
 */

  include('xmlrpc-api.inc');
  $api_key        = ''; // put your API key here
  $domain_name    = ''; // put your domain name here

// Examples of the node.get method
  
  // Get the node ID (nid), title and location for node 107 (Senator Eric Adams)
  $service = new nodeGet($domain_name, $api_key);
  $values = $service->get(array(
    'nid' => 107,
//    'fields' => array('nid', 'title', 'field_location'),
  ));
  print var_dump($values);


// Examples of the views.get method
/*
  
  // Get the node ID (nid) and title for all committees
  $service = new viewsGet($domain_name, $api_key);
  $values = $service->get(array(
    'view_name' => 'committees',
  ));
  print var_dump($values);
*/

/*
  // Get the node ID (nid) and title for all temporary committees
  $service = new viewsGet($domain_name, $api_key);
  $values = $service->get(array(
    'view_name' => 'committees',
    'display_id' => 'page_2',
  ));
  print var_dump($values);
*/

/*
  // Get the node ID (nid) and title for the first two committees
  $service = new viewsGet($domain_name, $api_key);
  $values = $service->get(array(
    'view_name' => 'committees',
    'limit' => 2,
  ));
  print var_dump($values);
*/

/*
  // Get a list of all committees, formatted as HTML
  $service = new viewsGet($domain_name, $api_key);
  $values = $service->get(array(
    'view_name' => 'committees',
    'format_output' => TRUE,
  ));
  print var_dump($values);
*/

/*
  // Get the last 5 senator news items for Eric Adams
  $service = new viewsGet($domain_name, $api_key);
  $values = $service->get(array(
    'view_name' => 'senator_news',
    'display_id' => 'block_1',
    'args' => array('Eric Adams'),
    'limit' => 5,
  ));
  print var_dump($values);
*/

/*
  // Get the last 5 senator news items for Eric Adams
  $service = new viewsGet($domain_name, $api_key);
  $values = $service->get(array(
    'view_name' => 'district_map',
    'args' => array('106'),
  ));
  print var_dump($values);
*/

  
?>