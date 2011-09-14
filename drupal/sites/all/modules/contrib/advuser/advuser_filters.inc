<?php
/**
 * @file
 * Advanced user module allows you to select users based on an advanced set of
 * filtering and apply actions to block, unblock, delete or email the selected
 * users.
 *
 * $Id: advuser_filters.inc,v 1.2.2.3 2009/06/23 15:33:25 earnie Exp $
 **/

/**
 * Return form for advuser administration filters.
 */
function advuser_filter_form() {
  $session = &$_SESSION['advuser_overview_filter'];
  $session = is_array($session) ? $session : array();
  $filters = advuser_filters();

  $i = 0;
  $form['filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Show only users where'),
    '#theme' => 'advuser_filters',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  foreach ($session as $filter) {
    list($type, $value, $op, $qop) = $filter;
    // Merge an array of arrays into one if necessary.
    if ($filters[$type]['form_type'] == 'select') {
      $options = $type == 'permission' 
               ? call_user_func_array(
                  'array_merge', 
                  $filters[$type]['options']
                 ) 
               : $filters[$type]['options']
      ;
      $params = array(
        '%property' => $filters[$type]['title'],
        '%value' => $options[$value]
      );
    } else {
      $params = array(
        '%property' => $filters[$type]['title'], 
        '%value' => $value
      );
    }
    if ($i++ > 0) {
      $form['filters']['current'][] = array(
        '#value' => t('<em>'.
                      $op.
                      '</em> where <strong>%property</strong> '.
                      _qop($qop).
                      ' <strong>%value</strong>',
                      $params
                     ).
                    ($i == count($session) ? ')' : ''), 
      );
    }
    else {
      $form['filters']['current'][] = array(
        '#value' => t('(<strong>%property</strong> '.
                      _qop($qop).
                      ' <strong>%value</strong>',
                      $params
                     ).
                    ($i == count($session) ? ')' : ''), 
      );
    }
  }


  foreach ($filters as $key => $filter) {
    $names[$key] = $filter['title'];
    switch ($filter['form_type']) {
      case 'select': {
        $form['filters']['status'][$key] = array(
          '#type' => 'select',
          '#options' => $filter['options'],
        );
      } break;
      case 'date': {
        $form['filters']['status'][$key] = array(
          '#type' => 'textfield',
          '#size' => 20,
          '#maxlength' => 25,
          '#default_value' => 'now',
          '#description' => 'You can enter this as an actual date (e.g. "'. date('M d Y') .'") or how long ago (e.g. "1 month 4 day 13hours ago")',
        );
      } break;
      case 'id': {
        $form['filters']['status'][$key] = array(
          '#type' => 'textfield',
          '#size' => 5,
          '#maxsize' => 10,
        );
      } break;
      case 'textfield': {
        $form['filters']['status'][$key] = array(
          '#type' => 'textfield',
          '#size' => 30,
        );
      } break;
      default: {
        $autocomplete = '';
        if ($filter['autocomplete']) {
          $autocomplete = "profile/autocomplete/". $filter['autocomplete'];
        }
        switch ($filter['type']) {
          case 'selection': {
            $form['filters']['status'][$key] = array(
              '#type' => 'select',
              '#options' => $filter['options'],
              '#autocomplete_path' => $autocomplete,
            );
          } break;
          case 'checkbox': {
            $form['filters']['status'][$key] = array(
              '#type' => 'checkbox',
            );
          } break;
          default: {
            $form['filters']['status'][$key] = array(
              '#type' => $filter['type'],
              '#options' => $filter['options'],
              '#autocomplete_path' => $autocomplete,
              '#size' => 20,
            );
          } break;
        } //End switch ($filter['type']).
      } break;
    }
  }

  $form['filters']['filter'] = array(
    '#type' => 'radios',
    '#options' => $names,
  );
  $form['filters']['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => (count($session) ? t('Refine') : t('Filter'))
  );
  if (count($session)) {
    $form['filters']['buttons']['undo'] = array(
      '#type' => 'submit',
      '#value' => t('Undo')
    );
    $form['filters']['buttons']['reset'] = array(
      '#type' => 'submit',
      '#value' => t('Reset')
    );
  }

  $form['filters']['filters_ops'] = array(
    '#type' => 'select',
    '#options' => array('AND' => t('and'), ') OR (' => t('or'))
  );

  $form['filters']['filters_qops'] = array(
    '#type' => 'select',
    '#options' => array(
      '=' => 'EQ', 
      '!=' => 'NE', 
      '<' => 'LT', 
      '>' => 'GT',
      '<=' => 'LE',
      '>=' => 'GE',
      'LIKE' => 'CO',
      'NOT LIKE' => 'NC', 
      'BEGINS WITH' => 'BE',
      'ENDS WITH' => 'EN',
    ),
    '#attributes' => array('title' => t("
      'EQ' => 'is equal to'
      'NE' => 'is not equal to'
      'LT' => 'is less than'
      'GT' => 'is greater than'
      'LE' => 'is less than or equal to'
      'GE' => 'is greater than or equal to'
      'CO' => 'contains'
      'NC' => 'does not contain'
      'BE' => 'begins with'
      'EN' => 'ends with'")
    ),
  );

  return $form;
}

/**
 * Helper function for translating symbols to language
 */
function _qop($qop) {
  static $_qop = NULL;
  if (!isset($_qop)) {
    $_qop = array(
      '=' => t('is equal to'),
      '!=' => t('is not equal to'),
      '<' => t('is less than'),
      '>' => t('is greater than'),
      '<=' => t('is less than or equal to'),
      '>=' => t('is greater than or equal to'),
      'LIKE' => t('contains'),
      'NOT LIKE' => t('does not contain'),
      'BEGINS WITH' => t('begins with'),
      'ENDS WITH' => t('ends with'),
    );
  }
  return isset($_qop[$qop]) ? $_qop[$qop] : $qop;
};

/**
 * Theme advuser administration filter form.
 */
function theme_advuser_filter_form($form) {
  $output = '<div id="user-admin-filter">';
  $output .= drupal_render($form['filters']);
  $output .= '</div>';
  $output .= drupal_render($form);
  return $output;
}

/**
 * Validate values entered.
 */
function advuser_filter_form_validate($form, &$form_state) {
  $ret = FALSE;
 
  if ($form_state['#id'] == 'advuser_filter_form') {
    switch ($form_state['values']['filter']) {
      case 'last_access': {
        switch (strtolower($form_state['values']['last_access'])) {
          case 'never': {
            $form_state['values']['last_access'] = 0;
            $ret = TRUE;
          } break;;

          case '0': {
            $ret = TRUE;
          } break;

          default: {
            if (!empty($form_state['values']['last_access']) && strtotime($form_state['values']['last_access']) <= 0) {
              form_set_error('date', t('You have to specify a valid date to filter by Accessed.'));
              $ret = FALSE;
            }
            else {
              $form_state['values']['last_access'] = strtotime($form_state['values']['last_access']);
              $ret = TRUE;
            }
          } break;
        }
      } break;

      case 'created': {
        if (!empty($form_state['values']['created']) && strtotime($form_state['values']['created']) <= 0) {
          form_set_error('date', t('You have to specify a valid date to filter by Created.'));
          $ret = FALSE;
        }
        else {
          $form_state['values']['created'] = strtotime($form_state['values']['created']);
          $ret = TRUE;
        }

      } break;
    }
  }
  return $ret;
}

/**
 * List advuser administration filters that can be applied.
 */
function advuser_filters() {
  // Regular filters
  $filters = array();
  $options = array();
  $t_module = t('module');
  foreach (module_list() as $module) {
    if ($permissions = module_invoke($module, 'perm')) {
      asort($permissions);
      foreach ($permissions as $permission) {
        $options["$module $t_module"][$permission] = t($permission);
      }
    }
  }

  ksort($options);
  $filters['permission'] = array(
    'title' => t('Permission'),
    'where' => " ((u.uid %in (SELECT ur.uid FROM {users_roles} ur WHERE ur.rid %in (SELECT p.rid FROM {permission} p WHERE p.perm %op '%s'))) %andor u.uid %eq 1)",
    'options' => $options,
    'form_type' => 'select',
  );

  $filters['status'] = array(
    'title' => t('Status'),
    'where' => "u.status %op '%s'",
    'options' => array(1 => t('active'), 0 => t('blocked')),
    'form_type' => 'select',
  );

  $filters['created'] = array(
    'title' => t('Created'),
    'where' => "u.created %op '%s'",
    'form_type' => 'date',
  );

  $filters['last_access'] = array(
    'title' => t('Accessed'),
    'where' => "u.access %op '%s'",
    'form_type' => 'date',
  );

  $filters['email'] = array(
    'title' => t('Email'),
    'where' => "u.mail %op '%s'",
    'form_type' => 'textfield',
  );

  $filters['uid'] = array(
    'title' => t('User Id'),
    'where' => "u.uid %op %d",
    'form_type' => 'id',
  );

  $filters['username'] = array(
    'title' => t('Username'),
    'where' => "u.name %op '%s'",
    'form_type' => 'textfield',
  );

  $roles = advuser_user_roles();
  if (count($roles)) {
    $filters['user_roles'] = array(
      'title' => t('Role'),
      'where' => "ur.rid %op %d",
      'form_type' => 'select',
      'options' => $roles,
    );
  }

  $profile_fields = advuser_profile_fields();
  foreach ($profile_fields as $field) {
    // Build array of options if they exist
    $opts = NULL;
    if ( ! empty($field->options) ) {
      $opts = array();
      foreach ( explode("\n", $field->options) as $opt ) {
        $opt = trim($opt);
        $opts[$opt] = $opt;
      }
    }
    // Each user defined profile field needs a unique table identifier for the
    //  JOIN and WHERE clauses.
    // TODO: Make sure the $field->name contains valid information for a table
    //  identifier.  This comment is to identify the source of a problem yet 
    //  to be discovered.
    $pv = $field->name;
    $filters[$field->name] = array(
      'title' => check_plain($field->title),
      'type' => $field->type,
      'class' => $field->name,
      'where' => "$pv.value %op '%s' AND $pv.uid = u.uid",
      'options' => $opts,
      'autocomplete' => $field->autocomplete ? $field->fid : FALSE,
    );
  }
  return $filters;
}

/**
 * Build query for advuser administration filters based on session.
 */
function advuser_build_filter_query() {
  $filters = advuser_filters();

  // Build query
  $where = $args = $join = array();

  foreach ($_SESSION['advuser_overview_filter'] as $filter) {
    list($key, $value, $op, $qop) = $filter;
    // This checks to see if this permission filter is an enabled permission 
    // for the authenticated role.  If so, then all users would be listed, and 
    // we can skip adding it to the filter query.
    switch ($key) {
      case 'permission': {
        $account = new stdClass();
        $account->uid = 'advuser_filter';
        $account->roles = array(DRUPAL_AUTHENTICATED_RID => 1);
        if (user_access($value, $account)) {
          continue;
        }
      } break;
      case 'created':
      case 'last_access': {
        $value = strtotime($value);
      } break;
    }

    $arg_prefix = $arg_suffix = NULL;
    switch ($qop) {
      case 'NOT LIKE':
      case 'LIKE': {
        $arg_prefix = $arg_suffix = '%';
      } break;
      case 'BEGINS WITH': {
        $qop = 'LIKE';
        $arg_suffix = '%';
      } break;
      case 'ENDS WITH': {
        $qop = 'LIKE';
        $arg_prefix = '%';
      } break;
    }

    switch ($qop) {
      case '!=':
      case 'NOT LIKE': {
        $in = 'NOT IN';
        $eq = '!=';
        $andor = 'AND';
      } break;
      default: {
        $in = 'IN';
        $eq = '=';
        $andor = 'OR';
      }
    }

    $_where = $op.' '.str_ireplace("%op", $qop, $filters[$key]['where']);
    $_where = str_ireplace("%eq", $eq, $_where);
    $_where = str_ireplace("%andor", $andor, $_where);
    $where[] = str_ireplace("%in", $in, $_where);
    $args[] = $arg_prefix . $value . $arg_suffix;
    $join[] = $filters[$key]['join'];
  }

  $where = count($where) ? 'AND ('. implode(' ', $where) . ')' : '';
  $join = count($join) ? ' '. implode(' ', array_unique($join)) : '';

  return array(
    'where' => $where,
    'join' => $join,
    'args' => $args,
  );
}

/**
 * Process result from user administration filter form.
 */
function advuser_filter_form_submit($form, &$form_state) {
  $op = $form_state['values']['op'];
  $filters = advuser_filters();
  $ret = 'admin/user/user/advuser';

  switch ($op) {
    case t('Undo'): 
      array_pop($_SESSION['advuser_overview_filter']);
      break;
    case t('Reset'): 
      $_SESSION['advuser_overview_filter'] = array();
      break;
    case t('Update'): 
      $ret = NULL;
      break;
    case t('Filter'):
    case t('Refine'):
    default:
      if (isset($form_state['values']['filter'])) {
        $filter = $form_state['values']['filter'];
        if ($filters[$filter]['form_type'] == 'select') {
          // Merge an array of arrays into one if necessary.
          $options = $filter == 'permission' ? call_user_func_array('array_merge', $filters[$filter]['options']) : $filters[$filter]['options'] ;
          if (isset($options[$form_state['values'][$filter]])) {
            $_SESSION['advuser_overview_filter'][] = array(
              $filter, 
              $form_state['values'][$filter], 
              $form_state['values']['filters_ops'], 
              $form_state['values']['filters_qops'],
            );
          }
        } else {
          if (isset($form_state['values'][$filter])) {
            $_SESSION['advuser_overview_filter'][] = array(
               $filter, 
               $form_state['values'][$filter], 
               $form_state['values']['filters_ops'], 
               $form_state['values']['filters_qops']
            );
          }
        }
      }
      break;
  }
  $form_state['#redirect'] = $ret;
}

/**
 * Theme user administration filter selector.
 */
function theme_advuser_filters($form) {

  $output = '<ul>';
  if (sizeof($form['current'])) {
    foreach (element_children($form['current']) as $key) {
      $output .= '<li>' . drupal_render($form['current'][$key]) . '</li>';
    }
  }
  $output .= '</ul>';

  $output .= '<div class="container-inline" id="user-admin-buttons">' . drupal_render($form['buttons']) . '</div>';
  $output .= '<br/><br/>';
  $output .= '<table class="multiselect ">';
  foreach (element_children($form['filter']) as $key) {
    $output .= '<tr>';
    $output .= '<td>' . (sizeof($form['current']) ? drupal_render($form['filters_ops']) : '') . '</td>';
    $output .= '<td class="a">' . drupal_render($form['filter'][$key]) . '</td>';
    $output .= '<td>' . $f . drupal_render($form['filters_qops']) . '</td>';
    $output .= '<td class="b">' . drupal_render($form['status'][$key]) . '</td>';
    $output .= '</tr>';
  }

  foreach (element_children($form['status']) as $key) {
    $output .= drupal_render($form['status'][$key]);
  }
  $output .= '</td></tr>';

  $output .= '</table>';

  return $output;
}

// vim:ft=php:sts=2:sw=2:ts=2:et:ai:sta:ff=unix
