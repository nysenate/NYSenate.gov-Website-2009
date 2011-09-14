Drupal.behaviors.spaces_design = function (context) {
  // This behavior attaches by ID, so is only valid once on a page.
  if ($('form#spaces-feature-form .spaces-design-processed').size()) {
    return;
  }
  // Add Farbtastic
  var target = $('form#spaces-features-form input#edit-settings-color', context);
  var farb = $.farbtastic('div#colorpicker', target);
  target.addClass('spaces-design-processed');

  $('.toggle-colorpicker', context).click(function() {
    $('div#colorpicker', context).toggleClass('hidden');
  });
};
