= Masquerade =

The Masquerade module allows users to temporarily switch to another user
account. It keeps a record of the original user account, so users can easily
switch back to the previous account.

== Installation ==

To install the Masquerade module, extract the module to your modules folder,
such as sites/all/modules. After enabling the module, it can be configured
under Administer > Site configuration > Masquerade. To enable users to
masquerade, assign the appropriate "masquerade module" permissions to the roles
available on your site.

== Module Weights ==

Some modules may conflict with Masquerade depending on their weights. Modules
known to conflict include:

 * [Organic Groups](http://drupal.org/project/og)
 * [Global Redirect](http://drupal.org/project/globalredirect)

By default, the weight of Masquerade is set to -10. If there are conflicts with
other modules, you can change the weights of modules on your site by:

1. Installing the [Weight](http://drupal.org/project/weight) or
[Utility](http://drupal.org/project/util) modules to configure the weights of
modules on your site.

2. Running the following SQL query in your database to change the weight of the
Organic Groups (for example) module:

    UPDATE system SET weight = 1 WHERE name = 'og'; 

== Help and Support ==

This module was developed by a number of contributors. For more information
about this module, see:

Project Page: http://drupal.org/project/masquerade
Issue Queue: http://drupal.org/project/issues/masquerade
