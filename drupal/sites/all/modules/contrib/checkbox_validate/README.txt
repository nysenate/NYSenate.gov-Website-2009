********************************************************************
                     D R U P A L    M O D U L E
********************************************************************
Name: Checkbox Validate Module
Author: Robert Castelo
Drupal: 6.x
********************************************************************
DESCRIPTION:

This module corrects display and behaviour of required checkboxes in all forms.

Corrects bugs in Drupal core: 

Checkboxes set as required not displaying required symbol (install this module to display)

Checkboxes set as required behave as optional (install this module to make behave as required)

Note: developers don't need to add any extra validation code to their modules to make up for the bug in core, and once core is fixed this module can be uninstalled.

See:

    * Radio/checkboxes set to 'required' are not validated
        http://drupal.org/node/179932    * Unchecked checkbox set to "required" bypasses validation (duplicate)
        http://drupal.org/node/259292


********************************************************************
INSTALLATION:

Note: It is assumed that you have Drupal up and running.  Be sure to
check the Drupal web site if you need assistance.

1. Place the entire directory into your Drupal directory:
   sites/all/modules/ or sites/default/modules/
   

2. Enable the module by navigating to:

   administer > build > modules
     
  Click the 'Save configuration' button at the bottom to commit your
  changes.
  
  
********************************************************************
USAGE

Once installed there's nothing else to do.
        



********************************************************************
AUTHOR CONTACT

- Report Bugs/Request Features:
   http://drupal.org/project/checkbox_validate
   
- Comission New Features:
   http://drupal.org/user/3555/contact
   
- Want To Say Thank You:
   http://www.amazon.com/gp/registry/O6JKRQEQ774F

        
********************************************************************
ACKNOWLEDGEMENT

- Extensive refactoring
sun (Daniel F. Kudwien) http://www.unleashedmind.com

- Optimisation
jcmarco (Jose Carlos Marco)
dboulet (Daniel Boulet) http://www.urbanink.net
