ABOUT

This module provides a simple way to exclude certain pages from being cached.  Sometimes
you want all pages to be cached for anonymous users except for one or two pages that have 
dynamic or random or rotating content.  If those pages are cached, the dynamic parts 
cease to be dynamic.  This module allows an administrator to selectively exclude certain 
paths from being cached so that dynamic content is actually dynamic.

REQUIREMENTS

- Drupal 6.x

INSTALLATION

- Copy the cacheexclude directory to your modules directory.
- Go to admin/build/modules and enable it.
- Go to admin/settings/cacheexclude and configure paths you want excluded from caching.

AUTHOR AND CREDIT

Larry "Crell" Garfield - Maintainer
Palantir.net