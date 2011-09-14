<?php
// $Id: sifr.inc,v 1.6 2009/01/17 20:13:55 sun Exp $

/**
 * @file
 * Dynamic Rendering plugin for sIFR v2.
 */

/**
 * Return plugin information.
 * 
 * @return array
 *   An array containing the keys
 *   - type: The type of this plugin. @see render_get_types().
 *   - name: The filename of this plugin (internal). Also used to display a
 *     plugin image in plugins/<name>.png.
 *   - title: The official title of this plugin.
 *   - url: An URI of the website of this plugin.
 *   - dependencies: An array of filenames that have to exist in the plugin
 *     folder.
 *   - file_masks: An array containing regular expressions matching
 *     corresponding font files.
 *   - properties: An array of plugin-specific properties to store in the
 *     database.
 */
function sifr_render_info() {
  return array(
    'type' => 'text',
    'name' => 'sifr',
    'title' => 'sIFR v2',
    'url' => 'http://www.mikeindustries.com/sifr/',
    'dependencies' => array('sIFR-print.css', 'sifr.js'),
    'file_masks' => array('.+\.swf'),
    'properties' => array('font', 'color', 'linkcolor', 'hovercolor', 'bgcolor', 'transparent', 'letterspacing', 'fontsize', 'paddingtop', 'paddingright', 'paddingbottom', 'paddingleft', 'textalign', 'lettercase', 'underline'),
  );
}

/**
 * Return plugin help on render/manage.
 * 
 * @return string
 *   A translatable string instructing the user how to use this plugin or
 *   an empty string to hide plugin instructions.
 */
function sifr_render_help() {
  return t('
  <h3>Good places to find sIFR fonts:</h3>
  <ul>
    <li><a href="http://www.fontsmack.com/">Font Smack</a></li>
    <li><a href="http://www.isarie.com/?p=17">Stefan Isarie</a></li>
  </ul>
  <p>Just download them from there and upload them here.</p>
  <h3>To create your own sIFR font files:</h3>
    <ol>
      <li>Download these files into one directory: !files</li>
      <li>Open sifr.fla in Macromedia Flash.</li>
      <li>Double-click the invisible textbox in the middle of the stage. If the &quot;Properties&quot; palette is not already visible, open it by selecting &quot;Window > Properties&quot;, and select which font you\'d like to use from the drop down menu. If you select a TrueType font, you can also create bold and italic styles for your font by clicking on the &quot;I&quot; or &quot;B&quot; buttons. The standard sifr.fla file contains most of the English characters you will generally need. If you need to embed additional characters or languages, click the &quot;Character&quot; button and select more characters from there.</li>
      <li>To export the new file, choose &quot;File > Export&quot; and save as fontname.swf</li>
      <li>Upload the your font file below.</li>
    </ol>',
    array(
      '!files' => render_download_link('sifr', 'sifr.fla') .', '. render_download_link('sifr', 'customize_me.as') .', '. render_download_link('sifr', 'dont_customize_me.as')
      )
  );
}

/**
 * Perform plugin installation checks executed on render/addrule.
 */
function sifr_render_setup() {
  // Check working directory.
  $dir = file_create_path('render');
  if (!file_check_directory($dir, 1)) {
    drupal_set_message(t('The sIFR working directory !dir is not writable.', array('!dir' => $dir)), 'error');
    return FALSE;
  }
  
  return TRUE;
}

/**
 * Returns font(s) and colors of a text replacement rule.
 * 
 * @param array $rule
 *   A text replacement rule.
 * 
 * @return array $fontstyle
 *   An array containing the keys
 *   - font
 *   - colors
 *     - color
 *     - linkcolor (optional)
 *     - hovercolor (optional)
 *     - bgcolor (optional)
 */
function sifr_render_rules($rule) {
  $fontstyle = array();
  $fontstyle['font'] = substr($rule['font'], strrpos($rule['font'], '/') + 1);
  $fontstyle['colors'] = array(
    'color' => $rule['color'],
    'linkcolor' => $rule['linkcolor'],
    // Hover color breaks sIFR in newer Flash versions. @see #224713
    // 'hovercolor' => $rule['hovercolor'],
    'bgcolor' => $rule['bgcolor'],
  );
  
  return $fontstyle;
}

/**
 * Return custom rule properties.
 * 
 * @param array $form
 *   A rule edit form, passed by reference.
 * @param array $edit
 *   User values for the form.
 */
function sifr_render_rule(&$form, $edit) {
  $info = sifr_render_info();
  // array_fill_keys() available on PHP 5.2+ only.
  foreach ($info['properties'] as $key) {
    if (!isset($edit[$key])) {
      $edit[$key] = '';
    }
  }

  $form['font'] = array(
    '#type' => 'fieldset',
    '#title' => t('Font'),
  );
  $form['font']['font'] = array(
    '#title' => t('Font'),
    '#type' => 'item',
    '#description' => t("Select a font to use for this rule."),
    '#required' => TRUE,
  );
  $form['font']['font']['fonts'] = render_font_select($edit, 'font');
  
  $form['colors'] = array(
    '#type' => 'fieldset',
    '#title' => t('Colors'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Each rule defines the colors for replaced text. Use hexadecimal (CSS-style) color values preceeded by &quot;<code>#</code>&quot; to define text color, linked text color, hover-over link color, and text background color.'),
  );
  $form['colors']['color'] = array(
    '#type' => 'textfield',
    '#title' => t('Text Color'),
    '#size' => 12,
    '#default_value' => $edit['color'] ? $edit['color'] : '#000000',
  );
  $form['colors']['linkcolor'] = array(
    '#type' => 'textfield',
    '#title' => t('Link Color'),
    '#size' => 12,
    '#default_value' => $edit['linkcolor'] ? $edit['linkcolor'] : '#000000',
  );
  // Hover color breaks sIFR in newer Flash versions. @see #224713
  /*
  $form['colors']['hovercolor'] = array(
    '#type' => 'textfield',
    '#title' => t('Hover Color'),
    '#size' => 12,
    '#default_value' => $edit['hovercolor'] ? $edit['hovercolor'] : '#666666',
  );
  */
  $form['colors']['bgcolor'] = array(
    '#type' => 'textfield',
    '#title' => t('Text Background Color'),
    '#size' => 12,
    '#default_value' => $edit['bgcolor'] ? $edit['bgcolor'] : '#FFFFFF',
  );
  $transparency_options = array(
    0 => t('No transparency'),
    1 => t('Use transparency'),
    2 => t('Opaque background'),
  );
  $form['colors']['transparent'] = array(
    '#title' => t('Transparency'),
    '#type' => 'radios',
    '#options' => $transparency_options,
    '#default_value' => $edit['transparent'],
    '#description' => t('<strong>Warning:</strong> Flash transparency is not well supported in all browsers and therefore not recommended.'),
  );
  $form['tweaks'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tweaks'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['tweaks']['letterspacing'] = array(
    '#type' => 'textfield',
    '#title' => t('Letter Spacing'),
    '#description' => t('A CSS value to adjust letter spacing on replaced text. Examples: &quot;-5px&quot;, &quot;-.2em&quot;'),
    '#size' => 12,
    '#default_value' => $edit['letterspacing'],
  );
  $form['tweaks']['fontsize'] = array(
    '#type' => 'textfield',
    '#title' => t('Font Size'),
    '#description' => t('A CSS value to adjust font size on replaced text. Examples: &quot;55px&quot;, &quot;2em&quot;'),
    '#size' => 12,
    '#default_value' => $edit['fontsize'],
  );
  $form['tweaks']['padding'] = array(
    '#type' => 'fieldset',
    '#title' => t('Padding'),
    '#description' => '<div style="display:block">'. t('If you use padding in the elements you want to replace, you have to set the amount of padding here (in pixels, but without the px part)') .'</div>',
    '#prefix' => '<div class="container-inline">',
    '#suffix' => '</div>',
  );
  $form['tweaks']['padding']['paddingtop'] = array(
    '#type' => 'textfield',
    '#title' => t('top'),
    '#size' => 6,
    '#default_value' => $edit['paddingtop'],
  );
  $form['tweaks']['padding']['paddingright'] = array(
    '#type' => 'textfield',
    '#title' => t('right'),
    '#size' => 6,
    '#default_value' => $edit['paddingright'],
  );
  $form['tweaks']['padding']['paddingbottom'] = array(
    '#type' => 'textfield',
    '#title' => t('bottom'),
    '#size' => 6,
    '#default_value' => $edit['paddingbottom'],
  );
  $form['tweaks']['padding']['paddingleft'] = array(
    '#type' => 'textfield',
    '#title' => t('left'),
    '#size' => 6,
    '#default_value' => $edit['paddingleft'],
  );
  $form['tweaks']['textalign'] = array(
    '#type' => 'select',
    '#title' => t('Text Alignment'),
    '#default_value' => $edit['textalign'],
    '#options' => array(
      'left' => t('Left'),
      'center' => t('Center'),
      'right' => t('Right'),
    ),
  );
  $form['tweaks']['lettercase'] = array(
    '#type' => 'select',
    '#title' => t('Case Transform'),
    '#default_value' => $edit['lettercase'],
    '#options' => array(
      'normal' => t('Normal'),
      'upper' => t('Upper-Case'),
      'lower' => t('Lower-Case'),
    ),
    '#description' => t('You can transform the text to be all upper-case or all lower-case'),
  );
  $form['tweaks']['underline'] = array(
    '#type' => 'checkbox',
    '#title' => t('Underline Links on Hover?'),
    '#default_value' => $edit['underline'],
    '#return_value' => 1,
  );
}

/**
 * Render a single Javascript text replacement rule.
 * 
 * @param array $rule
 *   A user-generated rule either containing custom rule properties or
 *   a default rule containing the keys selector, font, color, linkcolor,
 *   hovercolor, bgcolor and fontsize as they are needed for font preview
 *   in rule setup.
 * @see render_edit_rule();
 * 
 * @return string
 *   A single rendered JavaScript rule for this plugin.
 */
function sifr_render_render_rule_js($rule) {
  $properties = array();
  $info = sifr_render_info();
  // array_fill_keys() available on PHP 5.2+ only.
  foreach ($info['properties'] as $key) {
    if (!isset($rule[$key])) {
      $rule[$key] = '';
    }
  }

  // Convert spaces in filename.
  $fontpath = base_path() . str_replace('%2F', '/', rawurlencode($rule['font']));
  $properties['sFlashSrc']      = $fontpath;

  $properties['sColor']         = $rule['color'];
  $properties['sLinkColor']     = $rule['linkcolor'];
  // Hover color breaks sIFR in newer Flash versions. @see #224713
  // $properties['sHoverColor']    = $rule['hovercolor'];
  $properties['sBgColor']       = $rule['bgcolor'];
  $properties['nPaddingTop']    = is_numeric($rule['paddingtop']) ? $rule['paddingtop'] : null;
  $properties['nPaddingRight']  = is_numeric($rule['paddingright']) ? $rule['paddingright'] : null;
  $properties['nPaddingBottom'] = is_numeric($rule['paddingbottom']) ? $rule['paddingbottom'] : null;
  $properties['nPaddingLeft']   = is_numeric($rule['paddingleft']) ? $rule['paddingleft'] : null;
  switch ($rule['transparent']) {
    case '1':
      $properties['sWmode'] = 'transparent';
      break;
    
    case '2':
      $properties['sWmode'] = 'opaque';
      break;
  }
  $properties['sCase'] = in_array($rule['lettercase'], array('upper', 'lower')) ? $rule['lettercase'] : '';
  $vars = array();
  if ($rule['underline']) {
    $vars[] = 'underline=true';
  }
  if (in_array($rule['textalign'], array('left', 'center', 'right'))) {
    $vars[] = 'textalign='. $rule['textalign'];
  }
  $properties['sFlashVars'] = implode($vars, '&');
  
  $output = 'sIFR.replaceElement("'. $rule['selector'] .'", named({';
  foreach ($properties as $property => $value) {
    if (!empty($value)) {
      $output .= $property .': "'. $value .'", ';
    }
  }
  $output = substr($output, 0, -2);
  $output .= '}));';
  
  return $output;
}

/**
 * Wrap execution handler around JavaScript rules.
 * 
 * @param array $rules
 *   An array of all current rules for this plugin with already rendered
 *   JavaScript string in each element.
 * 
 * @return string
 *   A complete JavaScript to execute this plugin.
 */
function sifr_render_wrap_rules($rules) {
  $output = '';
  if (is_array($rules)) {
    $output .= "if(typeof sIFR == \"function\") {\n";
    foreach ($rules as $rule) {
      $output .= '  '. $rule ."\n";
    }
    $output .= "};\n";
  }
  
  return $output;
}

/**
 * Render a CSS file for this plugin.
 * 
 * @param array $rule
 *   A user-generated rule either containing custom rule properties or
 *   a default rule containing the keys selector, font, color, linkcolor,
 *   hovercolor, bgcolor and fontsize as they are needed for font preview
 *   in rule setup.
 * @see render_edit_rule();
 * 
 * @return string
 *   A stylesheet for this plugin.
 */
function sifr_render_css_screen($rules) {
  $output = "/* These are standard sIFR styles... do not modify */

.sIFR-flash {
  visibility: visible !important;
  margin: 0;
}

.sIFR-replaced {
  visibility: visible !important;
}

span.sIFR-alternate {
  position: absolute;
  left: 0;
  top: 0;
  width: 0;
  height: 0;
  display: block;
  overflow: hidden;
}

/* Hide Adblock Object tab: the text should show up just fine, not poorly with a tab laid over it. */
.sIFR-flash + div[adblocktab=true] {
  display: none !important;
}

/* These \"decoy\" styles are used to hide the browser text before it is replaced... the negative-letter spacing in this case is used to make the browser text metrics match up with the sIFR text metrics since the sIFR text in this example is so much narrower... your own settings may vary... any weird sizing issues you may run into are usually fixed by tweaking these decoy styles */

";
  
  foreach ($rules as $rule) {
    $fontsize       = trim($rule['fontsize']) ? "  font-size: $rule[fontsize];\n" : '';
    $letterspacing  = trim($rule['letterspacing']) ? "  letter-spacing: $rule[letterspacing];\n" : '';
    $rule['selector'] = str_replace(',', ', .sIFR-hasFlash ', $rule['selector']);
    $output .= "
.sIFR-hasFlash $rule[selector] {
  visibility: hidden;
$fontsize$letterspacing}
";
  }
  
  return $output;
}

/**
 * Load plugin JavaScript and stylesheet files.
 * 
 * Perform all necessary actions to load this plugin on all pages.
 */
function sifr_render_load() {
  $plugindir = render_find_render('sifr');
  if (!$plugindir) {
    $info = sifr_render_info();
    $link_sifr   = l($info['title'], $info['url']);
    $link_readme = l('sifr-README.txt', drupal_get_path('module', 'render') .'/plugins/sifr-README.txt');
    drupal_set_message(t('The sIFR library is in not installed correctly. Please download it from !link and follow installation instructions in !readme.', array('!link' => $link_sifr, '!readme' => $link_readme)), 'error');
  }
  else {
    drupal_add_js($plugindir .'/sifr.js');
    drupal_add_css($plugindir .'/sIFR-print.css', 'module', 'print');
  }
}

