$Id: README.txt,v 1.1.2.2.2.1 2008/12/02 20:22:46 robloach Exp $

Description
-----------
This module provides a central function for adding jCarousel jQuery plugin
elements. For more information about jCarousel, visit the official project:
http://sorgalla.com/jcarousel/


Installation
------------
1) Place this module directory in your modules folder (this will usually be
"sites/all/modules/").

2) Enable the module.


Usage
-----
The jcarousel_add function allows you to not only add the required jCarousel
JavaScript, but also apply the jCarousel to the elements on the page. The
arguments are as follows:

  jcarousel_add($selector, $options, $skin, $skin_path);

The $selector is the jQuery selector element to apply the jCarousel to. This
can usually be thought of as the #ID of the element (#carousel).

The $options are the configuration options that are sent during the creation
of the jCarousel element (optional). The configuration options can be found at:
http://sorgalla.com/projects/jcarousel/#Configuration

The $skin is the name of the skin to use (tango, ie7 or your own) (optional).

The $skin_path is only used if you're using a custom skin, and references the
path to the CSS file for the skin (optional).

See admin/help/jcarousel for a demonstration.
 

Example
-------
The following would add a vertical jCarousel to the page:

  <ul id="mycarousel">
    <li><img src="http://static.flickr.com/66/199481236_dc98b5abb3_s.jpg" width="75" height="75" alt="" /></li>
    <li><img src="http://static.flickr.com/75/199481072_b4a0d09597_s.jpg" width="75" height="75" alt="" /></li>
    <li><img src="http://static.flickr.com/57/199481087_33ae73a8de_s.jpg" width="75" height="75" alt="" /></li>
    <li><img src="http://static.flickr.com/77/199481108_4359e6b971_s.jpg" width="75" height="75" alt="" /></li>
    <li><img src="http://static.flickr.com/58/199481143_3c148d9dd3_s.jpg" width="75" height="75" alt="" /></li>
    <li><img src="http://static.flickr.com/72/199481203_ad4cdcf109_s.jpg" width="75" height="75" alt="" /></li>
    <li><img src="http://static.flickr.com/58/199481218_264ce20da0_s.jpg" width="75" height="75" alt="" /></li>
    <li><img src="http://static.flickr.com/69/199481255_fdfe885f87_s.jpg" width="75" height="75" alt="" /></li>
    <li><img src="http://static.flickr.com/60/199480111_87d4cb3e38_s.jpg" width="75" height="75" alt="" /></li>
    <li><img src="http://static.flickr.com/70/229228324_08223b70fa_s.jpg" width="75" height="75" alt="" /></li>
  </ul>
  <?php
    jcarousel_add('#mycarousel', array('vertical' => TRUE));
  ?>
See jcarousel_help() for more examples.


Author
------
Wim Leers (work@wimleers.com | http://wimleers.com/work)
Rob Loach (http://www.robloach.net)
