if (Drupal.jsEnabled) {
  $(document).ready(function() {
    $('table.spaces-features select').change(function() {
      if ($(this).val() == 0) {
        $(this).parents('tr').removeClass('enabled').addClass('disabled');
      }
      else {
        $(this).parents('tr').addClass('enabled').removeClass('disabled');
      }
    });
  });
}
