<?php

/**
 *  @file
 *  NYSS Signup administrative functions
 */

/**
 * Define module settings FormAPI array.
 *
 * @return
 *   FormAPI form array passed through system_settings_form.
 */
function nyss_signup_settings() {  
  $form['bronto'] = array(
    '#type' => 'fieldset',
    '#title' => t('Bronto Settings'),
  );  
  $form['bronto']['bronto_login'] = array(
    '#type' => 'textfield',
    '#title' => t('Bronto login'),
    '#default_value' => variable_get('bronto_login', ''),
    '#description' => t('Enter the login ID for your main Bronto account.')
  );  
  $form['bronto']['bronto_sitename'] = array(
    '#type' => 'textfield',
    '#title' => t('Bronto site name'),
    '#default_value' => variable_get('bronto_sitename', ''),
    '#description' => t('Enter the sitename associated with this site in this Bronto account')
  );  
  $form['bronto']['bronto_password'] = array(
    '#type' => 'textfield',
    '#title' => t('Bronto password'),
    '#default_value' => variable_get('bronto_password', ''),
    '#description' => t('Enter the password associated with this Bronto account.')
  );
  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General Bronto Mailing List'),
  );
  $form['general']['bronto_general_list'] = array(
    '#type' => 'textfield',
    '#title' => t('General Mailing List Name'),
    '#default_value' => variable_get('bronto_general_list', ''),
    '#description' => t('This is the Bronto name of the general, site-wide mailing list.'),
  );
  $form['general']['bronto_general_sitename'] = array(
    '#type' => 'textfield',
    '#title' => t('Subaccount site name'),
    '#default_value' => variable_get('bronto_general_sitename', ''),
    '#description' => t('Enter the sitename of the Bronto subaccount with the general mailing list')
  );  
  $form['bronto_subscription_confirm_body'] = array(
    '#type' => 'textarea',
    '#title' => t('Confirmation email body'),
    '#default_value' => variable_get('bronto_subscription_confirm_body', nyss_signup_confirm_body_default()),
    '#description' => t('The body of the confirmation email a user gets when they subscribe to a list.  Tokens: !site, !lists, !unsubscribe_link.'),
  );
  $form['bronto_subscription_unsubscribe_body'] = array(
    '#type' => 'textarea',
    '#title' => t('Unsubscribe email body'),
    '#default_value' => variable_get('bronto_subscription_unsubscribe_body', nyss_signup_unsubscribe_body_default()),
    '#description' => t('The body of the confirmation email a user gets when they unsubscribe from a list.  Tokens: !site, !lists, !site_link.'),
  );
  return system_settings_form($form);
}
