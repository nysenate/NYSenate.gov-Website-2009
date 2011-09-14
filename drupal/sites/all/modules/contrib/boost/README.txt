// $Id: README.txt,v 1.2.2.1.2.5.2.5 2009/05/01 23:13:31 mikeytown2 Exp $

DESCRIPTION
-----------
This module provides static page caching for Drupal 6.x, enabling a
potentially very significant performance and scalability boost for
heavily-trafficked Drupal sites.

For an introduction, read the original blog post at:
  http://bendiken.net/2006/05/28/static-page-caching-for-drupal

FEATURES
--------
* Maximally fast page serving for the anonymous visitors to your Drupal
  site, reducing web server load and boosting your site's scalability.
* On-demand page caching (static file created after first page request).
* Full support for multi-site Drupal installations.

INSTALLATION
------------
Please refer to the accompanying file INSTALL.txt for installation
requirements and instructions.

HOW IT WORKS
------------
Once Boost has been installed and enabled, page requests by anonymous
visitors will be cached as static HTML pages on the server's file system.
Periodically (when the Drupal cron job runs) stale pages (i.e. files
exceeding the maximum cache lifetime setting) will be purged, allowing them
to be recreated the first time that the next anonymous visitor requests that
page again.

New rewrite rules are added to the .htaccess file supplied with Drupal,
directing the web server to try and fulfill page requests by anonymous
visitors first and foremost from the static page cache, and to only pass the
request through to Drupal if the requested page is not cacheable, hasn't yet
been cached, or the cached copy is stale.

FILE SYSTEM CACHE
-----------------
The cached files are stored (by default) in the cache/ directory under your
Drupal installation directory. The Drupal pages' URL paths are translated
into file system names in the following manner:

  http://mysite.com/
  => cache/mysite.com/index.html

  http://mysite.com/about
  => cache/mysite.com/about.html

  http://mysite.com/about/staff
  => cache/mysite.com/about/staff.html

  http://mysite.com/node/42
  => cache/mysite.com/node/42.html

You'll note that the directory path includes the Drupal site name, enabling
support for multi-site Drupal installations.


DISPATCH MECHANISM
------------------
For each incoming page request, the new Apache mod_rewrite directives in
.htaccess will check if a cached version of the requested page should be
served as per the following simple rules:

  1. First, we check that the HTTP request method being used is GET.
     POST requests are not cacheable, and are passed through to Drupal.

  2. Since only anonymous visitors can benefit from the static page cache at
     present, we check that the page request doesn't include a cookie that
     is set when a user logs in to the Drupal site. If the cookie is
     present, we simply let Drupal handle the page request dynamically.

  3. Now, for the important bit: we check whether we actually have a cached
     HTML file for the request URL path available in the file system cache.
     If we do, we direct the web server to serve that file directly and to
     terminate the request immediately after; in this case, Drupal (and
     indeed PHP) is never invoked, meaning the page request will be served
     by the web server itself at full speed.

  4. If, however, we couldn't locate a cached version of the page, we just
     pass the request on to Drupal, which will serve it dynamically in the
     normal manner.

IMPORTANT NOTES
---------------
* To check whether you got a static or dynamic version of a page, look at
  the very end of the page's HTML source. You have the static version if the
  last line looks like this:
    <!-- Page cached by Boost @ 2008-11-24 15:06:31 -->
* If your Drupal URL paths contain non-ASCII characters, you may have to
  tweak your locate settings on the server in order to ensure the URL paths
  get correctly translated into directory paths on the file system. You can also
  turn off the ASCII filter under Cache -> Advanced on the performance page.

LIMITATIONS
-----------
* Only anonymous visitors will be served cached versions of pages;
  authenticated users will get dynamic content. This will limit the
  usefulness of this module for those community sites that require user
  registration and login for active participation.
* Only content of the type `text/html' will get cached at present. RSS feeds
  and URL paths that have some other content type (e.g. set by a third-party
  module) will be silently ignored by Boost.
* In contrast to Drupal's built-in caching, static caching will lose any
  additional HTTP headers set for an HTML page by a module. This is unlikely
  to be problem except for some very specific modules and rare use cases.
* Web server software other than Apache is not supported at the moment.
  Adding Lighttpd support would be desirable but is not a high priority for
  the author at present (see TODO.txt). (Note that while the LiteSpeed web
  server has not been specifically tested by the author, it may, in fact,
  work, since they claim to support .htaccess files and to have mod_rewrite
  compatibility. Feedback on this would be appreciated.)
* At the moment, Windows is untested. It *should* work, but it's untested ATM.

BUG REPORTS
-----------
Post feature requests and bug reports to the issue tracking system at:

  <http://drupal.org/node/add/project-issue/boost>


CREDITS
-------
Developed and maintained by Arto Bendiken <http://bendiken.net/>
Drupal 6.x maintained by Mike Carper <http://www.316solutions.net>
Ported to Drupal 6.x by Ben Lavender <http://bhuga.net/>
Ported to Drupal 5.x by Alexander I. Grafov <http://drupal.ru/>
Miscellaneous contributions by: Jacob Peddicord, Justin Miller, Barry
Jaspan.
