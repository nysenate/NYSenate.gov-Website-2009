USER LIST

Authored by Aaron Winborn
Advomatic, LLC
http://www.advomatic.com/
winborn (at) advomatic (dot) com

This module creates several user lists, which may be viewed as pages and
blocks. User lists may be displayed alphabetically, beginning with A-Z,
by newest, or as a list of users who have posted content of a certain
type. Lists may also be displayed by user role.

INSTALLATION:

Simply copy the folder and files into the modules directory. Then go to
Administer > Site building > Modules, and activate the user_list module.

Note that you must enable access with the 'access user lists' permission
to the user listings at /admin/access, which controls viewing both blocks
and pages. If enabled and allowed, the main user listing page may be
viewed at /user_list.

Go to /admin/settings/user_list to change the global settings for user
lists, and to /admin/block to configure specific user listing blocks if
desired. Note that all blocks provided by this module are appended with
"User List:", so they may be differentiated by similar blocks provided by
other modules.

Note: roles with a forward slash / in the name will not work correctly
when trying to navigate to those as a role-based user list and should be
renamed to work. See http://drupal.org/node/104839 for more information.

THEMING:

Two theme functions are available for custom themes. These are
theme('user_list_list'), which controls the actual list of users to
display, and theme('user_list_menu'), which controls the display of the
optional embedded menu on user listing pages. The user lists are in turn
themed with the user.module's theme('user_list'), which may also be
overridden for customization.

API:

If you wish to access a user list view directly from a module, theme, or
php code block, you may directly call _user_list() from your function with
the parameters you desire. The embedded menu may be called directly with
_user_list_embedded_menu().

TODO:

Allow display by profiles or tables
Integrate profile fields into table views
Add access perms per user list

