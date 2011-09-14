/* $Id: sifr-README.txt,v 1.7 2008/10/01 11:26:10 sun Exp $ */

-- INSTALLATION --

* Download sifr from http://novemberborn.net/sifr

* Create a sub-folder "sifr" in the module folder of render, i.e.
  modules/render/sifr.

* Copy the following files of that archive into modules/render/sifr/:

  * sifr.js
  * sIFR-print.css

* Upload your .swf font files at admin/settings/render/manage


-- TROUBLESHOOTING --

* If you experience weird font sizings and other presentation 'bugs' try
  altering your stylesheets and sifr settings for

  font-size, padding, margin, line-height

* If text elements are prepended with sifr fonts but not replaced, check if your
  stylesheets were properly loaded (by observing HTML Header) and if you are
  overwriting 'visibility' somewhere in your theme.

* Further help and support for sIFR JavaScript may be found at
  - http://novemberborn.net/sifr
  - http://www.mikeindustries.com/sifr
  - http://wiki.novemberborn.net/sifr/
  - http://forum.textdrive.com/viewforum.php?id=20


-- NOTES --

* Please read the (very easy) sIFR documentation included in the download
  package about creating your own custom sIFR fonts (requires Macromedia/Adobe
  Flash).

* Remember to check copyright / font licenses in front of publishing a font in
  the web.


-- FAQ --

Q: Why do sIFR links open in a new window instead of the current (_self)?

A: This seems to be a bug in the sIFR Action Script. If you still experience
   this bug and you are using the latest sIFR version available on
   http://www.mikeindustries.com/sifr/, you need to
   - alter the file dont_customize_me.as as described here
   - and re-create your sIFR fonts.

   In line 26 change:
<code>
function launchURL (index) {
	launchURL_anchor = eval("sifr_url_"+index);
	launchURL_target = eval("sifr_url_"+index+"_target");
	getURL(launchURL_anchor,launchURL_target);
}
</code>

   To:
<code>
function launchURL (index) {
	launchURL_anchor = eval("sifr_url_"+index);
	launchURL_target = eval("sifr_url_"+index+"_target");
	if ( launchURL_target != undefined ) {
		getURL(launchURL_anchor,launchURL_target);
	}
	else {
		getURL(launchURL_anchor);
	}
}
</code>


-- CREDITS --

sIFR plugin (formerly sifr.module) was
developed by Jeff Robbins (www.jjeff.com),
sponsored by Bryght (www.bryght.com) and is 
maintained by Daniel F. Kudwien (www.unleashedmind.com).


