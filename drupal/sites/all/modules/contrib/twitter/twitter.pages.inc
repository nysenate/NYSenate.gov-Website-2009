<?php

/**
 *
 */
function twitter_admin_form() {
  $form = array();

  $form['oauth'] = array(
    '#type' => 'fieldset',
    '#title' => t('OAuth Settings'),
    '#description' => t(''),
    '#access' => module_exists('oauth'),
    '#description' => t('To enable OAuth based access for twitter, you must <a href="@url">register your application</a> with twitter and add the provided keys here.', array('@url' => 'https://dev.twitter.com/apps/new')),
  );

  $form['oauth']['callback_url'] = array(
    '#type' => 'item',
    '#title' => t('Callback URL'),
    '#value' => url('twitter/oauth', array('absolute' => TRUE)),
  );

  $form['oauth']['twitter_consumer_key'] = array(
    '#type' => 'textfield',
    '#title' => t('OAuth Consumer key'),
    '#default_value' => variable_get('twitter_consumer_key', NULL),
  );

  $form['oauth']['twitter_consumer_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('OAuth Consumer secret'),
    '#default_value' => variable_get('twitter_consumer_secret', NULL),
  );

  $form['import'] = array(
    '#type' => 'fieldset',
    '#title' => t('Twitter import'),
    '#description' => t('Import and display the Twitter statuses of site users who have entered their Twitter account information.'),
  );

  $form['import']['twitter_import'] = array(
    '#type' => 'checkbox',
    '#title' => t('Import Twitter statuses'),
    '#default_value' => variable_get('twitter_import', TRUE),
  );

  $periods = array(0 => t('Never'));
  $periods += drupal_map_assoc(array(604800, 2419200, 7257600, 31449600), 'format_interval');
  $form['import']['twitter_expire'] = array(
    '#type' => 'select',
    '#title' => t('Delete old statuses'),
    '#default_value' => variable_get('twitter_expire', 0),
    '#options' => $periods
  );

  return system_settings_form($form);
}

function twitter_user_settings($account) {
  module_load_include('inc', 'twitter');

  $output = '';
  // This is directly calling a hook implementation, which is bad and naughty,
  // but oh well. We'll fix this in the next reshuffling when user account
  // management gets an overhaul.
  $twitter_accounts = twitter_twitter_accounts($account);
  if (!empty($twitter_accounts)) {
    $output .= drupal_get_form('twitter_account_list_form', $twitter_accounts);
  }
  $output .= drupal_get_form('twitter_account_form', $account);

  return $output;
}

function twitter_account_list_form($form_state, $twitter_accounts = array()) {
  $form['#tree'] = TRUE;
  $form['accounts'] = array();

  foreach ($twitter_accounts as $twitter_account) {
    $form['accounts'][] = _twitter_account_list_row($twitter_account);
  }

  if (!empty($twitter_accounts)) {
    $form['buttons']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save changes'),
    );
  }

  return $form;
}

function _twitter_account_list_row($account) {
  $form['#account'] = $account;

  $form['id'] = array(
    '#type' => 'value',
    '#value' => $account->id,
  );

  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $account->uid,
  );

  $form['screen_name'] = array(
    '#type' => 'value',
    '#value' => $account->screen_name,
  );

  $form['image'] = array(
    '#type' => 'markup',
    '#value' => theme('image', $account->profile_image_url, '', '', array(), FALSE),
  );

  $form['visible_name'] = array(
    '#type' => 'markup',
    '#value' => l($account->screen_name, 'http://www.twitter.com/' . $account->screen_name),
  );

  $form['description'] = array(
    '#type' => 'markup',
    '#value' => filter_xss($account->description),
  );

  $form['protected'] = array(
    '#type' => 'markup',
    '#value' => empty($account->protected) ? t('No') : t('Yes'),
  );

  if (user_access('import own tweets')){ // Here we use user_access('import own tweets') to check permission instead of user_access('import own tweets', $account->uid) is because we allow roles with sufficient permission to overwrite the user's import settings.
    $form['import'] = array(
    	'#type' => 'checkbox',
    	'#default_value' => user_access('import own tweets') ? $account->import : '',
    );

    $form['include_retweets'] = array(
    	'#type' => 'checkbox',
    	'#default_value' => user_access('import own tweets') ? $account->include_retweets : '',
    );
  }


  $form['delete'] = array(
    '#type' => 'checkbox',
  );

  return $form;
}

function theme_twitter_account_list_form($form) {

  if (user_access('import own tweets')) {
    $header = array('', t('Name'), t('Description'), t('Private'), t('Import'), t('Retweets'), t('Delete'));
  }else {
    $header = array('', t('Name'), t('Description'), t('Private'), t('Delete'));
  }

  if (user_access('make twitter accounts global')) {
    $header[] = '';
  }

  $rows = array();

  foreach (element_children($form['accounts']) as $key) {
    $element = &$form['accounts'][$key];
    if (user_access('import own tweets')) {
      $row = array(
      drupal_render($element['image']),
      drupal_render($element['id']) . drupal_render($element['screen_name']) . drupal_render($element['visible_name']),
      drupal_render($element['description']),
      drupal_render($element['protected']),
      drupal_render($element['import']),
      drupal_render($element['include_retweets']),
      drupal_render($element['delete']),
      );
    }else {
      $row = array(
      drupal_render($element['image']),
      drupal_render($element['id']) . drupal_render($element['screen_name']) . drupal_render($element['visible_name']),
      drupal_render($element['description']),
      drupal_render($element['protected']),
      drupal_render($element['delete']),
      );
    }

    if (user_access('make twitter accounts global')) {
      $label = ($element['#account']->is_global) ? t('remove global') : t('make global');
      $row[] = l($label, 'user/'. $element['#account']->uid .'/edit/twitter/global/'. $element['#account']->id);
    }

    $rows[] = $row;
  }

  $output = theme('table', $header, $rows);
  $output .= drupal_render($form);
  return $output;
}

function twitter_account_list_form_submit($form, &$form_state) {
  $accounts = $form_state['values']['accounts'];
  foreach($accounts as $account) {
    if (empty($account['delete'])) {
      twitter_account_save($account);
    }
    else {
      twitter_user_delete($account['id'], $account['screen_name']);
    }
  }
}

function twitter_user_make_global($form_state, $account, $twitter_uid) {
  module_load_include('inc', 'twitter');

  $twitter_account = twitter_account_load($twitter_uid);

  $form = array();

  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $account->uid,
  );

  $form['twitter_uid'] = array(
    '#type' => 'value',
    '#value' => $twitter_uid,
  );

  if ($twitter_account->is_global) {
    $text = t('Are you sure you want to remove %screen_name from the global accounts?', array('%screen_name' => $twitter_account->screen_name));
    $description = t('This means other users will no longer be allowed to post using this account.');
  }
  else {
    $text = t('Are you sure you want to allow other users to access the %screen_name account?', array('%screen_name' => $twitter_account->screen_name));
    $description = t('This will allow other users to post using this account.');
  }

  return confirm_form($form, $text, 'user/'. $account->uid .'/edit/twitter', $description);
}

function twitter_user_make_global_submit($form, &$form_state) {
  db_query("UPDATE {twitter_account} SET is_global = (1 - is_global) WHERE twitter_uid = %d", $form_state['values']['twitter_uid']);

  $form_state['redirect'] = 'user/'. $form_state['values']['uid'] .'/edit/twitter';
}

function twitter_account_form($form_state, $account = NULL) {
  if (empty($account)) {
    global $user;
    $account = $user;
  }

  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $account->uid,
  );

  if (_twitter_use_oauth()) {
    $form['#validate'] = array('twitter_account_oauth_validate');
  }
  else {
    $form['screen_name'] = array(
      '#type' => 'textfield',
      '#required' => TRUE,
      '#title' => t('Twitter user name'),
    );
    
    // only display the password field if OAuth is installed
    if (_twitter_use_oauth()) {
      $form['password'] = array(
        '#type' => 'password',
        '#title' => t('Password'),
        '#description' => t("If your Twitter account is protected, or you wish to post to Twitter from Drupal, you must enter the Twitter account's password.")
      );
    }

    $form['import'] = array(
      '#type' => 'checkbox',
      '#title' => t('Import statuses from this account'),
      '#default_value' => TRUE,
      '#access' => FALSE,
    );

  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add account'),
  );

  return $form;
}

function twitter_account_form_validate($form, &$form_state) {
  module_load_include('lib.php', 'twitter');
  module_load_include('inc', 'twitter');

  $verify = FALSE;

  $pass = $form_state['values']['password'];
  $name = $form_state['values']['screen_name'];

  if (!empty($pass)) {
    $verify = TRUE;
  }
  
  $twitter = new Twitter($name, $pass);
  // to verify, oauth must be installed
  if ($verify && _twitter_use_oauth()) {
    $account = $twitter->verify_credentials();
    if (!$account) {
      form_set_error("password", t('Twitter authentication failed. Please check your account name and try again.'));
    }
  } else {
    // if we're not verify credentials, simply load the user data, without oauth
    $account = $twitter->users_show($name, false);
  }
  $form_state['twitter_account'] = $account;
}

function twitter_account_form_submit($form, &$form_state) {
  module_load_include('inc', 'twitter');

  if (!empty($form_state['values']['screen_name'])) {
    $account = $form_state['twitter_account'];
    if (_twitter_use_oauth()) {
      $account->set_auth($form_state['values']);
    }
    twitter_account_save($account, TRUE, user_load($form_state['values']['uid']));
  }
}

function twitter_account_oauth_validate($form, &$form_state) {
  module_load_include('lib.php', 'oauth');
  module_load_include('lib.php', 'twitter');

  $key = variable_get('twitter_consumer_key', '');
  $secret = variable_get('twitter_consumer_secret', '');
  $twitter = new TwitterOAuth($key, $secret);
  $token = $twitter->get_request_token();

  $_SESSION['twitter_oauth']['token'] = $token;
  $_SESSION['twitter_oauth']['destination'] = $_GET['q'];
  drupal_goto($twitter->get_authorize_url($token));
}


function twitter_oauth_callback(&$form_state) {
  $form['#post']['oauth_token'] = $_GET['oauth_token'];

  $form['oauth_token'] = array(
    '#type' => 'hidden',
    '#default_value' => $_GET['oauth_token'],
  );

  return $form;
}

function twitter_oauth_callback_validate($form, &$form_state) {
  $key = variable_get('twitter_consumer_key', '');
  $secret = variable_get('twitter_consumer_secret', '');

  $form_state['twitter_oauth'] = $_SESSION['twitter_oauth'];
  unset($_SESSION['twitter_oauth']);

  $token = $form_state['twitter_oauth']['token'];
  if (!is_array($token) || !$key || !$secret) {
    form_set_error('oauth_token', t('Invalid Twitter OAuth request'));
  }

  if ($token['oauth_token'] != $form_state['values']['oauth_token']) {
    form_set_error('oauth_token', t('Invalid OAuth token.'));
  }

  module_load_include('lib.php', 'oauth');
  module_load_include('lib.php', 'twitter');
  module_load_include('inc', 'twitter');

  $twitter = new TwitterOAuth($key, $secret, $token['oauth_token'], $token['oauth_token_secret']);
  $response = $twitter->get_access_token();
  $form_state['twitter_oauth']['response'] = $response;
}

function twitter_oauth_callback_submit(&$form, &$form_state) {
  $key = variable_get('twitter_consumer_key', '');
  $secret = variable_get('twitter_consumer_secret', '');
  $response = $form_state['twitter_oauth']['response'];

  $twitter = new TwitterOAuth($key, $secret, $response['oauth_token'], $response['oauth_token_secret']);
  $account = $twitter->users_show($response['screen_name']);
  $account->set_auth($response);
  twitter_account_save($account, TRUE);
  $form_state['redirect'] = $form_state['twitter_oauth']['destination'];
  $form['#programmed'] = FALSE;
}
