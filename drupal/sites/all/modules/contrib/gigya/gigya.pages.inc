<?php
// $Id: gigya.pages.inc,v 1.1.2.4 2009/08/07 06:38:56 japerry Exp $

/**
 * @file
 * Page display functions for for gigya module.
 */

/**
 * Wrapper for the gigya javascript NotifyLogin function.
 * Creates a button which should allow a user to syncronize their account with gigya at a click of the button,
 */
function gigya_connect($account, $name = NULL) {
  global $base_url;
  module_load_include('inc', 'gigya');
  $title = isset($account->title) ? $account->title : $account->name;
  drupal_set_title(check_plain($title));

  $form = array();
  gigya_login_block_js();
  $bio = gigya_getUserInfo($_SESSION['gigya_uid']);

  if ($bio['isLoggedIn'] == TRUE) {

    $form['gigya'] = array(
      '#type' => 'fieldset',
      '#theme' => 'gigya_connect_display',
      '#description' => t('You may connect your profile to additional social networks here.'),
    );

    $form['gigya']['connect'] = array(
      '#weight' => 10,
      '#value' => '&nbsp;',
      '#prefix' => '<div class="gigya editConnectionsUI"><strong>Social Network Connections</strong><div id="'. variable_get('gigya_connect_uiconfig_containerID', GIGYA_DEFAULT_CONNECTUI_CONTAINERID) .'">',
      '#suffix' => '</div><script type="text/javascript">gigya.services.socialize.showEditConnectionsUI(Drupal.settings.gigya.conf, {containerID:"'. variable_get('gigya_connect_uiconfig_containerID', GIGYA_DEFAULT_CONNECTUI_CONTAINERID) .'"});</script></div>',
    );

    $linked_networks = _gigya_get_linked_networks($account->uid);
    if (!$linked_networks)
      $linked_networks[variable_get('site_name', '')] = $account->uid;

    // Retrieve actions that are already assigned to this hook-op combination.
    if (count($linked_networks) > 1) {
      $form['gigya']['assigned']['#type'] = 'value';
      $form['gigya']['assigned']['#weight'] = -1;
      $form['gigya']['assigned']['#value'] = array();
      foreach ($linked_networks as $network => $gid) {
        $form['gigya']['assigned']['#value'][$network] = array(
          'description' => $network,
          'link' => l(t('unlink network'), "user/". $account->uid ."/edit/gigya/unlink/". base64_encode($gid)),
        );
      }
    }
    else if (count($linked_networks) == 1) {
      if ($bio['loginProvider'])
        $msg = $bio['loginProvider'];
      else

        $msg = t('this site');
      foreach ($linked_networks as $network => $gid) {
        $form['gigya']['assigned'] = array(
          '#title' => t("Connected Networks"),
          '#value' => t("You are currently using <strong>%network</strong> as your login provider", array('%network' => $msg)),
        );
      }
    }
  }
  return drupal_render($form);
}

/**
 * The overriden form submit form to get the gigya parameters stored in save_profile
 */
function gigya_user_register_form_submit($form, &$form_state) {
  global $user;
  if (!$user || $user->uid == 0) {
    user_external_login_register($form_state['values']['name'], 'gigya');
    $account = user_load(array('name' => $form_state['values']['name']));
    user_save($account, array('mail' => $form_state['values']['mail']));
    $_SESSION['gigya_uid'] = $form_state['values']['gigya_uid'];
    if (module_exists('profile')) {
      $categories = variable_get('gigya_profile_categories', '');
      foreach ($categories as $cat_name) {
        profile_save_profile($form_state['values'], $account, $cat_name, TRUE);
      }
    }
    $user = $account;
  }
  if ($user && $user->uid > 0) {
    $_SESSION['gigya_uid'] = $form_state['values']['gigya_uid'];
    $edit = array(
      'uid' => $user->uid,
      'gigya_uid' => $form_state['values']['gigya_uid'],
      'loginProvider' => $form_state['values']['loginProvider'],
    );
    gigya_save_profile($edit);
  }
}

/**
 * Confirm removal of an assigned action.
 *
 * @param $hook
 * @param $op
 * @param $aid
 *   The action ID.
 * @ingroup forms
 * @see trigger_unassign_submit()
 */
function gigya_unlink($form_state, $gidraw = NULL) {
  global $user;
  $gid = base64_decode($gidraw);
  if (!($gid)) {
    drupal_goto('user/'. $user->uid .'/edit');
  }
  $form['gid'] = array(
    '#type' => 'value',
    '#value' => $gid,
  );
  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $user->uid,
  );

  $network = _gigya_network_lookup($gid);

  $destination = 'user/'. $user->uid .'/edit/gigya';

  if ($gid == $_SESSION['gigya_uid']) {
    $confmsg = t('This is your current login provider, if you unlink %title you will be logged out.', array('%title' => $network));
  }
  else {
    $confmsg = t('You can assign it again later if you wish.');
  }
  return confirm_form($form,
    t('Are you sure you want to unlink %title?', array('%title' => $network)),
    $destination,
    $confmsg,
    t('Unlink'), t('Cancel')
  );
}

function gigya_unlink_submit($form, &$form_state) {
  $form_values = $form_state['values'];
  if ($form_values['confirm'] == 1) {
    db_query("DELETE FROM {gigya} WHERE gigya_uid = '%s'", $form_values['gid']);
    if ($form_values['gid'] == $_SESSION['gigya_uid']) {
      drupal_goto('socialize-logout');
    }
    $form_state['redirect'] = 'user/'. $form_values['uid'] .'/edit/gigya';
  }
  else {
    drupal_goto('user/'. $form_values['uid'] .'/edit/gigya');
  }
}

function gigya_logout_ajax() {
  global $user, $base_path;
  module_load_include('.inc', 'user', 'user.pages');
  module_load_include('inc', 'gigya');

  if (isset($user) && $user->uid != 0) {
    $logout_behavior = array("logout_location" => $base_path ."logout");
  }
  else {
    $logout_behavior = array("logout_location" => $base_path);
  }
  drupal_add_js(array('gigya' => $logout_behavior), 'setting');

  $behavior_js = 'Drupal.behaviors.gigya_logout = function(){ gigya.services.socialize.logout(Drupal.settings.gigya.conf, {callback:Drupal.gigya.logoutResponse});};';
  drupal_add_js($behavior_js, 'inline');

  return '<div id="logoutMessage">'. t("Please wait while you are logged out of socialize") .'</div>';
}
/**
 * This function gets called from the gigya socialize login_uiconfig form. It stores the URI parameters posted from gigya
 * @return authenticated drupal user (which redirects to the authenticated session)
 */
function gigya_login_ajax() {
  global $_gigya_uid, $user, $base_path;
  module_load_include('inc', 'gigya');

  if (isset($user) && $user->uid > 0) { //we already logged in, this means we're in the action.
    //Note, we check in the user function to see where the user is coming from. Only users who come from a login form should get here.
    //We need to call notifyLogin.
    $dest = gigya_notify_login(_gigya_get_gid_by_uid($user->uid) ? _gigya_get_gid_by_uid($user->uid) : $user->name); //to get the login redirect parameter
    if (!isset($_SESSION['gigya_uid'])) { //for drupal users
      $_SESSION['gigya_uid'] = $user->name;
      $behavior_js = 'Drupal.behaviors.gigya_notifyLogin = function(){ Drupal.settings.gigya.notify_login_params.callback = Drupal.gigya.notifyLogin_callback; gigya.services.socialize.notifyLogin(Drupal.settings.gigya.conf, Drupal.settings.gigya.notify_login_params);};';
      drupal_add_js($behavior_js, 'inline');
      return t('Please wait while we log you into socialize...');
    }
    drupal_goto();
  }

  $_gigya_uid = $_GET['UID'];
  if (!empty($_GET['signature']) && !empty($_GET['timestamp']) && !empty($_GET['UID'])) {
    $gigya_login = array(
      'signature' => $_GET['signature'],
      'timestamp' => $_GET['timestamp'],
      'gigya_uid' => $_GET['UID'],
    );
  }
  else {
    drupal_goto();
  }
  return gigya_authenticate($gigya_login, TRUE);
}

/**
 * Wrapper for the gigya javascript getFriends function.
 * injects the gigya getFriends javascript function.
 */
function gigya_get_friends($account, $name = NULL) {
  $title = isset($account->title) ? $account->title : $account->name;
  drupal_set_title(check_plain($title));

  //add the onload functions
    module_load_include('inc', 'gigya');
  $site_friends = array();
  if ($friends = gigya_getFriendsInfo(_gigya_get_gid_by_uid($account->uid) ? _gigya_get_gid_by_uid($account->uid) : $account->name)) {
    foreach ($friends['friends']->friend as $friend) {
      $friend_arr = get_object_vars($friend);
      if ($friend_arr['isSiteUser'] === 'true')
        $site_friends[] = $friend_arr;
    }
  }

  return theme('gigya_friends', $site_friends);
}

/**
 * Wrapper for the gigya javascript userInfo function.
 * injects the gigya getUserInfo javascript function.
 */
function gigya_get_user($object, $name = NULL) {
  $title = isset($object->title) ? $object->title : $object->name;
  drupal_set_title(check_plain($title));

  //add the onload functions

  $behavior_js = 'Drupal.behaviors.gigya_getUserInfo = function(context){ gigya.services.socialize.getUserInfo(Drupal.settings.gigya.conf, {callback:Drupal.gigya.getUserInfo_callback}); }';
  drupal_add_js($behavior_js, 'inline');

  $userinfo = '<div id="userinfo"></div>';
  return $userinfo;

}

function gigya_setStatus_form($form_state, $hook, $id) {
  global $user;

  $form = array();

  if ($hook == 'user') {
    $account = user_load($id);
    $form['uid'] = array('#type' => 'value', '#value' => $id);
    $msg = variable_get('gigya_status_user_description', 'The given text will be posted to your social networks. You can use !user, !profileurl, !sitename to represent the username, and link to user profile.');
    $default = variable_get('gigya_status_user_default_message', 'Looking at my friend !user on !sitename. !profileurl');
  }
  if ($hook == 'node') {
    $node = node_load($id);
    $form['nid'] = array('#type' => 'value', '#value' => $id);
    $msg = variable_get('gigya_status_node_description', 'The given text will be posted to your social networks. You can use !url, !url-alias, !tinyurl, !title and !user as replacement text.');
    $default = variable_get('gigya_status_node_default_message', '!title is awesome, come take a look !tinyurl');

  }

  $form['status'] = array(
    '#type' => 'textfield',
    '#title' => t('Update Status'),
    '#description' => $msg,
    '#default_value' => $default,
  );
  $form['hide'] = array(
    '#type' => 'checkbox',
    '#title' => t('Never Show this Again'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Send'),
  );
  $form['close'] = array(
    '#type' => 'submit',
    '#value' => t('Close'),
  );


  $form['gigya_uid'] = array('#type' => 'value', '#value' => _gigya_get_gid_by_uid($user->uid));
  return $form;
}

function gigya_setStatus_form_submit($form, &$form_state) {

  global $user;

  if (isset($form_state['values']['nid'])) {
    $node = node_load($form_state['values']['nid']);

    $replacements = array('!title' => $node->title,
                        '!url' => url('node/'. $node->nid, array('absolute' => TRUE, 'alias' => TRUE)),
                        '!url-alias' => url('node/'. $node->nid, array('absolute' => TRUE)),
                        '!user' => $node->name);
    // Only generate the shortened URL if it's going to be used. No sense
    // burning through TinyURLs without a good reason.
    if (strstr($form_state['values']['status'], '!tinyurl') !== FALSE) {
      $replacements['!tinyurl'] = gigya_shorten_url(url('node/'. $node->nid, array('absolute' => TRUE)));
    }
  }
  else if (isset($form_state['values']['uid'])) {
    $account = node_load($form_state['values']['uid']);
    $replacements = array('!profileurl' => url('user/'. $user->nid, array('absolute' => TRUE)),
                          '!user' => $user->name,
                          '!sitename' => variable_get('site_name', ''),
                          );

  }

  switch ($form_state['values']['op']) {
    case 'Send':
      $status = strtr($form_state['values']['status'], $replacements);
      gigya_setStatus($_SESSION['gigya_uid'], $status);
      user_save($user, array('setStatus_popup_hide' => $form_state['values']['hide'] ? TRUE : FALSE));
      drupal_set_message('Update sent to social networks successfully!');
      break;
    case 'Close':
      user_save($user, array('setStatus_popup_hide' => $form_state['values']['hide'] ? TRUE : FALSE));
      break;
    default:

      break;
  }
}

function gigya_notify_friends($node) {
  module_load_include('inc', 'gigya');
  global $user;
  $title = check_plain(variable_get('gigya_share_link_title', GIGYA_DEFAULT_SHARE_LINK_TITLE));

  drupal_set_title($title);
  $friends = gigya_getFriendsInfo(_gigya_get_gid_by_uid($user->uid) ? _gigya_get_gid_by_uid($user->uid) : $user->name);

  if (variable_get('gigya_friends_uiconfig_raw', '')) {
    $login_UIConfig = variable_get('gigya_friends_uiconfig_raw', '');
  }

  else {
    $friends_uiconfig = "<config><body><captions background-color=\"". variable_get('gigya_friends_uiconfig_color_caption_background', GIGYA_DEFAULT_FRIENDSUI_COLOR_CAPTION_BACKGROUND) ."\" color=\"". variable_get('gigya_friends_uiconfig_color_caption_text', GIGYA_DEFAULT_FRIENDSUI_COLOR_CAPTION_TEXT) ."\"></captions><texts color=\"". variable_get('gigya_friends_uiconfig_color_text', GIGYA_DEFAULT_FRIENDSUI_COLOR_TEXT) ."\"><links color=\"". variable_get('gigya_friends_uiconfig_color_link', GIGYA_DEFAULT_FRIENDSUI_COLOR_LINK) ."\"></links></texts><controls><snbuttons color=\"". variable_get('gigya_friends_uiconfig_color_button_text', GIGYA_DEFAULT_FRIENDSUI_COLOR_BUTTON_TEXT) ."\"></snbuttons><scrollingarrow color=\"". variable_get('gigya_friends_uiconfig_color_navigation_arrow', GIGYA_DEFAULT_FRIENDSUI_COLOR_NAVIGATION_ARROW) ."\"></scrollingarrow></controls><background background-color=\"". variable_get('gigya_friends_uiconfig_color_background', GIGYA_DEFAULT_FRIENDSUI_COLOR_BACKGROUND) ."\" frame-color=\"". variable_get('gigya_friends_uiconfig_color_frame', GIGYA_DEFAULT_FRIENDSUI_COLOR_FRAME) ."\"></background></body></config>";
  }

  $gigya_friends_params = array(
    'friendsUI_params' => array(
      "width" => variable_get('gigya_friends_uiconfig_width', GIGYA_DEFAULT_FRIENDSUI_WIDTH),
      "height" => variable_get('gigya_friends_uiconfig_height', GIGYA_DEFAULT_FRIENDSUI_HEIGHT),
      "containerID" => variable_get('gigya_friends_uiconfig_containerID', GIGYA_DEFAULT_FRIENDSUI_CONTAINERID),
      "showCaption" => variable_get('gigya_friends_uiconfig_showCaption', GIGYA_DEFAULT_FRIENDSUI_SHOWCAPTION),
      "captionText" => variable_get('gigya_friends_uiconfig_captionText', GIGYA_DEFAULT_FRIENDSUI_CAPTIONTEXT),
      "UIConfig" => $friends_UIConfig,

    ),
  );
  drupal_add_js(array('gigya' => $gigya_friends_params), 'setting');
  $attach_behaviors_js = 'Drupal.attachBehaviors()';
  drupal_add_js($attach_behaviors_js, 'inline');

  $notification_setting = array(
    'notifyMsg' => $context->title,
  );

  drupal_add_js(array('gigya' => $notification_setting), 'setting');
  $msg = variable_get('gigya_share_message', '');

  $output = '
   <form id="socialize_notification" name="notification">
   <div id="socialize_notification_msg">
      <label style="vertical-align: top;">Message</label>
      <textarea id="notify_message" style="width 40%; padding:2px;" name="body" cols="50" rows="5">'. $msg .'</textarea>
    </div>
    <div class="friends-ui" id="'. variable_get('gigya_friends_uiconfig_containerID', GIGYA_DEFAULT_FRIENDSUI_CONTAINERID) .'" style="width:'. variable_get('gigya_friends_uiconfig_width', GIGYA_DEFAULT_FRIENDSUI_WIDTH) .'px; height:'. variable_get('gigya_friends_uiconfig_height', GIGYA_DEFAULT_FRIENDSUI_HEIGHT) .'px; padding-left:53px;">
      <div id="friends"></div>
    </div>
   </form>
   <div id="status"></div>';
  return $output;
}
