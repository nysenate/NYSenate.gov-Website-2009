//$Id: cck_select_other.js,v 1.1.2.4 2010/06/10 18:03:21 mradcliffe Exp $

/**
 *  cck_select_other javascript file 
 */

var cckSelectOther = {};

Drupal.behaviors.cckSelectOther = function (context) {

//  $.browser.msie == true ? $(this).click(Drupal.ConditionalFields.fieldChange) : $(this).change(Drupal.ConditionalFields.fieldChange); 

  $.browser.msie == true ? $(this).click(cckSelectOther.switch) : $(this).change(cckSelectOther.switch);

//  document.write(Drupal.settings.CCKSelectOther.field.length);
  var field_str = new String(Drupal.settings.CCKSelectOther.field);
  var fields = new Array();
  fields = field_str.split(',');

  // i is our index
  for (i in fields) {
    var field = fields[i].replace(/_/g, '-');

    var selectId = 'edit-field-' + field + '-select-other-list';
    var inputId = 'edit-field-' + field + '-select-other-text-input-wrapper';
    var value = $('#' + selectId + ' option:selected').val();

    // if value == other then display as block else don't display
    $('#' + inputId).css('display', (value == "other") ? 'block' : 'none');
  }

}

cckSelectOther.switch = function () {
  var field_str = new String(Drupal.settings.CCKSelectOther.field);
  var fields = new Array();
  fields = field_str.split(',');

  for (i in fields) {
    var field = fields[i].replace(/_/g, '-');

    var selectId = 'edit-field-' + field + '-select-other-list';
    var inputId = 'edit-field-' + field + '-select-other-text-input-wrapper';
    var value = $('#' + selectId + ' option:selected').val();

    // if value == other then display as block else don't display
    $('#' + inputId).css('display', (value == "other") ? 'block' : 'none');
  }
}
