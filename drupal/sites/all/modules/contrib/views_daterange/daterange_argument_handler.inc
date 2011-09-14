<?php
// $Id: daterange_argument_handler.inc,v 1.1 2009/03/18 19:35:22 crell Exp $

class daterange_argument_handler extends date_api_argument_handler {

  /**
   * Provide a link to the next level of the view from the summary.
   */
  function summary_name($data) {
    // Dispaly "$period $year".
    return $value = $data->{$this->name_alias} .' '. $data->year_sql;
  }

  /**
   * Provide the argument to use to link from the summary to the next level;
   * this will be called once per row of a summary, and used as part of
   * $view->get_url().
   *
   * @param $data
   *   The query results for the row.
   */
  function summary_argument($data) {
    $value = $data->{$this->name_alias};
    $year = $data->year_sql;

    // Get the date range for this period so that we can build the appropriate
    // argument.
    $range = $this->options['periods'][$value];

    // Convert the day of the year into an actual date stamp.
    $start_date = date_create();
    date_date_set($start_date, $year, $range['start']['month'], $range['start']['day']);
    $start_date = date_format_date($start_date, 'custom', 'Y-m-d');
    $end_date = date_create();
    date_date_set($end_date, $year, $range['end']['month'], $range['end']['day']);
    $end_date = date_format_date($end_date, 'custom', 'Y-m-d');

    $value = $start_date .'--'. $end_date;

    return $value;
  }

  /**
   * Create a summary query that matches the granularity.
   *
   * Needed or Views will do a groupby on the complete date instead
   * of only the part of the date actually used in the argument.
   */
  function summary_query() {
    $this->get_query_fields();

    // No way to do summaries on more than one field at a time.
    if (count($this->query_fields) > 1) {
      return;
    }

    $field = $this->query_fields[0]['field'];
    $date_handler = $this->query_fields[0]['date_handler'];

    // $sql_field is the date field, after timezone normalization and other nastiness
    // that Date_API module fortunately handles for us.  The resulting SQL is not pretty.
    $sql_field = $date_handler->sql_field($field['fullname']);

    // %m-%d is month-day, 2 digit format for both.  The extra % is to keep
    // Drupal's DB layer from eating the %d as a placeholder.
    $date_sql = "DATE_FORMAT($sql_field, '%m-%%d')";
    $year_sql = "YEAR($sql_field)";

    /* $this->options['periods'] is an array that looks something like this:

    $periods['period 1']['start']['month'] = 1;
    $periods['period 1']['start']['day'] = 1;
    $periods['period 1']['end']['month'] = 4;
    $periods['period 1']['end']['day'] = 15;
    $periods['period 2']['start']['month'] = 4;
    $periods['period 2']['start']['day'] = 16;
    $periods['period 2']['end']['month'] = 8;
    $periods['period 2']['end']['day'] = 31;
    $periods['period 3']['start']['month'] = 9;
    $periods['period 3']['start']['day'] = 1;
    $periods['period 3']['end']['month'] = 12;
    $periods['period 3']['end']['day'] = 31;
    */

    // Build up the SQL fragment to give us the
    $fragment = 'CASE ';

    foreach ($this->options['periods'] as $period => $range) {
      $start = sprintf("%02s-%02s", $range['start']['month'], $range['start']['day']);
      $end = sprintf("%02s-%02s", $range['end']['month'], $range['end']['day']);
      $fragment .= "WHEN {$date_sql} BETWEEN '{$start}' AND '{$end}' THEN '{$period}' ";

      // We will need a list of periods in order later, so just build it now
      // while we're already looping.  Note the quotations around $period, as
      // it is a string.
      $period_list[] = "'{$period}'";
    }

    $default_period = t('Default');
    $fragment .= "ELSE '{$default_period}' END ";


    /*  The resulting SQL fragment will look something like this, give or take whitespace:

    CASE
      WHEN $date_sql BETWEEN '01-01' AND '03-31' THEN 'First Period'
      WHEN $date_sql BETWEEN '04-01' AND '06-30' THEN 'Second Period'
      ...
      ELSE '$default'
    END
    */

    // Save the big ugly case statement as the formula for the grouping field
    // so that Views knows about it.
    $this->formula = $fragment;

    $this->ensure_my_table();

    // Add the computed "period" field to the query.
    $this->base_alias = $this->name_alias = $this->query->add_field(NULL, $this->formula, $field['query_name']);

    // Add the year to the query.  (Year is computed off of the date.)
    $this->query->add_field(NULL, $year_sql, 'year_sql');

    // We want to count based on the period field.
    $this->query->set_count_field(NULL, $this->formula, $field['query_name']);

    // Restrict the summary to the years that were specified.
    // @todo: Would this be faster as a HAVING?
    $years = date_range_years($this->options['year_range']);
    $this->query->add_where(0, $year_sql .' BETWEEN %d AND %d', array($years['0'], $years['1']));

    // Order the query by year, then the period.
    // FIELD(fieldname, list of fields) is a MySQL ism that allows a field to be
    // ordered in a custom way based on a provided list.  In this case we provide
    // it with the list of periods in the order they were entered into the
    // options form.  That allows, for instance, "Fourth" to come after "Third"
    // instead of after "First".
    $this->query->add_orderby(NULL, NULL, 'ASC', 'year_sql');
    $period_list = implode(', ', $period_list);
    $this->query->add_orderby(NULL, NULL, 'ASC', "FIELD({$this->base_alias}, {$period_list})");

    // summary_basics() will add a group by for the primary field (the date).  We
    // want to group by the year first, THEN by the primary field.  So we add
    // the group by here, then let Views do its default thing, and everything
    // happens in the correct order.
    $this->query->add_groupby('year_sql');

    $this->summary_basics(FALSE);
  }

  function options(&$options) {
    parent::options($options);

    // The granularity field no longer applies for this argument type, since
    // the whole point is to have a completely custom granularity.
    unset($options['granularity']);

    $options['periods'] = array();
  }

  /**
   * Add a form element to select date_fields for this argument.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // The granularity field no longer applies for this argument type, since
    // the whole point is to have a completely custom granularity.
    unset($form['granularity']);

    $form['periods'] = array(
      '#type' => 'fieldset',
      '#title' => t('Date ranges'),
      '#description' => t('Specify the date ranges within a year to query for.  Note that any part of the year that is not accounted for will be included in a default range of "Default", so make sure you cover the entire year.'),
    );

    // We want to retheme the form to show as a table.
    $form['periods']['ranges']['#theme'] = 'daterange_periods_form';

    $i = 0;
    if (!empty($form_state['post']['options']['periods']['ranges'])) {
      foreach ($form_state['post']['options']['periods']['ranges'] as $range) {
        $form['periods']['ranges']['range_'. $i++] = $this->daterange_form_fragment($range['period'], $range);
      }
    }
    else {

      foreach ($this->options['periods'] as $period => $range) {
        $form['periods']['ranges']['range_'. $i++] = $this->daterange_form_fragment($period, $range);
      }
    }

    // And always ensure there's at least one empty range.
    $form['periods']['ranges']['range_'. $i++] = $this->daterange_form_fragment();

    $form['periods']['add_range'] = array(
      '#type' => 'button',
      '#value' => t('Add range'),
    );
  }

  function daterange_form_fragment($period = '', $range = array()) {

    static $months;
    static $days;

    if (empty($months)) {
      $months = array(
        1  => t('January'),
        2  => t('February'),
        3  => t('March'),
        4  => t('April'),
        5  => t('May'),
        6  => t('June'),
        7  => t('July'),
        8  => t('August'),
        9  => t('September'),
        10 => t('October'),
        11 => t('November'),
        12 => t('December'),
      );
      $days = drupal_map_assoc(range(1, 31));
    }

    $form['period'] = array(
      '#type' => 'textfield',
      '#title' => t('Label'),
      '#default_value' => $period,
      '#size' => 20,
    );
    $form['start']['month'] = array(
      '#type' => 'select',
      '#title' => t('Start month'),
      '#options' => $months,
      '#default_value' => isset($range['start']['month']) ? $range['start']['month'] : 1,
    );
    $form['start']['day'] = array(
      '#type' => 'select',
      '#title' => t('Start day'),
      '#options' => $days,
      '#default_value' => isset($range['start']['day']) ? $range['start']['day'] : '',
    );
    $form['end']['month'] = array(
      '#type' => 'select',
      '#title' => t('End month'),
      '#options' => $months,
      '#default_value' => isset($range['end']['month']) ? $range['end']['month'] : 1,
    );
    $form['end']['day'] = array(
      '#type' => 'select',
      '#title' => t('End day'),
      '#options' => $days,
      '#default_value' => isset($range['end']['day']) ? $range['end']['day'] : '',
    );

    return $form;
  }

  function options_validate($form, &$form_state) {
    // It is very important to call the parent function here:
    parent::options_validate($form, $form_state);

    // @todo: Validate that the provided dates are valid.  (No April 31st, etc.)

  }

  function options_submit($form, &$form_state) {
    // It is very important to call the parent function here:
    parent::options_submit($form, $form_state);

    // We need to mutate the period data from the form version to the stored
    // version.  The stored version is optimized for easy reading on the
    // display side.  Note we don't actually save the data ourselves; Views
    // does that for us later.

    // Because the date argument form is multi-step, we need to deliberately
    // skip over this whole process if we're not on our own step.  Somehow
    // it still works.  Views magic.
    if (isset($form_state['values']['options']['periods']['ranges'])) {
      $periods = array();
      foreach ($form_state['values']['options']['periods']['ranges'] as $range) {
        // Filter out empty definitions.
        if (!empty($range['period'])) {
          $periods[$range['period']] = array('start' => $range['start'], 'end' => $range['end']);
        }
      }
      $form_state['values']['options']['periods'] = $periods;
    }
  }
}
