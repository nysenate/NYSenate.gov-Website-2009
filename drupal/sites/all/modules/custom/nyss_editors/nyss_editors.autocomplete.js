// $Id$

/**
 *  @file
 *  Autocomplete selections for office editors.
 */
Drupal.behaviors.nyssAutocomplete = function (context) {
  $('#edit-field-senator-0-nid-nid-autocomplete:not(.nyssAutocomplete-processed)', context).addClass('nyssAutocomplete-processed').each(function () {
    this.value = "/nyss-editors/autocomplete";
  });
};
