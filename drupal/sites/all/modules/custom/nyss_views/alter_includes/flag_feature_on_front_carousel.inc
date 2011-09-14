<?php
/*
 * View 'flag_feature_on_front_carousel'
 */
$view = new view;
$view->name = 'flag_feature_on_front_carousel';
$view->description = 'View for flag: Feature on front carousel';
$view->tag = 'flag';
$view->view_php = '';
$view->base_table = 'node';
$view->is_cacheable = FALSE;
$view->api_version = 2;
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->override_option('relationships', array(
  'flag_content_rel' => array(
    'label' => 'feature_on_front_carousel',
    'required' => 1,
    'flag' => 'feature_on_front_carousel',
    'user_scope' => 'any',
    'id' => 'flag_content_rel',
    'table' => 'node',
    'field' => 'flag_content_rel',
    'relationship' => 'none',
    'override' => array(
      'button' => 'Override',
    ),
  ),
  'field_feature_image_fid' => array(
    'label' => 'Feature image',
    'required' => 1,
    'delta' => -1,
    'id' => 'field_feature_image_fid',
    'table' => 'node_data_field_feature_image',
    'field' => 'field_feature_image_fid',
    'relationship' => 'none',
  ),
));
$handler->override_option('fields', array(
  'field_feature_image_fid' => array(
    'label' => '',
    'link_to_node' => 1,
    'label_type' => 'none',
    'format' => 'front_carousel_linked',
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
  'title' => array(
    'label' => '',
    'link_to_node' => 1,
    'exclude' => 0,
    'id' => 'title',
    'table' => 'node',
    'field' => 'title',
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
      'button' => 'Override',
    ),
  ),
));
$handler->override_option('filters', array(
  'status' => array(
    'operator' => '=',
    'value' => 1,
    'group' => '0',
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
    ),
    'id' => 'status',
    'table' => 'node',
    'field' => 'status',
    'relationship' => 'none',
  ),
));
$handler->override_option('access', array(
  'type' => 'none',
));
$handler->override_option('cache', array(
  'type' => 'none',
));
$handler->override_option('title', 'Feature on front carousel');
$handler->override_option('items_per_page', 5);
$handler->override_option('use_pager', '0');
$handler->override_option('style_plugin', 'list');
$handler->override_option('style_options', array(
  'grouping' => '',
  'type' => 'ul',
));
$handler = $view->new_display('page', 'Carousel', 'page_1');
$handler->override_option('path', 'flags/feature_on_front_carousel');
$handler->override_option('menu', array(
  'type' => 'none',
  'title' => 'Feature on front carousel',
  'description' => '',
  'weight' => '0',
  'name' => 'navigation',
));
$handler->override_option('tab_options', array(
  'type' => 'none',
  'title' => NULL,
  'description' => '',
  'weight' => NULL,
  'name' => 'navigation',
));
$handler = $view->new_display('page', 'Page', 'page_2');
$handler->override_option('fields', array(
  'title' => array(
    'label' => '',
    'link_to_node' => 1,
    'exclude' => 0,
    'id' => 'title',
    'table' => 'node',
    'field' => 'title',
    'relationship' => 'none',
  ),
  'ops' => array(
    'id' => 'ops',
    'table' => 'flag_content',
    'field' => 'ops',
    'relationship' => 'flag_content_rel',
  ),
));
$handler->override_option('items_per_page', 50);
$handler->override_option('style_plugin', 'table');
$handler->override_option('style_options', array(
  'grouping' => '',
  'override' => 1,
  'sticky' => 0,
  'order' => 'asc',
  'columns' => array(
    'title' => 'title',
    'ops' => 'ops',
  ),
  'info' => array(
    'title' => array(
      'sortable' => 0,
      'separator' => '',
    ),
    'ops' => array(
      'separator' => '',
    ),
  ),
  'default' => '-1',
));
$handler->override_option('path', 'featured-carousel');
$handler->override_option('menu', array(
  'type' => 'none',
  'title' => '',
  'description' => '',
  'weight' => 0,
  'name' => 'navigation',
));
$handler->override_option('tab_options', array(
  'type' => 'none',
  'title' => '',
  'description' => '',
  'weight' => 0,
  'name' => 'navigation',
));
$handler = $view->new_display('block', 'Block: Administrative list', 'block_1');
$handler->override_option('fields', array(
  'title' => array(
    'label' => 'Title',
    'link_to_node' => 1,
    'exclude' => 0,
    'id' => 'title',
    'table' => 'node',
    'field' => 'title',
    'relationship' => 'none',
    'override' => array(
      'button' => 'Use default',
    ),
  ),
  'field_feature_image_fid' => array(
    'label' => 'Image',
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
    'label' => 'Ops',
    'exclude' => 0,
    'id' => 'ops',
    'table' => 'flag_content',
    'field' => 'ops',
    'relationship' => 'flag_content_rel',
    'override' => array(
      'button' => 'Use default',
    ),
  ),
  'edit_node' => array(
    'label' => 'Edit',
    'text' => '',
    'exclude' => 0,
    'id' => 'edit_node',
    'table' => 'node',
    'field' => 'edit_node',
    'override' => array(
      'button' => 'Use default',
    ),
    'relationship' => 'none',
  ),
));
$handler->override_option('title', 'Featured on front carousel');
$handler->override_option('use_pager', 'mini');
$handler->override_option('style_plugin', 'table');
$handler->override_option('style_options', array(
  'grouping' => '',
  'override' => 1,
  'sticky' => 0,
  'order' => 'asc',
  'columns' => array(
    'title' => 'title',
    'field_feature_image_fid' => 'field_feature_image_fid',
    'ops' => 'ops',
    'edit_node' => 'ops',
  ),
  'info' => array(
    'title' => array(
      'sortable' => 0,
      'separator' => '',
    ),
    'field_feature_image_fid' => array(
      'separator' => '',
    ),
    'ops' => array(
      'separator' => '| ',
    ),
    'edit_node' => array(
      'separator' => '',
    ),
  ),
  'default' => '-1',
));
$handler->override_option('block_description', '');
$handler->override_option('block_caching', -1);
$handler = $view->new_display('feed', 'Carousel RSS', 'feed_1');
$handler->override_option('style_plugin', 'rss');
$handler->override_option('style_options', array(
  'mission_description' => FALSE,
  'description' => '',
));
$handler->override_option('row_plugin', 'node_rss');
$handler->override_option('row_options', array(
  'relationship' => 'none',
  'item_length' => 'default',
));
$handler->override_option('path', 'front_carousel/rss');
$handler->override_option('menu', array(
  'type' => 'none',
  'title' => '',
  'description' => '',
  'weight' => 0,
  'name' => 'navigation',
));
$handler->override_option('tab_options', array(
  'type' => 'none',
  'title' => '',
  'description' => '',
  'weight' => 0,
  'name' => 'navigation',
));
$handler->override_option('displays', array(
  'page_2' => 'page_2',
  'default' => 0,
  'page_1' => 0,
  'block_1' => 0,
  'page_3' => 0,
  'page_4' => 0,
));
$handler->override_option('sitename_title', FALSE);
$views[$view->name] = $view;
