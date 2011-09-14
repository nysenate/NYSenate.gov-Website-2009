<?php
// $Id: spaces.spaces.inc,v 1.1.2.4 2010/02/09 18:31:34 yhahn Exp $

/**
 * Provides a homepage setting for each space.
 */
class space_setting_home implements space_setting {
  var $id;
  function __construct($id = NULL) {
    if ($id) {
      $this->id = $id;
    }
    else {
      $this->id = 'home';
    }
  }

  function form($space, $value = array()) {
    $options = array(0 => '---');

    // This is exceedingly hackish but effective way of ensuring that
    // the link options provided are correct, especially when being
    // generated on preset forms.
    $original = spaces_get_space();
    spaces_set_space($space, TRUE);
    $links = menu_navigation_links('features');
    spaces_set_space($original, TRUE);

    $form = array();
    if (count($links)) {
      foreach ($links as $link) {
        $options[$link['href']] = $link['title'];
      }
      $form = array(
        '#title' => t('Homepage'),
        '#description' => t('The default page for this space.'),
        '#type' => 'select',
        '#options' => $options,
        '#default_value' => $value ? $value : 0,
      );
    }
    return $form;
  }

  function validate($space, $value) {
    // Exclude space "prototypes" (like that used for the preset form)
    /*
    if ($space->sid) {
      if (!$value && is_array($space->features) && (array_sum($space->features) != 0)) {
        form_set_error('settings]['. $this->id, t('You must select a homepage for this space.'));
      }
    }
    */
  }

  function submit($space, $value) {
    return $value;
  }
}

/**
 * Customizer for feature menus.
 */
class space_customizer_menu implements space_customizer {

  var $name = 'Menu';

  function form($space, $feature) {
    $menu = spaces_features_items('menu', $feature);
    if (!empty($menu)) {
      $form = array();
      $menu_items = menu_navigation_links('features');
      $default_items = $menu_items;
      $this->customize($space, $menu_items);
      foreach ($menu_items as $key => $item) {
        if (in_array($item['href'], $menu)) {
          $form[$item['href']] = array(
            '#title' => $item['href'],
            '#type' => 'fieldset',
            '#tree' => TRUE,
          );
          $form[$item['href']]['title'] = array(
            '#title' => t('Title'),
            '#type' => 'textfield',
            '#size' => 40,
            '#maxlength' => 255,
            '#default_value' => $item['title'],
          );
          $form[$item['href']]['default'] = array(
            '#type' => 'value',
            '#value' => $default_items[$key]['title'],
          );
        }
      }
    }
    return $form;
  }

  function validate($space, $feature, $value) {
    return;
  }

  function submit($space, $feature, $value) {
    $customizer = $space->customizer['menu'];
    foreach ($value as $path => $item) {
      if ($item['title'] == $item['default']) {
        unset($customizer[$path]);
      }
      else if ($item['title'] != $item['default']) {
        $customizer[$path] = $item['title'];
      }
    }
    return $customizer;
  }

  function customize($space, &$menu = NULL) {
    foreach ($menu as $k => $item) {
      if (!empty($space->customizer['menu'][$item['href']])) {
        $menu[$k]['title'] = $space->customizer['menu'][$item['href']];
      }
    }
  }
}

/**
 * Customizer for feature blocks.
 */
class space_customizer_block implements space_customizer {

  var $name = 'Blocks';
  var $info = array();

  /**
   * Helper method to return the block info.
   */
  function get_block_info($module, $delta) {
    if (!isset($this->info[$module])) {
      $this->info[$module] = module_invoke($module, 'block', 'list');

      // If the block is provided by Views, doctor the info to strip out the
      // view name leaving only the block's display name.
      if ($module == 'views') {
        foreach ($this->info[$module] as $k => $v) {
          $viewname = strpos($v['info'], ':');
          if ($viewname !== FALSE) {
            $v['info'] = substr($v['info'], $viewname + 2);
            $this->info[$module][$k] = $v;
          }
        }
      }
    }
    return !empty($this->info[$module][$delta]['info']) ? $this->info[$module][$delta]['info'] : '';
  }

  /**
   * Implementation of form().
   */
  function form($space, $feature) {
    global $theme_key;
    init_theme();
    $regions = system_region_list($theme_key);

    // Collect all contexts associated with this feature
    $feature_contexts = drupal_map_assoc(spaces_features_items('context', $feature));
    $contexts = context_enabled_contexts();
    $contexts = array_intersect_key($contexts, $feature_contexts);

    $master_contexts = array();
    $master_defaults = array();

    foreach ($contexts as $identifier => $context) {
      if (!empty($context->block)) {

        // Get customized values -- unfortunately we can't use our own customization
        // methods as block customization is a bit more complex.
        $customizer = !empty($space->customizer['block'][$identifier]) ? $space->customizer['block'][$identifier] : array();
        $subject = !empty($space->customizer['block']['subject']) ? $space->customizer['block']['subject'] : array();

        $form = array( '#title' => $identifier, '#tree' => TRUE);
        $defaults = array('#tree' => TRUE);

        foreach ($context->block as $i => $block) {
          // @TODO: remove this once context is less confused about itself.
          $block = (array) $block;
          $bid = "{$block['module']}-{$block['delta']}";

          // Sanity check that this region exists
          if (!empty($block['region']) && !empty($regions[$block['region']])) {
            $region = $block['region'];
            if (!isset($form[$region])) {
              $form[$region] = array('#title' => $regions[$region], '#tree' => TRUE);
            }

            $block_details = module_invoke($block['module'], 'block', 'view', $block['delta']);
            $default_subject = !empty($block_details['subject']) ? $block_details['subject'] : '';
            $default_weight = isset($block[$i]['weight']) ? $block[$i]['weight'] : 0;
            $default_status = isset($block[$i]['status']) ? $block[$i]['status'] : 1;

            // Store defaults to compare against changed values in submit handler
            $defaults[$region][$bid]['weight'] = array('#type' => 'value', '#value' => $default_weight);
            $defaults[$region][$bid]['status'] = array('#type' => 'value', '#value' => $default_status);
            $defaults[$region][$bid]['subject'] = array('#type' => 'value', '#value' => $default_subject);

            $form[$region][$bid] = array(
              '#tree' => TRUE,
              '#weight' => isset($customizer[$region][$bid]['weight']) ? $customizer[$region][$bid]['weight'] : 0,
            );
            $form[$region][$bid]['weight'] = array(
              '#type' => 'weight',
              '#delta' => 25,
              '#default_value' => isset($customizer[$region][$bid]['weight']) ? $customizer[$region][$bid]['weight'] : 0,
            );
            $form[$region][$bid]['status'] = array(
              '#type' => 'checkbox',
              '#default_value' => isset($customizer[$region][$bid]['status']) ? $customizer[$region][$bid]['status'] : 1,
            );
            // If the block subject is empty, it's likely to be for a good reason
            // e.g. the subject is generated dynamically or the block is slimmed
            // down. Let's respect that.
            if (!empty($default_subject)) {
              $form[$region][$bid]['subject'] = array(
                '#type' => 'textfield',
                '#default_value' => !empty($subject[$bid]) ? $subject[$bid] : $default_subject,
                '#description' => $this->get_block_info($block['module'], $block['delta']),
              );
            }
            else {
              $form[$region][$bid]['subject'] = array(
                '#type' => 'markup',
                '#value' => $this->get_block_info($block['module'], $block['delta']),
              );
            }
          }
        }

        $master_contexts[$identifier] = $form;
        $master_defaults[$identifier] = $defaults;
      }
    }

    if (!empty($master_contexts) && !empty($master_defaults)) {
      $master_form = array(
        '#theme' => 'spaces_block_customizer_settings_form',
        'contexts' => array_merge(array('#tree' => TRUE), $master_contexts),
        'defaults' => array_merge(array('#tree' => TRUE), $master_defaults),
      );
      return $master_form;
    }
    else {
      return NULL;
    }
  }

  /**
   * Implementation of validate().
   */
  function validate($space, $feature, $value) {
    return;
  }

  /**
   * Implementation of submit().
   * Iterate through and only record the aspects of each block that have been customized.
   */
  function submit($space, $feature, $value) {
    $customizer = $space->customizer['block'];
    foreach ($value['contexts'] as $identifier => $context) {
      foreach ($context as $region => $blocks) {
        foreach ($blocks as $bid => $block) {
          foreach ($block as $k => $v) {
            // Clear out values that haven't changed from defaults
            if ($v === $value['defaults'][$identifier][$region][$bid][$k]) {
              unset($block[$k]);
            }
            // Store subjects "flatly"
            else if ($k == 'subject') {
              unset($block[$k]);
              $customizer['subject'][$bid] = $v;
            }
          }
          if (!empty($block)) {
            $customizer[$identifier][$region][$bid] = $block;
          }
        }
      }
    }
    return $customizer;
  }

  /**
   * Implementation of customize().
   */
  function customize($space, $identifier, &$block = NULL) {
    // Unset disabled blocks and change weights based on customizer settings. See spaces_context_active_contexts_alter.
    if (!empty($space->customizer['block'][$identifier])) {
      $customizer = $space->customizer['block'][$identifier];
      foreach ($block as $key => $b) {
        // @TODO: remove this once context is less confused about itself.
        $b = (array) $b;
        $block[$key] = (array) $block[$key];
        $bid = "{$b['module']}-{$b['delta']}";
        // If the block is not enabled, yank it out of the blocks array
        if (!empty($customizer[$b['region']][$bid])) {
          if (isset($customizer[$b['region']][$bid]['status']) && $customizer[$b['region']][$bid]['status'] === 0) {
            unset($block[$key]);
          }
          if (isset($customizer[$b['region']][$bid]['weight'])) {
            $block[$key]['weight'] = $customizer[$b['region']][$bid]['weight'];
          }
        }
      }
    }
  }

  /**
   * Additional method: customize_subject() for customizing a block subject.
   */
  function customize_subject($space, &$block) {
    $bid = "{$block->module}-{$block->delta}";
    if (!empty($space->customizer['block']['subject'][$bid])) {
      $block->subject = $space->customizer['block']['subject'][$bid];
    }
  }
}
