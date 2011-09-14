/* $Id: README.txt,v 1.5 2008/10/01 11:26:10 sun Exp $ */

-- SUMMARY --

Render module provides an very easy, user-friendly administrative interface for
quickly implementing rendering rules for various technologies depending on
Cascading Style Sheets (CSS) and/or Javascript (JS) on any Drupal site without
requiring any adjustments to the site's theme.

For a full description visit the project page:
  http://drupal.org/project/render
Bug reports, feature suggestions and latest developments:
  http://drupal.org/project/issues/render


-- REQUIREMENTS --

* None.


-- INSTALLATION --

* Copy render module to your modules directory and enable it on the admin
  modules page.


-- CONFIGURATION --

* Create rendering rules to apply for each plugin at 
  admin/settings/render/addrule


-- TROUBLESHOOTING --

* Always choose CSS selectors as specific as possible. Instead of just

  'li a' 
  use
  '#header ul.primary-links a' (or similar)

  for your rules.

* Rule weight is important. A rendering rule is usually executed only once.
  If you want to render certain elements that are already covered by another
  rule, the rule rendering those certain elements has to come first.


-- NOTES --

* Remember to check copyright / font licenses in front of publishing a font in
  the web.


-- CONTACT --

Current maintainers:
* Daniel F. Kudwien (sun) - dev@unleashedmind.com

Previous maintainers:
* Jeff Robbins (jjeff)

This project has been sponsored by:
* UNLEASHED MIND
  Specialized in consulting and planning of Drupal powered sites, UNLEASHED
  MIND offers installation, development, theming, customization, and hosting
  to get you started. Visit http://www.unleashedmind.com for more information.

* Bryght
  Visit http://www.bryght.com for more information.
