<?php

/**
 * Helper to implementation of hook_content_default_fields().
 */
function _nyss_organization_content_default_fields() {
  $fields = array();

  // Exported field: field_cta_html
  $fields[] = array(
    'field_name' => 'field_cta_html',
    'type_name' => 'initiative',
    'display_settings' => array(
      'weight' => '4',
      'parent' => '',
      '2' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => '3',
      'size' => 60,
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_cta_html][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'CTA HTML',
      'weight' => '6',
      'description' => '',
      'type' => 'text_textarea',
      'module' => 'text',
    ),
  );

  // Exported field: field_extra_images
  $fields[] = array(
    'field_name' => 'field_extra_images',
    'type_name' => 'initiative',
    'display_settings' => array(
      'weight' => '2',
      'parent' => '',
      '2' => array(
        'format' => 'image_plain',
        'exclude' => 1,
      ),
      '3' => array(
        'format' => 'image_plain',
        'exclude' => 1,
      ),
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '3',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '0',
    'widget' => array(
      'file_extensions' => 'jpg jpeg png gif',
      'file_path' => '',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'file_widgets' => NULL,
      'max_resolution' => 0,
      'min_resolution' => 0,
      'alt' => '',
      'custom_alt' => 0,
      'title' => '',
      'custom_title' => 0,
      'use_default_image' => 0,
      'progress_indicator' => 'bar',
      'title_type' => 'textfield',
      'label' => 'Extra Images',
      'weight' => '4',
      'description' => 'These extra images will not be available from anywhere but the bottom of this content page.',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Exported field: field_feature_image
  $fields[] = array(
    'field_name' => 'field_feature_image',
    'type_name' => 'initiative',
    'display_settings' => array(
      'weight' => 0,
      'parent' => '',
      '2' => array(
        'format' => 'image_plain',
        'exclude' => 1,
      ),
      '3' => array(
        'format' => 'image_plain',
        'exclude' => 1,
      ),
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '1',
    'widget' => array(
      'file_extensions' => 'jpg jpeg png gif',
      'file_path' => '',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'file_widgets' => NULL,
      'max_resolution' => 0,
      'min_resolution' => 0,
      'alt' => '',
      'custom_alt' => 0,
      'title' => '',
      'custom_title' => 0,
      'use_default_image' => 0,
      'url' => '',
      'custom_target' => 0,
      'target' => '_self',
      'progress_indicator' => 'bar',
      'title_type' => 'textfield',
      'nofollow' => 0,
      'label' => 'Feature image',
      'weight' => 0,
      'description' => '',
      'type' => 'linkimagefield_widget',
      'module' => 'linkimagefield',
    ),
  );

  // Exported field: field_hide_upcoming_events
  $fields[] = array(
    'field_name' => 'field_hide_upcoming_events',
    'type_name' => 'initiative',
    'display_settings' => array(
      'weight' => '19',
      'parent' => 'group_committee_controls',
      '4' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'number_integer',
    'required' => '0',
    'multiple' => '0',
    'module' => 'number',
    'active' => '1',
    'prefix' => '',
    'suffix' => '',
    'min' => '0',
    'max' => '1',
    'allowed_values' => '0|Show Upcoming Events block
1|Hide Upcoming Events block',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => 0,
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Hide Upcoming Events',
      'weight' => '1',
      'description' => 'Check this box if you want to prevent the "Upcoming Events" block from appearing in the left-hand sidebar of web pages related to this initiative.',
      'type' => 'optionwidgets_onoff',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_sidebar_html
  $fields[] = array(
    'field_name' => 'field_sidebar_html',
    'type_name' => 'initiative',
    'display_settings' => array(
      'weight' => '3',
      'parent' => '',
      '2' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => '3',
      'size' => 60,
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_sidebar_html][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Sidebar HTML',
      'weight' => '5',
      'description' => '',
      'type' => 'text_textarea',
      'module' => 'text',
    ),
  );

  // Exported field: field_title_image
  $fields[] = array(
    'field_name' => 'field_title_image',
    'type_name' => 'initiative',
    'display_settings' => array(
      'weight' => '6',
      'parent' => '',
      '2' => array(
        'format' => 'image_plain',
        'exclude' => 1,
      ),
      '3' => array(
        'format' => 'image_plain',
        'exclude' => 1,
      ),
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '0',
    'widget' => array(
      'file_extensions' => 'png gif jpg jpeg',
      'file_path' => '',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'max_resolution' => 0,
      'min_resolution' => 0,
      'alt' => '',
      'custom_alt' => 0,
      'title' => '',
      'custom_title' => 0,
      'title_type' => 'textfield',
      'default_image' => NULL,
      'use_default_image' => 0,
      'label' => 'Custom Title Image',
      'weight' => '8',
      'description' => '',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Exported field: field_top_image
  $fields[] = array(
    'field_name' => 'field_top_image',
    'type_name' => 'initiative',
    'display_settings' => array(
      'weight' => '1',
      'parent' => '',
      '2' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'linkimage_urllink',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'linkimage_urllink',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'linkimage_urllink',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'linkimage_urllink',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'linkimage_urllink',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '0',
    'widget' => array(
      'file_extensions' => 'png gif jpg jpeg',
      'file_path' => '',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'max_resolution' => 0,
      'min_resolution' => 0,
      'alt' => '',
      'custom_alt' => 0,
      'title' => '',
      'custom_title' => 0,
      'title_type' => 'textfield',
      'default_image' => NULL,
      'use_default_image' => 0,
      'url' => '',
      'custom_target' => 0,
      'target' => '_self',
      'nofollow' => 0,
      'label' => 'Top Image',
      'weight' => '3',
      'description' => 'If there is an image in this field, it will appear at the top of the Initiative page. Otherwise, the Featured Image will be used.',
      'type' => 'linkimagefield_widget',
      'module' => 'linkimagefield',
    ),
  );

  // Exported field: field_twitter_feed
  $fields[] = array(
    'field_name' => 'field_twitter_feed',
    'type_name' => 'initiative',
    'display_settings' => array(
      'weight' => '5',
      'parent' => '',
      '2' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '120',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_twitter_feed][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Twitter Feed',
      'weight' => '7',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_district
  $fields[] = array(
    'field_name' => 'field_district',
    'type_name' => 'organization',
    'display_settings' => array(
      'weight' => '3',
      'parent' => 'group_categories',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '0',
    'multiple' => '1',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'district' => 'district',
      'blog' => 0,
      'cable_broadcast' => 0,
      'campaign' => 0,
      'committee' => 0,
      'community_project_fund' => 0,
      'story' => 0,
      'event' => 0,
      'expenditure_report' => 0,
      'feed' => 0,
      'group' => 0,
      'in_the_news' => 0,
      'initiative' => 0,
      'legislation' => 0,
      'outline' => 0,
      'page' => 0,
      'panel' => 0,
      'payroll' => 0,
      'photo' => 0,
      'poll' => 0,
      'press_release' => 0,
      'report' => 0,
      'senator' => 0,
      'testimony' => 0,
      'transcript' => 0,
      'video' => 0,
      'webform' => 0,
      'organization' => FALSE,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => 60,
      'default_value' => array(
        '0' => array(
          'nid' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'District',
      'weight' => '6',
      'description' => 'You may optionally select one or more districts that this content may reference.',
      'type' => 'nodereference_select',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_facebook_link
  $fields[] = array(
    'field_name' => 'field_facebook_link',
    'type_name' => 'organization',
    'display_settings' => array(
      'weight' => '8',
      'parent' => 'group_social_bookmarks',
      '2' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'link',
    'required' => '0',
    'multiple' => '0',
    'module' => 'link',
    'active' => '1',
    'attributes' => array(
      'target' => 'default',
      'rel' => '',
      'class' => 'facebook',
    ),
    'display' => array(
      'url_cutoff' => '80',
    ),
    'url' => 0,
    'title' => 'none',
    'title_value' => '',
    'enable_tokens' => 0,
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'url' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Facebook link',
      'weight' => '8',
      'description' => 'Please enter the URL to this organization\'s Facebook page, if it exists.',
      'type' => 'link',
      'module' => 'link',
    ),
  );

  // Exported field: field_feature_image
  $fields[] = array(
    'field_name' => 'field_feature_image',
    'type_name' => 'organization',
    'display_settings' => array(
      'weight' => 0,
      'parent' => 'group_media_resources',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'image_plain',
        'exclude' => 1,
      ),
      '3' => array(
        'format' => 'image_plain',
        'exclude' => 1,
      ),
      '4' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '1',
    'widget' => array(
      'file_extensions' => 'jpg jpeg png gif',
      'file_path' => '',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'max_resolution' => 0,
      'min_resolution' => 0,
      'alt' => '',
      'custom_alt' => 0,
      'title' => '',
      'custom_title' => 0,
      'title_type' => 'textfield',
      'default_image' => NULL,
      'use_default_image' => 0,
      'url' => '',
      'custom_target' => 0,
      'target' => '_self',
      'nofollow' => 0,
      'file_widgets' => NULL,
      'label' => 'Feature image',
      'weight' => '-1',
      'description' => '',
      'type' => 'linkimagefield_widget',
      'module' => 'linkimagefield',
    ),
  );

  // Exported field: field_flickr_link
  $fields[] = array(
    'field_name' => 'field_flickr_link',
    'type_name' => 'organization',
    'display_settings' => array(
      'weight' => '12',
      'parent' => 'group_social_bookmarks',
      '2' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'link',
    'required' => '0',
    'multiple' => '0',
    'module' => 'link',
    'active' => '1',
    'attributes' => array(
      'target' => 'default',
      'rel' => '',
      'class' => 'flickr',
    ),
    'display' => array(
      'url_cutoff' => '80',
    ),
    'url' => 0,
    'title' => 'none',
    'title_value' => '',
    'enable_tokens' => 0,
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'url' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Flickr Link',
      'weight' => '12',
      'description' => 'Please enter the URL to this organization\'s Flickr page, if it exists.',
      'type' => 'link',
      'module' => 'link',
    ),
  );

  // Exported field: field_initiative
  $fields[] = array(
    'field_name' => 'field_initiative',
    'type_name' => 'organization',
    'display_settings' => array(
      'weight' => '5',
      'parent' => 'group_categories',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '0',
    'multiple' => '0',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'initiative' => 'initiative',
      'blog' => 0,
      'campaign' => 0,
      'committee' => 0,
      'community_project_fund' => 0,
      'story' => 0,
      'district' => 0,
      'event' => 0,
      'expenditure_report' => 0,
      'feed' => 0,
      'group' => 0,
      'in_the_news' => 0,
      'legislation' => 0,
      'outline' => 0,
      'page' => 0,
      'panel' => 0,
      'payroll' => 0,
      'photo' => 0,
      'poll' => 0,
      'press_release' => 0,
      'report' => 0,
      'senator' => 0,
      'testimony' => 0,
      'transcript' => 0,
      'video' => 0,
      'webform' => 0,
      'cable_broadcast' => FALSE,
      'organization' => FALSE,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => 60,
      'default_value' => array(
        '0' => array(
          'nid' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Initiative',
      'weight' => '7',
      'description' => '',
      'type' => 'nodereference_select',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_location
  $fields[] = array(
    'field_name' => 'field_location',
    'type_name' => 'organization',
    'display_settings' => array(
      'weight' => '-3',
      'parent' => '',
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'location',
    'required' => '0',
    'multiple' => '0',
    'module' => 'location_cck',
    'active' => '1',
    'location_settings' => array(
      'form' => array(
        'fields' => array(
          'name' => array(
            'collect' => '1',
            'default' => '',
            'weight' => '-100',
          ),
          'street' => array(
            'collect' => '1',
            'default' => '',
            'weight' => '-99',
          ),
          'additional' => array(
            'collect' => '1',
            'default' => '',
            'weight' => '-98',
          ),
          'city' => array(
            'collect' => '1',
            'default' => '',
            'weight' => '-97',
          ),
          'province' => array(
            'collect' => '1',
            'default' => '',
            'weight' => '-96',
          ),
          'postal_code' => array(
            'collect' => '1',
            'default' => '',
            'weight' => '-95',
          ),
          'phone' => array(
            'collect' => '1',
            'default' => '',
            'weight' => '-94',
          ),
          'fax' => array(
            'collect' => '1',
            'default' => '',
            'weight' => '-93',
          ),
          'locpick' => array(
            'collect' => '1',
            'weight' => '-92',
          ),
          'country' => array(
            'collect' => '4',
            'default' => 'us',
            'weight' => '-91',
          ),
        ),
      ),
      'display' => array(
        'hide' => array(
          'province_name' => 'province_name',
          'country_name' => 'country_name',
          'coords' => 'coords',
          'name' => 0,
          'street' => 0,
          'additional' => 0,
          'city' => 0,
          'province' => 0,
          'postal_code' => 0,
          'country' => 0,
          'locpick' => 0,
          'fax' => 0,
          'phone' => 0,
          'map_link' => 0,
        ),
      ),
    ),
    'gmap_macro' => '[gmap]',
    'gmap_marker' => 'drupal',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'name' => '',
          'street' => '',
          'additional' => '',
          'city' => '',
          'province' => '',
          'postal_code' => '',
          'phone' => '',
          'fax' => '',
          'locpick' => array(
            'user_latitude' => '',
            'user_longitude' => '',
          ),
          'cck_preview_in_progress' => TRUE,
          'location_settings' => array(
            'form' => array(
              'fields' => array(
                'name' => array(
                  'default' => '',
                  'collect' => '1',
                  'weight' => '-100',
                ),
                'street' => array(
                  'default' => '',
                  'collect' => '1',
                  'weight' => '-99',
                ),
                'additional' => array(
                  'default' => '',
                  'collect' => '1',
                  'weight' => '-98',
                ),
                'city' => array(
                  'default' => '',
                  'collect' => '1',
                  'weight' => '-97',
                ),
                'province' => array(
                  'default' => '',
                  'collect' => '1',
                  'weight' => '-96',
                ),
                'postal_code' => array(
                  'default' => '',
                  'collect' => '1',
                  'weight' => '-95',
                ),
                'phone' => array(
                  'default' => '',
                  'collect' => '1',
                  'weight' => '-94',
                ),
                'fax' => array(
                  'default' => '',
                  'collect' => '1',
                  'weight' => '-93',
                ),
                'locpick' => array(
                  'default' => array(
                    'user_latitude' => '',
                    'user_longitude' => '',
                  ),
                  'collect' => '1',
                  'weight' => '-92',
                  'nodiff' => TRUE,
                ),
                'country' => array(
                  'default' => 'us',
                  'collect' => '4',
                  'weight' => '-91',
                ),
                'cck_preview_in_progress' => array(
                  'default' => TRUE,
                ),
                'location_settings' => array(
                  'default' => array(
                    'form' => array(
                      'fields' => array(
                        'name' => array(
                          'default' => '',
                          'collect' => '1',
                          'weight' => '-100',
                        ),
                        'street' => array(
                          'default' => '',
                          'collect' => '1',
                          'weight' => '-99',
                        ),
                        'additional' => array(
                          'default' => '',
                          'collect' => '1',
                          'weight' => '-98',
                        ),
                        'city' => array(
                          'default' => '',
                          'collect' => '1',
                          'weight' => '-97',
                        ),
                        'province' => array(
                          'default' => '',
                          'collect' => '1',
                          'weight' => '-96',
                        ),
                        'postal_code' => array(
                          'default' => '',
                          'collect' => '1',
                          'weight' => '-95',
                        ),
                        'phone' => array(
                          'default' => '',
                          'collect' => '1',
                          'weight' => '-94',
                        ),
                        'fax' => array(
                          'default' => '',
                          'collect' => '1',
                          'weight' => '-93',
                        ),
                        'locpick' => array(
                          'default' => array(
                            'user_latitude' => '',
                            'user_longitude' => '',
                          ),
                          'collect' => '1',
                          'weight' => '-92',
                          'nodiff' => TRUE,
                        ),
                        'country' => array(
                          'default' => 'us',
                          'collect' => '4',
                          'weight' => '-91',
                        ),
                        'location_settings' => array(
                          'default' => array(
                            'form' => array(
                              'weight' => '0',
                              'collapsible' => 1,
                              'collapsed' => 1,
                              'fields' => array(
                                'name' => array(
                                  'default' => '',
                                  'collect' => 1,
                                  'weight' => '2',
                                ),
                                'street' => array(
                                  'default' => '',
                                  'collect' => 1,
                                  'weight' => '4',
                                ),
                                'additional' => array(
                                  'default' => '',
                                  'collect' => 1,
                                  'weight' => '6',
                                ),
                                'city' => array(
                                  'default' => '',
                                  'collect' => 0,
                                  'weight' => '8',
                                ),
                                'province' => array(
                                  'default' => '',
                                  'collect' => 0,
                                  'weight' => '10',
                                ),
                                'postal_code' => array(
                                  'default' => '',
                                  'collect' => 0,
                                  'weight' => '12',
                                ),
                                'country' => array(
                                  'default' => 'us',
                                  'collect' => 1,
                                  'weight' => '14',
                                ),
                                'lid' => array(
                                  'default' => FALSE,
                                ),
                                'latitude' => array(
                                  'default' => 0,
                                ),
                                'longitude' => array(
                                  'default' => 0,
                                ),
                                'source' => array(
                                  'default' => 0,
                                ),
                                'is_primary' => array(
                                  'default' => 0,
                                ),
                              ),
                            ),
                            'display' => array(
                              'weight' => '0',
                              'hide' => array(
                                'name' => 0,
                                'street' => 0,
                                'additional' => 0,
                                'city' => 0,
                                'province' => 0,
                                'postal_code' => 0,
                                'country' => 0,
                                'province_name' => 0,
                                'country_name' => 0,
                                'map_link' => 0,
                                'coords' => 0,
                              ),
                            ),
                          ),
                        ),
                        'lid' => array(
                          'default' => FALSE,
                        ),
                        'latitude' => array(
                          'default' => 0,
                        ),
                        'longitude' => array(
                          'default' => 0,
                        ),
                        'source' => array(
                          'default' => 0,
                        ),
                        'is_primary' => array(
                          'default' => 0,
                        ),
                        'delete_location' => array(
                          'default' => FALSE,
                          'nodiff' => TRUE,
                        ),
                      ),
                    ),
                    'display' => array(
                      'hide' => array(
                        'name' => 0,
                        'street' => 0,
                        'additional' => 0,
                        'city' => 0,
                        'province' => 0,
                        'postal_code' => 0,
                        'country' => 0,
                        'locpick' => 0,
                        'fax' => 0,
                        'phone' => 0,
                        'province_name' => 0,
                        'country_name' => 0,
                        'map_link' => 0,
                        'coords' => 0,
                      ),
                    ),
                  ),
                ),
                'lid' => array(
                  'default' => FALSE,
                ),
                'latitude' => array(
                  'default' => 0,
                ),
                'longitude' => array(
                  'default' => 0,
                ),
                'source' => array(
                  'default' => 0,
                ),
                'is_primary' => array(
                  'default' => 0,
                ),
                'delete_location' => array(
                  'default' => FALSE,
                  'nodiff' => TRUE,
                ),
              ),
            ),
            'display' => array(
              'hide' => array(
                'name' => 0,
                'street' => 0,
                'additional' => 0,
                'city' => 0,
                'province' => 0,
                'postal_code' => 0,
                'country' => 0,
                'locpick' => 0,
                'fax' => 0,
                'phone' => 0,
                'province_name' => 0,
                'country_name' => 0,
                'map_link' => 0,
                'coords' => 0,
              ),
            ),
          ),
          'country' => 'us',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Location',
      'weight' => '-3',
      'description' => '',
      'type' => 'location',
      'module' => 'location_cck',
    ),
  );

  // Exported field: field_myspace_link
  $fields[] = array(
    'field_name' => 'field_myspace_link',
    'type_name' => 'organization',
    'display_settings' => array(
      'weight' => '10',
      'parent' => 'group_social_bookmarks',
      '2' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'link',
    'required' => '0',
    'multiple' => '0',
    'module' => 'link',
    'active' => '1',
    'attributes' => array(
      'target' => 'default',
      'rel' => '',
      'class' => 'myspace',
    ),
    'display' => array(
      'url_cutoff' => '80',
    ),
    'url' => 0,
    'title' => 'none',
    'title_value' => '',
    'enable_tokens' => 0,
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'url' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'MySpace Link',
      'weight' => '10',
      'description' => 'Please enter the URL to this organization\'s MySpace page, if it exists.',
      'type' => 'link',
      'module' => 'link',
    ),
  );

  // Exported field: field_picasa_link
  $fields[] = array(
    'field_name' => 'field_picasa_link',
    'type_name' => 'organization',
    'display_settings' => array(
      'weight' => '13',
      'parent' => 'group_social_bookmarks',
      '2' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'link',
    'required' => '0',
    'multiple' => '0',
    'module' => 'link',
    'active' => '1',
    'attributes' => array(
      'target' => 'default',
      'rel' => '',
      'class' => 'picasa',
    ),
    'display' => array(
      'url_cutoff' => '80',
    ),
    'url' => 0,
    'title' => 'none',
    'title_value' => '',
    'enable_tokens' => 0,
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'url' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Picasa Link',
      'weight' => '13',
      'description' => 'Please enter the URL to this organization\'s Picasa page, if it exists.',
      'type' => 'link',
      'module' => 'link',
    ),
  );

  // Exported field: field_senator
  $fields[] = array(
    'field_name' => 'field_senator',
    'type_name' => 'organization',
    'display_settings' => array(
      'weight' => '2',
      'parent' => 'group_categories',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '0',
    'multiple' => '0',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'senator' => 'senator',
      'blog' => 0,
      'campaign' => 0,
      'committee' => 0,
      'story' => 0,
      'district' => 0,
      'event' => 0,
      'feed' => 0,
      'group' => 0,
      'in_the_news' => 0,
      'legislation' => 0,
      'outline' => 0,
      'page' => 0,
      'photo' => 0,
      'poll' => 0,
      'press_release' => 0,
      'report' => 0,
      'testimony' => 0,
      'transcript' => 0,
      'video' => 0,
      'webform' => 0,
      'community_project_fund' => FALSE,
      'expenditure_report' => FALSE,
      'initiative' => FALSE,
      'panel' => FALSE,
      'payroll' => FALSE,
      'cable_broadcast' => FALSE,
      'organization' => FALSE,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => 60,
      'default_value' => NULL,
      'default_value_php' => NULL,
      'label' => 'Senator',
      'weight' => '5',
      'description' => 'Begin typing the name of the senator that you want this content associated with and select senator from list that appears.',
      'type' => 'nodereference_autocomplete',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_twitter_link
  $fields[] = array(
    'field_name' => 'field_twitter_link',
    'type_name' => 'organization',
    'display_settings' => array(
      'weight' => '9',
      'parent' => 'group_social_bookmarks',
      '2' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'link',
    'required' => '0',
    'multiple' => '0',
    'module' => 'link',
    'active' => '1',
    'attributes' => array(
      'target' => 'default',
      'rel' => '',
      'class' => 'twitter',
    ),
    'display' => array(
      'url_cutoff' => '80',
    ),
    'url' => 0,
    'title' => 'none',
    'title_value' => '',
    'enable_tokens' => 0,
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'url' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Twitter link',
      'weight' => '9',
      'description' => 'Please enter the URL for this organization\'s Twitter page, if it exists.',
      'type' => 'link',
      'module' => 'link',
    ),
  );

  // Exported field: field_youtube_link
  $fields[] = array(
    'field_name' => 'field_youtube_link',
    'type_name' => 'organization',
    'display_settings' => array(
      'weight' => '11',
      'parent' => 'group_social_bookmarks',
      '2' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'link',
    'required' => '0',
    'multiple' => '0',
    'module' => 'link',
    'active' => '1',
    'attributes' => array(
      'target' => 'default',
      'rel' => '',
      'class' => 'youtube',
    ),
    'display' => array(
      'url_cutoff' => '80',
    ),
    'url' => 0,
    'title' => 'none',
    'title_value' => '',
    'enable_tokens' => 0,
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'url' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'YouTube Link',
      'weight' => '11',
      'description' => 'Please enter the URL to this organization\'s YouTube page, if it exists.',
      'type' => 'link',
      'module' => 'link',
    ),
  );

  // Translatables
  array(
    t('CTA HTML'),
    t('Custom Title Image'),
    t('District'),
    t('Extra Images'),
    t('Facebook link'),
    t('Feature image'),
    t('Flickr Link'),
    t('Hide Upcoming Events'),
    t('Initiative'),
    t('Location'),
    t('MySpace Link'),
    t('Picasa Link'),
    t('Senator'),
    t('Sidebar HTML'),
    t('Top Image'),
    t('Twitter Feed'),
    t('Twitter link'),
    t('YouTube Link'),
  );

  return $fields;
}

/**
 * Helper to implementation of hook_fieldgroup_default_groups().
 */
function _nyss_organization_fieldgroup_default_groups() {
  $groups = array();

  // Exported group: group_images
  $groups[] = array(
    'group_type' => 'standard',
    'type_name' => 'organization',
    'group_name' => 'group_images',
    'label' => 'Images',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'label' => 'above',
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '0',
    'fields' => array(
      '0' => 'field_feature_image',
    ),
  );

  // Exported group: group_relationships
  $groups[] = array(
    'group_type' => 'standard',
    'type_name' => 'organization',
    'group_name' => 'group_relationships',
    'label' => 'Related to',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'label' => 'above',
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '1',
    'fields' => array(
      '0' => 'field_senator',
      '1' => 'field_district',
      '2' => 'field_initiative',
    ),
  );

  // Exported group: group_social_bookmarks
  $groups[] = array(
    'group_type' => 'standard',
    'type_name' => 'organization',
    'group_name' => 'group_social_bookmarks',
    'label' => 'Social Bookmarks',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 1,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 1,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'above',
      ),
    ),
    'weight' => '2',
    'fields' => array(
      '0' => 'field_facebook_link',
      '1' => 'field_twitter_link',
      '2' => 'field_myspace_link',
      '3' => 'field_youtube_link',
      '4' => 'field_flickr_link',
      '5' => 'field_picasa_link',
    ),
  );

  // Translatables
  array(
    t('Images'),
    t('Related to'),
    t('Social Bookmarks'),
  );

  return $groups;
}

/**
 * Helper to implementation of hook_imagecache_default_presets().
 */
function _nyss_organization_imagecache_default_presets() {
  $items = array(
    'full_node_featured_image' => array(
      'presetname' => 'full_node_featured_image',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '545',
            'height' => '',
            'upscale' => 0,
          ),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Helper to implementation of hook_user_default_permissions().
 */
function _nyss_organization_user_default_permissions() {
  $permissions = array();

  // Exported permission: create initiative content
  $permissions[] = array(
    'name' => 'create initiative content',
    'roles' => array(
      '0' => 'Web Editor',
      '1' => 'Web Editor+',
      '2' => 'admin',
    ),
  );

  // Exported permission: create organization content
  $permissions[] = array(
    'name' => 'create organization content',
    'roles' => array(),
  );

  // Exported permission: delete any initiative content
  $permissions[] = array(
    'name' => 'delete any initiative content',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: delete any organization content
  $permissions[] = array(
    'name' => 'delete any organization content',
    'roles' => array(),
  );

  // Exported permission: delete own initiative content
  $permissions[] = array(
    'name' => 'delete own initiative content',
    'roles' => array(
      '0' => 'Web Editor',
      '1' => 'Web Editor+',
      '2' => 'admin',
    ),
  );

  // Exported permission: delete own organization content
  $permissions[] = array(
    'name' => 'delete own organization content',
    'roles' => array(),
  );

  // Exported permission: edit any initiative content
  $permissions[] = array(
    'name' => 'edit any initiative content',
    'roles' => array(
      '0' => 'Office Editor',
      '1' => 'Web Editor',
      '2' => 'Web Editor+',
      '3' => 'admin',
    ),
  );

  // Exported permission: edit any organization content
  $permissions[] = array(
    'name' => 'edit any organization content',
    'roles' => array(),
  );

  // Exported permission: edit own initiative content
  $permissions[] = array(
    'name' => 'edit own initiative content',
    'roles' => array(
      '0' => 'Web Editor',
      '1' => 'Web Editor+',
      '2' => 'admin',
    ),
  );

  // Exported permission: edit own organization content
  $permissions[] = array(
    'name' => 'edit own organization content',
    'roles' => array(),
  );

  return $permissions;
}
