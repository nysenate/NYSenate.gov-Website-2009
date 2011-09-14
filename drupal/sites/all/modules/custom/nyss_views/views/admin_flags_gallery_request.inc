<?php
  /*
   * View 'admin_flags_gallery_request'
   */
  $view = new view;
  $view->name = 'admin_flags_gallery_request';
  $view->description = 'An administrator\'s list of content requested to be promoted to the main Senate Gallery page.';
  $view->tag = 'admin';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'flag_content_rel' => array(
      'label' => 'Request to promote to main gallery',
      'required' => 1,
      'flag' => 'request_to_gallery',
      'user_scope' => 'any',
      'id' => 'flag_content_rel',
      'table' => 'node',
      'field' => 'flag_content_rel',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'flag_content_rel_1' => array(
      'label' => 'Promoted to Main Senate Gallery',
      'required' => 0,
      'flag' => 'promote_to_main_gallery',
      'user_scope' => 'any',
      'id' => 'flag_content_rel_1',
      'table' => 'node',
      'field' => 'flag_content_rel',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('fields', array(
    'title' => array(
      'label' => 'Post',
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'field_feature_image_fid' => array(
      'label' => 'Photo',
      'link_to_node' => 0,
      'label_type' => 'custom',
      'format' => 'senator_teaser_imagelink',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_feature_image_fid',
      'table' => 'node_data_field_feature_image',
      'field' => 'field_feature_image_fid',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'field_senator_nid' => array(
      'label' => 'Senator',
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_senator_nid',
      'table' => 'node_data_field_senator',
      'field' => 'field_senator_nid',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'ops' => array(
      'label' => 'Promote',
      'exclude' => 0,
      'id' => 'ops',
      'table' => 'flag_content',
      'field' => 'ops',
      'relationship' => 'flag_content_rel_1',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'ops_1' => array(
      'label' => 'Deny request',
      'exclude' => 0,
      'id' => 'ops_1',
      'table' => 'flag_content',
      'field' => 'ops',
      'relationship' => 'flag_content_rel',
    ),
    'edit_node' => array(
      'label' => 'Ops',
      'text' => 'edit content',
      'exclude' => 0,
      'id' => 'edit_node',
      'table' => 'node',
      'field' => 'edit_node',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
  ));
  $handler->override_option('sorts', array(
    'timestamp' => array(
      'order' => 'DESC',
      'granularity' => 'second',
      'id' => 'timestamp',
      'table' => 'flag_content',
      'field' => 'timestamp',
      'relationship' => 'flag_content_rel',
      'override' => array(
        'button' => 'Override',
      ),
    ),
  ));
  $handler->override_option('filters', array(
    'flagged' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'flagged',
      'table' => 'flag_content',
      'field' => 'flagged',
      'relationship' => 'flag_content_rel',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'flagged_1' => array(
      'operator' => '=',
      'value' => '0',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'flagged_1',
      'table' => 'flag_content',
      'field' => 'flagged',
      'relationship' => 'flag_content_rel_1',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'role',
    'role' => array(
      '3' => 3,
      '5' => 5,
    ),
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Senate carousel administration');
  $handler->override_option('header', 'Content that has been marked with the \'request to promote photo to main gallery\' by an office editor will appear on this page.');
  $handler->override_option('header_format', '1');
  $handler->override_option('header_empty', 1);
  $handler->override_option('empty', 'There are currently no items for review for promotion to the gallery.');
  $handler->override_option('empty_format', '1');
  $handler->override_option('items_per_page', 50);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'title' => 'title',
      'field_feature_image_fid' => 'field_feature_image_fid',
      'field_senator_nid' => 'field_senator_nid',
      'ops' => 'edit_node',
      'ops_1' => 'edit_node',
      'edit_node' => 'edit_node',
    ),
    'info' => array(
      'title' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'field_feature_image_fid' => array(
        'separator' => '',
      ),
      'field_senator_nid' => array(
        'separator' => '',
      ),
      'ops' => array(
        'separator' => '',
      ),
      'ops_1' => array(
        'separator' => '',
      ),
      'edit_node' => array(
        'separator' => '| ',
      ),
    ),
    'default' => '-1',
  ));
  $handler = $view->new_display('page', 'Page: Gallery Administration', 'page_1');
  $handler->override_option('title', 'Senate gallery administration');
  $handler->override_option('path', 'admin/content/nyss/gallery');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'Photos',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
  ));
  $handler = $view->new_display('page', 'Page: Video Gallery Administration', 'page_2');
  $handler->override_option('relationships', array(
    'flag_content_rel' => array(
      'label' => 'Request to promote video to main gallery',
      'required' => 1,
      'flag' => 'request_video_to_gallery',
      'user_scope' => 'any',
      'id' => 'flag_content_rel',
      'table' => 'node',
      'field' => 'flag_content_rel',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'flag_content_rel_1' => array(
      'label' => 'Promoted to Main Senate Video Gallery',
      'required' => 0,
      'flag' => 'promote_video_to_main_gallery',
      'user_scope' => 'any',
      'id' => 'flag_content_rel_1',
      'table' => 'node',
      'field' => 'flag_content_rel',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('fields', array(
    'title' => array(
      'label' => 'Post',
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'field_video_embed' => array(
      'label' => 'Video',
      'link_to_node' => 0,
      'label_type' => 'custom',
      'format' => 'thickbox',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_video_embed',
      'table' => 'node_data_field_video',
      'field' => 'field_video_embed',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'field_senator_nid' => array(
      'label' => 'Senator',
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_senator_nid',
      'table' => 'node_data_field_senator',
      'field' => 'field_senator_nid',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'ops' => array(
      'label' => 'Promote',
      'exclude' => 0,
      'id' => 'ops',
      'table' => 'flag_content',
      'field' => 'ops',
      'relationship' => 'flag_content_rel_1',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'ops_1' => array(
      'label' => 'Deny request',
      'exclude' => 0,
      'id' => 'ops_1',
      'table' => 'flag_content',
      'field' => 'ops',
      'relationship' => 'flag_content_rel',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'edit_node' => array(
      'label' => 'Edit',
      'text' => 'edit content',
      'exclude' => 0,
      'id' => 'edit_node',
      'table' => 'node',
      'field' => 'edit_node',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'timestamp' => array(
      'order' => 'DESC',
      'granularity' => 'second',
      'id' => 'timestamp',
      'table' => 'flag_content',
      'field' => 'timestamp',
      'relationship' => 'flag_content_rel',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('filters', array(
    'flagged' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'flagged',
      'table' => 'flag_content',
      'field' => 'flagged',
      'relationship' => 'flag_content_rel',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'flagged_1' => array(
      'operator' => '=',
      'value' => '0',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'flagged_1',
      'table' => 'flag_content',
      'field' => 'flagged',
      'relationship' => 'flag_content_rel_1',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('title', 'Senate video gallery administration');
  $handler->override_option('header', 'Content that has been marked with the \'request to promote video to main gallery\' by an office editor will appear on this page.');
  $handler->override_option('empty', 'There are currently no items for review for promotion to the video gallery.');
  $handler->override_option('path', 'admin/content/nyss/video');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'Video',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
  ));
  $handler = $view->new_display('page', 'Page: Front Carousel Administration', 'page_3');
  $handler->override_option('relationships', array(
    'flag_content_rel' => array(
      'label' => 'Promoted to a Senator\'s Carousel',
      'required' => 1,
      'flag' => 'senator_carousel',
      'user_scope' => 'any',
      'id' => 'flag_content_rel',
      'table' => 'node',
      'field' => 'flag_content_rel',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'flag_content_rel_1' => array(
      'label' => 'Promoted to Front Senate Carousel',
      'required' => 0,
      'flag' => 'feature_on_front_carousel',
      'user_scope' => 'any',
      'id' => 'flag_content_rel_1',
      'table' => 'node',
      'field' => 'flag_content_rel',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('fields', array(
    'title' => array(
      'label' => 'Post',
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'field_feature_image_fid' => array(
      'label' => 'Photo',
      'link_to_node' => 0,
      'label_type' => 'custom',
      'format' => 'imagefield__lightshow2__senator_teaser__front_carousel',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_feature_image_fid',
      'table' => 'node_data_field_feature_image',
      'field' => 'field_feature_image_fid',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'field_senator_nid' => array(
      'label' => 'Senator',
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_senator_nid',
      'table' => 'node_data_field_senator',
      'field' => 'field_senator_nid',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'ops' => array(
      'label' => 'Promote',
      'exclude' => 0,
      'id' => 'ops',
      'table' => 'flag_content',
      'field' => 'ops',
      'relationship' => 'flag_content_rel_1',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'edit_node' => array(
      'label' => 'Ops',
      'text' => 'edit content',
      'exclude' => 0,
      'id' => 'edit_node',
      'table' => 'node',
      'field' => 'edit_node',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('sorts', array(
    'timestamp' => array(
      'order' => 'DESC',
      'granularity' => 'second',
      'id' => 'timestamp',
      'table' => 'flag_content',
      'field' => 'timestamp',
      'relationship' => 'flag_content_rel',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('header', 'Content that has been marked with the "feature on senator\'s carousel" flag by an office editor will appear on this page. You may promote content from this list to the front carousel using the "Feature on front carousel" flag next to the appropriate image.');
  $handler->override_option('empty', 'There are currently no items that have been promoted to any Senator\'s carousel.');
  $handler->override_option('path', 'admin/content/nyss/carousel');
  $handler->override_option('menu', array(
    'type' => 'default tab',
    'title' => 'Carousel',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'normal',
    'title' => 'NYSS Promoted Content',
    'description' => '',
    'weight' => '0',
  ));
  $views[$view->name] = $view;

