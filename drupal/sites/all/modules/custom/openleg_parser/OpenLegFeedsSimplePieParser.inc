<?php
/**
 * Parses Feed from OpenLeg RSS (1.6)
 * URL for most current meeting items:
 * http://open.nysenate.gov/legislation/search/?term=otype:meeting&format=rss&sort=when&sortOrder=true
 */
 
class OpenLegFeedsSimplePieParser extends FeedsSimplePieParser {

  /**
   * Implementation of FeedsParser::parse().
   */
  public function parse(FeedsImportBatch $batch, FeedsSource $source) {
    parent::parse($batch, $source);
  }

  /**
   * Parse the description field to get the unique items for this parser
   */
  protected function parseExtensions(&$item, $simplepie_item) {
    $item += $this->parse_meeting_info_from_description($item['description'], $item['url'], $item['title']);
  }

  /**
   * Helper function that parses the description field to extract the location, time, chair, and committee for the meeting
   * as well as uses the committee and url field to create a summary with quick link
   *
   * @param string $description, string $url
   *  The description field, which takes the form: room; summary; when; committee; location; chair;
   * The url field, which is a string containing the unique url
   * @return an array
   */
  function parse_meeting_info_from_description($description, $url, $title) {
//    dsm($description);
    $description = str_replace(';n', '<br />', $description);
    list($committee, $location, $chair, $summary) = explode('; ', $description);
    $dateStr = substr($title, strpos($title, '(')+1, strpos($title, ')')-1);
    $dateStr = str_replace(')', '', $dateStr);
    
    // Removes the attribute nonesense
    $summary = str_replace('Summary:', '', $summary);
    $summary = str_replace(';', '', $summary);
    
    // Get Room Number
    $summaryRoom = str_replace('location:', '', $location);
    
    // Removes the attribute nonsense
    $committee = str_replace('committee:', '', $committee);
    
    // Removes the attribute nonsense
    $location = str_replace('location:', '', $location);
    
    // Create Date from Title String
    $dateUnix = strtotime($dateStr);
    if ($location != 'Off the Floor' && $location != 'off the floor') {
      $dateRead = date("l, F jS, Y g:ia", $dateUnix); // For use later in reading
    } else {
      $dateRead = date("l, F jS, Y", $dateUnix); // For use later in reading
    }
    
    // Begin GMT to EST/EDT Adjustments
    
    $in_dst="false";

    if( (date(m)>=4) && (date(m)<=10) ) { // IS CURRENT DATE INSIDE OF APRIL->OCT WINDOW?
      if( (date(m)>4) && (date(m)<10) ) { //IS CURRENT DATE INSIDE MAY->SEPT WINDOW?
        $in_dst="true";
      } else if($date(m)=="4") { //IS IT APRIL?
        if( (date(j)<=7) && (date(D)=="Sun") ) { //IS IT THE FIRST SUN OF THE MONTH?
          if(date(H)>"1") {//IS IT PAST 2:00AM?
            $in_dst="true";
          }
        }
      } else if($date(m)=="10") {//IS IT OCT?
        if( (date(j)<=25) && (date(D)=="Sun") ) { //IS IT THE LAST SUN OF THE MONTH?
          if(date(H)>"1") {//IS IT PAST 2:00AM?
            $in_dst="false";
          }
        }
      }
    }

    if($in_dst=="true") {//INSIDE OF DST
      $dateUnix += 14400; //CHANGE NUMBER OF SECONDS HERE TO MODIFY
    } else {//OUT OF DST
      $dateUnix += 18000; //CHANGE NUMBER OF SECONDS HERE TO MODIFY
    }

    // Modified from: http://php.bigresource.com/PHP-Daylight-Savings-Time-GMT-Alogorithm-H87oEoQs.html
    
    // End GMT to EST/EDT Adjustments
    
    $dateStart = date ("Y-m-d\TH:i:s", $dateUnix);
    if ($location != 'Off the Floor') {
     $dateUnix += 3600; // Add one hour for meeting end
     $dateEnd = date ("Y-m-d\TH:i:s", $dateUnix);
   } else {
      $dateEnd = $dateStart;
    }
    
    // Scrubbing to get the Building by Building Code (CAP, LOB, or Other)    
    $length = strlen($location);
    $chars = 3;
    $start = $length - $chars;
    $buildCode = substr ($location, $start, $chars);
        
    // Switch on LOB; all others in Capitol Building
    if ($buildCode == "LOB") {
      $building = "Legislative Office Building";
    } else {
      $building = "Capitol Building";
    }
  
    // Scrubbing to remove the Building Code from the Room to make it useful
    if ($buildCode == 'LOB' || $buildCode == 'CAP') {
      $room = substr ($location, 0, strlen($room) - 4);
    } else if ($buildCode == 'tol') {
      $room = substr ($location, 0, strlen($room) - 8);
    } else {
      $room = $summaryRoom;
    }
       
    // Removes the attribute nonsense 
    $chair = str_replace('chair:', '', $chair);
    $chair = str_replace(';', '', $chair);
    
    $eventType = 3;
    $meetingTitle = $committee.' Meeting';
    
    // Adds the Event "Header"
    $body = '<p align="center"><strong>Senate Committee on '.$committee.'<br />'.$chair.'<br />'.$dateRead.'<br />'.$summaryRoom.'</strong></p><!--break-->';
    
    // OpenLeg Parsing and Scrubbing and Munging to get Body Info
    $doc = new DOMDocument('1.0');
    @$doc->loadHTMLFile($url);
    $qp = qp($doc, NULL, array('ignore_parser_warnings' => TRUE));

//    $noteSummary = $qp->find('#header ');
//    $noteSummary = $noteSummary->find('div:even');
//    $noteSummary = $noteSummary->find('div:first');
    $billSummary = $qp->find('.billSummary');
//    $noteSummary = $qp->find('#committeeNotes');
    
    $tableTest = $billSummary->text();
//    $noteText = $noteSummary->text();
//    $noteText .= ' Hello World ';
    
    $body .= $summary;
    
//    if (strlen($noteText) > 5) {
//      $body .= '<br />'.$noteText;
//    }
    
    $body .= '<br/><br/><a href="'.$url.'" target="_blank">Click Here</a> for full details on this '.$committee.' Committee meeting.';
    
    if (strlen($tableTest) > 5) {
      $body.= '<table border="0" cellspacing="0" cellpadding="0"><tbody><tr><td width="20%"><p align="center"><strong>Printed No.</strong></p></td><td width="15%"><p align="center"><strong>Sponsor</strong></p></td><td width="65%"><p align="center"><strong>Description</strong></p></td></tr>';
    }

    $baseURL = 'http://open.nysenate.gov';
    $i = 0;
    foreach ($billSummary as $item) {
      // Get text for each item
      $legDesc = $item->text();

      // Get item name
      $legHolder = $item->text();
      $legTitle = substr($legHolder, 0, strpos($legHolder, ': '));
      
      // Nomming to keep up apperaenes for messed up OpenLeg entries
      if (strpos($legTitle, 'MEETING')) {
        $body = str_replace('Printed No.', '', $body);
        $body = str_replace('Sponsor', '', $body);
        $body = str_replace('Description', '', $body);
        break;
      } 
      
      $legTitle = str_replace('<br />', '', $legTitle);
//      $legTitle = substr($legTitle, 4, strlen($legTitle));

      // Find URLs
      $urls = '';
      $billInfo = $item->find('a');
      foreach ($billInfo as $value) {
        $urls .= $value->attr('href');
        $urls .= ' : ';
      }

      // Explode to get URLs
      list($legURL, $sponsorURL, $billCommitteeURL) = explode(' : ', $urls);

      // Munge around in the Description
      $legDesc = str_replace($legTitle, '', $legHolder);
      $legDesc = str_replace(': ', '', $legDesc);

      // Munge around in the Sponsor
      $sponsor = str_replace ('/legislation/search/?term=sponsor:%22', '', $sponsorURL);
      $sponsor = str_replace('%22', '', $sponsor);
      $sponsor = strtolower($sponsor);
      $sponsor = ucfirst($sponsor);
      

       $billCommittee = str_replace ('/legislation/search/?term=committee:%22', '', $billCommitteeURL);
       $billCommittee = str_replace('%22', '', $billCommittee);

      $sponsorGone = 'Sponsor'.strtoupper($sponsor);
      $committeeGone = 'Committee'.strtoupper($billCommittee);

      $legDesc = str_replace($sponsorGone, '', $legDesc);
      $legDesc = str_replace($committeeGone, '', $legDesc);
      $legDesc = str_replace('/', '', $legDesc);

      // Create full URL
      $legURL = $baseURL.$legURL;
      $sponsorURL = $baseURL.$sponsorURL;
      
      // Add a carriage return
      $sponsor = '<br>'.$sponsor;
      $legDesc = '<br>'.$legDesc;

      // Add to Body & Increment Counter
      $body .= '<tr><td valign="top"><a href="'.$legURL.'">'.$legTitle.'</a></td><td valign="top"><a href="'.$sponsorURL.'">'.$sponsor.'</a></td><td valign="top"><p>'.$legDesc.'</p></td></tr>';
      
      $i = $i+1;
    }
    if (strlen($tableTest) > 5) {
      $body .= '</tbody></table>';
    }
    
    $livestreamURL = $this->getLiveStream($committee);
    
    return array(
      'meeting_title' => $meetingTitle,
      'author_by' => TRUE,
      'summary' => $body,
      'committee' => $committee,
      'chair' => $chair,
      'date_start' => $dateStart,
      'date_end' => $dateEnd,
      'event_type' => $eventType,
      'local_name' => $location,
      'street' => $room.', '.$building,
      'city' => 'Albany',
      'state' => 'NY',
      'zip' => '12247',
      'country' => 'us',
      'livestream' => $livestreamURL,
    );
  }
  
  function getLiveStream ($committee) {
    $baseURL = 'http://www.livestream.com/nysenate_';

    switch ($committee) {
      case "Aging" : $channel = 'aging';
          break;
      case "Agriculture" : $channel = 'agriculture';
          break;
      case "Banks" : $channel = 'banks';
            break;
      case "Children and Families" : $channel = 'children_families';
          break;
      case "Cities" : $channel = 'cities';
          break;
      case "Civil Service and Pensions" : $channel = 'civil_service_pensions';
          break;
      case "Codes" : $channel = 'codes';
          break;
      case "Commerce, Economic Development and Small Business" : $channel = 'commerce';
          break;
      case "Consumer Protection" : $channel = 'consumerprotection';
          break;
      case "Corporations, Authorities and Commissions" : $channel = 'corpauthcomm';
          break;
      case "Crime Victims, Crime and Correction" : $channel = 'victimscrimecorrection';
          break;
      case "Cultural Affairs, Tourism, Parks and Recreation" : $channel = 'culturalaffairs';
          break;
      case "Education" : $channel = 'education';
          break;
      case "Elections" : $channel = 'elections';
          break;
      case "Energy and Telecommunications" : $channel = 'energytelcom';
          break;
      case "Environmental Conservation" : $channel = 'enviroment';
          break;
      case "Ethics" : $channel = 'ethics';
          break;
      case "Finance" : $channel = 'finance';
          break;
      case "Health" : $channel = 'health';
          break;
      case "Higher Education" : $channel = 'highereducation';
          break;
      case "Housing, Construction, and Community Development" : $channel = 'housing';
          break;
      case "Insurance" : $channel = 'insurance';
          break;
      case "Investigations and Government Operations" : $channel = 'investigations_governmentops';
          break;
      case "Judiciary" : $channel = 'judiciary';
          break;
      case "Labor" : $channel = 'labor';
          break;
      case "Local Government" : $channel = 'localgov';
          break;
      case "Mental Health and Developmental Disabilities" : $channel = 'mentalhealth';
          break;
      case "Racing, Gaming and Wagering" : $channel = 'gaming';
          break;
      case "Rules" : $channel = 'rules';
          break;
      case "Social Services" : $channel = 'socialservices';
          break;
      case "Transportation" : $channel = 'transportation';
          break;
      case "Veterans, Homeland Security and Military Affairs" : $channel = 'vetshomesecuritymil';
          break;
      case "MTA Capital Program Review Board (CPRB)" : $channel = 'mtacrpb';
          break;
      case "New York State Conference of Black Senators" : return 0;
      case "Puerto Rican/Latino Caucus" : $channel = 'puertorican_latinocaucus';
          break;
      case "Upstate Caucus" : $channel = 'upstatecaucus';
          break;
      case "Budget and Tax Reform" :     $channel = 'budget_taxreform';
          break;
      case "Temporary Committee on Rules and Administration Reform" : return 'http://http://www.livestream.com/rulesreformandadministration';
      case "Minority News Conferences" : $channel = 'minority_newsconference';
          break;
      case "Joint Budget Hearings" : $channel = 'joint_budget';
          break;
    }
    return $baseURL.$channel;
  }  

  public function getMappingSources() {
    return parent::getMappingSources() + array(
      'author_by' => array (
        'name' => t('Authored By'),
        'description' => t('Authored By Check'),
      ),
      'meeting_title' => array(
        'name' => t('Meeting Title'),
        'description' => t('Meeting Title'),
      ),
      'event_type' => array(
        'name' => t('Event Type'),
        'description' => t('Sets Event Type to Committee Meeting'),
      ),
      'summary' => array(
        'name' => t('Body'),
        'description' => t('Body'),
      ),
      'committee' => array(
        'name' => t('Committee'),
        'description' => t('Name of Committee'),
      ),
      'chair' => array(
        'name' => t('Chair'),
        'description' => t('Name of Chair'),
      ),
      'date_start' => array(
        'name' => t('Date: Start'),
        'description' => t('Start Date of Meeting'),
      ),
      'date_end' => array(
        'name' => t('Date: End'),
        'description' => t('End Date of Meeting'),
      ),
      'livestream' => array(
        'name' => t('Livestream URL'),
        'description' => t('Livestream URL for each Committee'),
      ),
      'local_name' => array(
        'name' => t('Location Name'),
        'description' => t('Name of the Location'),
      ),
      'street' => array(
        'name' => t('Street'),
        'description' => t('Street address.'),
      ),
      'city' => array(
        'name' => t('City'),
        'description' => t('City.'),
      ),
      'state' => array(
        'name' => t('State'),
        'description' => t('State.'),
      ),
      'zip' => array(
        'name' => t('Zip'),
        'description' => t('Zip Code.'),
      ),
      'country' => array(
        'name' => t('Country'),
        'description' => t('Country.'),
      ),
    );
  }

}
