$Id: README.txt,v 1.2.2.2.2.5 2010/02/03 07:09:46 danielb Exp $

Node Export README

CONTENTS OF THIS FILE
----------------------

  * Introduction
  * Installation
  * Configuration
  * Usage


INTRODUCTION
------------
The export module allows users to export a node and then import it to another 
website. The authorship is set to the current user, the menu and url aliases 
are reset.

This module makes reasonable checks on access permissions.  A user cannot export 
a node unless they can use the input format of that node, and unless they have
permission to create new nodes of that type based on a call to node_access().

Maintainer: Daniel Braksator (http://drupal.org/user/134005)
Project page: http://drupal.org/project/node_export.

Note: this module was originally built upon code from the node_clone module
maintained by Peter Wolanin (http://drupal.org/user/49851) at 
http://drupal.org/project/node_clone which was derived from code posted by
Steve Ringwood (http://drupal.org/user/12856) at 
http://drupal.org/node/73381#comment-137714


INSTALLATION
------------
1. Copy node_export folder to modules directory (usually sites/all/modules).
2. At admin/build/modules enable the Node Export module.


CONFIGURATION
-------------
1. Enable permissions at admin/user/permissions.
   Security Warning: Users with the permission "use PHP to import nodes"
   will be able to change nodes as they see fit before an import, as well as 
   being able to execute PHP scripts on the server.  It is advisable not to
   give this permission to a typical node author, only the administrator or
   developer should use this feature.  You may even like to turn this module
   off when it is no longer required.
2. Configure module at admin/settings/node_export.


USAGE
-----
1. To export nodes, either:
   a) click the 'Export' tab on a node page or,
   b) use the Content page (admin/content/node) to filter the nodes you wish to
      export and then choose 'Export nodes' under the 'Update options'.
2. To import nodes go to 'Node Export: Import' (admin/content/import).