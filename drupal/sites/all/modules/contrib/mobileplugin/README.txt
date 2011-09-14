// $Id: README.txt,v 1.4 2010/01/25 21:29:10 teemule Exp $

Mobile Plugin provides a mobile optimized view to a Drupal site.

Features
 * Automatic device detection
 * Domain based mobile site distinction
 * A block for user to select mobile or full desktop site
 * A distinct theme for the mobile site (documented theme provided)
 * Separate block administration for the mobile site
 * Filtering out system or module CSS and JS if not specifically allowed
 * Suggesting word breaks to long words
 * Scaling images smaller or setting smaller view size to external images
 * Replacing embedded youtube videos with thumbnails to m.youtube
 * Separate configurable mobile groups based on device properties
 * Testing for selected roles or from the administration
 * Hooks and API to extend or support in other modules

Authors:
Teemu Lehtinen, Mikko Hyytiainen @ Nitro FX Oy, Finland
Andrea Trasatti

Included code from project:
http://simplehtmldom.sourceforge.net

INSTALLATION

You will need a mobile optimized Drupal theme to properly use this module.
Install and enable a simple mobile theme mobile_garland.
  http://drupal.org/project/mobile_garland

1. Download the latest stable Mobile Plugin -release for your Drupal branch.
2. Extract the contents to your sites/all/modules -folder.
3. Enable the module and optimizations in
     Administer > Site building > Modules
4. Enable the module for your test roles in
     Administer > User management > Access control

After testing enable the module for all roles in
  Administer > User management > Access control

To enable users to override automatic device detection add a full/mobile
switch -block to a desired region on your site in
  Administer > Site building > Blocks

See the guide at drupal.org for more information
  http://drupal.org/node/458912
