// $Id: README.txt,v 1.1.2.1 2009/05/11 15:43:12 morbus Exp $

CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Installation
 * Call to action API


INTRODUCTION
------------

Current Maintainer: Morbus Iff <morbus@disobey.com>

The Activism module is an attempt to standardize the way online advocacy
tools are built in Drupal. There are many great modules out there for adding
only advocacy tools to your site, but there has been no common practice in
implementing these tools that allows you to 1) create multiple take action
pages for any given type of advocacy module installed, 2) link various take
action pages together (i.e. sign a petition then go tell-a-friend), and
3) integrate with external CRM systems. We hope this module will act as a
framework for implementing custom online advocacy functionality in Drupal
going forward.

The Activism module creates a "Campaign" node type with a set of standard
configuration settings which can be associated with a "Call to action"
module. These modules hook into the Activism module to create a form for
taking action on campaign pages. The Activism module allows you to:

  * Store standardized signup data from any custom form implemented through
    a "Call to action" module and export that data into a CSV file.

  * Allow users to "opt-in" to an e-mail list upon taking action (integration
    and actual sending is up to you - we only provide a checkbox that allows
    them to express interest; future versions will allow integration with
    CiviCRM and CiviMail).

  * Set end dates for campaigns and a message to display when it expires.

  * Set campaign goals and track progress.

  * Send an autoresponder to users after they take action on a campaign.

  * Send users to any other campaign or URL once action has been taken.

  * Use Tokens to automatically fill in content for certain autoresponders
    (support for Tokens will be enhanced in future versions).

Additional "Call To Action" modules will be developed as we further build out
this module. Activism module currently ships with Activism Petition module to
allow for creation of online petitions and the Activism Tell a Friend module.
Modules which will be released in the future are:

  * Activism E-card for custom e-card campaigns.
  * Activism Letter for launching various types of letter writing campaigns.
  * Activism CiviCRM for full integration with CiviCRM.

If anyone is interested in integrating with any other CRM systems or creating
a custom "Call to Action" module, please contact us at heytrellon@trellon.com
or contact zfactor <http://drupal.org/user/132922>.

Developed by your friendly Drupal experts at Trellon. Code has been processed
through Coder, Coder Tough Love, and ships with plenty of SimpleTests.


INSTALLATION
------------

Optional capabilities:
  * Date Popup (from Date module) <http://drupal.org/project/date>
    * If enabled, all date fields will become popup jQuery calendars.


CALL TO ACTION API
------------------

To define a new call to action type, add hook_activism_cta_info() to your
module. This hook functions very similarly to hook_node_info() and returns
an array of information on the module's call to action types. Attributes are:

  "name": the human-readable name of the call to action. Required.

  "module": a string telling Activism how a module's functions map to hooks.
  (see below for further explanation on the additional hooks available).

  "description": a brief description of the call to action. Required.

If your call to action offers campaign-specific configuration, you may use a
form alter  to attach yourself to a campaign "call to action" tab, as below:

  function hook_form_activism_campaign_cta_form_alter($form, &$form_state) {
    if ($form['#node']->activism_cta_module == 'MY_MODULE_NAME_FROM_INFO') {

    }
  }

Form items that you wish to save alongside the node can be prepended with
"activism_" to be automatically added to a $node passed to node_save() during
the form's submission (which you'd handle in a standard hook_nodeapi()). You
can, of course, define your own #submit (and #validate) handlers and do your
own magick, but campaign-specific CTA settings should be savable with a
straight node_save() (for programmatic campaign creation, etc.).

The actual call to action form itself - the one that the activists of the
campaign will be interacting with - should be returned by a hook called
hook_activism_cta_form(). If you've defined the 'module' of your call to
action as "activism_example", then you'd return a $form element from the
following hook:

  function activism_example_activism_cta_form() {

    return $form;
  }

Call to actions tend to share a number of common fields, most obviously
geographic location as well as first name, last name, and e-mail address.
Similarly, successfully signing up for a call to action is logged in a goal
tracking database table used to build a campaign's Report page.

To ensure that all call to actions can be properly logged, you should use
the activism_signup_form_element() helper function to add these common bits
of information. Currently, the following fields are available: first_name,
last_name, mail, street_address, city, state, postal_code, phone, mobile,
and comment. You can add your own fields to the form, but it'll be up to you
to store them as necessary, and they won't be usable within prebuilt Reports.

An example of adding a first name, last name, and e-mail address:

  function activism_example_activism_cta_form(&$form_state, $node) {
    activism_signup_form_element($form, 'first_name');
    activism_signup_form_element($form, 'last_name');
    activism_signup_form_element($form, 'mail');

    return $form;
  }

You can modify these elements after adding them to the form (such as tweaking
#required, or adding AHAH, autocomplete, or similar wizardry), but you should
attempt to retain their visual appearance, and MUST keep the form keys the
same (so that action logging and goal tracking know what they are).

It is the responsibility of the call to action module to decide if the $form
returned from this hook contains the actual form, or contains an error message
(due to already having been submitted, administrative misconfiguration, etc.).

When you add a submit button to your CTA form, you should set the #weight to
10 to allow other elements and modules to more easily insert elements prior
to it. This is particularly necessary for the shipped feature of mailing list
opt-ins - this is added AFTER your CTA form is built which, with an unweighted
submit button, would mean the checkbox shows up AFTER the submit button and
not before (the better and more usable approach).

