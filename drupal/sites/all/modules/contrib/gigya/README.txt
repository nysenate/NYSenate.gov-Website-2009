Authentication In order to properly authenticate users, the gigya module
must be setup. You can configure it through admin->site settings->gigya
Make sure you have the following 
	* Site API Key 
	* Your user private key from gigya 
	* Selected social networks

That should be all thats required to setup authentication. You can
further customize the UI by looking at the subsections. If profile
module is enabled, you can select which gigya social network mappings
should be assigned to your local profile settings, and display the
profile category on the user registration page.

Configure Status Action 
The status popup action can be found under
admin->site configuration->actions Below, you can add a new action, the
status popup is 'Gigya Status Popups'. Once created you'll have a few
options to choose from in the configuration. Make sure that you set the
content types for which the popup is assigned to. If no content types
are selected, you will not see status popups!

Assign Status Action 
Once configured, you need to assign it to a trigger. For this example, 
we'll set it up for comments. Goto 'Site
Building' -> Triggers -> 'Comments' You can then choose an action to
assign on saving a 'new comment'. Once this is assigned, statuses should
work for any comments that you create within the content type configured
for the status!

Configure Newsfeed Actions
The newsfeed (status feed) action can be
found under admin->site configuration->actions Below, you can add a new
action, the newsfeed action is 'Gigya Socialize Status feed'. Once
created you'll have a few options to choose from in the configuration.
Make sure that you set the content types for which the newsfeed action
is assigned to. If no content types are selected, you will not see
newsfeeds for anything related to content!. However, if you wish to make
a newsfeed publish upon a user action only, you can leave the content
types select field empty.

Configure Node Types for newsfeed actions
This is not required because the action (verb) is assigned in the 
configuration for the newsfeed actions. However, its suggested that 
you make different actions per each 'thing' you wish to publish. IE,
a newsfeed for user update that says 'just updated' as the action, or 
'just watched' for a content type that is a video, etc.

Assign Newsfeed Action
Once configured, you need to assign newsfeeds to
a trigger. For this example, we'll set it up for content updates only.
Goto 'Site Building' -> Triggers -> 'Content' You can then choose an
action to assign on 'After saving an updated post' Once this is
assigned, newsfeeds should be published for any updated content type
configured for the status!

Troubleshooting 
Q: I don't see the popups occurring! 
A: Most likely not seeing the popup is because the content type is not 
setup, action is not setup, or your user does not have the capability for
'Status'. Only Twitter, MySpace, and Facebook can use status updates. 
Additionally, you must configure on gigya.com your account to allow 
sending of status updates to facebook.

Q: I connected all my social networks to my drupal account, and now when
I connect with socialize and link to drupal, they all disappear! 
A: This is normal operation. Unfortunately you'll have to re-connect 
to your social networks if you use socialize to login rather than drupal
