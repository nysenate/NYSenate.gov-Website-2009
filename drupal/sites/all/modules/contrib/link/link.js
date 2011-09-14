// $Id: link.js,v 1.1.2.3 2007/11/16 04:11:58 quicksketch Exp $

/**
 * Attaches add more fields behaviour to any form.
 * Dynamic adding of fields requires:
 *   - a button to click to produce more fields (id="field-name-more")
 *   - a wrapper div around the set of fields to be duplicated (id="field-name-wrapper")
 *     additional fields will be prepended to the end of this fieldset
 *   - a hidden element counter with the current number of fields (id="field-name-count")
 *   - field-name should be replaced by a unique identifier for your field
 *   - a callback function which produces an additional field
 */
Drupal.linkAutoAttach = function() {
  $('input.more-links').each(function() {
    var uri = this.value;
    // Extract the base name from the id (my-text-field-url -> my-text-field).
    var base = this.id.substring(0, this.id.length - 9);
    var button = base + '-more';
    var wrapper = base + '-wrapper';
    var counter = base + '-count';
    var link = new Drupal.jslink(uri, button, wrapper, counter);
  });
};

/**
 * JS jslink object.
 */
Drupal.jslink = function(uri, button, wrapper, counter) {
  this.button = '#'+ button;
  this.wrapper = '#'+ wrapper;
  this.counter = '#'+ counter;
  Drupal.redirectFormButton(uri, $(this.button).get(0), this);
};

/**
 * Handler for the form redirection submission.
 */
Drupal.jslink.prototype.onsubmit = function() {
  // Increment count
  var count = parseInt($(this.counter).val());
  $(this.counter).val(count + 1);
};

/**
 * Handler for the form redirection completion.
 */
Drupal.jslink.prototype.oncomplete = function(data) {
  // Avoid unnecessary scrolling
  Drupal.freezeHeight(); 

  // Place HTML into temporary div
  var div = document.createElement('div');
  $(div).html(data);

  // Append to form and update behaviour
  $(div).hide();
  $(this.wrapper).append(div);
  $(div).slideDown('fast');
  Drupal.linkAutoAttach();
    
  Drupal.unfreezeHeight();
};

/**
 * Handler for the form redirection error.
 */
Drupal.jslink.prototype.onerror = function(error) {
  alert('An error occurred:\n\n'+ error);
};

// Global killswitch
if (Drupal.jsEnabled) {
  $(document).ready(Drupal.linkAutoAttach);
};
