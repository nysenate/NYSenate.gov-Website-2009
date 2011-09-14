if (Drupal.jsEnabled) {
  $(document).ready(function(){
    // When the Senator has changed, load new possible committes the Senator chairs.
    $('#edit-field-senator-0-nid-nid').change(function(){
      // Disable our committee select element until we have the new data.
      $('#edit-field-committee-nid-nid').attr('disabled', 'disabled').addClass('nyss-editors-waiting');
      $.ajax({
        type: 'POST',
        data: {
          nid: $('#edit-field-senator-0-nid-nid').val(),
          value: $('#edit-field-committee-nid-nid').val()
        },
        url: Drupal.settings.nyss_editors.senator_select_committees_url,
        dataType: 'json',
        success: function(data) {
          if (data.status) {
            // Success! Enable the select and put in the new data.
            $('#edit-field-committee-nid-nid').removeAttr('disabled').removeClass('nyss-editors-waiting').html(data.options);
          }
          else {
            // Failed for some reason.
            alert(data.errorMessage);
            $('#edit-field-committee-nid-nid').removeAttr('disabled').removeClass('nyss-editors-waiting');
          }
        },
        error: function(XMLHttpRequest, textStatus, errorThrown) {
          alert('An HTTP error '+ XMLHttpRequest.status +' occurred.\n'+ Drupal.settings.nyss_editors.senator_select_committees_url);
          $('#edit-field-committee-nid-nid').removeAttr('disabled').removeClass('nyss-editors-waiting');
        }
      });
    });
  });
}
