
Module: RPX
Author: Peat Bakke <peat@janrain.com>, Nathan Rambeck <http://nathan.rambeck.org>, Rendahl Weishar <ren@janrain.com>

Description
===========
It's a simple module for using JanRain's RPX service in Drupal.

RPX provides simple registration and login for OpenID, Facebook, MySpace, AOL, Yahoo!, Google,
Twitter, Windows Live, and other identity providers.  Tres chic.

Installation
============

1. Download the module, unzip the source, and put the resulting directory into the 
   modules/ directory of your Drupal application.
2. Enable the module in Drupal at Administer > Site Building > Modules > Other
3. Provide your RPX API Key at Administer > Site Configuration > RPX Configuration
4. Recommended: Change your user settings to allow users to create accounts without
   administrator approval at Administer > User Management > User Settings
 
... If you don't have an API Key, click the "Setup this site for RPX" link, and one will
installed for you.

In order to enable Facebook, MySpace, and Windows Live accounts, you must register with the
respective services.  Links from the control panel are provided, with step-by-step setup 
instructions.

Troubleshooting
===============

Problem: Users get an error during registration that says "The configured token URL has not been whitelisted"
Solution: Try editing the settings in your RPX account to use a wildcard for subdomains. So your domains would
  include mysite.com and also *.mysite.com. http://rpxnow.com/account

For detailed technical documention, please visit:

* http://rpxnow.com/docs/
* http://api.drupal.org/
