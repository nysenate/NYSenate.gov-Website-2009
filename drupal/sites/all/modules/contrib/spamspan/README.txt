Readme
------

The SpamSpan module obfuscates email addresses to help prevent spambots from
collecting them.  It implements the technique at http://www.spamspan.com

The problem with most email address obfuscators is that they rely upon
JavaScript being enabled on the client side.  This makes the technique
inaccessible to people with screen readers.  SpamSpan however will produce
clickable links if JavaScript is enabled, and will show the email address as
<code>example [at] example [dot] com</code> if the browser does not support
JavaScript or if JavaScript is disabled.

Installation
------------

1. Create a directory in your Drupal modules directory (probably
   sites/all/modules/) called spamspan and copy all of the module's
   files into it.

2. Go to 'administer > modules', and enable the spamspan.module

3. Go to 'administer > site configuration > input formats' and configure the 
   desired input formats to enable the filter.

4. Rearrange the filters on the input format's 'rearrange' tab to
   resolve conflicts with other filters.  NB: To avoid problems, you
   should at least make sure that the SpamSpan filter has a higher
   weighting (greater number) than the line break filter which comes
   with Drupal, so that the line break filter is executed first.  If you use HTML
   filter, you may need to make sure that <span> is one of the allowed tags.
   Also, URL filter must come after SpamSpan.

5. (optional) Select the configure tab to set available options

Bugs
----

Please report any bugs using the bug tracker at
http://drupal.org/project/issues/spamspan


Module Author
------------

Lawrence Akka : Contact me via http://drupal.org/user/63367
