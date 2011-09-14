Drupal.behaviors.gigya_notifyFriends = function(context){
  $('.friends-ui:not(.gigya_notifyFriends-processed)', context).addClass('gigya_notifyFriends-processed').each(
    function () {
      gigya.services.socialize.getUserInfo(Drupal.settings.gigya.conf, {callback:Drupal.gigya.notifyFriends_callback});
      gigya.services.socialize.addEventHandlers(Drupal.settings.gigya.conf, { onConnect:Drupal.gigya.notifyFriends_callback, onDisconnect:Drupal.gigya.notifyFriends_callback });
   });
};
