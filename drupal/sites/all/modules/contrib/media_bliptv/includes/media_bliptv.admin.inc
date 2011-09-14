<?php
// $Id: media_bliptv.admin.inc,v 1.1.2.2 2011/02/18 17:16:07 aaron Exp $

/**
 * @file media_bliptv/includes/media_bliptv.admin.inc
 * Administrative functions for Media: BlipTV.
 */

/**
 * The administrative settings form for Media: BlipTV.
 */
function media_bliptv_settings() {
  $form = media_bliptv_admin_form();
  $form['settings_info'] = array(
    '#type' => 'item',
    '#value' => t('These settings specifically affect videos displayed from !bliptv. You can also read more about its !api.', array('!bliptv' => l(t('BlipTV'), MEDIA_BLIPTV_MAIN_URL, array('attributes' => array('target' => '_blank'))), '!api' => l(t("developer's API"), MEDIA_BLIPTV_API_INFO, array('attributes' => array('target' => '_blank'))))),
    '#weight' => -10,
  );
  return system_settings_form($form);
}

/**
 * This form will be displayed both at /admin/settings/media_bliptv and
 * admin/content/emfield.
 */
function media_bliptv_admin_form() {
  $tags = array('none' => t('No video'), 'flv' => t('Flash Video'), 'override' => t('Override tag'), 'web' => t('Web'), 'Web High Resolution' => t('Web High Resolution'), 'Portable (iPod)' => t('Portable (iPod)'), 'Portable (other)' => t('Portable (other)'), 'Television' => t('Television'), 'HDTV' => t('HDTV'), 'Cell Phone' => t('Cell Phone'), 'Source' => t('Source'));
  $formats = array('none' => t('No video'), 'flv' => t('Flash video (flv)'), 'mov' => t('Quicktime Movie (mov)'), 'mp3' => t('MP3'), 'm4a' => t('m4a'), 'mpg' => t('MPEG'), 'mp4' => t('mp4'), 'm4v' => t('m4v'), 'wmv' => t('Windows Media (wmv)'));

  $form = array();

  $form['display_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Display options'),
    '#description' => t("These options control the display of videos from Blip.TV."),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['display_options'][media_bliptv_variable_name('use_embed')] = array(
    '#type' => 'checkbox',
    '#title' => t('Use embed'),
    '#description' => t('If checked, then display videos using an embed tag. However, as this is not HTML4 compliant, you may need to uncheck this box, which will display the video using an object tag. Note that in that case, the video may not display in some mobile devices.'),
    '#default_value' => media_bliptv_variable_get('use_embed'),
  );
  $options = array(
    'window' => t('window'),
    'opaque' => t('opaque'),
    'transparent' => t('transparent'),
  );
  $form['display_options'][media_bliptv_variable_name('wmode')] = array(
    '#type' => 'select',
    '#title' => t('wmode'),
    '#description' => t("The %wmode attribute is used to determine how to display the video on the screen. In most cases, %opaque should be fine. Selecting %window will cause the video to be displayed outside of the HTML structure entirely, which will probably cause problems with menu dropdowns and the like. Using %opaque, the default, will cause it to be layered using CSS, whereas %transparent will cause it to always drop behind any elements positioned over it. Note that %transparent is more processer intensive for the end-user.", array('%wmode' => t('wmode'), '%opaque' => t('opaque'), '%window' => t('window'), '%transparent' => t('transparent'))),
    '#options' => $options,
    '#default_value' => media_bliptv_variable_get('wmode'),
  );

  $form['video_formats'] = array(
    '#type' => 'fieldset',
    '#title' => t('Video formats'),
    '#description' => t("Blip.TV allows users to upload videos of various formats, sizes, and qualities. These options will allow the administrator to choose the default video formats to display. Blip.TV uses 'tags' to determine this, such as 'Web' for a standard web resolution, and 'HDTV' for a high definition. If you select a tag, then the video format provided by Blip.TV for that tag will be displayed. If you select 'Override tag', then you may specify that the first available video of the given format will be displayed instead, which may or may not have your desired resolution. If a tag or format is not available for a specific video, the module will display the Flash video format instead, which is always present."),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['video_formats']['rss'] = array(
    '#type' => 'fieldset',
    '#title' => t('RSS'),
    '#description' => t("This will determine the preferred video format for RSS feeds."),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['video_formats']['rss'][media_bliptv_variable_name('rss_tag')] = array(
    '#type' => 'select',
    '#title' => t('RSS full page tag'),
    '#description' => t("When RSS feeds are displayed, and this tag is available for a video, then the clip for that tag will be displayed as an enclosure tag in the feed. Select 'Override tag' if you wish to control the format displayed. Select 'No video' if you do not wish a video to be displayed in RSS feeds."),
    '#options' => $tags,
    '#default_value' => media_bliptv_variable_get('rss_tag'),
  );
  $form['video_formats']['rss'][media_bliptv_variable_name('rss_format')] = array(
    '#type' => 'select',
    '#title' => t('RSS full page format override'),
    '#description' => t("When RSS feeds are displayed, and the 'Override tag' option is selected above, then this format will be displayed as an enclosure tag in the feed."),
    '#options' => $formats,
    '#default_value' => media_bliptv_variable_get('rss_format'),
  );
  return $form;
}
