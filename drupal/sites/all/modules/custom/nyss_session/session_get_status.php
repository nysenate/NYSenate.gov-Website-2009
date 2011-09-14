<?php
header('Cache-Control: no-cache, must-revalidate');
header('Expires: Mon, 26 Jul 1997 05:00:00 GMT');
header('Content-type: application/json');

$status = nyss_session_get_status();
print json_encode($status);

function nyss_session_get_status() {
  $result = _nyss_session_get_xml("http://63.118.56.3/wtsstatus.xml");
  $status = array();
  // Parse out values from the retrieved XML
  $status['state'] = (string)$result->channel->item->wtsstate;
  $status['text'] = (string)$result->channel->item->wtstext;
  $status['start_day'] = (string)$result->channel->item->startstringday;
  $status['start_time'] = (string)$result->channel->item->startstringtime;
  $status['majority_conference_meeting'] = (string)$result->channel->item->wtsmajconfmeeting;
  $status['last_convened'] = (string)$result->channel->item->wtslastconvened;
  $status['last_adjourned'] = (string)$result->channel->item->wtslastadjourned;

  // Calculate a boolean value
  // This flag also gets set individually below, so this code arguably isn't necessary.
  // Belts and braces. Belts and braces.
  $status['display_video'] = in_array(trim(strtolower($status['state'])), 
    array(
      "standby to convene", 
      "standby to reconvene", 
      "in session", 
      "senate and assembly convened in joint session",
      "convened in extraordinary session",
    )
  );
  // Construct the message and headline, and decide whether to display video.
  switch (trim(strtolower($status['state']))) {
    // Senate is meeting, so show video
    case 'standby to convene':
      $status['message'] = 'The Senate is standing by to convene. ';
      $status['message'] .= $status['text'];
      $status['headline'] = 'Senate Status';
      $status['display_video'] = TRUE;
      break;
    case 'standby to reconvene':
      $status['message'] = 'The Senate is standing by to reconvene. ';
      $status['message'] .= $status['text'];
      $status['headline'] = 'Senate Status';
      $status['display_video'] = TRUE;
      break;
    case 'in session':
      $status['message'] = 'The Senate is in Session. ';
      $status['message'] .= $status['text'];
      $status['headline'] = 'Senate Status. ';
      $status['display_video'] = TRUE;
      break;
    case 'senate and assembly convened in joint session':
      $status['message'] = 'The Senate and Assembly has convened in a Joint Session. ';
      $status['message'] .= $status['text'];
      $status['headline'] = 'Senate Status';
      $status['display_video'] = TRUE;
      break;
    case 'convened in extraordinary session':
      $status['message'] = 'The Senate is Convened in Extraordinary Session. ';
      $status['message'] .= $status['text'];
      $status['headline'] = 'Senate Status';
      $status['display_video'] = TRUE;
      break;

    // Senate is not currently meeting, so point people to video archives
    case 'adjourned to [date, time]':
      $status['message'] = 'Adjourned until ' . $status['start_time'] . ', ' . $status['start_day'] . '. ';
      $status['message'] .= _nyss_session_archives_text();
      $status['message'] .= $status['text'];
      $status['headline'] = 'When is Session?';
      $status['display_video'] = FALSE;
      break;
    case 'adjourned to the call of the temporary president':
      $status['message'] = 'Adjourned to the call of the Temporary President. ';
      $status['message'] .= _nyss_session_archives_text();
      $status['message'] .= $status['text'];
      $status['headline'] = 'When is Session?';
      $status['display_video'] = FALSE;
      break;
    case 'temporarily at ease':
    case 'at ease':
      $status['message'] = 'The Senate is Temporarily at Ease. ';
      $status['message'] .= _nyss_session_archives_text();
      $status['message'] .= $status['text'];
      $status['headline'] = 'Senate Status';
      $status['display_video'] = FALSE;
      break;
    case 'in recess until [time]':
      $status['message'] = 'The Senate is in recess until ' . $status['start_time'] . '. ';
      $status['message'] .= _nyss_session_archives_text();
      $status['message'] .= $status['text'];
      $status['headline'] = 'When is Session?';
      $status['display_video'] = FALSE;
      break;
    case 'in recess':
      $status['message'] = 'The Senate is in recess. ';
      $status['message'] .= _nyss_session_archives_text();
      $status['message'] .= $status['text'];
      $status['headline'] = 'When is Session?';
      $status['display_video'] = FALSE;
      break;

    // Free form text doesn't meet any of the above categories, so don't show video
    // OR point to the video archives.
    case 'free form text box':
      $status['message'] = $status['text'];
      $status['headline'] = 'Senate Status';
      $status['display_video'] = FALSE;
      break;

    default:
      // belts and braces logic to make sure the temporary president case gets matched correctly
      if (substr($status['state'], 0, 12) == 'Adjourned to' && preg_match('/temporary president/i', $status['state'], $matches)) {
        $status['message'] = 'The Senate is adjourned to the call of the Temporary President. ';
        $status['message'] .= _nyss_session_archives_text();
        $status['message'] .= $status['text'];
        $status['headline'] = 'When is Session?';
        $status['display_video'] = FALSE;
      }
      // ... and to match the adjourned to case
      else if (substr($status['state'], 0, 12) == 'Adjourned to' && trim($status['start_day']) != '' && trim($status['start_time']) != '') {
        $status['message'] = 'Adjourned until ' . $status['start_time'] . ', ' . $status['start_day'] . '. ';
        $status['message'] .= _nyss_session_archives_text();
        $status['message'] .= $status['text'];
        $status['headline'] = 'When is Session?';
        $status['display_video'] = FALSE;
      }
      // ... and to match the in recess case
      else if (substr($status['state'], 0, 15) == 'In Recess until' && $status['start_time'] != '') {
        $status['message'] = 'The Senate is in recess until ' . $status['start_time'] . '. ';
        $status['message'] .= _nyss_session_archives_text();
        $status['message'] .= $status['text'];
        $status['headline'] = 'When is Session?';
        $status['display_video'] = FALSE;
      }
      // If nothing matches, use the value of $status['state'] directly
      else if ($status['state'] != '') {
        $status['message'] = $status['state'] . ' ';
        $status['message'] .= $status['text'];
        $status['headline'] = 'Senate Status';
        $status['display_video'] = FALSE;
      }
      // If even that doesn't exist, use the value of $status['text'] directly
      else if ($status['text']) {
        $status['message'] = $status['text'];
        $status['headline'] = 'Senate Status';
        $status['display_video'] = FALSE;
      }
      // As a final resort, admit that status is unknown.
      else {
        $status['message'] = 'We are currently experiencing technical difficulties. Please stand by. ';
        $status['headline'] = 'Senate Status';
        $status['display_video'] = FALSE;
      }
      break;
  }
  $last_char = substr(trim($status['message']), -1, 1);
  // add a period in case the journal clerk's office appends a message and forgets to punctuate.
  if (!in_array($last_char, array('.', '?', '!'))) {
    $status['message'] = trim($status['message']) . '. ';
  }
  $status['internal'] = nyss_internalusers_is_internal();
  $status['ip']=ip_address();
  return $status;
}

/**
 * Retrieves some XML-formatted data.
 *
 * @param $url
 *   The URL for the data source.
 * @return
 *   A SimpleXML object based on the XML that was retrieved.
 */
function _nyss_session_get_xml($url) {
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, $url);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 5);
  curl_setopt($ch, CURLOPT_TIMEOUT, 5);
  $data = curl_exec($ch);
  curl_close($ch);
  return simplexml_load_string($data);
}

/**
 * Helper function to return a text string with links to video archives and the
 * Legislative Cable Channel Calendar.
 *
 * @return
 *   HTML
 */
function _nyss_session_archives_text() {
  return 'Please visit our <a href="http://www.nysenate.gov/video_archives">video archives</a> ' .
    'or check your local listings on the <a href="http://www.nysenate.gov/calendar/legislative-cable-channel">Legislative Cable Channel Calendar</a>. ';
}

/**
 * Test whether the current user is internal or not, based on their IP number
 * Return value is Boolean
 */
function nyss_internalusers_is_internal() {
  $ip=ip_address();
  if (substr($ip, 0, 9) == '63.118.56' || substr($ip, 0, 9) == '63.118.57') {
    return true;
  }
  return false;
}

function ip_address() {
  if (array_key_exists('HTTP_X_FORWARDED_FOR', $_SERVER)) {
    $ip_address_parts = explode(',', $_SERVER['HTTP_X_FORWARDED_FOR']);
    return array_pop($ip_address_parts);
  }
  return $_SERVER['REMOTE_ADDR'];
}