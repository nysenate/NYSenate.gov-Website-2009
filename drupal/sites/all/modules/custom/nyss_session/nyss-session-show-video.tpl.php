<?php
  $status = nyss_session_get_status();
  $current_channel = variable_get('nyss_videosettings_main_livestream_channel', 'nysenate');
?>
<p><?php print $status['message']; ?></p>
<?php if ($status['display_video']): ?>
  <?php if (!nyss_internalusers_is_internal()): ?>
    <?php if (nyss_videosettings_livestream_working()): ?>
      <center>
        <div id="livestream_block">
          <script src="http://static.mogulus.com/scripts/playerv2.js?channel=<?php print $current_channel; ?>&amp;layout=playerEmbedDefault&amp;backgroundColor=0xffffff&amp;backgroundAlpha=1&amp;backgroundGradientStrength=0&amp;chromeColor=0x000000&amp;headerBarGlossEnabled=true&amp;controlBarGlossEnabled=true&amp;chatInputGlossEnabled=false&amp;uiWhite=true&amp;uiAlpha=0.5&amp;uiSelectedAlpha=1&amp;dropShadowEnabled=true&amp;dropShadowHorizontalDistance=10&amp;dropShadowVerticalDistance=10&amp;paddingLeft=10&amp;paddingRight=10&amp;paddingTop=10&amp;paddingBottom=10&amp;cornerRadius=3&amp;backToDirectoryURL=null&amp;bannerURL=null&amp;bannerText=null&amp;bannerWidth=320&amp;bannerHeight=50&amp;showViewers=true&amp;embedEnabled=true&amp;chatEnabled=false&amp;onDemandEnabled=true&amp;programGuideEnabled=false&amp;fullScreenEnabled=true&amp;reportAbuseEnabled=false&amp;gridEnabled=false&amp;initialIsOn=false&amp;initialIsMute=false&amp;initialVolume=10&amp;contentId=null&amp;initThumbUrl=null&amp;playeraspectwidth=4&amp;playeraspectheight=3&amp;mogulusLogoEnabled=false&amp;width=550&amp;height=430&amp;wmode=window" type="text/javascript"></script>
        </div>
      </center>
    <?php endif; ?>
    <p>Having trouble? Try viewing the video at <a href="http://www.livestream.com/<?php print $current_channel; ?>Livestream.com/nysenate</a>.
    You can also try viewing with our <a href= "http://senreal3.senate.state.ny.us/ramgen/sennet_tv.smil">RealPlayer Stream.</a> 
    Or, try our <a href="http://senreal3.senate.state.ny.us/ramgen/sennet_audio.smil">RealPlayer Audio Stream</a><br />
    Visit our <a href = "http://www.youtube.com/nysenateuncut">uncut video archives on Youtube</a></p>
  <?php else: ?>
    <?php print theme('nyss_internalusers_message'); ?>
  <?php endif; ?>
<?php endif; ?>