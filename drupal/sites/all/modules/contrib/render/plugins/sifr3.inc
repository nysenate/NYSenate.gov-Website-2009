<?php
// $Id: sifr3.inc,v 1.1 2009/01/17 20:13:55 sun Exp $

/**
 * @file
 * Dynamic Rendering plugin for sIFR v3.
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
function sifr3_render_info() {
  return array(
    'type' => 'text',
    'name' => 'sifr3',
    'title' => 'sIFR v3',
    'url' => 'http://novemberborn.net/sifr3',
    'dependencies' => array('sifr.js', 'sifr.css'),
    'file_masks' => array('.+\.swf'),
    'properties' => array('font', 'color', 'linkcolor', 'hovercolor', 'backgroundcolor', 'letterspacing', 'wmode', 'texttransform', 'fontsize', 'fontweight', 'fontstyle', 'marginleft', 'marginright', 'textalign', 'textindent', 'display', 'opacity', 'leading', 'kerning', 'cursor', 'underline'),
  );
}

/**
 * Return plugin help on render/manage.
 * 
 * @return string
 *   A translatable string instructing the user how to use this plugin or
 *   an empty string to hide plugin instructions.
 */
function sifr3_render_help() {
  return t('<h3>sIFR 3 Information</h3>
<ul>
  <li><a href="http://novemberborn.net/sifr3" target="_blank">sIFR 3 web site</a></li>
</ul>
<h3>Font Movies</h3>
<p>sIFR 3 font rules will not work with sIFR 2 font movies. To create a sIFR 3 font movie, open <code>sifr.fla</code> in your sIFR 3 flash folder. After selecting a font, export movie and upload. You can then create a rule using this font movie.</p>');
}

/**
 * Perform plugin installation checks executed on render/addrule.
 */
function sifr3_render_setup() {
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
function sifr3_render_rules($rule) {
  $fontstyle = array();
  $fontstyle['font'] = substr($rule['font'], strrpos($rule['font'], '/') + 1);
  $fontstyle['colors'] = array(
    'color' => $rule['color'],
    'linkcolor' => $rule['linkcolor'],
    'hovercolor' => $rule['hovercolor'],
    'bgcolor' => $rule['backgroundcolor'],
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
function sifr3_render_rule(&$form, $edit) {
  $info = sifr3_render_info();
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
  $form['colors']['hovercolor'] = array(
    '#type' => 'textfield',
    '#title' => t('Hover Color'),
    '#size' => 12,
    '#default_value' => $edit['hovercolor'] ? $edit['hovercolor'] : '#666666',
  );
  $form['colors']['backgroundcolor'] = array(
    '#type' => 'textfield',
    '#title' => t('Text Background Color'),
    '#size' => 12,
    '#default_value' => $edit['backgroundcolor'],
  );
  $transparency_options = array(
    'window'      => t('Window'),
    'transparent' => t('Transparent'),
    'opaque'      => t('Opaque'),
  );
  $form['colors']['wmode'] = array(
    '#title' => t('Flash Player window mode'),
    '#type' => 'select',
    '#options' => $transparency_options,
    '#default_value' => $edit['wmode'],
    '#description' => t("The window mode parameter allows layering of Flash content within DHTML layers and can be 'window' (default), 'opaque', or 'transparent'. Using a window mode of 'opaque' or 'transparent' will prevent a Flash movie from playing in the topmost layer and allow you to adjust the layering of the movie within other layers of the HTML document."),
  );

  $form['text'] = array(
    '#type' => 'fieldset',
    '#title' => t('Text'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['text']['letterspacing'] = array(
    '#type' => 'textfield',
    '#title' => t('Letter Spacing'),
    '#description' => t('A CSS value to adjust letter spacing on replaced text. Examples: &quot;-5px&quot;, &quot;-.2em&quot;'),
    '#size' => 12,
    '#default_value' => $edit['letterspacing'],
  );
  $form['text']['fontsize'] = array(
    '#type' => 'textfield',
    '#title' => t('Font Size'),
    '#description' => t('A CSS value to adjust font size on replaced text. Examples: &quot;55px&quot;, &quot;2em&quot;'),
    '#size' => 12,
    '#default_value' => $edit['fontsize'],
  );

  $form['text']['margin'] = array(
    '#type' => 'fieldset',
    '#title' => t('Margin'),
    '#description' => '<div style="display: block;">'. t('If you use margin in the elements you want to replace, you have to set the amount of margin here (in pixels, but without the px part)') .'</div>',
    '#prefix' => '<div class="container-inline">',
    '#suffix' => '</div>',
  );
  $form['text']['margin']['marginleft'] = array(
    '#type' => 'textfield',
    '#title' => t('left'),
    '#size' => 6,
    '#default_value' => $edit['marginleft'],
  );
  $form['text']['margin']['marginright'] = array(
    '#type' => 'textfield',
    '#title' => t('right'),
    '#size' => 6,
    '#default_value' => $edit['marginright'],
	);
  $form['text']['textalign'] = array(
    '#type' => 'select',
    '#title' => t('Text Alignment'),
    '#default_value' => $edit['textalign'],
    '#options' => array(
      'left' => t('Left'),
      'center' => t('Center'),
      'right' => t('Right'),
    ),
  );
  $form['text']['texttransform'] = array(
    '#type' => 'select',
    '#title' => t('Case Transform'),
    '#default_value' => $edit['texttransform'],
    '#options' => array(
      'none' => t('Normal'),
      'capitalize' => t('Capitalize'),
      'uppercase' => t('Upper-Case'),
      'lowercase' => t('Lower-Case'),
    ),
    '#description' => t('You can transform the text to be all upper-case or all lower-case'),
  );
  $form['text']['display'] = array(
    '#type' => 'select',
    '#title' => t('Display'),
    '#default_value' => $edit['display'],
    '#options' => array(
      'inline' => t('Inline'),
      'block' => t('Block'),
      'none' => t('None'),
    ),
    '#description' => t('You can use inline, block and none.'),
   );
   $form['text']['cursor'] = array(
    '#type' => 'select',
    '#title' => t('Cursor'),
    '#default_value' => $edit['cursor'],
    '#options' => array(
      'pointer' => t('Pointer'),
      'arrow' => t('Arrow'),
    ),
    '#description' => t('Accepted values for Cursor are "Pointer", which causes the default pointer for links (a "hand") to appear, and "Arrow", which stops the pointer from appearing.'),
   );
   $form['text']['fontweight'] = array(
    '#type' => 'select',
    '#title' => t('Font weight'),
    '#default_value' => $edit['fontweight'],
    '#options' => array(
      'normal' => t('Normal'),
      'bold' => t('Bold'),
    ),
    '#description' => t('You can use normal and bold. Make sure you have embedded the font in bold if you want to use it.'),
   );
   $form['text']['fontstyle'] = array(
    '#type' => 'select',
    '#title' => t('Font style'),
    '#default_value' => $edit['fontstyle'],
    '#options' => array(
      'normal' => t('Normal'),
      'italic' => t('Italic'),
    ),
    '#description' => t('You can use normal and italic. Make sure you have embedded the font in italic if you want to use it.'),
   );
   $form['text']['textindent'] = array(
    '#type' => 'textfield',
    '#title' => t('Text indent'),
    '#size' => 6,
    '#default_value' => $edit['textindent'],
    '#description' => t('You can only use a number, without a unit.'),
  );
  $form['text']['opacity'] = array(
    '#type' => 'textfield',
    '#title' => t('Opacity'),
    '#size' => 6,
    '#default_value' => $edit['opacity'],
    '#description' => t('Sets or retrieves the alpha transparency value of the text field. Valid values are 0 (fully transparent) to 100 (fully opaque). The default value is 100.'),
  );
  $form['text']['leading'] = array(
    '#type' => 'textfield',
    '#title' => t('Leading'),
    '#size' => 6,
    '#default_value' => $edit['leading'],
    '#description' => t('Use leading: with a number. You can only use a number, without a unit. Ex. leading: -10;'),
  );
  $form['text']['kerning'] = array(
    '#type' => 'checkbox',
    '#title' => t('Kerning'),
    '#default_value' => $edit['kerning'],
    '#return_value' => 1,
    '#description' => t('A Boolean value that indicates whether kerning is enabled or disabled. Kerning puts a predetermined amount of space between certain character pairs to improve readability. The default value is false, which indicates that kerning is disabled.'),
  );
  $form['text']['underline'] = array(
    '#type' => 'checkbox',
    '#title' => t('Underline links on hover?'),
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
function sifr3_render_render_rule_js($rule) {
  $properties = array();
  $info = sifr3_render_info();
  // array_fill_keys() available on PHP 5.2+ only.
  foreach ($info['properties'] as $key) {
    if (!isset($rule[$key])) {
      $rule[$key] = '';
    }
  }

  // Generate the font definition for doing a sIFR.activate();
  $font_name = basename($rule['font']);
  $font_path = base_path() . str_replace('%2F', '/', rawurlencode($rule['font']));

  // Generate the text replacement definition for sIFR.replace().
  $css = array(
    '.sIFR-root'  => array(
      'display'          => $rule['display'],
      'font-size'        => $rule['fontsize'],
      'font-weight'      => (!empty($rule['fontweight']) ? $rule['fontweight'] : 'normal'),
      'font-style'       => (!empty($rule['fontstyle']) ? $rule['fontstyle'] : 'normal'),
      'color'            => $rule['color'],
      'background-color' => $rule['backgroundcolor'],
      'margin-left'      => intval($rule['marginleft']),
      'margin-right'     => intval($rule['marginright']),
      'text-align'       => $rule['textalign'],
      'text-indent'      => intval($rule['textindent']),
      'text-transform'   => $rule['texttransform'],
      'text-decoration'  => ($rule['underline'] ? 'underline' : 'none'),
      'letter-spacing'   => intval($rule['letterspacing']),
      'opacity'          => (!empty($rule['opacity']) ? $rule['opacity'] : '100'),
      'leading'          => intval($rule['leading']),
      'kerning'          => ($rule['kerning'] ? 'true' : 'false'),
      'cursor'           => $rule['cursor'],    
    ),
    'a' => array(
      'text-decoration' => 'none',
    ),
    'a:link' => array(
      'color' => $rule['linkcolor'],
    ),
    'a:hover' => array(
      'color' => $rule['hovercolor'],
      'text-decoration' => ($rule['underline'] ? 'underline' : 'none'),
    ),
  );

  return array('font' => $font_path, 'selector' => $rule['selector'], 'css' => $css, 'wmode' => $rule['wmode']);
}

/**
 * Wrap execution handler around JavaScript rules.
 * 
 * @param array $rules
 *   An array of all current rules for this plugin.
 * 
 * @return string
 *   JavaScript settings which can be used by another script to perform 
 *   transformations.
 */
function sifr3_render_wrap_rules($rules) {
  $output = '';
  $output .= "Drupal.behaviors.renderSIFR3 = function () {\n";
  if (is_array($rules)) {
    $fonts = array();
    $rules_output = '';
    foreach ($rules as $rule) {
      // Build JavaScript-safe variable name.
      $rule['fontname'] = preg_replace('@[^a-zA-Z0-9_-]@', '', $rule['font']);
      // Output sIFR font object once for each font.
      if (!isset($fonts[$rule['fontname']])) {
        $fonts[$rule['fontname']] = $rule['fontname'];
        $output .= "  var ". $rule['fontname'] ." = { src: '". $rule['font'] ."' };\n";
      }
      // Prepare replacement rules.
      $rules_output .= "  sIFR.replace(". $rule['fontname'] .", ". drupal_to_js($rule) .");\n";
    }
    // Output sIFR font activation.
    $output .= "  sIFR.activate(". implode(', ', $fonts) .");\n";
    // Output sIFR font replacements.
    $output .= $rules_output;
  }
  $output .= "}\n";
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
function sifr3_render_css_screen($rules) {
  $output = "
@media screen {
  .sIFR-flash {
    visibility: visible !important;
    margin: 0;
    padding: 0;
  }
  
  .sIFR-replaced, .sIFR-ignore {
    visibility: visible !important;
  }
  
  .sIFR-alternate {
    position: absolute;
    left: 0;
    top: 0;
    width: 0;
    height: 0;
    display: block;
    overflow: hidden;
  }
  
  .sIFR-replaced div.sIFR-fixfocus {
    margin: 0pt; 
    padding: 0pt; 
    overflow: auto; 
    letter-spacing: 0px; 
    float: none;
  }
}

@media print {
  .sIFR-flash {
    display    : none !important;
    height     : 0;
    width      : 0;
    position   : absolute;
    overflow   : hidden;
  }
  
  .sIFR-alternate {
    visibility : visible !important;
    display    : block   !important;
    position   : static  !important;
    left       : auto    !important;
    top        : auto    !important;
    width      : auto    !important;
    height     : auto    !important;
  }
}

";
  $output .= "@media screen {";
  foreach ($rules as $rule) {
    $fontsize       = trim($rule['fontsize']) ? "  font-size: $rule[fontsize];\n" : '';
    $letterspacing  = trim($rule['letterspacing']) ? "  letter-spacing: $rule[letterspacing];\n" : '';
    $rule['selector'] = str_replace(',', ', .sIFR-active ', $rule['selector']);
    $output .= "
  .sIFR-active $rule[selector] {
    visibility: hidden;
  $fontsize$letterspacing}
";
  }
  $output .= '}';

  return $output;
}

/**
 * Load plugin JavaScript and stylesheet files.
 * 
 * Perform all necessary actions to load this plugin on all pages.
 */
function sifr3_render_load() {
  $plugindir = render_find_render('sifr3');
  if (!$plugindir) {
    $info = sifr3_render_info();
    $link_sifr   = l($info['title'], $info['url']);
    $link_readme = l('sifr3-README.txt', drupal_get_path('module', 'render') .'/plugins/sifr3-README.txt');
    drupal_set_message(t('The sIFR library is in not installed correctly. Please download it from !link and follow installation instructions in !readme.', array('!link' => $link_sifr, '!readme' => $link_readme)), 'error');
  }
  else {
    drupal_add_js($plugindir .'/sifr.js');
  }
}

