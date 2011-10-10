// $Id: icl_translate_notifications.js,v 1.7 2010/09/03 14:40:56 jozik Exp $

jQuery(document).ready(function(){
  // Render reminders
  jQuery.ajax({
    type: "POST",
    url: Drupal.settings.icl_reminders_message.ajax_url,
    data: {icl_translator_ajx_action:'reminders_get'},
    cache: false,
    dataType: 'json',
    success: function(msg){
      if(!msg.error){
        jQuery('#icl_reminders_wrapper').html(msg.message).fadeIn();
      }  
    }
  });
})

function iclRemindersInit() {
  jQuery('.icl_reminders_link_dismiss').click(function() {
    var data = {icl_translator_ajx_action:'reminder_dismiss'};
    var hide = jQuery(this).parent();
    jQuery.ajax({
        type: "POST",
        url: jQuery(this).attr('href'),
        data: data,
        cache: false,
        dataType: 'json',
        success: function(msg){
            if(!msg.error){
              if (hide.parent().children('div').length < 2) {
                hide.parent().fadeOut();
              } else {              
                hide.fadeOut().remove();
              }
            }            
        }
    });
    return false;
  });
  
  jQuery('#icl_reminders_show').click(function() {
    var data = {icl_translator_ajx_action:'reminders_show'};
    var thisV = jQuery(this);
    jQuery.ajax({
        type:   "POST",
        url: jQuery(this).attr('href'),
        data: data,
        cache: false,
        dataType: 'json',
        success: function(msg){
            if(!msg.error){                
              thisV.parent().children('div').toggle();
              if (thisV.parent().children('div').is(':visible')) {
                var txtV = Drupal.settings.icl_reminders_message.hide_txt;
                var hrefV = Drupal.settings.icl_reminders_message.hide_link;
              } else {
                var txtV = Drupal.settings.icl_reminders_message.show_txt;
                var hrefV = Drupal.settings.icl_reminders_message.show_link;
              }
            thisV.html(txtV).attr('href', hrefV);
            }            
        }
    });
    return false;
  });
}
