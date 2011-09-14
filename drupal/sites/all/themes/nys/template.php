<?php
// $Id: template.php,v 1.17 2008/09/11 10:52:53 johnalbin Exp $

/**
 * @file
 * Contains theme override functions and preprocess functions for the theme.
 *
 * ABOUT THE TEMPLATE.PHP FILE
 *
 *   The template.php file is one of the most useful files when creating or
 *   modifying Drupal themes. You can add new regions for block content, modify
 *   or override Drupal's theme functions, intercept or make additional
 *   variables available to your theme, and create custom PHP logic. For more
 *   information, please visit the Theme Developer's Guide on Drupal.org:
 *   http://drupal.org/theme-guide
 *
 * OVERRIDING THEME FUNCTIONS
 *
 *   The Drupal theme system uses special theme functions to generate HTML
 *   output automatically. Often we wish to customize this HTML output. To do
 *   this, we have to override the theme function. You have to first find the
 *   theme function that generates the output, and then "catch" it and modify it
 *   here. The easiest way to do it is to copy the original function in its
 *   entirety and paste it here, changing the prefix from theme_ to nys_.
 *   For example:
 *
 *     original: theme_breadcrumb()
 *     theme override: nys_breadcrumb()
 *
 *   where nys is the name of your sub-theme. For example, the
 *   zen_classic theme would define a zen_classic_breadcrumb() function.
 *
 *   If you would like to override any of the theme functions used in Zen core,
 *   you should first look at how Zen core implements those functions:
 *     theme_breadcrumbs()      in zen/template.php
 *     theme_menu_item_link()   in zen/template.php
 *     theme_menu_local_tasks() in zen/template.php
 *
 *   For more information, please visit the Theme Developer's Guide on
 *   Drupal.org: http://drupal.org/node/173880
 *
 * CREATE OR MODIFY VARIABLES FOR YOUR THEME
 *
 *   Each tpl.php template file has several variables which hold various pieces
 *   of content. You can modify those variables (or add new ones) before they
 *   are used in the template files by using preprocess functions.
 *
 *   This makes THEME_preprocess_HOOK() functions the most powerful functions
 *   available to themers.
 *
 *   It works by having one preprocess function for each template file or its
 *   derivatives (called template suggestions). For example:
 *     THEME_preprocess_page    alters the variables for page.tpl.php
 *     THEME_preprocess_node    alters the variables for node.tpl.php or
 *                              for node-forum.tpl.php
 *     THEME_preprocess_comment alters the variables for comment.tpl.php
 *     THEME_preprocess_block   alters the variables for block.tpl.php
 *
 *   For more information on preprocess functions, please visit the Theme
 *   Developer's Guide on Drupal.org: http://drupal.org/node/223430
 *   For more information on template suggestions, please visit the Theme
 *   Developer's Guide on Drupal.org: http://drupal.org/node/223440 and
 *   http://drupal.org/node/190815#template-suggestions
 */


// COMMENT OUT BEFORE LAUNCH!  THIS IS FOR THEME DEVELOPMENT USAGE ONLY.
// drupal_rebuild_theme_registry();


/*
 * Add any conditional stylesheets you will need for this sub-theme.
 *
 * To add stylesheets that ALWAYS need to be included, you should add them to
 * your .info file instead. Only use this section if you are including
 * stylesheets based on certain conditions.
 */
/* -- Delete this line if you want to use and modify this code
// Example: optionally add a fixed width CSS file.
if (theme_get_setting('nys_fixed')) {
  drupal_add_css(path_to_theme() . '/layout-fixed.css', 'theme', 'all');
}
// */


/**
 * Implementation of HOOK_theme().
 */
function nys_theme(&$existing, $type, $theme, $path) {
  $hooks = zen_theme($existing, $type, $theme, $path);
  // Add your theme hooks like this:
  /*
  $hooks['hook_name_here'] = array( // Details go here );
  */
  // @TODO: Needs detailed comments. Patches welcome!
  $hooks['search_theme_form'] = array(
	// Forms always take the form argument.
      'arguments' => array('form' => NULL),
  );
  return $hooks;
}

/**
 * Override or insert variables into all templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered (name of the .tpl.php file.)
 */
/* -- Delete this line if you want to use this function
function nys_preprocess(&$vars, $hook) {
  $vars['sample_variable'] = t('Lorem ipsum.');
}
// */

/**
 * Override or insert variables into the page templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("page" in this case.)
 */
function nys_preprocess_page(&$vars, $hook) {
  if ($node = menu_get_object()) {
    $vars['node'] = $node;
  }
  else {
    $vars['node'] = FALSE;
  }

// RANDOM BACKGROUND FOR HEADER - change second number in the rand() function to the amount of background images there are to rotate randomly through
  $random_number = mt_rand(1,5);
  $vars['random_bg'] = 'bg-'.$random_number;
  $vars['senator'] = context_get('nyss', 'senator');
  $vars['senator_theme'] = '';
  if ($vars['senator']) {
    $vars['senator_analytics'] = nyss_senator_analytics($vars['senator']->nid);
    if ($vars['senator']->field_status[0]['value']) {
      drupal_set_message(nyss_senator_inactive_message($vars['senator']), 'status');
      $vars['messages'] .= theme('status_messages');
    }
    if ($vars['senator']->field_status[0]['value'] != 'former') {
     $vars['senator_theme'] = $vars['senator']->field_theme[0]['value']; 
    } else {
     $vars['senator_theme'] = 'grey';
    }
    if ($vars['senator']->field_senators_district[0]['nid']) {
      $vars['district'] = node_load($vars['senator']->field_senators_district[0]['nid']);
    }
  }

  // CUSTOM SEARCH PAGE TITLE
  if(isset($vars['template_files'][1]) && $vars['template_files'][1] == 'page-search-nyss_search') {
    $vars['title'] = t('Senator Search: ');
    if($vars['senator'] && $vars['senator']->title != '') {
      $vars['title'] .= $vars['senator']->title;
      $vars['instructions'] = '<p>' .
        t('You are searching for content by Senator !title. If you are looking for content by a different senator, search from within their page on !list.',
          array(
            '!title' => $vars['senator']->title,
            '!list' => l(t('this list'), 'senators')
          )
        ) . '</p>';
    }
    else {
      $vars['title'] .= t('No Senator Selected');
      $vars['instructions'] = '<p>' . t('You are searching for senator content, but have not selected a senator. Pick a senator from !list and search from within their page.', array('!list' => l(t('this list'), 'senators'))) . '</p>';
    }
  }
  // Build out the Party Affiliation tag, $party_affiliation_list, as seen in the Senator Header
  if ($vars['senator'] && is_array($vars['senator']->field_party_affiliation)) {
    $parties = array();
    foreach ($vars['senator']->field_party_affiliation as $party) {
      if ($party['value']) {
        $parties[] = $party['value'];
      }
    }
    $vars['party_affiliation_list'] = '('. implode(', ', $parties) .')';
  }

  // Create the main navigation menu.
  if ($vars['senator'] && count($vars['senator']->field_navigation)) {
    $vars['nyss_menu'] = nyss_senator_build_menu($vars['senator']);
  }
  else {
    // Render the default primary links using nice menu.
    $vars['nyss_menu'] = theme('nyss_misc_primary_menu');
  }
  $vars['nyss_footer_menu'] = theme('nyss_misc_footer_menu');
  // Build the Section Header variable based on arg() or node type for the page being viewed
  if ($vars['senator'] == FALSE && (arg(0) == 'blog')) {
    $vars['section_header'] = t('The New York Senate Blog');
  }
  if ($vars['senator'] == TRUE && (arg(2) == 'blog' || ($vars['node'] && $vars['node']->type == 'blog'))) {
    $vars['section_header'] = t('!title\'s Blog', array('!title' => $vars['senator']->title));
  }
  // Classes for body element. Allows advanced theming based on context
  // (home page, node of certain type, etc.)
  $body_classes = array($vars['body_classes']);
  if (!$vars['is_front']) {
    // Add unique classes for each page and website section
    $path = drupal_get_path_alias($_GET['q']);
    list($section, ) = explode('/', $path, 2);
    $body_classes[] = ('no-sidebars');
    $body_classes[] = zen_id_safe('page-' . $path);
    $body_classes[] = zen_id_safe('section-' . $section);
    if (arg(0) == 'node' && is_numeric(arg(1))) {
      $body_classes[] = 'full-node';
    }
    if (arg(0) != 'node') {
      $body_classes[] = 'not-node';
    }
    if (arg(0) == 'node') {
      if (arg(1) == 'add') {
        if ($section == 'node') {
          array_pop($body_classes); // Remove 'section-node'
        }
        $body_classes[] = 'section-node-add'; // Add 'section-node-add'
      }
      elseif (is_numeric(arg(1)) && (arg(2) == 'edit' || arg(2) == 'delete')) {
        if ($section == 'node') {
          array_pop($body_classes); // Remove 'section-node'
        }
        $body_classes[] = 'section-node-' . arg(2); // Add 'section-node-edit' or 'section-node-delete'
      }
    }
  }
  if (theme_get_setting('zen_wireframes')) {
    $body_classes[] = 'with-wireframes'; // Optionally add the wireframes style.
  }

  if ($vars['senator'] == TRUE) {
    $body_classes[] = 'senator'; // Class for a senator
    $vars['senator_name'] = l($vars['senator']->title . nyss_senator_status_for_title($vars['senator']), $vars['senator']->path);
  }
  if ($vars['senator'] == FALSE) {
    $body_classes[] = 'not-senator'; // Class for a non-senator
  }
  if ($vars['senator'] == TRUE && arg(2) == 'blog') {
    $body_classes[] = 'senator_blog'; // Class for a senator's blog
  }
  $vars['body_classes'] = implode(' ', $body_classes); // Concatenate with spaces
  if (!empty($vars['left_forms']) || !empty($vars['left'])) {
    $vars['body_classes'] = str_replace('no-sidebars', 'one-sidebar sidebar-left', $vars['body_classes']);
  }
}

/**
 * Override or insert variables into the node templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("node" in this case.)
 */

function nys_preprocess_node(&$vars, $hook) {
  $vars['senator'] = nyss_senator_node($vars['node']);
  if ($vars['senator'] && $vars['senator']->field_senators_district[0]['nid']) {
    $vars['district'] = node_load($vars['senator']->field_senators_district[0]['nid']);
  }
  if (module_exists('service_links')) {
    $vars['service_links'] = theme('links', service_links_render($vars['node'], TRUE));
  }
  if (module_exists('og')) {
    unset($vars['og_links']);
  }
  $vars['terms'] = nys_get_comma_tax_list($vars);
}

function nys_get_comma_tax_list($vars) {
  if (arg(0) == 'committee') {
    $schema = 'committee/'. check_plain(arg(1)) .'/issues/';
  }
  else {
    if (!empty($vars['senator'])) {
      $schema = 'senator/'. nyss_senator_title_to_url($vars['senator']) .'/issues/';
    }
    else {
      $schema = FALSE;
    }
  }

  if (empty($vars['node']->taxonomy))return;
  foreach ($vars['node']->taxonomy as $taxonomy) {
    if ($taxonomy->vid == 1) {
      if ($taxonomy->name == 'Miscellaneous') {
        break;
      }
      if ($schema) {
        $terms[$taxonomy->vid][$taxonomy->tid] = l($taxonomy->name, $schema . strtolower(str_replace(' ', '_', check_plain($taxonomy->name))));
      }
      else {
        $terms[$taxonomy->vid][$taxonomy->tid] = l($taxonomy->name, 'taxonomy/term/' . $taxonomy->tid);
      }
    }
  }
  $tax_terms_output = '<ul>';
  if(isset($terms)) {
    foreach ($terms as $vid => $terms) {
      $vocabulary = taxonomy_vocabulary_load($vid);
      $vocab_name = check_plain($vocabulary->name);
      $tax_terms_output .= '<li class="'. strtolower(str_replace(' ', '_', $vocab_name)) .'">';
      $tax_terms_output .= '<label>'. $vocab_name .'</label>';
      $tax_terms_output .= '<span class="term_list">'.implode(', ', $terms).'</span>';
      $tax_terms_output .= '</li>';
    }
  }
  $tax_terms_output .= '</ul>';
  return $tax_terms_output;
}

/**
 * Override or insert variables into the comment templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("comment" in this case.)
 */
/* -- Delete this line if you want to use this function
function nys_preprocess_comment(&$vars, $hook) {
  $vars['sample_variable'] = t('Lorem ipsum.');
}
// */

/**
 * Override or insert variables into the block templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("block" in this case.)
 */
/* -- Delete this line if you want to use this function
function nys_preprocess_block(&$vars, $hook) {
  $vars['sample_variable'] = t('Lorem ipsum.');
}
// */

function nys_preprocess_search_result(&$variables) {
  $result = $variables['result'];
  $variables['url'] = check_url($result['link']);
  $variables['title'] = check_plain($result['title']);
  $variables['node'] = $result['node'];
  $info = array();
  if (!empty($result['type'])) {
    $info['type'] = check_plain($result['type']);
  }
  if (!empty($result['user'])) {
    $info['user'] = $result['user'];
  }
  if (!empty($result['date'])) {
    $info['date'] = format_date($result['date'], 'small');
  }
  if (isset($result['extra']) && is_array($result['extra'])) {
    $info = array_merge($info, $result['extra']);
  }
  // Check for existence. User search does not include snippets.
  $variables['snippet'] = isset($result['snippet']) ? $result['snippet'] : '';
  // Provide separated and grouped meta information..
  $variables['info_split'] = $info;
  $variables['info'] = implode(' - ', $info);
  // Provide alternate search result template.
  $variables['template_files'][] = 'search-result-'. $variables['type'];
}


function nys_node_submitted($node) {
  $senator = nyss_senator($node);
  if ($senator && $senator->nid && isset($node->field_authored_by_senator) && $node->field_authored_by_senator[0]['value']) {
    $username = l($senator->title, 'node/'. $senator->nid);
  }
  else {
    $username = $node->name;
  }
  return t('Posted by !username on @datetime',
    array(
      '!username' => $username,
      '@datetime' => format_date($node->created, 'custom', 'l, F jS, Y'),
    ));
}

/**
 * Function for custom user login form.
 *
 **/

function nys_user_bar() {
  global $user;
  $output = '';

  if (!$user->uid) {
    $output .= (l(t('LOGIN'), 'user', array('title' => t('LOGIN'))) ."  OR  " .l(t('REGISTER'), 'user/register'));
  }
  else {
    $output .= l(t('MY ACCOUNT'), 'user/'.$user->uid, array('title' => t('Edit your account')))."&nbsp;&nbsp;&nbsp;&nbsp;" .(l(t('LOGOUT'), 'logout'));
  }

  $output = '<div id="user-bar">'.$output.'</div>';

  return $output;
}

/**
 * Function for Social Networking buttons, for Senators/Majority Leader
 *
 **/
function nys_social_buttons() {
  $output = '<div id="social_buttons"><a class="facebook" href=""></a><a class="twitter" href=""></a></div>';
  return $output;
}

/**
  * Theme override for search form.
  */
function nys_search_theme_form($form) {
  $before_focus = t('Search');
  // Set a default value in the search box, you can change 'search' to whatever you want - you can change/delete this
  $form['search_theme_form']['#value'] = $before_focus;
  // Additionally, hide the text when editing - you can change/delete this
  // Remember to change the value 'search' here too if you change it in the previous line
  $form['search_theme_form']['#attributes'] = array('onblur' => "if (this.value == '') {this.value = '" . $before_focus . "';}", 'onfocus' => "if (this.value == '" . $before_focus . "') {this.value = '';}" );
  // Don't change this
  $output = drupal_render($form);
  return $output;
}

/**
 * Function for Share Links
 *
 **/
function nys_share_links() {
  global $base_path;
  $output = '';
  $output .= '<h3>Share This</h3>';
  $output .= '<ul>';
  $output .= '<li class="share_digg"><a href="#"><img src="'.$base_path.path_to_theme().'/images/share_icons/digg.png"/></a></li>';
  $output .= '<li class="share_facebook"><a href="#"><img src="'.$base_path.path_to_theme().'/images/share_icons/facebook.png"/></a></li>';
  $output .= '<li class="share_delicious"><a href="#"><img src="'.$base_path.path_to_theme().'/images/share_icons/delicious.png"/></a></li>';
  $output .= '<li class="share_twitter"><a href="#"><img src="'.$base_path.path_to_theme().'/images/share_icons/twitter.png"/></a></li>';
  $output .= '<li class="share_stumbleupon"><a href="#"><img src="'.$base_path.path_to_theme().'/images/share_icons/stumbleupon.png"/></a></li>';
  $output .= '<li class="share_feedburner"><a href="#"><img src="'.$base_path.path_to_theme().'/images/share_icons/feedburner.png"/></a></li>';
  $output .= '<li class="share_wordpress"><a href="#"><img src="'.$base_path.path_to_theme().'/images/share_icons/wordpress.png"/></a></li>';
  $output .= '</ul>';
  return $output;
}

function nys_links($links, $attributes = array('class'=>'links')) {
  unset($links['node_read_more']);
  unset($links['blog_usernames_blog']);
  return theme_links($links, $attributes);
}

function nys_comment_submitted($comment) {
  return t('by !username',
    array(
      '!username' => $comment->name,
    ));
}

function nys_date_all_day($which, $date1, $date2, $format, $node, $view = NULL) {
  if (empty($date1) || !is_object($date1)) {
    return '';
  }
  if (empty($date2)) {
    $date2 = $date1;
  }
  $granularity = array_pop(date_format_order($format));
  switch ($granularity) {
    case 'second':
      $max_comp = date_format($date2, 'H:i:s') == '23:59:59';
      break;
    case 'minute':
      $max_comp = date_format($date2, 'H:i') == '23:59';
      break;
    case 'hour':
      $max_comp = date_format($date2, 'H') == '23';
      break;
    default:
      $max_comp = FALSE;
  }
  // Time runs from midnight to the maximum time -- call it 'All day'.
  if (date_format($date1, 'H:i:s') == '00:00:00' && $max_comp) {
    $format = date_limit_format($format, array('year', 'month', 'day'));
    return trim(date_format_date($$which, 'custom', $format) .' '. theme('date_all_day_label'));
  }
  // There is no time, use neither 'All day' nor time.
  elseif (date_format($date1, 'H:i:s') == '00:00:00' && date_format($date2, 'H:i:s') == '00:00:00') {
    $format = date_limit_format($format, array('year', 'month', 'day'));
    return date_format_date($$which, 'custom', $format);
  }
  // Normal formatting - OVERRIDE TO ADD PERIOD.
  else {
    return date_format_date($$which, 'custom', 'M. d');
  }
}

/**
 * Returns the "Something to say" 'block'.
 */
function nys_get_something_to_say() {
  global $user;
  $output = '';
  $output .= '<div id="something_to_say">';
  $output .= '<ul>';
  $output .= '<li>';
  $output .= ($user->uid > 0) ? l(t('Blog about an issue you care about.'), 'node/add/story') : l(t('Blog about an issue you care about.'), 'user', array('query' => array('destination' => 'node/add/story')));
  $output .= '</li>';
  $output .= '<li>';
  $output .= ($user->uid > 0) ? l(t('Tell us a story about your life.'), 'node/add/story') : l(t('Tell us a story about your life.'), 'user', array('query' => array('destination' => 'node/add/story')));
  $output .= '</li>';
  $output .= '<li class="last">' . l(t('Have a suggestion? Let us know!'), 'contact') . '</li>';
  $output .= '</ul>';
  $output .= '</div>';
  return $output;
}

/**
 * Theme emvideo thickboxes
 */

function nys_emvideo_modal_generic($field, $item, $formatter, $node, $options = array()) {
  return theme('nyss_videosettings_modal_generic', $field, $item, $formatter, $node, $options);
}
 
// THEME THE ICAL CALENDAR ICON
function nys_calendar_ical_icon($url) {
  if ($url[0] == '/') { $url = substr($url, 1); }
  return '<div class="calendar-icon">' . l(t('Add to Your Calendar'), $url, array('attributes'=>array('class'=>'ical-icon', 'title'=>t('Add to Your Calendar')))) . '</div>';
}

// MAKE CCK FILE FIELDS OPEN IN NEW WINDOW
function nys_filefield_file($file) {
  // Views may call this function with a NULL value, return an empty string.
  if (empty($file['fid'])) {
    return '';
  }

  $path = $file['filepath'];
  $url = file_create_url($path);
  $icon = theme('filefield_icon', $file);

  // Set options as per anchor foaarmat described at
  // http://microformats.org/wiki/file-format-examples
  // TODO: Possibly move to until I move to the more complex format described
  // at http://darrelopry.com/story/microformats-and-media-rfc-if-you-js-or-css
  $options = array(
    'attributes' => array(
      'type' => $file['filemime'],
      'length' => $file['filesize'],
      'target' => '_blank',
    ),
  );

  // Use the description as the link text if available.
  if (empty($file['data']['description'])) {
    $link_text = $file['filename'];
  }
  else {
    $link_text = $file['data']['description'];
    $options['attributes']['title'] = $file['filename'];
  }

  return '<div class="filefield-file clear-block">'. $icon . l($link_text, $url, $options) .'</div>';
}

// BOOK PREPROCESS VARIABLES
function nys_preprocess_book_navigation(&$variables) {
  $node = node_load($variables['book_link']['nid']);
  $variables['display'] = TRUE;
  if (strlen($node->body) >= 3000 || $variables['book_link']['nid'] == $variables['book_link']['bid']) {
    $book_link = $variables['book_link'];
    $tree = menu_tree_all_data(book_menu_name($book_link['bid']));
    $variables['tree'] = '<div class="book-navigation-tree">'. menu_tree_output($tree) . '</div>';
  }
  else {
    $variables['display'] = FALSE;
  }
}

function nys_menu_item_link($link) {
  if (empty($link['localized_options'])) {
    $link['localized_options'] = array();
  }

  $extra = '';
  $span = '<span class="';
  $div = '<div class="';

  if (isset($link['type']) && $link['type'] & MENU_IS_LOCAL_TASK) {
    $link['title'] = '<span class="tab">' . check_plain($link['title']) . '</span>';
    $link['localized_options']['html'] = TRUE;
  }
  if (isset($link['module']) && $link['module'] == 'book') {
    $explode = explode('/', $link['link_path']);
    $nid = $explode[1];
    $result = db_query('SELECT COUNT(c.cid) AS comment_count, n.comment FROM {comments} AS c LEFT JOIN {node} AS n on n.nid = c.nid WHERE c.nid = %d AND c.status = 0 GROUP BY c.nid', $nid);
    while($row = db_fetch_object($result)) {
      if ($row->comment == NULL || $row->comment = 0) {
        $extra = 'disabled';
        break;
      }
      else {
        $extra = $row->comment_count;
      }
    }
    //global $user;
    //if ($user->uid == 37) { print $extra .'<br />'; }
    if ($extra != 'disabled' && $extra != '') {
      if ($extra == 0) { $span .= 'no-comments '; } else { $span .= 'yes-comments '; }
      $extra = format_plural($extra, '(1&nbsp;comment)', '(@count&nbsp;comments)');

      $extra = l($extra, $link['href'], array('fragment' => 'comments', 'html' => 'true'));
    }
    else {
      unset($extra);
    }
	  if ((arg(0) == 'node') && (is_numeric(arg(1))) && (arg(2) != 'edit')) {
      if (arg(1) == $explode[1]) {
        $div .= 'book-active-chapter ';
      }
    }
  }

  $span .= '">';
  $div .= '">';

  if (isset($link['module']) && $link['module'] == 'book' && arg(1) == $explode[1]) {
    return $div . t($link['title']) . ' ' . $span . $extra .'</span></div>';
  }
  else {
		return $div . l($link['title'], $link['href'], $link['localized_options']) . ' ' . $span . $extra .'</span></div>';
  }
}

function nys_webform_view_messages($node, $teaser, $page, $submission_count, $limit_exceeded, $allowed_roles) {
  global $user;

  $type = 'notice';

  // If not allowed to submit the form, give an explaination.
  if (array_search(TRUE, $allowed_roles) === FALSE && $user->uid != 1) {
    if (empty($allowed_roles)) {
      // No roles are allowed to submit the form.
      $message = t('Submissions for this form are closed.');
    }
    elseif (isset($allowed_roles[2])) {
      // The "authenticated user" role is allowed to submit and the user is currently logged-out.
      $message = t('You must <a href="!login">login</a> or <a href="!register">register</a> to view this form.', array('!login' => url(('user/login'), array('query' => drupal_get_destination())), '!register' => url(('user/register'), array('query' => drupal_get_destination()))));
    }
    else {
      // The user must be some other role to submit.
      $message = t('You do not have permission to view this form.');
    }
  }

  // If the user has exceeded the limit of submissions, explain the limit.
  if ($limit_exceeded) {
    if ($node->webform['submit_interval'] == -1 && $node->webform['submit_limit'] > 1) {
      $message = t('You have submitted this form the maximum number of times (@count).', array('@count' => $node->webform['submit_limit']));
    }
    elseif ($node->webform['submit_interval'] == -1 && $node->webform['submit_limit'] == 1) {
      $message = t('You have already submitted this form.');
    }
    else {
      $message = t('You may not submit another entry at this time.');
    }
    $type = 'error';
  }

  // If the user has submitted before, give them a link to their submissions.
  if ($submission_count > 0) {
    if (empty($message)) {
      $message = t('Thank you for submitting this form.') .' '. t('<a href="!url">View your previous submissions</a>.', array('!url' => url('node/'. $node->nid .'/submissions')));
    }
    else {
      $message .= ' '. t('<a href="!url">View your previous submissions</a>.', array('!url' => url('node/'. $node->nid .'/submissions')));
    }
  }

  if ($page && isset($message)) {
    drupal_set_message($message, $type);
  }
}
