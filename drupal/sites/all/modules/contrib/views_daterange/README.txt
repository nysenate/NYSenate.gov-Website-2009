$Id: README.txt,v 1.1 2009/03/18 19:35:22 crell Exp $

ABOUT

This module provides a new Views argument plugin for date fields that allows
for arbitrary date ranges in summary views.  If you need to generate a listing
of nodes by quarter, academic term, or some other site-specific date range then
this is the module for you.

Note: This module has only been tested on MySQL 5.x and I'm fairly sure it will
not work on PostgreSQL.  Unfortunately it requires doing seriously bizarre things
in SQL that are not at all portable.

REQUIREMENTS

- Drupal 6.x
- Views 2.x
- Date 2.0 or later

INSTALLATION and USAGE

- Copy the module directory to your modules directory.
- Go to admin/build/modules and enable it.

In a view, you will now find a new Argument handler under the "Date" group called
"Date: Date range".  It works in the same way as the normal "Date: Date" argument,
except that instead of setting a granularity for the summary view you may configure
your own arbitrary set of date ranges at the bottom of the configuration form.

These date ranges should be in the order you wish them displayed, and together
should cover the entire year.  They may be given any label you wish.

When the view is displayed, if no date is given then a summary view will be
generated that uses the specified date ranges rather than more common ranges like
a summary by month or by year.  Each date range will be within a given calendar
year, so will be along the lines of "Quarter 3 2008", "Quarter 1 2009", etc.

Each summary link will link to a normal view page filtered by that date range.
That page should behave normally like any other date-based view.

AUTHOR AND CREDIT

Larry Garfield
http://www.palantir.net/

This module was initially developed by Palantir.net.
