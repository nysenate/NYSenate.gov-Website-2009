<?php
// $Id: node_export.api.php,v 1.1.2.8 2010/11/30 01:43:16 danielb Exp $

/**
 * @file
 * Documents node_export's hooks for api reference.
 */

/**
 * Override export access on a node.
 *
 * Let other modules alter this - for example to only allow some users to
 * export specific nodes or types.
 *
 * @param &$access
 *   Boolean access value for current user.
 * @param $node
 *   The node to determine access for.
 */
function hook_node_export_access_alter(&$access, $node) {
  // no example code
}

/**
 * Manipulate a node on import/export.
 *
 * @param &$node
 *   The node to alter.
 * @param $original_node
 *   The unaltered node.
 * @param $method
 *   'export' for exports, and 'prepopulate' or 'save-edit' for imports
 *   depending on the method used.
 */
function hook_node_export_node_alter(&$node, $original_node, $method) {
  // no example code
}

/**
 * Override one line of the export code output.
 *
 * @param &$out
 *   The line of output.
 * @param $tab
 *   The $tab variable from node_export_node_encode().
 * @param $key
 *   The $key variable from node_export_node_encode().
 * @param $value
 *   The $value variable from node_export_node_encode().
 * @param $iteration
 *   The $iteration variable from node_export_node_encode().
 */
function hook_node_export_node_encode_line_alter(&$out, $tab, $key, $value, $iteration) {
  // Start with something like this, and work on it:
  $out = $tab ."  '". $key ."' => ". node_export_node_encode($value, $iteration) .",\n";
}

/**
 * Manipulate node array before bulk export or import.
 *
 * The purpose of this is to allow a module to check nodes in the array for
 * two or more nodes that must retain a relationship, and to add/remove other
 * data to the array to assist with maintaining dependencies, relationships,
 * references, and additional data required by the nodes.
 *
 * @param &$nodes
 *   The node array to alter.
 * @param $op
 *   'import', 'after import', or 'export'.
 */
function hook_node_export_node_bulk_alter(&$nodes, $op) {
  // no example code
}

/**
 * Circumvent the default node export output method.
 *
 * @param &$return
 *   The node export code.  Leave as FALSE for no change.
 * @param $var
 *   The node.
 * @param $format
 *   A string indicating what the export format is, and whether to do anything.
 */
function hook_node_export_node_encode_alter(&$return, $var, $format) {
  // your code here

  /*
   Initially $return will be FALSE, if you change $return to something else,
   you will override node_export's default node code to whatever that value is.
   $var contains the node object.
   Now you could either decide to always override the $return value (which
   would be a problem if multiple modules decided to do that as only one of
   them would work), but it would be better to only intervene when $format is
   set to some string that your module recognises. The idea is that if we went
   to the URL node/40/node_export/xml it would try to export node 40 with 'xml'
   as the $format.
   (You do not need to actually return anything)
   */
}

/**
 * Circumvent the default node import method.
 *
 * @param &$return
 *   The array/object to return to node export.
 * @param $string
 *   The node code.
 */
function hook_node_export_node_decode_alter(&$return, $string) {
  // your code here

  /*
   This goes hand-in-hand with hook_node_export_node_encode_alter().
   You would have to autodetect the format in the $string and change the
   $return value if required.
   (Don't return anything)
  */
}

/**
 * Circumvent the default bulk node export output method.
 *
 * @param &$node_code
 *   The node export code.  Leave as FALSE for no change.
 * @param $nodes
 *   The node.
 * @param $format
 *   A string indicating what the export format is, and whether to do anything.
 */
function hook_node_export_node_bulk_encode_alter(&$node_code, $nodes, $format) {
  // your code here

  /*
   Again, $node_code starts off as FALSE, if you change it you override it
   Your code would ideally loop through $nodes, pass them off to the function
   you created earlier to export single nodes, and then somehow concatenate all
   the returns from that function into $node_code.
   (again, you don't actually return anything)

   You should also implement your own hook_node_operations() following what
   node_export did, but changing the label slightly, and adding the 2nd callback
   argument that is your $format string. But keep the callback the same as
   node_export, don't replace that.
  */
}

/**
 * Register a format handler, for exporting code using other methods.
 *
 * @return
 *   An array keyed by format names containing an array with keys #title and
 *   #module, where the value for #title is the display name of the format, and
 *   the value for #module is the module that implements it.
 */
function hook_node_export_format_handlers() {
  return array(
    'format_short_name' => array(
      '#title' => t('Format Title'),
      '#module' => 'format_module_name',
    ),
  );
}