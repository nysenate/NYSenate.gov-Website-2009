DESCRIPTION
-----------

This project provides a class library for accessing the New York State Senate's 
services API via XML-RPC.

HOW TO USE THE CLASS LIBRARY
----------------------------

The class library is located in file xmlrpc-api.inc. It creates two classes:
* nodeGet
* viewsGet
The file named xml-rpc-test.php contains examples showing how to use it.

The xmlrpc-api library relies upon the XML-RPC for PHP library (current version, 3.0.0beta):
* http://phpxmlrpc.sourceforge.net/
* http://sourceforge.net/projects/phpxmlrpc/files/phpxmlrpc/3.0.0beta/xmlrpc-3.0.0.beta.zip/download

This class library can also be used with very little modification to access
APIs created by Drupal websites other than NYSenate.gov.

MORE INFORMATION
----------------

See the developer documentation for NYSenate.gov at
http://www.nysenate.gov/developers/apis

ACKNOWLEDGMENTS
---------------
Thanks to Annabel Bush for writing the proof-of-concept code upon which this
library based.
