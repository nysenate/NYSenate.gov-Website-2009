$Id: README.txt,v 1.1.4.1.2.1 2009/05/12 04:36:02 yhahn Exp $

spaces for Drupal 6.x

Note
----
Spaces for Drupal 6 is currently ALPHA. While it is functional and
relatively stable it is also under active development and not fully
polished for use by casual site builders. At the moment, you will
probably want a working knowledge of PHP and a desire to leverage
the concepts in Spaces in order to have a rewarding experience : )

DRUPAL-6--2 Notes
-----------------
There are some important and major changes in the 2.x branch of Spaces
that are especially relevant to those who have gotten used to some
concepts from the 1.x branch of Spaces.

1. Spaces features are now provided by the Features module.

   Amongst other things, this means that features *must live in code*.
   To make a feature exported by the Features module spaces-aware all
   you need to do is add the following key to your feature's .info file:

      spaces[types] = 'all'

   This will enable your feature for all space types. You can specify
   a subset of space types you would like to enable your feature for
   like this:

      spaces[types][] = "og"
      spaces[types][] = "user"

   A UI for making features spaces enabled is planned but not yet
   complete. Please bear with editing .info files by hand for now.

2. A single feature can contain more than one context and need not use
   the "spaces > feature > $featurename"  namespace/attribute/value
   convention. This makes it possible to make far more complex and
   interesting features.

Introduction
------------
Spaces allows a subset of features provided by the Features module [1]
to be enabled, disabled, or set to more specific settings per "space".

A space is essentially some aspect of Drupal that might be leveraged
to group content and settings together. For example, a group [2] might
act as a collaborative workspace for a team, a user space might act
as a personal blog, calendar, and gallery, or a taxonomy space might
act as a whole thematic section to a site.

1: http://drupal.org/project/features
2: http://drupal.org/project/og

Installation
------------
A typical spaces setup consists of:

1. spaces.module -- the core Spaces module. Required.
2. Any number of space type modules. Currently, the following space
   type modules exist: spaces_site, spaces_og, spaces_user,
   spaces_taxonomy. At least one of these modules should be enabled,
   and more than one can be utilized simultaneously.
3. Any number of spaces feature modules. Spaces comes with the example
   features spaces_blog which provides a simple blog feature. You can
   build your own features for use with spaces fairly easily using CCK,
   Views, Context and other Drupal modules.

Once some combination of these modules are installed, you will want to
do some additional setup.

Menu setup
----------
To gain access to the current space's menu, you can set your primary
or secondary navigation links to the "Spaces" menu [3]. For greater
control of these links in your theme, you can use the API function
spaces_features_menu() to retrieve the current space's links at any
time.

Spaces also provides some useful administration links that you may
want to include in your theme. You can access these using the API
funciton spaces_space_links().

3: admin/build/menu/settings

Path prefixing
--------------
Spaces is based on the concept of path prefixing. A url prefix is
defined for each space, and whenever that url prefix is present the
associated space will be enabled.

For example, when creating a new group using spaces_og, you might
define a prefix "knitting" for the group. To access the group's space,
simply go to /knitting on your site.

Features and settings
---------------------
Once you've set up your first space, you can customize the settings
and features for that space using its spaces settings page. The
location of this page varies by space type -- for groups and users,
it is located under the "Spaces" tab on the group node [4].

4: e.g. node/43/spaces or user/7/spaces

Spaces presets
--------------
In addition to customizing features and settings on a per-space basis,
you can provide presets to your users to make setting up a new space
very easy. On the spaces presets administration page [5], you can add
new presets (the process is nearly identical to configuring features
and settings for a space), disable/enable existing presets, and choose
a default for each space type on your site.

5: admin/build/spaces

Maintainers
-----------
alex_b (Alex Barth)
jmiccolis (Jeff Miccolis)
yhahn (Young Hahn)
Ian Ward
