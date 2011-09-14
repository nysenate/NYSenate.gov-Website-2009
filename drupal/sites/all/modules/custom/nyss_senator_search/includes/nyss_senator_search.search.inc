<?php

function nyss_senator_search_search($address_string = '') {
  $nysboe = 'http://nymap.elections.state.ny.us/nysboe/';
  $zip = substr($address_string, -5);
  if (is_numeric($zip) == TRUE) {
    if (substr($zip, 0, 2) == '11' && $zip[2] != '2') {
      drupal_set_message(
        t(
          'Residents of Queens: Addresses that contain hyphens (ie 12-34 Main St.) may occasionally produce inaccurate search results. ' .
          'If you live in Queens, please use the !lookup_link to verify your Senator. We apologize for any inconvenience.', 
          array(
            '!lookup_link' => l(t('New York Board of Election look up tool'), 'http://nymap.elections.state.ny.us/nysboe/')
          )
        )
      );
    }
  }
  
  $xml = nyss_senator_search_cd_lookup($address_string); //lookup happening
  $cd_arr = explode(" ", $xml->congressional->district);
  $cd = $cd_arr[count($cd_arr) - 1];
  $cd_upper_arr = explode(" ",$xml->senate->district);
  $cd_upper = $cd_upper_arr[count($cd_upper_arr) - 1];
  $cd_lower_arr = explode(" ",$xml->assembly->district);
  $cd_lower = $cd_lower_arr[count($cd_lower_arr) - 1];
  
  $nearbyDistricts_count = count((array)($xml->senate->nearbyDistricts));
  if ($nearbyDistricts_count > 0)
  {
    $nearbyDistrictsArray = get_object_vars($xml->senate->nearbyDistricts);
    $i = 0;
    if ($nearbyDistrictsArray['senate']->district != null) {// nearby district = 1 
      $nearbyDistricts = t('This address is within 1/3 of a mile of this Senate district:<br />');
      $nearbyDistricts .= l($nearbyDistrictsArray['senate']->district, $nearbyDistrictsArray['senate']->districtUrl) . '<br />';
    } else // nearby district >=2
    {
      $nearbyDistricts = t('This address is within 1/3 of a mile of these Senate districts:<br /><ul>');
      while ($nearbyDistrictsArray['senate'][$i]->district != null)
      {
        $nearbyDistricts .= '<li>' . l($nearbyDistrictsArray['senate'][$i]->district, $nearbyDistrictsArray['senate'][$i]->districtUrl) . '</li>';
        $i++;
      }
      
      $nearbyDistricts .= '</ul>';
    }
    drupal_set_message($nearbyDistricts);
    
  }

  $items = array(
    t('Federal Congress: !cd', array('!cd' => $cd)), 
    t('NYS Senate: !cd_upper', array('!cd_upper' => $cd_upper)), 
    t('NYS Assembly: !cd_lower', array('!cd_lower' => $cd_lower)
    ),
  );
  if ($cd) {
    $sql = "SELECT s.nid FROM {content_type_senator} s
    LEFT JOIN {node} n ON s.vid = n.vid
    LEFT JOIN {content_type_senator} node_data_field_status ON n.vid = node_data_field_status.vid    
    LEFT JOIN {content_type_district} d ON s.field_senators_district_nid = d.nid
    WHERE n.status = 1 AND (n.type in ('senator')) AND (node_data_field_status.field_status_value IS NULL) AND d.field_district_number_value = %d";
    $senator_nid = db_result(db_query(db_rewrite_sql($sql), $cd_upper));
    $senator = node_load($senator_nid);
    $senator->guest_address = $address_string;
    $output .= theme('nyss_senator_search_result', $senator, $zip, $cd_upper, $cd_lower, $cd, $items);
  }
  else {
    $output .= theme('nyss_senator_search_result', $senator, $zip, $cd_upper, $cd_lower, $cd, $items);
   
  }
  return $output;
}

