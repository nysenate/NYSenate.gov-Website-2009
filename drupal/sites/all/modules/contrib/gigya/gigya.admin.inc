<?php
// $Id: gigya.admin.inc,v 1.1.2.5 2009/08/17 21:02:55 brauerranch Exp $

/**
 * @file
 * This module provides a link to Gigya profiles from a users' drupal account.
 *
 * Development of this module is sponsered by gigya, Inc and implimented by Acquia.
 *
 * @version 1.0
 * @package gigya
 */

/**
 * Constants defined for gigya system settings
 */
define('GIGYA_DEFAULT_ICONSIZE', 30);
define('GIGYA_DEFAULT_LOGINUI_WIDTH', '120');
define('GIGYA_DEFAULT_LOGINUI_HEIGHT', '110');
define('GIGYA_DEFAULT_LOGINUI_COLOR_BACKGROUND', 'Transparent');
define('GIGYA_DEFAULT_LOGINUI_COLOR_FRAME', '#DFDFDF');
define('GIGYA_DEFAULT_LOGINUI_COLOR_TEXT', '#3A3A3A');
define('GIGYA_DEFAULT_LOGINUI_COLOR_LINK', '#0066CC');
define('GIGYA_DEFAULT_LOGINUI_COLOR_NAVIGATION_ARROW', '#79BCFD');
define('GIGYA_DEFAULT_LOGINUI_COLOR_CAPTION_BACKGROUND', '#4692DE');
define('GIGYA_DEFAULT_LOGINUI_COLOR_CAPTION_TEXT', '#FFFFFF');
define('GIGYA_DEFAULT_LOGINUI_COLOR_BUTTON_TEXT', '#3A3A3A');
define('GIGYA_DEFAULT_LOGINUI_COLOR_BACKGROUND_TRANSPARENT', TRUE);
define('GIGYA_DEFAULT_LOGINUI_CONTAINERID', 'divConnect');
define('GIGYA_DEFAULT_FRIENDSUI_WIDTH', '360');
define('GIGYA_DEFAULT_FRIENDSUI_HEIGHT', '400');
define('GIGYA_DEFAULT_FRIENDSUI_COLOR_BACKGROUND', 'Transparent');
define('GIGYA_DEFAULT_FRIENDSUI_COLOR_FRAME', '#DFDFDF');
define('GIGYA_DEFAULT_FRIENDSUI_COLOR_TEXT', '#3A3A3A');
define('GIGYA_DEFAULT_FRIENDSUI_COLOR_LINK', '#0066CC');
define('GIGYA_DEFAULT_FRIENDSUI_COLOR_NAVIGATION_ARROW', '#79BCFD');
define('GIGYA_DEFAULT_FRIENDSUI_COLOR_CAPTION_BACKGROUND', '#4692DE');
define('GIGYA_DEFAULT_FRIENDSUI_COLOR_CAPTION_TEXT', '#FFFFFF');
define('GIGYA_DEFAULT_FRIENDSUI_COLOR_BUTTON_TEXT', '#3A3A3A');
define('GIGYA_DEFAULT_FRIENDSUI_COLOR_BACKGROUND_TRANSPARENT', TRUE);
define('GIGYA_DEFAULT_FRIENDSUI_CONTAINERID', 'friends');
define('GIGYA_DEFAULT_FRIENDSUI_SHOWCAPTION', FALSE);
define('GIGYA_DEFAULT_FRIENDSUI_CAPTIONTEXT', 'Select Friends');
define('GIGYA_DEFAULT_CONNECTUI_WIDTH', '360');
define('GIGYA_DEFAULT_CONNECTUI_HEIGHT', '400');
define('GIGYA_DEFAULT_CONNECTUI_COLOR_BACKGROUND', 'Transparent');
define('GIGYA_DEFAULT_CONNECTUI_COLOR_FRAME', '#DFDFDF');
define('GIGYA_DEFAULT_CONNECTUI_COLOR_TEXT', '#3A3A3A');
define('GIGYA_DEFAULT_CONNECTUI_COLOR_LINK', '#0066CC');
define('GIGYA_DEFAULT_CONNECTUI_COLOR_NAVIGATION_ARROW', '#79BCFD');
define('GIGYA_DEFAULT_CONNECTUI_COLOR_CAPTION_BACKGROUND', '#4692DE');
define('GIGYA_DEFAULT_CONNECTUI_COLOR_CAPTION_TEXT', '#FFFFFF');
define('GIGYA_DEFAULT_CONNECTUI_COLOR_BUTTON_TEXT', '#3A3A3A');
define('GIGYA_DEFAULT_CONNECTUI_COLOR_BACKGROUND_TRANSPARENT', TRUE);
define('GIGYA_DEFAULT_CONNECTUI_CONTAINERID', 'divConnect');
define('GIGYA_DEFAULT_CONNECTUI_SHOWCAPTION', FALSE);
define('GIGYA_DEFAULT_CONNECTUI_CAPTIONTEXT', 'Select social networks');
define('GIGYA_DEFAULT_SHARE_SUBJECT', 'A site recommendation for you');
define('GIGYA_DEFAULT_SHARE_MESSAGE', 'I wanted to recommend this site to you. I enjoy it and think you will like it.');
define('GIGYA_DEFAULT_SHARE_LINK_TITLE', 'Share with friends');
define('GIGYA_DEFAULT_LOGINUI_FBCONNECT', FALSE);
/**
 *
 */
function gigya_admin_form() {
  global $user;
  include_once($base_path .'modules/user/user.pages.inc');
  module_load_include('inc', 'gigya');
  $capabilities = gigya_get_capabilities();
  $form = array();
  $form['keys'] = array(
    '#type' => 'fieldset',
    '#title' => t('Gigya Socialize keys'),
    '#description' => t('Keys needed for connecting to the Gigya Socialize service.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => -4,
  );
  $form['keys']['gigya_APIKey'] = array(
    '#type' => 'textfield',
    '#title' => t('Gigya API Key'),
    '#description' => t('Specify the gigya API key for this domain'),
    '#default_value' => variable_get('gigya_APIKey', ''),
    '#required' => TRUE,
    '#weight' => -10,
  );
  $form['keys']['gigya_SecretKey'] = array(
    '#type' => 'textfield',
    '#title' => t('Gigya Secret Key'),
    '#description' => t('Specify the gigya Secret (Base64 encoded) key for this domain'),
    '#default_value' => variable_get('gigya_SecretKey', ''),
    '#required' => TRUE,
    '#weight' => -9,
  );
  
  $form['gigya_selected_networks'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Networks available to socialize'),
    '#default_value' => variable_get('gigya_selected_networks', array()),
    '#options' => gigya_get_networks(),
    '#required' => TRUE,
    '#description' => t('Select the networks this site should be allowed to connect to via socialize'),
    '#weight' => -3,
  );

  $form['posting'] = array(
    '#type' => 'fieldset',
    '#title' => t('Socialize status update options'),
    '#description' => t('Users with social networks that allow status updates will
                        be able to send updates when they create new content. Status updates
                        in this case will be sent from the Node Add or Node Edit form itself.
                        For Popup notifications you must configure an Action and Trigger.
                        Newsfeeds can only be configured through Actions and Triggers.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => -2,
  );
  $form['posting']['gigya_status_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Node types for Status updates'),
    '#options' => node_get_types('names'),
    '#default_value' => variable_get('gigya_status_types', array('story' => 'story', 'blog' => 'blog')),
  );
  $form['posting']['gigya_default_format'] = array(
    '#type' => 'textfield',
    '#title' => t('Default format string'),
    '#maxlength' => 140,
    '#description' => t('The given text will be posted to your social networks. You can use !url, !url-alias, !tinyurl, !title, and !user as replacement text.'),
    '#default_value' => variable_get('gigya_default_format', 'New post: !title !tinyurl'),
  );
  $form['sharing'] = array(
    '#type' => 'fieldset',
    '#title' => t('Share with a friend settings'),
    '#description' => t('Set which node types will have the Share with Friends functionality enabled.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => -2,
  );
  $form['sharing']['gigya_share_link_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Link text for "share with friends"'),
    '#default_value' => variable_get('gigya_share_link_title', GIGYA_DEFAULT_SHARE_LINK_TITLE),
  );
  $form['sharing']['gigya_share_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Node types for "Share with a friend"'),
    '#options' => node_get_types('names'),
    '#default_value' => variable_get('gigya_share_types', array('story' => 'story', 'blog' => 'blog')),
  );
  $form['sharing']['gigya_share_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Suggested message for "Share with a friend"'),
    '#default_value' => variable_get('gigya_share_message', GIGYA_DEFAULT_SHARE_MESSAGE),
  );
  $form['login_uiconfig'] = array(
    '#type' => 'fieldset',
    '#title' => t('Parameters for Login UIConfig'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['login_uiconfig']['gigya_login_requiredCapabilities'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Required capabilities for login providers'),
    '#default_value' => variable_get('gigya_login_requiredCapabilities', array('login' => 'login')),
    '#options' => $capabilities,
    '#description' => t('Unless you wish to restrict to only social networks, check only "login" here'),
  );
  $form['login_uiconfig']['gigya_login_surpress_login'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display only Socialize component in the login block (suppress Drupal login)'),
    '#default_value' => variable_get('gigya_login_surpress_login', FALSE),
    '#description' => t('Checking this option will disable normal drupal login. Admins can login via /user'),
  );
  //display 'user register' options here to make it easier for site admins
  $form['login_uiconfig']['user_register'] = array(
    '#type' => 'radios', '#title' => t('Public Registration Settings:'),
    '#default_value' => variable_get('user_register', 1),
    '#options' => array(
      t('Only socialize or administrators can create new accounts.'),
      t('Visitors can create accounts outside of socialize and no administrator approval is required.'),
      t('Visitors can create accounts outside of socialize but administrator approval is required.')
    ),
    '#description' => t('Used in conjunction with the surpress login option above,
                        you can effectively disable users from creating accounts
                        unless they use socialize. Note, all socialize users will
                        get automatically approved to use the site. Do not use
                        socialize if the site is not for public registrants!'),
  );
  $form['login_uiconfig']['gigya_login_uiconfig_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Login UI Title'),
    '#default_value' => variable_get('gigya_login_uiconfig_title', ''),
    '#description' => t('Leave blank for no title. Note: An override for this is
                        also available in the block configuration screen.'),
  );
  $form['login_uiconfig']['gigya_login_uiconfig_width'] = array(
    '#type' => 'textfield',
    '#title' => t('UI Box Width'),
    '#default_value' => variable_get('gigya_login_uiconfig_width', GIGYA_DEFAULT_LOGINUI_WIDTH),
    '#description' => t('Select width for Login Box'),
  );
  $form['login_uiconfig']['gigya_login_uiconfig_height'] = array(
    '#type' => 'textfield',
    '#title' => t('UI Box Height'),
    '#default_value' => variable_get('gigya_login_uiconfig_height', GIGYA_DEFAULT_LOGINUI_HEIGHT),
    '#description' => t('Select height for Login Box'),
  );
  $form['login_uiconfig']['gigya_login_uiconfig_iconsize'] = array(
    '#type' => 'textfield',
    '#title' => t('Icon Size'),
    '#default_value' => variable_get('gigya_login_uiconfig_iconsize', GIGYA_DEFAULT_ICONSIZE),
    '#description' => t('How big should the social network icons be'),
  );
  /**
   * Colors for the loginUI. If colorpicker module is enabled, we'll use that instead.
   */
  $color_field_type = (function_exists('colorpicker_2_or_later') ? 'colorpicker_' : '') .'textfield';
  $form['login_uiconfig']['gigya_login_uiconfig_color_background'] = array(
    '#type' => $color_field_type,
    '#title' => t('Background'),
    '#default_value' => variable_get('gigya_login_uiconfig_color_background', GIGYA_DEFAULT_LOGINUI_COLOR_BACKGROUND),
  );
  $form['login_uiconfig']['gigya_login_uiconfig_color_background_transparent'] = array(
    '#type' => 'checkbox',
    '#title' => t('Transparent Background'),
    '#default_value' => variable_get('gigya_login_uiconfig_color_background_transparent', GIGYA_DEFAULT_LOGINUI_COLOR_BACKGROUND_TRANSPARENT),
    '#attributes' => array(
      'onClick' => 'getElementById("edit-gigya-login-uiconfig-color-background").value="";',
    ),
  );
  if (variable_get('gigya_login_uiconfig_color_background_transparent', GIGYA_DEFAULT_LOGINUI_COLOR_BACKGROUND_TRANSPARENT)) {
    variable_set('gigya_login_uiconfig_color_background', '');
  }
  $form['login_uiconfig']['gigya_login_uiconfig_color_frame'] = array(
    '#type' => $color_field_type,
    '#title' => t('Frame'),
    '#default_value' => variable_get('gigya_login_uiconfig_color_frame', GIGYA_DEFAULT_LOGINUI_COLOR_FRAME),
  );
  $form['login_uiconfig']['gigya_login_uiconfig_color_text'] = array(
    '#type' => $color_field_type,
    '#title' => t('Text'),
    '#default_value' => variable_get('gigya_login_uiconfig_color_text', GIGYA_DEFAULT_LOGINUI_COLOR_TEXT),
  );
  $form['login_uiconfig']['gigya_login_uiconfig_color_link'] = array(
    '#type' => $color_field_type,
    '#title' => t('Link'),
    '#default_value' => variable_get('gigya_login_uiconfig_color_link', GIGYA_DEFAULT_LOGINUI_COLOR_LINK),
  );
  $form['login_uiconfig']['gigya_login_uiconfig_color_navigation_arrow'] = array(
    '#type' => $color_field_type,
    '#title' => t('Navigation Arrow'),
    '#default_value' => variable_get('gigya_login_uiconfig_color_navigation_arrow', GIGYA_DEFAULT_LOGINUI_COLOR_NAVIGATION_ARROW),
  );
  $form['login_uiconfig']['gigya_login_uiconfig_color_caption_background'] = array(
    '#type' => $color_field_type,
    '#title' => t('Caption Background'),
    '#default_value' => variable_get('gigya_login_uiconfig_color_caption_background', GIGYA_DEFAULT_LOGINUI_COLOR_CAPTION_BACKGROUND),
  );
  $form['login_uiconfig']['gigya_login_uiconfig_color_caption_text'] = array(
    '#type' => $color_field_type,
    '#title' => t('Caption Text'),
    '#default_value' => variable_get('gigya_login_uiconfig_color_caption_text', GIGYA_DEFAULT_LOGINUI_COLOR_CAPTION_TEXT),
  );
  $form['login_uiconfig']['gigya_login_uiconfig_color_button_text'] = array(
    '#type' => $color_field_type,
    '#title' => t('Button Text'),
    '#default_value' => variable_get('gigya_login_uiconfig_color_button_text', GIGYA_DEFAULT_LOGINUI_COLOR_BUTTON_TEXT),
  );
  $form['login_uiconfig']['login_advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced LoginUI Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => 2,
  );
  $form['login_uiconfig']['login_advanced']['gigya_login_uiconfig_urlredirect'] = array(
    '#type' => 'textfield',
    '#title' => t('URL redirect after login'),
    '#default_value' => variable_get('gigya_login_uiconfig_urlredirect', 'user'),
    '#description' => t('Choose an alternate URL to direct users to after login. Defaults to user. Do not use a beginning or ending slash!'),
  );
  $form['login_uiconfig']['login_advanced']['gigya_login_advanced_custombuttons'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom Login Icons URL'),
    '#default_value' => variable_get('gigya_login_advanced_custombuttons', 'user'),
    '#description' => t('Choose an alternate URL to pull in flash button data'),
  );  
  $form['login_uiconfig']['login_advanced']['gigya_login_uiconfig_containerID'] = array(
    '#type' => 'textfield',
    '#title' => t('LoginUI container ID:'),
    '#default_value' => variable_get('gigya_login_uiconfig_containerID', GIGYA_DEFAULT_LOGINUI_CONTAINERID),
    '#description' => t('div ID for loginUI'),
    '#required' => TRUE,    
  );
  $form['login_uiconfig']['login_advanced']['gigya_login_advanced_facebookconnect'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use facebook connect for facebook users?'),
    '#default_value' => variable_get('gigya_login_advanced_facebookconnect', GIGYA_DEFAULT_LOGINUI_FBCONNECT),
    '#description' => t('It is recommended to use facebook connect, !connect',
                        array('!connect' => l('but you must follow these steps first to configure it', 'http://wiki.gigya.com/030_Gigya_Socialize_API_2.0/020_Socialize_Setup/10_Opening_a_Facebook_External_Application'))),
  );
  $form['login_uiconfig']['login_advanced']['gigya_login_advanced_raw'] = array(
    '#type' => 'textarea',
    '#title' => t('Login UIConfig Advanced coding (Overwrites above settings)'),
    '#default_value' => variable_get('gigya_login_advanced_raw', ''),
    '#description' => t('Use this textbox to put in your own settings. If you are
                        not using this box, make sure it is empty!'),
  );
//friends UI
  $form['friends_uiconfig'] = array(
    '#type' => 'fieldset',
    '#title' => t('Parameters for friends UIConfig'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['friends_uiconfig']['gigya_friends_uiconfig_showCaption'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show caption?'),
    '#default_value' => variable_get('gigya_friends_uiconfig_showCaption', GIGYA_DEFAULT_FRIENDSUI_SHOWCAPTION),
    '#description' => t('Uncheck to disable caption.'),
  );
  $form['friends_uiconfig']['gigya_friends_uiconfig_captionText'] = array(
    '#type' => 'textfield',
    '#title' => t('Friends UI Caption'),
    '#default_value' => variable_get('gigya_friends_uiconfig_captionText', GIGYA_DEFAULT_FRIENDSUI_CAPTIONTEXT),
    '#description' => t('Leave blank for no title.'),
  );
  $form['friends_uiconfig']['gigya_friends_uiconfig_width'] = array(
    '#type' => 'textfield',
    '#title' => t('UI Box Width'),
    '#default_value' => variable_get('gigya_friends_uiconfig_width', GIGYA_DEFAULT_FRIENDSUI_WIDTH),
    '#description' => t('Select width for Login Box'),
  );
  $form['friends_uiconfig']['gigya_friends_uiconfig_height'] = array(
    '#type' => 'textfield',
    '#title' => t('UI Box Height'),
    '#default_value' => variable_get('gigya_friends_uiconfig_height', GIGYA_DEFAULT_FRIENDSUI_HEIGHT),
    '#description' => t('Select height for Login Box'),
  );
  /**
   * Colors for the loginUI. If colorpicker module is enabled, we'll use that instead.
   */
  $color_field_type = (function_exists('colorpicker_2_or_later') ? 'colorpicker_' : '') .'textfield';
  $form['friends_uiconfig']['gigya_friends_uiconfig_color_background'] = array(
    '#type' => $color_field_type,
    '#title' => t('Background'),
    '#default_value' => variable_get('gigya_friends_uiconfig_color_background', GIGYA_DEFAULT_FRIENDSUI_COLOR_BACKGROUND),
  );
  $form['friends_uiconfig']['gigya_friends_uiconfig_color_background_transparent'] = array(
    '#type' => 'checkbox',
    '#title' => t('Transparent Background'),
    '#default_value' => variable_get('gigya_friends_uiconfig_color_background_transparent', GIGYA_DEFAULT_FRIENDSUI_COLOR_BACKGROUND_TRANSPARENT),
    '#attributes' => array(
      'onClick' => 'getElementById("edit-gigya-friends-uiconfig-color-background").value="";',
    ),
  );
  if (variable_get('gigya_friends_uiconfig_color_background_transparent', GIGYA_DEFAULT_FRIENDSUI_COLOR_BACKGROUND_TRANSPARENT)) {
    variable_set('gigya_friends_uiconfig_color_background', '');
  }
  $form['friends_uiconfig']['gigya_friends_uiconfig_color_frame'] = array(
    '#type' => $color_field_type,
    '#title' => t('Frame'),
    '#default_value' => variable_get('gigya_friends_uiconfig_color_frame', GIGYA_DEFAULT_FRIENDSUI_COLOR_FRAME),
  );
  $form['friends_uiconfig']['gigya_friends_uiconfig_color_text'] = array(
    '#type' => $color_field_type,
    '#title' => t('Text'),
    '#default_value' => variable_get('gigya_friends_uiconfig_color_text', GIGYA_DEFAULT_FRIENDSUI_COLOR_TEXT),
  );
  $form['friends_uiconfig']['gigya_friends_uiconfig_color_link'] = array(
    '#type' => $color_field_type,
    '#title' => t('Link'),
    '#default_value' => variable_get('gigya_friends_uiconfig_color_link', GIGYA_DEFAULT_FRIENDSUI_COLOR_LINK),
  );
  $form['friends_uiconfig']['gigya_friends_uiconfig_color_navigation_arrow'] = array(
    '#type' => $color_field_type,
    '#title' => t('Navigation Arrow'),
    '#default_value' => variable_get('gigya_friends_uiconfig_color_navigation_arrow', GIGYA_DEFAULT_FRIENDSUI_COLOR_NAVIGATION_ARROW),
  );
  $form['friends_uiconfig']['gigya_friends_uiconfig_color_caption_background'] = array(
    '#type' => $color_field_type,
    '#title' => t('Caption Background'),
    '#default_value' => variable_get('gigya_friends_uiconfig_color_caption_background', GIGYA_DEFAULT_FRIENDSUI_COLOR_CAPTION_BACKGROUND),
  );
  $form['friends_uiconfig']['gigya_friends_uiconfig_color_caption_text'] = array(
    '#type' => $color_field_type,
    '#title' => t('Caption Text'),
    '#default_value' => variable_get('gigya_friends_uiconfig_color_caption_text', GIGYA_DEFAULT_FRIENDSUI_COLOR_CAPTION_TEXT),
  );
  $form['friends_uiconfig']['gigya_friends_uiconfig_color_button_text'] = array(
    '#type' => $color_field_type,
    '#title' => t('Button Text'),
    '#default_value' => variable_get('gigya_friends_uiconfig_color_button_text', GIGYA_DEFAULT_FRIENDSUI_COLOR_BUTTON_TEXT),
  );
  $form['friends_uiconfig']['friends_advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced friendsUI Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => 2,
  );
  $form['friends_uiconfig']['friends_advanced']['gigya_friends_uiconfig_containerID'] = array(
    '#type' => 'textfield',
    '#title' => t('FriendsUI container ID:'),
    '#default_value' => variable_get('gigya_friends_uiconfig_containerID', GIGYA_DEFAULT_FRIENDSUI_CONTAINERID),
    '#description' => t('div ID for loginUI'),
  );
  $form['friends_uiconfig']['friends_advanced']['gigya_friends_advanced_raw'] = array(
    '#type' => 'textarea',
    '#title' => t('Friends UIConfig Advanced coding (Overwrites above settings)'),
    '#default_value' => variable_get('gigya_friends_advanced_raw', ''),
    '#description' => t('Use this textbox to put in your own settings. If you are not using this box, make sure it is empty!'),
  );
  //connect UI
  $form['connect_uiconfig'] = array(
    '#type' => 'fieldset',
    '#title' => t('Parameters for editConnections UIConfig'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['connect_uiconfig']['gigya_connect_uiconfig_showCaption'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show caption?'),
    '#default_value' => variable_get('gigya_connect_uiconfig_showCaption', GIGYA_DEFAULT_CONNECTUI_SHOWCAPTION),
    '#description' => t('Uncheck to disable caption.'),
  );
  $form['connect_uiconfig']['gigya_connect_requiredCapabilities'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Required services for socialize connect'),
    '#default_value' => variable_get('gigya_connect_requiredCapabilities', array("login" => "login", "notifications" => "notifications", "friends" => "friends", "status" => "status")),
    '#options' => $capabilities,
    '#description' => t('Choose which capabilities you wish to enable users when connecting to social networks'),
    '#weight' => -8,
  );
  $form['connect_uiconfig']['gigya_connect_uiconfig_captionText'] = array(
    '#type' => 'textfield',
    '#title' => t('ConnectUI Caption'),
    '#default_value' => variable_get('gigya_connect_uiconfig_captionText', GIGYA_DEFAULT_CONNECTUI_CAPTIONTEXT),
    '#description' => t('Leave blank for no title.'),
  );
  $form['connect_uiconfig']['gigya_connect_uiconfig_width'] = array(
    '#type' => 'textfield',
    '#title' => t('UI Box Width'),
    '#default_value' => variable_get('gigya_connect_uiconfig_width', GIGYA_DEFAULT_CONNECTUI_WIDTH),
    '#description' => t('Select width for Login Box'),
  );
  $form['connect_uiconfig']['gigya_connect_uiconfig_height'] = array(
    '#type' => 'textfield',
    '#title' => t('UI Box Height'),
    '#default_value' => variable_get('gigya_connect_uiconfig_height', GIGYA_DEFAULT_CONNECTUI_HEIGHT),
    '#description' => t('Select height for Login Box'),
  );

  /**
   * Colors for the loginUI. If colorpicker module is enabled, we'll use that instead.
   */
  $color_field_type = (function_exists('colorpicker_2_or_later') ? 'colorpicker_' : '') .'textfield';
  $form['connect_uiconfig']['gigya_connect_uiconfig_color_background'] = array(
    '#type' => $color_field_type,
    '#title' => t('Background'),
    '#default_value' => variable_get('gigya_connect_uiconfig_color_background', GIGYA_DEFAULT_CONNECTUI_COLOR_BACKGROUND),
  );
  $form['connect_uiconfig']['gigya_connect_uiconfig_color_background_transparent'] = array(
    '#type' => 'checkbox',
    '#title' => t('Transparent Background'),
    '#default_value' => variable_get('gigya_connect_uiconfig_color_background_transparent', GIGYA_DEFAULT_CONNECTUI_COLOR_BACKGROUND_TRANSPARENT),
    '#attributes' => array(
      'onClick' => 'getElementById("edit-gigya-friends-uiconfig-color-background").value="";',
    ),
  );
  if (variable_get('gigya_connect_uiconfig_color_background_transparent', GIGYA_DEFAULT_CONNECTUI_COLOR_BACKGROUND_TRANSPARENT)) {
    variable_set('gigya_connect_uiconfig_color_background', '');
  }
  $form['connect_uiconfig']['gigya_connect_uiconfig_color_frame'] = array(
    '#type' => $color_field_type,
    '#title' => t('Frame'),
    '#default_value' => variable_get('gigya_connect_uiconfig_color_frame', GIGYA_DEFAULT_CONNECTUI_COLOR_FRAME),
  );
  $form['connect_uiconfig']['gigya_connect_uiconfig_color_text'] = array(
    '#type' => $color_field_type,
    '#title' => t('Text'),
    '#default_value' => variable_get('gigya_connect_uiconfig_color_text', GIGYA_DEFAULT_CONNECTUI_COLOR_TEXT),
  );
  $form['connect_uiconfig']['gigya_connect_uiconfig_color_link'] = array(
    '#type' => $color_field_type,
    '#title' => t('Link'),
    '#default_value' => variable_get('gigya_connect_uiconfig_color_link', GIGYA_DEFAULT_CONNECTUI_COLOR_LINK),
  );
  $form['connect_uiconfig']['gigya_connect_uiconfig_color_navigation_arrow'] = array(
    '#type' => $color_field_type,
    '#title' => t('Navigation Arrow'),
    '#default_value' => variable_get('gigya_connect_uiconfig_color_navigation_arrow', GIGYA_DEFAULT_CONNECTUI_COLOR_NAVIGATION_ARROW),
  );
  $form['connect_uiconfig']['gigya_connect_uiconfig_color_caption_background'] = array(
    '#type' => $color_field_type,
    '#title' => t('Caption Background'),
    '#default_value' => variable_get('gigya_connect_uiconfig_color_caption_background', GIGYA_DEFAULT_CONNECTUI_COLOR_CAPTION_BACKGROUND),
  );
  $form['connect_uiconfig']['gigya_connect_uiconfig_color_caption_text'] = array(
    '#type' => $color_field_type,
    '#title' => t('Caption Text'),
    '#default_value' => variable_get('gigya_connect_uiconfig_color_caption_text', GIGYA_DEFAULT_CONNECTUI_COLOR_CAPTION_TEXT),
  );
  $form['connect_uiconfig']['gigya_connect_uiconfig_color_button_text'] = array(
    '#type' => $color_field_type,
    '#title' => t('Button Text'),
    '#default_value' => variable_get('gigya_connect_uiconfig_color_button_text', GIGYA_DEFAULT_CONNECTUI_COLOR_BUTTON_TEXT),
  );
  $form['connect_uiconfig']['connect_advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced editConnectionsUI Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => 2,
  );
  $form['connect_uiconfig']['connect_advanced']['gigya_connect_uiconfig_containerID'] = array(
    '#type' => 'textfield',
    '#title' => t('editconnectionsUI container ID:'),
    '#default_value' => variable_get('gigya_connect_uiconfig_containerID', GIGYA_DEFAULT_CONNECTUI_CONTAINERID),
    '#description' => t('div ID for connectUI'),
  );
  $form['connect_uiconfig']['connect_advanced']['gigya_connect_advanced_raw'] = array(
    '#type' => 'textarea',
    '#title' => t('editconnections UIConfig Advanced coding (Overwrites above settings)'),
    '#default_value' => variable_get('gigya_connect_advanced_raw', ''),
    '#description' => t('Use this textbox to put in your own settings. If you are not using this box, make sure it is empty!'),
  );
  //we need to disable email verification, so the user just logs in.
  $form['user_email_verification'] = array('#type' => 'value', '#value' => FALSE);
  $form['user_mail_register_no_approval_required_notify'] = array('#type' => 'value', '#value' => TRUE);

  if (variable_get('user_pictures',0)) {
    $form['picture'] = array(
      '#type' => 'fieldset',
      '#title' => t('Gigya user profile picture'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );      
    
    $form['picture']['gigya_user_picture'] = array ( 
      '#type' => 'checkbox',
      '#title' => t('Allow users to associate loginProvider to user picture?'),
      '#default_value' => variable_get('gigya_user_picture', FALSE),
      '#description' => t('Checking this option allows users to connect their user picture to their drupal profile picture'),
    );
  }
  
  if (module_exists('profile')) {
    $form['profile'] = array(
      '#type' => 'fieldset',
      '#title' => t('Gigya <=> Drupal Profile Mappings'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    if ($profile_categories = profile_categories()) {
      $profile_fields = array();
      $category_names = array();
      foreach ($profile_categories as $category) {
        $category_names[$category['name']] = $category['name'];
        $profiles = profile_form_profile(NULL, NULL, $category['name'], TRUE);
        if ($profiles && $profiles[$category['name']]) {
          foreach ($profiles[$category['name']] as $field_name => $profile) {
            if (is_array($profile)) {
              $form['profile']['gigya_profile_'. $field_name] = array(
                '#type' => 'select',
                '#title' => $profile['#title'],
                '#options' => array_merge(array(0 => ''), _gigya_get_profile_fields()),
                '#default_value' => variable_get('gigya_profile_'. $field_name, ''),
              );
            }
          }
        }
      }
      $form['profile']['gigya_profile_categories'] = array(
        '#type' => 'select',
        '#title' => t('Select profile categories to display for user registration'),
        '#options' => $category_names,
        '#multiple' => TRUE,
        '#default_value' => variable_get('gigya_profile_categories', ''),
      );
    }
    else {
      drupal_set_message(t("Although the profile module is enabled, You currently have no profile categories created"));
    }
  }
  else {
    $form['from'] = array(
      '#type' => 'item',
      '#title' => t('Profile Module Disabled'),
      '#value' => t('If you wish to map profile settings to gigya settings, please enable the profile module'),
    );
  }

  return system_settings_form($form);
}