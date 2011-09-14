<div class="frontpage-senator-spotlight">
  <div class="frontpage-senator-photo">
    <?php print theme('imagecache', 'frontpage_senator_photo', $senator->field_profile_picture[0]['filepath'], $senator->title, $senator->title, array('align' => 'left')); ?>
  </div>
  <div class="frontpage-senator-title"><?php print l($senator->title, 'node/'.$senator->nid); ?></div>
  <div class="frontpage-senator-district">
    <?php
      $district = node_load($senator->field_senators_district[0]['nid']);
      print $district->title;
    ?>
  </div>
  <div class="frontpage-senator-links">
    <?php print l(t('Biography'), $senator->path.'/bio') . ' | ' . l(t('Contact'), $senator->path.'/contact'); ?>
  </div>
  <?php print theme('nyss_senator_social_buttons', $senator->nid); ?>
</div>
<div class="frontpage-senator-spotlight-explanation">
  <?php print t("This area features information about individual members of the Senate on a rotating, non-partisan basis. Click to read this Senator's biography, or find your Senator's website below."); ?>
</div>
