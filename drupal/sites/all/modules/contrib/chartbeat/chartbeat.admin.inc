<?php
// $Id: chartbeat.admin.inc,v 1.1 2009/11/11 16:30:41 robloach Exp $

/**
 * Menu callback for the String Overrides module to display its administration
 */
function chartbeat_admin_settings() {
  $form['chartbeat_uid'] = array(
    '#type' => 'textfield',
    '#title' => t('User ID'),
    '#description' => t('The user ID associated with your <a href="@chartbeat">Chartbeat</a> account.', array('@chartbeat' => 'http://chartbeat.com')),
    '#default_value' => variable_get('chartbeat_uid', ''),
  );
  $form['chartbeat_domain'] = array(
    '#type' => 'textfield',
    '#title' => t('Domain'),
    '#description' => t('The domain to be reporting from on your account.'),
    '#default_value' => variable_get('chartbeat_domain', ''),
  );
  return system_settings_form($form);
}
