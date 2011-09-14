<?php
// $Id: context_reaction_http_header.inc,v 1.1 2010/04/21 17:02:16 febbraro Exp $

/**
 * Expose http header changes as context reactions.
 */
class context_reaction_http_header extends context_reaction {

  function options_form($context) {
    $values = $this->fetch_from_context($context);
    
    $items['http_header'] = array(
      '#title' => t('HTTP Headers'),
      '#tree'  => 'tree',
    );
    // Retrieve hooked module data
    $items_from_hook = module_invoke_all('context_http_header_def');
    
    // get set values from the context for these hooks  
    foreach ($items_from_hook as $header => $item) {
      $items_from_hook[$header]['#default_value'] = $values['http_header'][$header];
    }
    
    $items['http_header'] = array_merge($items['http_header'], $items_from_hook);
    
    return $items;
  }
  
  /**
   * Public method that is called from hooks or other integration
   * points.
   */
  function execute() {
    $contexts = $this->get_contexts();
   
    // for every context
    foreach ($contexts as $context) {
      $http_header_items = $context->reactions['http_header']['http_header'];
      $header_builds = module_invoke_all('context_http_header_build', $http_header_items);
            
      // parse the header builds for the header and the action
      
      $headers = _context_http_header_header_map($header_builds);

      // add headers to the page
      foreach ($headers as $header) {
        drupal_set_header($header);
      }
    }
  }
}