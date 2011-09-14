<?php

/**
 * @file
 * Administrative functionality for RPX module.
 *
 */

/**
 * RPX module settings page
 */
function rpx_admin_settings() {
  
  if (variable_get('rpx_form_submitted', FALSE) || isset($_REQUEST['token'])) {

    $api_key = variable_get('rpx_apikey', FALSE);
    
    // If there is an api OR the api key is being changed,
    // then do a callback lookup to get new rpx variables
    if (($api_key || isset($_POST['rpx_apikey']) && $api_key != $_POST['rpx_apikey'])) {
      
      // If the api key has changed, use the new key instead of the stored one
      $api_key = isset($_POST['rpx_apikey']) ? $_POST['rpx_apikey'] : $api_key;
      if (!($lookup = RPX::lookup($api_key, 'apiKey'))) {
        drupal_set_message(t('Error contacting RPX.  Please verify your internet connection.'), 'error', TRUE);
      }
      if ($lookup['adminUrl'] != 'N' ) {
        variable_set('rpx_apikey', $lookup['apiKey']);
        variable_set('rpx_admin_url', $lookup['adminUrl']);
        variable_set('rpx_realm', $lookup['realm']);
        variable_set('rpx_realm_scheme', $lookup['realmScheme']);
        variable_set('rpx_app_id', $lookup['appId']);
        variable_set('rpx_social_pub', $lookup['socialPub']);
  
        // get the provider info as well
        if ($lookup) {
          $providers = RPX::get_enabled_providers($lookup['realm'], $lookup['realmScheme']);
          variable_set('rpx_enabled_providers', $providers);
        }
      }
      else {
        drupal_set_message( t('Looks like your API key was incorrect.  Please verify the key and try again.'), 'error', true );
      }
  
    }
    // If a token is set then lookup both the api key and extra rpx variables
    elseif (isset($_GET['token'])) {
      if (!($lookup = RPX::lookup($_GET['token'], 'token'))) {
        drupal_set_message(t('Error contacting RPX.  Please verify your internet connection.'), 'error', TRUE);
      }
          
      variable_set('rpx_admin_url', $lookup['adminUrl']);
      variable_set('rpx_realm', $lookup['realm']);
      variable_set('rpx_realm_scheme', $lookup['realmScheme']);
      variable_set('rpx_apikey', $lookup['apiKey']);
      variable_set('rpx_app_id', $lookup['appId']);
      variable_set('rpx_social_pub', $lookup['socialPub']);
      // Redirect back to the setting page, without the token appended
      drupal_goto('admin/settings/rpx');
    }
    variable_del('rpx_form_submitted');
  }
  
  return drupal_get_form('rpx_admin_settings_form');
}

/**
 * RPX Module settings form
 */
function rpx_admin_settings_form() {
  
  $api_key = variable_get('rpx_apikey', FALSE);
  
  if (!$api_key && !isset($_GET['token'])) {
    global $user, $base_url;
    $request_id = $_SESSION['rpx_request_id'] = md5($user->mail . time());
    $text = '<p>Before using RPX with this site you must setup an account at rpxnow.com. Visiting the following link will allow you to setup your RPX account and will return the required api key: <strong><a href="!create_rp">Setup this site for RPX</a></strong></p>';
    $form['setup'] = array('#value' => t($text, array(
      '!create_rp' => RPX::create_api .'?'. http_build_query(array(
        'base' => $base_url . base_path(),
        'return' => url('admin/settings/rpx', array('absolute' => TRUE)),
        'requestId' => $request_id
      ))
    )));
  }
  
  $form['api'] = array(
    '#type' => 'fieldset',
    '#title' => t('RPX Setup'),
    '#collapsible' => TRUE,
    '#collapsed' => variable_get('rpx_apikey', '') ? TRUE : FALSE,
    '#description' => t('To make changes to your RPX account and integration with this site visit <a href="@account_link">@account_link</a>.', array('@account_link' => 'https://rpxnow.com/account')),
  );
  $form['api']['rpx_apikey'] = array(
    '#type' => 'textfield',
    '#title' => t('RPX API Key'),
    '#default_value' => variable_get('rpx_apikey', ''),
    '#description' => t('The API Key provided for this site at <a href="@account_link">@account_link</a>', array('@account_link' => 'https://rpxnow.com/account')),
  );
  
  $form['api']['rpx_realm'] = array(
      '#type' => 'item',
      '#title' => t('RPX Realm'),
      '#value' => variable_get('rpx_realm', ''),
      '#description' => t('The RPX realm for this site (Set automatically based on your API Key)') //,
  );
  $path = variable_get('rpx_apikey', '') ? variable_get('rpx_admin_url', '') : '';
  $form['api']['rpx_admin_url_hidden'] = array(
    '#type' => 'item',
    '#title' => t('RPX Admin URL'),
    '#value' => t('<a href="@account_stats">@account_stats</a>', array('@account_stats' => $path)),
    '#description' => t('The RPX admin URL (Set automatically based on your API Key)'),
    '#attributes' => array('disabled' => 'disabled')
  );
  
  $force_lookup = isset($_GET['update-providers']) ? TRUE : FALSE;
  $providers = rpx_get_admin_provider_array($force_lookup);
  if (count($providers)) {
    $form['providers'] = array(
        '#type' => 'fieldset',
        '#title' => 'Identity Providers',
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
        '#description' => t('<a href="@setup_url" target="_blank">Configure/add providers here.</a> <a href="@update_url">Click here</a> to update your list of enabled providers from the RPX servers.', array('@update_url' => url('admin/settings/rpx', array('query' => 'update-providers')), '@setup_url' => variable_get('rpx_admin_url', '') .'/setup_providers#steps'))
    );
    
    $form['providers']['list'] = array(
      '#type' => 'item',
      '#value' => theme('item_list', $providers) 
    );
  }
  
  $form['api']['rpx_signin_string'] = array(
    '#type' => 'textfield',
    '#title' => t('RPX Signin Label'),
    '#default_value' => (variable_get('rpx_signin_string', RPX_SIGNIN_STRING)=='')?RPX_SIGNIN_STRING:variable_get('rpx_signin_string', RPX_SIGNIN_STRING),
    '#description' => t('The text that will appear above the icons on the login page.'),
  );
  
  $form['rpx_attach_login_form'] = array(
    '#type' => 'checkbox',
    '#title' => t('Attach RPX Sign-In link to login forms'),
    '#default_value' => variable_get('rpx_attach_login_form', 0) ? 1 : 0,
    '#description' => t('Attach the RPX Sign-In link to regular Drupal login block and the login page'),
  );
  
  $form['rpx_extra_profile_data'] = array(
    '#type' => 'checkbox',
    '#title' => t('Extra profile data'),
    '#default_value' => variable_get('rpx_extra_profile_data', 0) ? 1 : 0,
    '#description' => t('Enable extra user profile fields. <strong>Note: This feature will be removed in the next release. It is suggested that you disable this and use profile field mapping instead.</strong>'),
  );

  $form['rpx_force_registration_form'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force registration form'),
    '#default_value' => variable_get('rpx_force_registration_form', 0) ? 1 : 0,
    '#description' => t('Always show registration form on RPX login, in case there are additional required fields to be captured'),
  );

  $form['rpx_javascript_global'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force RPX javascript on every page'),
    '#default_value' => variable_get('rpx_javascript_global', 0) ? 1 : 0,
    '#description' => t('Certain caching setups may cause some RPX login links not to work. If that is the case, try checking this option to resolve the issue. You may also need to clear the cache on the <a href="!performance_link">Performance</a> page.', array('!performance_link' => url('admin/settings/performance'))),
  );

  if (module_exists('openid')) {
    $form['rpx_openid_override'] = array(
      '#type' => 'checkbox',
      '#title' => t('Allow RPX to override OpenID'),
      '#default_value' => variable_get('rpx_openid_override', 0) ? 1 : 0,
      '#description' => t('Allow the RPX login link to replace the core OpenID module login link'),
    );
  }
  
  if (variable_get('rpx_social_pub', FALSE)) {
    $form['rpx_attach_share_link'] = array(
      '#type' => 'checkbox',
      '#title' => t('Attach "share" to comments'),
      '#default_value' => variable_get('rpx_attach_share_link', 0) ? 1 : 0,
      '#description' => t('Attach the RPX social publishing pop-up to comments'),
    );
  }
  
  $email_token_help = t('Available variables are:') .' !username, !site, !uri, !uri_brief, !mailto, !date, !login_uri, !edit_uri, !login_url.';
  $form['email']['verify_rpx'] = array(
    '#type' => 'fieldset',
    '#title' => t('Verification Email'),
    '#collapsible' => TRUE,
    '#collapsed' => (variable_get('user_register', 1) != 1),
    '#description' => t('Some RPX providers do not provide verified email addresses. '.
                        'If your <a href="@user_settings">user settings</a> require emails be verified, '.
                        'an email will be dispatched to these users in order to verify their email address before they can login.',
                        array('@user_settings' => url('admin/user/settings'))) .' '. $email_token_help
  );
  $form['email']['verify_rpx']['rpx_bypass_email_verification'] = array(
    '#type' => 'checkbox',
    '#title' => t('Bypass email verification for RPX registration'),
    '#default_value' => variable_get('rpx_bypass_email_verification', 0) ? 1 : 0,
    '#description' => t('If checked, users who register using RPX will not be required verify their email address even if their provider does not provide a verified email.'),
  );
  $form['email']['verify_rpx']['user_mail_rpx_confirm_email_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#default_value' => _rpx_mail_text('rpx_confirm_email_subject'),
    '#maxlength' => 180,
  );
  $form['email']['verify_rpx']['user_mail_rpx_confirm_email_body'] = array(
    '#type' => 'textarea',
    '#title' => t('Body'),
    '#default_value' => _rpx_mail_text('rpx_confirm_email_body'),
    '#rows' => 15,
  );

  $form['#submit'][] = 'rpx_admin_settings_submit';
  
  $form['buttons']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration') );
  $form['buttons']['reset'] = array('#type' => 'submit', '#value' => t('Reset to defaults') );
 
  return $form;
}

/* set display list of providers from enabled list via rpx profile */
function rpx_get_admin_provider_array($force_lookup = FALSE) {
  
    $providers = variable_get('rpx_enabled_providers', array());
    $realm = variable_get('rpx_realm', '');
    $realm_scheme = variable_get('rpx_realm_scheme', 'http');
    if ( (!count($providers) && $realm) || $force_lookup ) {
      $providers = RPX::get_enabled_providers($realm, $realm_scheme);
      variable_set('rpx_enabled_providers', $providers);
    }
    $providers = _rpx_providers();
    $display_list = array();
    foreach ($providers as $provider) {
      $display_list[] = theme('rpx_icon', $provider) .' '. $provider['title'];
    }
    return $display_list;
}

function rpx_admin_settings_submit($form, &$form_state) {
  // unset RPX variables 
  variable_del('rpx_apikey');
  variable_del('rpx_realm');
  variable_del('rpx_realm_scheme');
  variable_del('rpx_enabled_providers');
  variable_del('rpx_signin_string');
  variable_del('rpx_app_id');
  variable_del('rpx_social_pub');
  
  variable_set('rpx_form_submitted', TRUE);
  $op = isset($form_state['values']['op']) ? $form_state['values']['op'] : '';

  // Exclude unnecessary elements.
  unset($form_state['values']['submit'], $form_state['values']['reset'], $form_state['values']['form_id'], $form_state['values']['op'], $form_state['values']['form_token'], $form_state['values']['form_build_id']);

  foreach ($form_state['values'] as $key => $value) {
    if ($op == t('Reset to defaults')) {
      variable_del($key);
      
    }
    else {
      variable_set('rpx_signin_string', $form_state['values']['rpx_signin_string']);
      if (is_array($value) && isset($form_state['values']['array_filter'])) {
        $value = array_keys(array_filter($value));
      }
      variable_set($key, $value);
    }
  }
  if ($op == t('Reset to defaults')) {
    drupal_set_message(t('The configuration options have been reset to their default values.'));
  }
  else {
    drupal_set_message(t('The configuration options have been saved.'));
  }
  
  cache_clear_all();
  drupal_rebuild_theme_registry();
}

function rpx_profile_settings() {
  return drupal_get_form('rpx_profile_settings_form');
}

function rpx_profile_settings_form($form_state) {
  
  $form['rpx_import_profile_photo'] = array(
    '#type' => 'checkbox',
    '#title' => t('Import Profile Picture'),
    '#default_value' => variable_get('rpx_import_profile_photo', 0) ? 1 : 0,
    '#description' => t('If checked, the user\'s profile picture will be automatically imported as their Drupal profile picture.'),
  );

  if (module_exists('profile')) {
    $options = _rpx_profile_field_options();
  }
  else {
    // If the profile module is not enabled, notify the user
    if (!count($form_state['post']))
      drupal_set_message(t('The profile module must be enabled to map RPX data to profile fields.'));
    $options = array();
  }
  $map = variable_get('rpx_profile_fields_map', array());
  $form['mapping'] = array(
      '#type' => 'fieldset',
      '#title' => t('Field Mapping'),
      '#description' => t('<p>Select the Drupal profile fields that should be mapped to RPX data. Currently only 3 Drupal profile field types are supported: single-line text, multi-line text, and URL.</p>'),
      '#tree' => TRUE
  );
  $form['mapping']['givenName'] = array(
      '#type' => 'select',
      '#title' => t('First name'),
      '#default_value' => $map['givenName'],
      '#options' => $options
  );
  $form['mapping']['familyName'] = array(
      '#type' => 'select',
      '#title' => t('Last name'),
      '#default_value' => $map['familyName'],
      '#options' => $options
  );
  $form['mapping']['displayName'] = array(
      '#type' => 'select',
      '#title' => t('Display Name'),
      '#default_value' => $map['displayName'],
      '#options' => $options
  );
  $form['mapping']['gender'] = array(
      '#type' => 'select',
      '#title' => t('Gender'),
      '#default_value' => $map['gender'],
      '#options' => $options
  );
  $form['mapping']['birthday'] = array(
      '#type' => 'select',
      '#title' => t('Birthday'),
      '#default_value' => $map['birthday'],
      '#options' => $options
  );
  $form['mapping']['phoneNumber'] = array(
      '#type' => 'select',
      '#title' => t('Phone Number'),
      '#default_value' => $map['phoneNumber'],
      '#options' => $options
  );
  $form['mapping']['streetAddress'] = array(
      '#type' => 'select',
      '#title' => t('Street Address'),
      '#default_value' => $map['streetAddress'],
      '#options' => $options
  );
  $form['mapping']['locality'] = array(
      '#type' => 'select',
      '#title' => t('City'),
      '#default_value' => $map['locality'],
      '#options' => $options
  );
  $form['mapping']['region'] = array(
      '#type' => 'select',
      '#title' => t('State/Province'),
      '#default_value' => $map['region'],
      '#options' => $options
  );
  $form['mapping']['postalCode'] = array(
      '#type' => 'select',
      '#title' => t('Zipcode/Postal code'),
      '#default_value' => $map['postalCode'],
      '#options' => $options
  );
  $form['mapping']['country'] = array(
      '#type' => 'select',
      '#title' => t('Country'),
      '#default_value' => $map['country'],
      '#options' => $options
  );
  
  $form['submit'] = array('#type' => 'submit', '#value' => t('Save') );
  $form['mapping']['#theme'] = 'rpx_field_mapping_form';
  return $form;
}

function _rpx_profile_field_options() {
  $options = array('' => '');
  $result = db_query("SELECT fid, title, name FROM {profile_fields} WHERE type IN ('textfield', 'textarea', 'url') ORDER BY weight, title");
  while ($row = db_fetch_object($result)) {
    $options[$row->name] = $row->title;
  }

  return $options;
}

function rpx_profile_settings_form_submit($form_state, $form_values) {
  $values = $form_values['values'];
  variable_set('rpx_import_profile_photo', $values['rpx_import_profile_photo']);
  $map = array();
  foreach ($values['mapping'] as $k => $v) {
    if ($v) {
      $map[$k] = $v;
    }
  }
  variable_set('rpx_profile_fields_map', $map);
}


/**
 * Theme RPX field mapping form.
 *
 * @ingroup themeable
 */
function theme_rpx_field_mapping_form($form) {
  $headers = array(t('RPX Profile Field'), '',  t('Drupal Profile Field'));
  foreach (element_children($form) as $key) {
    $rpx_title = $form[$key]['#title'];
    unset($form[$key]['#title']);
    $rows[] = array(
      $rpx_title,
      ' => ',
      drupal_render($form[$key]),
    );
  }
  return theme('table', $headers, $rows);
}
