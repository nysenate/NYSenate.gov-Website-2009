<?php
// $Id: views-view-field.tpl.php,v 1.1 2008/05/16 22:22:32 merlinofchaos Exp $
 /**
  * This template is used to print a single field in a view. It is not
  * actually used in default Views, as this is registered as a theme
  * function which has better performance. For single overrides, the
  * template is perfectly okay.
  *
  * Variables available:
  * - $view: The view object
  * - $field: The field handler object that can process the input
  * - $row: The raw SQL result that can be used
  * - $output: The processed output that will normally be used.
  *
  * When fetching output from the $row, this construct should be used:
  * $data = $row->{$field->field_alias}
  *
  * The above will guarantee that you'll always get the correct data,
  * regardless of any changes in the aliasing that might happen if
  * the view is modified.
  */
?>
<?php
$default_image = '<img src="' . base_path() . path_to_theme() . '/images/nyss_seal_120x90.png" alt="See video" alt="See video" id="thumbnail" width="120" height="90" />';
// string begins <a href, ends ></a>
// if there's an image, it should have a string that begins '<img src=" and ends '></a>'
// If there's an image, there should be a value packed away in 
//    $row->node_data_field_video_field_video_data
?>
<?php 
$row_data = unserialize($row->node_data_field_video_field_video_data);
$url = $row_data['thumbnail']['url'];
if (!$url) {
  $output = str_replace('></a>', ">$default_image</a>", $output);
}
print $output; ?>