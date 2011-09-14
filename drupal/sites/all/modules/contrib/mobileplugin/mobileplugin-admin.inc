<?php
// $Id: mobileplugin-admin.inc,v 1.7 2010/01/26 17:01:42 teemule Exp $

/**
 * Creates the settings form.
 * @return the settings form
 */
function mobileplugin_admin_settings() {
	$form = array();
	$form['domains'] = array(
		'#type' => 'fieldset',
		'#title' => t('Domain based mobile version'),
		'#description' => t('Optional domains used to select the site version. Don\'t use http://')
	);
	$form['domains']['mobileplugin_mobile_domain'] = array(
		'#type' => 'textfield',
		'#title' => t('Domain for mobile site'),
		'#default_value' => variable_get('mobileplugin_mobile_domain', ''),
	);
	$form['domains']['mobileplugin_full_domain'] = array(
		'#type' => 'textfield',
		'#title' => t('Domain for full site'),
		'#default_value' => variable_get('mobileplugin_full_domain', ''),
	);
	$form['detection'] = array(
		'#type' => 'fieldset',
		'#title' => t('Automatic device detection')
	);
	$form['detection']['mobileplugin_detection'] = array(
		'#type' => 'checkbox',
		'#title' => t('Enable automatic device detection'),
		'#default_value' => variable_get('mobileplugin_detection', true)
	);
	if (module_exists('wurfl')) {
		$form['detection']['wurfl'] = array(
			'#type' => 'markup',
			'#value' => t('WURFL module exists and is used for device detection.')
		);
	}
	$form['tools'] = array(
		'#type' => 'fieldset',
		'#title' => t('Administrative tools')
	);
	$form['tools']['flush'] = array(
		'#type' => 'button',
		'#value' => t('Flush cache and scaled images')
	);
	if (variable_get('cache', 0)) {
		drupal_set_message(l(t('Disable page cache or multiple themes will not work.'), 'admin/settings/performance'), 'error');
	}
	if (!variable_get('preprocess_css', false)) {
		drupal_set_message(l(t('Using aggregate and compress CSS files is recommended.'), 'admin/settings/performance'));
	}
	return system_settings_form($form);
}

/**
 * Validates the settings form.
 * @param form_id an unique id
 * @param form_values the sent form values
 */
function mobileplugin_admin_settings_validate($form, &$form_state) {
	drupal_get_messages();
	if ($form_state['values']['op'] == t('Flush cache and scaled images')) {
		_mobileplugin_flush();
	}
	if (substr($form_state['values']['mobileplugin_mobile_domain'], 0, 7) == 'http://') {
		form_set_error('mobileplugin_mobile_domain', t('Do not use http://'));
	}
	if (substr($form_state['values']['mobileplugin_full_domain'], 0, 7) == 'http://') {
		form_set_error('mobileplugin_full_domain', t('Do not use http://'));
	}
}

/**
 * Lists device groups.
 * @return page content
 */
function mobileplugin_groups() {
	$c = '<ul>';
	$result = db_query('select name,theme from {mobileplugin_groups}');
	while($row = db_fetch_array($result)) {
		$c .= '<li><strong>' . check_plain($row['name']) . '</strong> (' . check_plain($row['theme']) . ')<br />'
			. l(t('Edit group'), 'admin/build/mobileplugin/groups/edit/' . urlencode($row['name'])) . '<br />'
			. l(t('Filter group css and js'), 'admin/build/mobileplugin/groups/filter/' . urlencode($row['name'])) . '<br />'
			. l(t('Edit group blocks'), 'admin/build/block/list/' . urlencode($row['theme'])) . '<br />'
			. l(t('Test group until the end of the session'), 'admin/build/mobileplugin/test/' . urlencode($row['name'])) . '</li>';
	}
	$c .= '</ul><p>' . l(t('Add new group'), 'admin/build/mobileplugin/groups/edit') . '</p>';
	$c .= '<p>' . l(t('Test touchscreen class until the end of the session'), 'admin/build/mobileplugin/test/_touchscreen') . '</p>';
	if (isset($_SESSION['mobileplugin_group'])) {
		$c .= '<p>' . l(t('Stop testing group') . ': ' . check_plain($_SESSION['mobileplugin_group']), 'admin/build/mobileplugin/test') . '</p>';
	}
	return $c;
}

/**
 * Creates the group edit form.
 * @param name a group name
 * @return the edit form
 */
function mobileplugin_groups_form(&$form_state, $name = false) {
	$form = array();
	if ($name) {
		$group = _mobileplugin_get_group_setup($name);
		if (!$group) {
			drupal_not_found();
			exit();
		}
		_mobileplugin_group_setup_in($group);
		$title = t('Edit group') . ': ' . $group['name'];
		$desc = t('Settings for a device group. Set up rules to pick devices.');
	} else {
		$group = array('name' => '', 'theme' => '', 'images' => true, 'youtube' => true);
		$title = t('Group settings');
		$desc = t('Create a new device group and settings for it.');
		$form['group_name'] = array(
			'#type' => 'textfield',
			'#required' => true,
			'#title' => t('Group name')
		);
	}
	$form['group'] = array(
		'#type' => 'fieldset',
		'#title' => $title,
		'#description' => $desc
	);
	$form['group']['name'] = array(
		'#type' => 'hidden',
		'#default_value' => $group['name']
	);
	$form['group']['theme'] = array(
		'#type' => 'select',
		'#title' => t('Drupal theme'),
		'#default_value' => _mobileplugin_get_setup_val($group, 'theme', 'mobile_garland'),
		'#options' => _mobileplugin_get_theme_names()
	);
	$form['group']['breakwords'] = array(
		'#type' => 'textfield',
		'#title' => t('Suggest a word break after this many characters, zero to disable'),
		'#default_value' => _mobileplugin_get_setup_val($group, 'breakwords', 30)
	);
	$form['group']['imageact'] = array(
		'#type' => 'select',
		'#title' => t('Image action'),
		'#default_value' => _mobileplugin_get_setup_val($group, 'imageact', 'scale'),
		'#options' => array('none' => t('Do nothing'), 'scale' => t('Scale down'), 'remove' => t('Remove'))
	);
	$form['group']['imagesize'] = array(
		'#type' => 'textfield',
		'#title' => t('Maximum image size as width x height'),
		'#default_value' => _mobileplugin_get_setup_val($group, 'imagesize', '180x180')
	);
	$form = array_merge($form, module_invoke_all('mobileplugin_setup', $group));
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save')
	);
	if ($name) {
		$form['delete'] = array(
			'#type' => 'submit',
			'#value' => t('Delete group')
		);
	}
	$form['cancel'] = array(
		'#type' => 'button',
		'#value' => t('Cancel')
	);
	return $form;
}

/**
 * Gets a group setup by group name.
 * @param group_name a group name
 * @return a group setup
 */
function _mobileplugin_get_group_setup($group_name) {
	$result = db_query('select name,theme,data from {mobileplugin_groups} where name="%s"', $group_name);
	return db_fetch_array($result);
}

/**
 * Gets enabled themes.
 * @return an array of enabled themes
 */
function _mobileplugin_get_theme_names() {
	$themes = array();
	foreach (list_themes() as $t) {
		if ($t->status) {
			$themes[$t->name] = $t->name;
		}
	}
	return $themes;
}

/**
 * Validates the group edit form.
 * @param form_id an unique id
 * @param form_values the sent form values
 */
function mobileplugin_groups_form_validate($form, &$form_state) {
	if ($form_state['values']['op'] == t('Cancel')) {
		drupal_get_messages();
		drupal_goto('admin/build/mobileplugin/groups');
		exit();
	}
	if (isset($form_state['values']['group_name'])) {
		if (db_result(db_query('select name from {mobileplugin_groups} where name="%s"', $form_state['values']['group_name']))) {
			form_set_error('group_name', t('Group with a same name exists.'));
		}
	}
}

/**
 * Submits the group edit form.
 * @param form_id an unique id
 * @param form_values the sent form values
 */
function mobileplugin_groups_form_submit($form, &$form_state) {
	$pick_keys = array('op', 'name', 'group_name', 'theme');
	$drop_keys = array('submit', 'delete', 'cancel', 'form_token', 'form_id');
	$values = $form_state['values'];
	$pick = array();
	foreach ($pick_keys as $key) {
		$pick[$key] = $values[$key];
	}
	foreach (array_merge($pick_keys, $drop_keys) as $key) {
		unset($values[$key]);
	}
	if ($pick['op'] == t('Delete group')) {
		db_query('delete from {mobileplugin_groups} where name="%s"', $pick['name']);
		drupal_set_message(t('The group deleted.'));
	} else if (strlen($pick['name']) > 0) {
		$group = _mobileplugin_get_group_setup($pick['name']);
		if ($group) {
			_mobileplugin_group_setup_in($group);
			$values['filtercss'] = $group['filtercss'];
			$values['filterjs'] = $group['filterjs'];
			db_query('update {mobileplugin_groups} set theme="%s",data="%s" where name="%s"', $pick['theme'], serialize($values), $pick['name']);
			drupal_set_message(t('Changes to the group saved.'));
		}
	} else {
		db_query('insert into {mobileplugin_groups} (name,theme,data) values ("%s","%s","%s")', $pick['group_name'], $pick['theme'], serialize($values));
		drupal_set_message(t('New group added.'));
	}
	cache_clear_all('mobileplugin_grouplist', 'cache');
	cache_clear_all('mobileplugin_optimized', 'cache_page', true);
	cache_clear_all();
	drupal_goto('admin/build/mobileplugin/groups');
}

/**
 * Creates the group filter css and js form.
 * @param name a group name
 * @return the edit form
 */
function mobileplugin_filter_form(&$form_state, $name = false) {
	if (!$name) {
		drupal_not_found();
		exit();
	}
	$result = db_query('select name,theme,data from {mobileplugin_groups} where name="%s"', $name);
	$group = db_fetch_array($result);
	if (!$group) {
		drupal_not_found();
		exit();
	}
	_mobileplugin_group_setup_in($group);
	$form = array();
	$form['name'] = array(
		'#type' => 'hidden',
		'#value' => $group['name']
	);
	$form['css'] = array(
		'#type' => 'textarea',
		'#title' => t('Allow CSS files for group') . ' <em>' . $group['name'] . '</em>',
		'#default_value' => _mobileplugin_list2textarea(_mobileplugin_get_setup_val($group, 'filtercss', array('sites/all/themes/', 'themes/', 'sites/default/files'))),
		'#description' => t('List a path per line. Stylesheets from these locations are allowed.')
	);
	$form['js'] = array(
		'#type' => 'textarea',
		'#title' => t('Allow JS files for group') . ' <em>' . $group['name'] . '</em>',
		'#default_value' => _mobileplugin_list2textarea(_mobileplugin_get_setup_val($group, 'filterjs', array())),
		'#description' => t('List a path per line. Javascripts from these locations are allowed.')
	);
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save')
	);
	$form['cancel'] = array(
		'#type' => 'button',
		'#value' => t('Cancel')
	);
	return $form;
}

/**
 * Validates the group filter css and js form.
 * @param form_id an unique id
 * @param form_values the sent form values
 */
function mobileplugin_filter_form_validate($form, &$form_state) {
	if ($form_state['values']['op'] == t('Cancel')) {
		drupal_get_messages();
		drupal_goto('admin/build/mobileplugin/groups');
		exit();
	}
}

/**
 * Submits the group filter css and js form.
 * @param form_id an unique id
 * @param form_values the sent form values
 */
function mobileplugin_filter_form_submit($form, &$form_state) {
	$group = _mobileplugin_get_group_setup($form_state['values']['name']);
	if (!$group) {
		drupal_not_found();
		exit();
	}
	$data = array();
	if ($group['data']) {
		$data = unserialize($group['data']);
	}
	$data['filtercss'] = _mobileplugin_textarea2list($form_state['values']['css']);
	$data['filterjs'] = _mobileplugin_textarea2list($form_state['values']['js']);
	db_query('update {mobileplugin_groups} set data="%s" where name="%s"', serialize($data), $group['name']);
	drupal_set_message(t('Changes to the css and js filter saved.'));
	cache_clear_all('mobileplugin_grouplist', 'cache');
	cache_clear_all();
	drupal_goto('admin/build/mobileplugin/groups');
}

/**
 * Gets an editable textarea content for a list.
 * @param list a list of values
 * @return each value on a line
 */
function _mobileplugin_list2textarea($list) {
	$content = '';
	foreach ($list as $value) {
		$content .= $value . "\n";
	}
	return $content;
}

/**
 * Gets a list from edited textarea content.
 * @param content each value on a line
 * @return a list of values
 */
function _mobileplugin_textarea2list($content) {
	$list = array();
	foreach (explode("\n", $content) as $value) {
		$value = trim($value);
		if (!empty($value)) {
			$list[] = $value;
		}
	}
	return $list;
}

/**
 * Lists detection rules.
 * @return page content
 */
function mobileplugin_rules() {
	$c = '<ul>';
	$result = db_query('select rid,capability,operator,value,group_name,weight from {mobileplugin_rules} order by weight asc');
	while($row = db_fetch_array($result)) {
		$c .= '<li>' . l(t('Edit rule:'), 'admin/build/mobileplugin/rules/edit/' . intval($row['rid']))
			. ' <strong>' . check_plain($row['capability'] . ' ' . $row['operator'] . ' ' . $row['value'])
			. '</strong> ? group=<strong>' . $row['group_name'] . '</strong> (weight=' . intval($row['weight']) . ')</li>';
	}
	$c .= '</ul><p>' . l(t('Add new rule'), 'admin/build/mobileplugin/rules/edit') . '</p>';
	return $c;
}

/**
 * Creates the rules edit form.
 * @param rid a rule id
 * @return the edit form
 */
function mobileplugin_rules_form(&$form_state, $rid = '') {
	$form = array();
	if ($rid != '') {
		$result = db_query('select rid,capability,operator,value,group_name,weight from {mobileplugin_rules} where rid="%d"', $rid);
		$rule = db_fetch_array($result);
		if (!$rule) {
			drupal_not_found();
			exit();
		}
	} else {
		$rule = array('rid' => '', 'capability' => '', 'operator' => '==', 'value' => '', 'group_name' => '', 'weight' => 0);
	}
	$form['rule'] = array(
		'#type' => 'fieldset',
		'#title' => t('Edit rule'),
		'#description' => t('Devices will be assigned to a group by the lightest matching rule.')
	);
	$form['rule']['rid'] = array(
		'#type' => 'hidden',
		'#default_value' => $rule['rid']
	);
	$form['rule']['capability'] = array(
		'#type' => 'textfield',
		'#required' => true,
		'#title' => t('Property'),
		'#default_value' => $rule['capability'],
		'#description' => t('"USERAGENT" for HTTP User-Agent field. If using WURFL: "ID" for WURFL ID or WURFL capability name')
	);
	$form['rule']['operator'] = array(
		'#type' => 'select',
		'#required' => true,
		'#title' => t('Operator'),
		'#default_value' => $rule['operator'],
		'#options' => array(
			'=~' => t('contains one of'),
			'!=~' => t('contains none of'),
			'==' => t('is one of'),
			'!=' => t('is none of'),
			'<=' => t('is smaller or equal'),
			'>=' => t('is greater or equal')
		)
	);
	$form['rule']['value'] = array(
		'#type' => 'textarea',
		'#cols' => 5,
		'#required' => true,
		'#title' => t('Value(s)'),
		'#default_value' => $rule['value'],
		'#description' => t('Values to compare to one per line.')
	);
	$gt = explode(',', $rule['group_name']);
	$form['rule']['group_name'] = array(
		'#type' => 'select',
		'#required' => true,
		'#title' => t('Group'),
		'#default_value' => $gt[0],
		'#options' => _mobileplugin_get_group_names(),
		'#description' => t('A group to assign when the rule matches')
	);
	$form['rule']['touchscreen'] = array(
		'#type' => 'select',
		'#required' => true,
		'#title' => t('Touchscreen'),
		'#default_value' => count($gt[1]) > 0 ? $gt[1] : 'none',
		'#options' => array(
			'none' => t('Detect separately'),
			'0' => t('Not a touchsreen'),
			'1' => t('Is a touchscreen')
		)
	);
	$form['rule']['weight'] = array(
		'#type' => 'weight',
		'#title' => t('Weight'),
		'#default_value' => $rule['weight']
	);
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save')
	);
	if ($rid != '') {
		$form['delete'] = array(
			'#type' => 'submit',
			'#value' => t('Delete rule')
		);
	}
	$form['cancel'] = array(
		'#type' => 'button',
		'#value' => t('Cancel')
	);
	return $form;
}

/**
 * Gets Mobile Plugin groups.
 * @return an array of Mobile Plugin groups
 */
function _mobileplugin_get_group_names() {
	$groups = array('no' => 'No detection');
	$result = db_query('select name from {mobileplugin_groups}');
	while ($row = db_fetch_array($result)) {
		$groups[$row['name']] = $row['name'];
	}
	return $groups;
}

/**
 * Validates the group edit form.
 * @param form_id an unique id
 * @param form_values the sent form values
 */
function mobileplugin_rules_form_validate($form, &$form_state) {
	if ($form_state['values']['op'] == t('Cancel')) {
		drupal_get_messages();
		drupal_goto('admin/build/mobileplugin/rules');
		exit();
	}
}

/**
 * Submits the group edit form.
 * @param form_id an unique id
 * @param form_values the sent form values
 */
function mobileplugin_rules_form_submit($form, &$form_state) {
	$values = $form_state['values'];
	$group = $values['group_name'];
	if ($values['group_name'] != 'no' && $values['touchscreen'] != 'none') {
		$group .= ',' . $values['touchscreen'];
	}
	if ($values['op'] == t('Delete rule')) {
		db_query('delete from {mobileplugin_rules} where rid=%d', $values['rid']);
		drupal_set_message(t('The rule deleted.'));
	} else if (strlen($values['rid']) > 0) {
		db_query('update {mobileplugin_rules} set capability="%s",operator="%s",value="%s",group_name="%s",weight=%d where rid=%d', $values['capability'], $values['operator'], $values['value'], $group, $values['weight'], $values['rid']);
		drupal_set_message(t('Changes to the rule saved.'));
	} else {
		db_query('insert into {mobileplugin_rules} (capability,operator,value,group_name,weight) values ("%s","%s","%s","%s",%d)', $values['capability'], $values['operator'], $values['value'], $group, $values['weight']);
		drupal_set_message(t('New rule added.'));
	}
	cache_clear_all('mobileplugin_rulelist', 'cache');
	drupal_goto('admin/build/mobileplugin/rules');
}

/**
 * Starts a test using the given group.
 * @param group a group name to test
 */
function mobileplugin_test_group($group = false) {
	global $mobileplugin_group;
	if (!$group) {
		unset($_SESSION['mobileplugin_group']);
	} else if ($group == '_touchscreen') {
		$_SESSION['mobileplugin_group'] = $mobileplugin_group . ',1';
	} else {
		$_SESSION['mobileplugin_group'] = _mobileplugin_validate_group($group) . ',0';
	}
	drupal_goto('admin/build/mobileplugin/groups');
}

/**
 * Displays debug information about the detection.
 * @return the page content
 */
function mobileplugin_debug() {
	$content = '<p>HTTP_USER_AGENT: ' . check_plain($_SERVER['HTTP_USER_AGENT']) . '</p>';
	list($group, $touch) = _mobileplugin_detect_group();
	$content .= '<p>' . t('Detected group') . ': <strong>' . $group . '</strong><br />'
		. t('Detected touchscreen') . ': ' . ($touch ? 'true' : 'false') . '</p>';
	return $content;
}

/**
 * Flushes cached node optimizations and scaled images.
 */
function _mobileplugin_flush() {
	cache_clear_all('mobileplugin_', 'cache', true);
	cache_clear_all('mobileplugin_', 'cache_page', true);
	_mobileplugin_rmdir(file_directory_path() . '/mobileplugin');
	drupal_set_message(t('Mobile Plugin caches cleared.'));
	drupal_goto('admin/build/mobileplugin');
}

/**
 * Removes a directory with it's contents.
 * @param dirname a directory path to remove
 * @return true on success
 */
function _mobileplugin_rmdir($dirname) {
	if (!file_exists($dirname)) {
		return false;
	}
	if (is_file($dirname) || is_link($dirname)) {
		return unlink($dirname);
	}
	$dir = dir($dirname);
	while (false !== $entry = $dir->read()) {
		if ($entry == '.' || $entry == '..') {
			continue;
		}
		_mobileplugin_rmdir($dirname . '/' . $entry);
	}
	$dir->close();
	return rmdir($dirname);
}
