// $Id$

$(document).ready(function(){
  $.ajax({                  
    type: "GET",
    url: '/sites/all/modules/custom/nyss_session/session_get_status.php',
    dataType: "json",
    success: parseJSON,
    error: err
  });
});

function err(xhr, reason, ex)
{
//   alert("error");
}
function parseJSON(json)
{
  if (json.internal) {
    $('#conditional-livestream').html('<p>We have detected that you are visiting NYSenate.gov from the Senate network.</p><h3>To watch Senate session live, select:<br /><a href="http://senreal2.senate.state.ny.us/ramgen/sennettv.smil" target="_blank">RealPlayer Video</a> or <a href="http://senreal2.senate.state.ny.us/ramgen/senaudch.smil" target="_blank">RealPlayer Audio Stream</a>.</h3><p>(RealPlayer delivers high-quality video and audio to hundreds of Senate users simultaneously across the Senate\'s own network. So you won\'t have to compete with the general public on the Internet to catch Senate events, and Internet slowdowns or outages won\'t affect you.)</p><p>If you are looking for a Committee hearing or an other event that is not streamed via Real, visit <a href="http://www.livestream.com/nysenate" target="_blank">NYSenate on Livestream.com</a> (alternate Livestream channels: <a href="http://www.livestream.com/nysenate2" target="_blank">NY Senate 2</a>, <a href="http://www.livestream.com/nysenate3" target="_blank">NY Senate 3</a>, <a href="http://www.livestream.com/nysenate4" target="_blank">NY Senate 4</a>, or <a href="http://www.livestream.com/rulesreformandadministration" target="_blank">Rules Reform and Administration</a>). Also, you can visit our NYSenate Clips on <a href="http://www.youtube.com/nysenate" target="_blank">YouTube</a> or <a href="http://nysenate.blip.tv/" target="_blank">Blip.tv</a> or our NYSenate Uncut on <a href="http://www.youtube.com/nysenateuncut" target="_blank">YouTube</a> or <a href="http://nysenateuncut.blip.tv/" target="_blank">Blip.tv</a>.</p>');
  }
  $('#conditional-livestream').show();
}
