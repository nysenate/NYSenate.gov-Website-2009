$Id$

Conditional Fields:
--------------------
A Drupal module


Author:
--------------------
Gregorio Magini (peterpoe) <gmagini@gmail.com> - http://www.wikirandom.org
Initially inspired by the Explainfield module -> http://drupal.org/project/explainfield


Short Description:
--------------------
Content fields and groups visibility based on the values of user defined "controlling" fields.


Description:
--------------------
Conditional Fields allows you to assign fields with allowed values as "controlling fields" for other fields and groups. When a field or group is "controlled", it will only be available for editing and displayed if the selected values of the controlling field match the "trigger values" assigned to it.
When editing a node, the controlled fields are dynamically shown and hidden with javascript.
You can, for example, make a custom "article teaser" field that is shown only if a "Has teaser" checkbox is checked.


Dependencies:
--------------------
- Drupal core: 6.x or 5.x (note that the 5.x branch of Conditional Fields is very outdated, while the 6.x branch is actively maintained).
- CCK / content.module > http://drupal.org/project/cck
- OPTIONAL: Fieldgroups (included in CCK) > If enabled you can also set groups as controlled fields


Installation:
--------------------
- Copy the unpacked folder "conditional_fields" in your modules folder (usually [base_path]/sites/all/module).
- Go to the modules administration page (admin/build/modules) and activate the module (you will find it in the "CCK" package)
- Assign the "Administer conditional fields" permission to the desired user roles.


Usage:
--------------------
Read the Conditional Fields handbook:
http://drupal.org/node/475488


Limitations:
--------------------
- Each field or group can be controlled from only one field (though a field can control any number of fields and groups). This will be corrected in later development.
- If the controlling field is in a group, it can only control or be controlled only by fields that are in the same group.
- Conditional Fields, for now, supports only core CCK fields and widgets (checkbox, select, and radio) as controlling fields. Fields from other modules might work, but probably won't. There are confirmed incompatibilities with many non-core CCK modules (Date, Multigroup, Content Taxonomy, etc). 


To Do:
--------------------
Any help is welcome!
--------------------
Check the issue queue of this module for more information:
http://drupal.org/project/issues/conditional_fields

These are the top priority future features:
- Extend compatibility with non-core CCK modules
- Negate conditions (so that a field can be triggered when some allowed values are *not* selected)
- Allow multiple controlling fields on the same field
- Views integration
- Allow nested conditional fields
