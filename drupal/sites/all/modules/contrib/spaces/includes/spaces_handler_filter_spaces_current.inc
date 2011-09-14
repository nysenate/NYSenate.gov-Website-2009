<?php
/**
 * Spaces view filter handler.
 * 
 * This filter delegates filtering to the 'views_filter' method on the calling space object.
 * Refer to the 'space_og' class in the Spaces OG module for an example implementation.  If
 * you are creating your own space type by implementing the 'space' interface, you can use
 * as-is or modify the 'views_filter' method for the purposes of your space type.
 */
class spaces_handler_filter_spaces_current extends views_handler_filter {
  /**
   * Meta query handler which delegates query building to the
   * implementing spaces.
   */
  function query() {
    $space = spaces_get_space();
    if ($space && $space->type != 'site') {
      if ($this->relationship) {
        $base_table = $this->view->query->relationships[$this->relationship]['table'];
      }
      else {
        $base_table = $this->view->base_table;
      }
      $space->views_filter($this->view->query, $base_table, $this->relationship);
    }
    else if ($this->options['operator'] === 'all') {
      // Set a failure condition and let the display manager handle it.
      $this->view->build_info['fail'] = TRUE;
    }
  }

  /**
   * Provide a form for setting the operator.
   *
   * This may be overridden by child classes, and it must
   * define $form['operator'];
   */
  function operator_form(&$form, &$form_state) {
    $options = $this->operator_options();
    if (!empty($options)) {
      $form['operator'] = array(
        '#type' => 'select',
        '#title' => t('When not in a space'),
        '#default_value' => $this->operator,
        '#options' => $options,
        '#description' => t('Helpful if you want to use this view both inside and out of spaces.'),
      );
    }
  }

  /**
   * Provide filter application conditions.
   */
  function operator_options() {
    return array(
      'all' => t('Hide all results'),
      'active' => t('Show all results'),
    );
  }
}
