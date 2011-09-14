<?php
_pathauto_include();
?>
<?php
if ($cd){
?>
<div style="float: left; width: 215px; padding: 0 10px 30px 0;" class="senator-search-left">
<h3><?php echo t('Your Senator')?> </h3>
<div style="float: left; padding-right: 10px;">
<a class="picture" href="<?php print url('node/'. $senator->nid)?>  ">
<img src="<?php echo base_path(). file_directory_path(). '/imagecache/senator_teaser/profile-pictures/' . $senator->field_profile_picture[0]['filename'] ?> " alt=" <?php print $senator->title ?> photo" /></a></div>
<div style="float: left; clear: right;"><a href="<?php echo url('node/'. $senator->nid)?>">Sen. <?php echo $senator->title ?></a><br />
<?php  echo substr($senator->field_party_affiliation[0]['value'], 0, 1) . '-' . t('District') . $cd_upper;?>
</div>
<div style="clear: both;">
<p><?php echo theme('locations', $senator->locations, $hide); ?></p>
<?php echo theme('item_list', $items, t('Your Districts'));?>
</div></div>
  
<div style="float: left; width: 300px; padding: 0 0 30px 0;" class="senator-search-right">
<h3> <?php echo t('Contact Your Senator')?></h3>
<?php echo drupal_get_form('nyss_contact_mail_senator', $senator, $zip);?>
</div>    
<div style="clear: both; border-top: solid 1px #E2DED5; padding: 20px 0 0 0;"><p><?php echo t('Not your district? Try:')?> </p></div>
<?php 
}
else {
?>
<p> <?php echo t('Your district could not be located. Try:')?></p>
<?php     
}
?>

<ul>
<li><?php echo l(t('Viewing the district map'), 'districts/map')?></li>
<li><?php echo l(t('Picking from a list of all Senators'), 'senators')?></li>
<li><?php echo l(t('Contacting the NY State Senate technology team for help'), 'contact')?></li>
<li><?php echo t('Searching again in the top-left corner of this screen.') ?></li>
</ul>
<p style="padding-top: 1em;"><?php echo 
    t(
      '<em>Residents of Queens:</em> Addresses that contain hyphens (ie 12-34 Main St.) may occasionally produce inaccurate search results. ' .
      'If you live in Queens, please use the !lookup_link to verify your Senator. We apologize for any inconvenience.',
      array(
        '!lookup_link' => l(t('New York Board of Election look up tool'), 'http://nymap.elections.state.ny.us/nysboe/')
      )
    ) ?></p>
