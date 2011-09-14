/**
 * Binds the object to the specified function (and optional parameters).  This
 * bind variant ignores all parameters passed into the function by the caller
 * and only uses those parameters used to create the bind.
 *
 * @param object the object to use as the 'this' reference
 * @param func the function to bind object to
 * @param ... an option set of parameters that will be passed to the
 *        specified function when it is called
 */
bindIgnoreCallerArgs =
function(object, func) {
  var __method = func;
  var __args = [];
  for (var i = 2; i < arguments.length; i++) {
    __args.push(arguments[i]);
  }
  delete i;
  return function() {
    var args = [];
    args = args.concat(__args);
    return __method.apply(object, args);
  };
};

Drupal.gigya = {};

/**
 * Debug code for the login block, should be removed after further testing
 */
Drupal.gigya.printResponse = function(response) {
     if ( response['status'] == 'OK' ) {               
         var availableProviders= response['availableProviders'];   
         var msg = response['context']['myAppTitle'] + '\n\n';  
         if ( null!=availableProviders ) {  
             for (var providerName in availableProviders) {  
                 msg += providerName + ':\n' ;  
                 var provider = availableProviders[providerName];  
                 for (var properties in provider) {  
                     msg+= ' ' +properties+ '  :  ' + provider[properties] + '\n';  
                 }
                 msg+='\n';  
             }
             alert(msg);
         }
         else {
             alert('Error : NO available providers were returned');  
         }
     }
     else {   
         alert('Error :' + response['statusMessage']);  
     }
};

Drupal.gigya.logoutResponse = function (response) {      
    if ( response['status'] == 'OK' ) {
      document.getElementById('logoutMessage').innerHTML = "Successfully logged out, redirecting";
      window.location = Drupal.settings.gigya.logout_location;
    }
    else {    
     alert('Error :' + response['statusMessage']);    
    }    
}; 


/**
 * Callback for the getUserInfo function
 * takes getUserInfo object and renders the HTML to display an array of the user object
 * note: probably should be removed in production, since its just for dumping user output.
 */
Drupal.gigya.getUserInfo_callback = function(response)
{
  if (response.status == 'OK')
  {
    var user = response['user'];  

    var str="<pre>"; //variable which will hold property values
    for(prop in user)
    {
      if (prop == 'birthYear' && user[prop] == 2009) {
        user[prop] = '';
      }
      if (prop == 'identities') {
            for(ident in user[prop])
            {
               for(provide in user[prop][ident])
               {
                 str+=provide + " SUBvalue :"+ user[prop][ident][provide]+"\n";
               }
            }
      }
      str+=prop + " value :"+ user[prop]+"\n";//Concate prop and its value from object
    }
    str+="</pre>";
    
    document.getElementById('userinfo').innerHTML = str;
  }
  else {  
     alert('Error :' + response['statusMessage']);  
  }      
};

/**
 * Callback for the gigya.login function
 * checks to make sure a user is logged in or out, and displays the loginUI page accordingly
 * has an additional check for a drupal user, and if logged out, performs the gigya logout function
 */
Drupal.gigya.login_callback = function(response) {
  var conf = Drupal.settings.gigya.conf;
  var params = Drupal.settings.gigya.params;
  params += {callback:Drupal.gigya.printResponse};
  var login_params = Drupal.settings.gigya.login_params;
  if (response.status == 'OK')
  {
    if (!response.loggedIn)
    {
        gigya.services.socialize.getAvailableProviders(conf,params);
        gigya.services.socialize.showLoginUI(conf,login_params);
    }
    if (response.loggedIn)
    {
      if (typeof Drupal.settings.gigya.drupal_logged_out != "undefined") {
        if(Drupal.settings.gigya.drupal_logged_out)
        {
          gigya.services.socialize.getAvailableProviders(conf,params);
          gigya.services.socialize.showLoginUI(conf,login_params);
          //gigya.services.socialize.logout(Drupal.settings.gigya.conf,{callback:Drupal.gigya.login_callback});
        }
      }
      else 
      {
        //alert("already logged in!");
      }
    }
  }
};

/**
 * Callback for the gigya.notifyLogin function
 * In production, this function may not be needed. Sends an alert if the user logged in.
 */
Drupal.gigya.notifyLogin_callback = function(response) 
{
  if ( response['status'] == 'OK' ) {
    window.location = Drupal.settings.gigya.login_redirect;
  } else {
    alert("Unable to log you in. Please contact the system administrator");
  }
};

Drupal.gigya.notifyFriends_callback = function(res)
{
  if(res.user!=null && res.user.isConnected)
  {   
      user = res.user ;    
      // Show friend-selector component
      document.getElementById("friends").style.display = "block";
  var params =
  {
      containerID:"friends",
      onSelectionDone:Drupal.gigya.notifyFriends_onSelectionDone,
      onClose:Drupal.gigya.notifyFriends_onClose,
      showEditLink:'false'    
  }
  Drupal.settings.gigya.conf.disabledProviders = 'myspace, google, yahoo, aol';
  gigya.services.socialize.showFriendSelectorUI(Drupal.settings.gigya.conf, params);
      
  } else {
      document.getElementById("friends").style.display = "none";
  }
};

// If the user clicked "OK" in the friend-selector component
// Send a notification to the selected friends.
Drupal.gigya.notifyFriends_onSelectionDone = function(response)
{
  var subject = "Notifiation message"; //gigya needs a subject, although its never displayed in fb or twitter.
  var body = document.notification.body.value;
  
  if (!body) {
    alert("Please write a message first!");
    return;
  }
  
  if (response.friends.getSize() > 0)
  {
      var params = 
      {
          callback:sendNotification_callback,
          subject:subject,
          body:body,
          recipients:response.friends
      };
    gigya.services.socialize.sendNotification(Drupal.settings.gigya.conf, params)
    }
};
Drupal.gigya.notifyFriends_onClose = function(response) 
{
  Popups.close();
};

// Display a status message according to the response from sendNotification
function sendNotification_callback(response)
{
  switch (response.status)
  {
    case 'OK':
      document.getElementById('socialize_notification').innerHTML = '';
      document.getElementById('status').style.color = "green";
      document.getElementById('status').style.fontSize = "20pt";
      document.getElementById('status').style.textAlign = "center";
      document.getElementById('status').innerHTML = "Notification sent successful.";
      setTimeout(bindIgnoreCallerArgs(this,Popups.close),Popups.originalSettings.popups.autoCloseFinalMessageDelay);
      break;
    default:
      document.getElementById('socialize_notification').innerHTML = '';
      document.getElementById('status').style.color = "red";
      document.getElementById('status').style.fontSize = "20pt";
      document.getElementById('status').style.textAlign = "center";
      document.getElementById('status').innerHTML = "<p>Unable to send notification. <br /> status=" + response.status + "</p>";
      setTimeout(bindIgnoreCallerArgs(this,Popups.close),Popups.originalSettings.popups.autoCloseFinalMessageDelay);
  }
};

// Toggle the gigya login/register block depending on which router you're taking.
Drupal.gigya.toggleScreens = function() {
  $("fieldset#user-login-description > legend > a").click(function(){
    if(!$("fieldset#user-register-description").hasClass("collapsed")) {
      Drupal.toggleFieldset($("fieldset#user-register-description"));
    }
  });
  $("fieldset#user-register-description > legend > a").click(function(){
    if (!$("fieldset#user-login-description").hasClass("collapsed")) {
      Drupal.toggleFieldset($("fieldset#user-login-description"));
    }
  });
};

Drupal.gigya.loadSetStatusPopup = function(url) {
  //$('body').append('<a href="' + url + '" id="setStatus" style="display:none">setStatus</a>'); 
  var popupElement = document.createElement('a');
  popupElement.href='/' + url;
  //popupElement.href=url;
  popupElement.setAttribute('style','display:none;');
  //popupElement.setAttribute('destination','index.php');
  popupElement.setAttribute('class','popups-form popups-processed');
  popupElement.textContent="setStatus";
  parent.path=url;
  
  Popups.openPath(popupElement,Popups.options,parent);
 // Popups.message('Titles','here we go!');
};
Drupal.gigya.SetStatusPopup_onClose = function(response) 
{
  Popups.close();
};
