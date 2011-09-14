<?php
// $Id: jcarousel.jq.inc,v 1.1.2.1 2008/12/05 08:38:23 robloach Exp $

/**
 * @file
 * Adds support for the jQ module.
 *
 * jq_add('jcarousel', $selector, $options);
 */
function jcarousel_jq($op, $plugin = NULL) {
  switch ($op) {
    case 'info':
      return array(
        'jcarousel' => array(
          'name' => t('jCarousel'),
          'description' => t('jCarousel is a jQuery plugin for controlling a list of items in horizontal or vertical order.'),
          'version' => '0.2.3',
          'url' => 'http://sorgalla.com/jcarousel/',
        ),
      );
    break;
    case 'add':
      switch ($plugin) {
        case 'jcarousel':
          // When adding the plugin, allow additional arguments so that
          // we can automatically add the jQuery $selector and $callback
          // function.
          $args = func_get_args();
          unset($args[0]); // $op
          unset($args[1]); // $plugin
          call_user_func_array('jcarousel_add', $args);
        break;
      }
    break;
  }
}
