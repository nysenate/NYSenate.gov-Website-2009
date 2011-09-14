<?php
$email = $senator->field_email[0]['email'];
if (module_exists('spamspan')) {
  $formatted_email = spamspan($email);
}
else {
  $formatted_email = '<a href="mailto:'. $email .'">'. check_plain($email) .'</a>';
}
$extra_contact_info = $senator->field_extra_contact_information[0]['value'];
?>
<div class="senator-contact-page">
  <p>
    <?php echo theme('locations', $senator->locations, array('latitude', 'longitude')); ?>
    <div class="senator-contact-extra-information"><?php print $extra_contact_info; ?></div>
    <br />
    <strong>Email address:</strong> <?php print $formatted_email; ?>
  </p>
  <div class="block" style="margin-top: 2em;">
    <h2 class="title block_title">Send an Email to Your Senator</h2>
    <?php print drupal_get_form('nyss_contact_mail_senator', $senator); ?>
  </div>
</div>
