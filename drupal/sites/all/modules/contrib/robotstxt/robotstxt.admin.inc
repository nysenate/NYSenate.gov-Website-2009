<?php
// $Id: robotstxt.admin.inc,v 1.1.2.2 2009/02/19 22:49:06 hass Exp $

/**
 * @file
 * Administrative page callbacks for the robotstxt module.
 */

/**
 * Administration settings form.
 *
 * @see system_settings_form()
 */
function robotstxt_admin_settings() {
  $form['robotstxt'] = array(
    '#type' => 'textarea',
    '#title' => t('Contents of robots.txt'),
    '#default_value' => _robotstxt_get_content(),
    '#cols' => 60,
    '#rows' => 20,
    '#wysiwyg' => FALSE,
  );

  return system_settings_form($form);
}
