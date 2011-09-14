<?php

/**
 *  @file
 *  NYSS Signup unsubscribe functions
 */

/**
 * Unsubscribe page.
 */
function nyss_signup_unsubscribe_page($email = NULL) {
  if (!$email) {
    $output .= drupal_get_form('nyss_signup_unsubscribe_email_form');
  }
  else {
    $lists = array();
  
    require_once(drupal_get_path('module', 'nyss_signup') . '/includes/bronto_api.inc');
    $accounts = nyss_signup_accounts();

    $sitenames = array(variable_get('bronto_general_sitename', ''));
    $results = db_query("SELECT b.field_bronto_sitename_value AS sitename FROM {content_field_bronto_sitename} b INNER JOIN {node} n ON n.vid = b.vid WHERE b.field_bronto_sitename_value IS NOT NULL");
    while ($obj = db_fetch_object($results)) {
      $sitenames[] = $obj->sitename;
    }
    
    // Go through each subaccount (general, senator, committee) and see if user is subscribed.
    foreach ($sitenames as $sitename) {
      $bronto = new bronto_api(variable_get('bronto_login', ''), variable_get('bronto_sitename', ''), variable_get('bronto_password', ''), $accounts[$sitename]);
      $account_lists = $bronto->get_contact_lists($email);
      if (is_array($account_lists)) {
        $i = count($list);
        foreach ($account_lists as $list) { 
          $lists[$list . '___' . $accounts[$sitename]] = $list;
          $i++;
        }
      }
      unset($bronto);
    }
    
    // Add the email to the mailing list
    if (empty($lists)) {
      drupal_set_message('No lists found for that email address.');
      drupal_goto('nyss_signup/unsubscribe');
    }

    $output .= drupal_get_form('nyss_signup_unsubscribe_lists_form', $lists, $email);
  }
  
  return $output;
}

/**
 * Form to enter an email address to pull lists for unsubscribing.
 * @return
 *   FormAPI array.
 */
function nyss_signup_unsubscribe_email_form() {
  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#required' => TRUE,
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
function nyss_signup_unsubscribe_email_form_submit(&$form, &$form_state) {
  $form['#redirect'] = 'nyss_signup/unsubscribe/' . $form_state['values']['email'];
}

/**
 * Form that allows users to select from which lists to unsubscribe.
 * @param $lists
 *   Array of list names that the email is subscribed to.
 * @return
 *   FormAPI array.
 */
function nyss_signup_unsubscribe_lists_form($form_state, $lists, $email) {
  $form['email'] = array(
    '#type' => 'value',
    '#value' => $email,
  );

  // Sort by list name, preserving key, and set as options.
  $options = array();
  ksort($lists);
  foreach ($lists as $key => $list) {
    $options[$key] = $list;
  }

  $form['lists'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Your lists'),
    '#description' => t('Check the lists from which you wish to unsubscribe.'),
    '#options' => $options,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Unsubscribe'),
  );
  return $form;
}

/**
 * Implementation of hook_submit().
 */
function nyss_signup_unsubscribe_lists_form_submit(&$form, &$form_state) {
  require_once(drupal_get_path('module', 'nyss_signup') . '/includes/bronto_api.inc');

  $lists = array();
  foreach ($form_state['values']['lists'] as $list) {
    if ($list) {
      list($list, $siteId) = split('___', $list);
      $lists[] = $list;
      $bronto = new bronto_api(variable_get('bronto_login', ''), variable_get('bronto_sitename', ''), variable_get('bronto_password', ''), $siteId);
      $bronto->remove_email_from_list($form_state['values']['email'], $list);
      unset($bronto);
    }
  }
  if (count($lists)) {
    // Send unsubscribe confirmation email
    $body = t(
        variable_get('bronto_subscription_unsubscribe_body', nyss_signup_unsubscribe_body_default()), 
        array(
          '!site' => variable_get('site_name', ''), 
          '!lists' => implode("\n", $lists), 
          '!site_link' => url('', array('absolute' => TRUE))
        )
      ) . "\n\n" . 
      t('View your subscriptions: ') . 
      url('nyss_signup/unsubscribe/' . $form_state['values']['email'], array('absolute' => TRUE));

    $params = array(
      'subject' => t('Unsubscribed from !site mailing lists', array('!site' => variable_get('site_name', ''))),
      'body' => $body,
    );

    $response = drupal_mail('nyss_signup', 'bronto_subscription_unsubscribe', $form_state['values']['email'], language_default(), $params, variable_get('site_mail', ini_get('sendmail_from')));

    drupal_set_message(t('You have successfully unsubscribed from the checked lists.'));
  }
  else {
    drupal_set_message(t('You have not unsubscribed from any lists.'));
  }
  $form['#redirect'] = 'nyss_signup/unsubscribe/' . $form_state['values']['email'];
}
