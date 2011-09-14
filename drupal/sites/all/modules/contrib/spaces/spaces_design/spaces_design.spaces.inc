<?php
// $Id: spaces_design.spaces.inc,v 1.1.2.1 2009/08/13 17:25:37 yhahn Exp $

/**
 * Provides a logo setting for each space.
 */
class space_setting_logo implements space_setting {
  var $id;

  function __construct($id = NULL) {
    $this->id = 'logo';
  }

  function form($space, $value = array()) {
    $form = array();
    $form['#title'] = t('Logo');
    $form['#description'] = t('Upload a logo image for this space. The image will be resized to better fit the design of this site.');
    if (!empty($value['fid'])) {
      $file = db_fetch_object(db_query('SELECT * FROM {files} f WHERE f.fid = %d', $value['fid']));
      if (!empty($file)) {
        $form['file'] = array(
          '#type' => 'value',
          '#value' => $file,
        );
        $form['display'] = array(
          '#type' => 'markup',
          '#value' => theme('imagecache', 'spaces-logo', $file->filepath),
        );
        $form['delete'] = array(
          '#type' => 'checkbox',
          '#title' => t('Delete current logo'),
        );
      }
    }
    $form['upload'] = array(
      '#type' => 'file',
      '#title' => t('Upload logo'),
      '#size' => 30,
      '#description' => t('Upload a new logo for this space.'),
      '#element_validate' => array('spaces_design_upload_validate'),
    );
    $form['fid'] = array(
      '#type' => 'value',
      '#value' => !empty($value['fid']) ? $value['fid'] : 0,
    );

    return $form;
  }

  function validate($space, $value) { return $value; }

  function submit($space, $value) {
    // Always clear out upload key -- not used
    unset($value['upload']);

    // Delete logo if specified
    if (!empty($value['delete']) && !empty($value['file'])) {
      file_delete($value['file']->filepath);
      db_query('DELETE FROM {files} WHERE fid = %d', $value['file']->fid);

      // Clear out fields
      if ($value['file']->fid == $value['fid']) {
        unset($value['fid']);
      }
      unset($value['delete']);
      unset($value['file']);
    }

    // Flush imagecache images
    if (!empty($value['fid'])) {
      $file = db_fetch_object(db_query('SELECT * FROM {files} f WHERE f.fid = %d', $value['fid']));
      if ($file) {
        imagecache_image_flush($file->filepath);
      }
    }
    // Clear out fid if logo is omitted
    else {
      unset($value['fid']);
    }
    return $value;
  }
}

/**
 * Provides a color pallette for each space.
 */
class space_setting_color implements space_setting {
  var $id;

  function __construct($id = NULL) {
    $this->id = 'color';
  }

  function form($space, $value = array()) {
    $form = array(
      '#theme' => 'spaces_design_colorpicker',
      '#title' => t('Colors'),
      '#description' => t('Enter an RGB hexidecimal value like <strong>#ffffff</strong>. Leave blank to use the default colors for this space.'),
      '#type' => 'textfield',
      '#size' => '7',
      '#maxlength' => '7',
      '#default_value' => $value ? $value : '#',
    );
    return $form;
  }

  function validate($space, $value) { return $value; }

  function submit($space, $value) {
    // Clear out values if the color is invalid
    if (!_spaces_design_validate_color($value)) {
      $value = '';
    }
    return $value;
  }
}

/**
 * Element validator for logo upload. Actually handles file creation and
 * value setting tasks all at once.
 */
function spaces_design_upload_validate($element, &$form_state) {
  // If required, validate the uploaded picture.
  $validators = array(
    'file_validate_is_image' => array(),
    'file_validate_image_resolution' => array('600x600'),
    'file_validate_size' => array(1000 * 1024),
  );

  // @TODO: the first argument is troublesome -- the upload is registered in the
  // global $_FILES array under the 'settings' key -- probably because this
  // is the root level key in the form. Look into changing this...
  if ($file = file_save_upload('settings', $validators, file_directory_path())) {

    // Remove the old picture.
    if (isset($form_state['values']['space']->settings['logo']['fid'])) {
      $old_file = $form_state['values']['space']->settings['logo']['file'];
      if (file_exists($old_file->filepath)) {
        file_delete($old_file->filepath);
        db_query('DELETE FROM {files} WHERE fid = %d', $old_file->fid);
      }
    }

    // Uploaded file was not an image, set an error
    if ($error = file_validate_is_image($file)) {
      form_set_error($error);

      file_delete($file->filepath);
      db_query('DELETE FROM {files} WHERE fid = %d', $file->fid);
      $form_state['values']['settings']['logo']['fid'] = 0;
    }
    else {
      file_set_status($file, 1);
      $form_state['values']['settings']['logo']['fid'] = $file->fid;

      // Retrieve autocolor for logo and see if it makes sense to populate the color field.
      if ($autocolor = _spaces_design_image_autocolor($file->filepath)) {
        $form_state['values']['settings']['color'] = $autocolor;
      }
    }
  }
}

