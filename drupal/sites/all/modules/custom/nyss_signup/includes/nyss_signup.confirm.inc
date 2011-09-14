<?php

/**
 *  @file
 *  NYSS Signup confirmation functions
 */

/**
 * Confirmation page after mailing list sign up (with options to sign up for more).
 */
function nyss_signup_confirm_page() {
  $output = t('You are signing up for the !list mailing list. Fill out the form below to complete this process and opt in if you want to receive other updates from the New York Senate.', array('!list' => $_SESSION['bronto_list']));
  $output .= drupal_get_form('nyss_signup_confirm_form');
  return $output;
}

/*
 * Confirmation form allowing user to sign up for committee lists, and to fill in their personal info.
 */
function nyss_signup_confirm_form() {
  $form['info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Your Information'),
  );
  $form['info']['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#default_value' => $_SESSION['bronto_email'],
  );
  $form['info']['firstname'] = array(
    '#type' => 'textfield',
    '#title' => t('First Name'),
  );
  $form['info']['lastname'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Name'),
  );
  $form['info']['address1'] = array(
    '#type' => 'textfield',
    '#title' => t('Address 1'),
  );
  $form['info']['address2'] = array(
    '#type' => 'textfield',
    '#title' => t('Address 2'),
  );
  $form['info']['city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
  );
  $form['info']['state'] = array(
    '#type' => 'textfield',
    '#title' => t('State'),
    '#default_value' => 'New York',
  );
  $form['info']['zip'] = array(
    '#type' => 'textfield',
    '#title' => t('Zip'),
    '#default_value' => $_SESSION['bronto_zip'],
  );
  $form['info']['mobile'] = array(
    '#type' => 'textfield',
    '#title' => t('Mobile'),
    '#default_value' => $_SESSION['bronto_mobile'],
  );

  $accounts = nyss_signup_accounts();
  $list = $_SESSION['bronto_list'];
  $sitename = $_SESSION['bronto_sitename'];
  $general_list = variable_get('bronto_general_list', '');
  $general_sitename = variable_get('bronto_general_sitename', '');

  // Show general list and chosen list as options.
  $options = array();
  $options[$general_list . '___' . $accounts[$general_sitename]] = $general_list;
  if ($list != $general_list) {
	$options[$list . '___' . $accounts[$sitename]] = $list;
  }
  $form['general_list'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Sign up for NY Senate Updates'),
    '#options' => $options,
    '#default_value' => array($list . '___' . $accounts[$sitename]),
  );

  // If subscribing to general list, show committee lists as options.  
  if ($list == $general_list) {
    $options = array();
    $results = db_query("SELECT n.title, n.nid, b.field_bronto_sitename_value AS sitename FROM {content_field_bronto_sitename} b INNER JOIN {node} n ON b.vid = n.vid WHERE n.type = 'committee' AND n.status = 1 ORDER BY sitename ASC");
    while ($obj = db_fetch_object($results)) {
      if ($obj->sitename) {
        $committee_list = nyss_signup_get_list_name_from_nid($obj->nid);
        $options[$committee_list . '___' . $accounts[$obj->sitename]] = $obj->title;
      }
    }

    $form['lists'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Sign Up for Committee Updates'),
      '#options' => $options,
      '#default_value' => array($list . '___' . $accounts[$sitename]),
    );
  }
  
  // Get issues from "Issues" vocabulary, and any additional ones the senator/committee added.
  $options = array();
  $vidtree = taxonomy_get_tree(1);
  foreach ($vidtree as $vid) {
    $options[$vid->name] = $vid->name;
  }
  $node = node_load($_SESSION['bronto_issues_nid']);
  if ($node->field_bronto_issues[0]['value']) {
    foreach (explode(';', $node->field_bronto_issues[0]['value']) as $bronto_issue) {
      $options[trim($bronto_issue)] = trim($bronto_issue);
    }
  }
  ksort($options);
  $form['issues'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Limit mailings to specific issues'),
    '#options' => $options,
  );
  
  $form['legal']['ver-age'] = array(
    '#type' => 'checkbox',
    '#title' => t('I confirm that I am over 13 years old'),
    '#default_Value' => 0,
    '#required' => TRUE,
    '#prefix' => '<div style="border-top: solid 1px #E2DED5;"></div>', 
  );
  $form['legal']['ver-priv'] = array(
    '#type' => 'checkbox',
    '#title' => t('I have read the !policy', array('!policy' => l(t('Privacy Policy'), 'privacy-policy', array('attributes' => array('target' => '_blank')))) ),
    '#default_Value' => 0,
    '#required' => TRUE,
  );
  $form['legal']['ver-top'] = array(
    '#type' => 'checkbox',
    '#title' => t('I have read the !policy', array('!policy' => l(t('Terms of Participation'), 'legal', array('attributes'=>array('target'=>'_blank'))))),
    '#default_Value' => 0,
    '#required' => TRUE,
    '#suffix' => '<div style="border-top: solid 1px #E2DED5;">&nbsp;</div>', 
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  return $form;
}

/**
 * Implementation of hook_submit().
 */
function nyss_signup_confirm_form_submit(&$form, &$form_state) {
  require_once(drupal_get_path('module', 'nyss_signup') . '/includes/bronto_api.inc');

  // Update the fields
  $fields = array();
  if ($form_state['values']['firstname']) {
    $fields['firstname'] = $form_state['values']['firstname'];
  }
  if ($form_state['values']['lastname']) {
    $fields['lastname'] = $form_state['values']['lastname'];
  }
  if ($form_state['values']['address1']) {
    $fields['address1'] = $form_state['values']['address1'];
  }
  if ($form_state['values']['address2']) {
    $fields['address2'] = $form_state['values']['address2'];
  }
  if ($form_state['values']['city']) {
    $fields['city'] = $form_state['values']['city'];
  }
  if ($form_state['values']['state']) {
    $fields['state'] = $form_state['values']['state'];
  }
  if ($form_state['values']['mobile']) {
    $fields['mobile'] = $form_state['values']['mobile'];
  }
  if ($form_state['values']['zip']) {
    $fields['zip'] = $form_state['values']['zip'];
  }
  if (count($form_state['values']['issues'])) {
    $issues = array();
    foreach ($form_state['values']['issues'] as $issue) {
      if ($issue) {
        $issues[] = $issue;
      }
    }
    if (count($issues)) {
      $fields['issues'] = '| ' . implode(' | ', $issues) . ' |';
    }
  }

  // Add the email to the mailing lists
  // Start with the general list...
  $lists = array();
  if (count($form_state['values']['general_list'])) {
    foreach ($form_state['values']['general_list'] as $list) {
      if ($list) {
        list($list, $siteID) = split('___', $list);
        $nid = nyss_signup_get_nid_from_mailing_list($list);
        nyss_signup_add_to_db($list, $siteID, $form_state['values']['email'], $nid, $fields);
        $lists[] = $list;
      }
    }
  }
  
  // ...Then do all the others.
  if (count($form_state['values']['lists'])) {
    foreach ($form_state['values']['lists'] as $list) {
      if ($list) {
        list($list, $siteID) = split('___', $list);
        $nid = nyss_signup_get_nid_from_mailing_list($list);
        nyss_signup_add_to_db($list, $siteID, $form_state['values']['email'], $nid, $fields);
        $lists[] = $list;
      }
    }
  }

  // Send confirmation email
  if (count($lists)) {
    $body = t(variable_get('bronto_subscription_confirm_body', nyss_signup_confirm_body_default()), array('!site' => variable_get('site_name', ''), '!lists' => implode("\n", $lists), '!unsubscribe_link' => url('nyss_signup/unsubscribe/' . $_SESSION['bronto_email'], array('absolute' => TRUE))));

    $params = array(
      'subject' => t('Confirmation of subscription to !site mailing lists', array('!site' => variable_get('site_name', ''))),
      'body' => $body,
    );

    $response = drupal_mail('nyss_signup', 'bronto_subscription_confirm', $form_state['values']['email'], language_default(), $params, variable_get('site_mail', ini_get('sendmail_from')));

    drupal_set_message(t('Thank you. You have successfully signed up for your selected updates.'));
  }
  else {
    drupal_set_message(t('Thank you. Your information has been received.'));
  }
  $form_state['redirect'] = $_SESSION['bronto_redirect'];
}
