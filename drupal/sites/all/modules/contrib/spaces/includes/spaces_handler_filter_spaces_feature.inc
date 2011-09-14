<?php
// $Id: spaces_handler_filter_spaces_feature.inc,v 1.1.2.1.2.2 2009/05/04 04:59:17 yhahn Exp $

/**
 * Filter to only show node types associated with current feature.
 */
class spaces_handler_filter_spaces_feature extends views_handler_filter {
  
  /**
   * override can_expose()
   */
  function can_expose() {
    return FALSE;
  }
  
  function query() {
    $contexts = context_active_contexts();
    $types = array();
    foreach ($contexts as $context) {
      if (!empty($context->node)) {
        $types = array_merge($types, $context->node);
      }
    }
    $types = drupal_map_assoc($types);

    if (!empty($types)) {
      $placeholders = db_placeholders($types, 'varchar');
      if (!empty($this->relationship)) {
        $table = $this->relationship;
      }
      else {
        $table = $this->query->ensure_table('node');
      }
      $this->query->add_where($this->options['group'], "$table.type IN ($placeholders)", $types);
    }
  }
}
