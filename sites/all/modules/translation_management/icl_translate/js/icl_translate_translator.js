// $Id: icl_translate_translator.js

jQuery(document).ready(function(){
  jQuery('.icl_translate_translator_language_show').click(function(){
    if (jQuery(this).attr('checked')) {
      jQuery(this).parents('div').next('.icl_translate_language_pairs').slideDown();
    } else {
      var hide;
      jQuery(this).parents('div').next('.icl_translate_language_pairs').slideUp();
      jQuery(this).parents('div').next('.icl_translate_language_pairs').find('input').attr('checked', 0);
    }
  });
  
  jQuery('.icl_assign_translator').each(function() { jQuery(this).data('oldValue', jQuery(this).val()); });
  jQuery('.icl_assign_translator').change(icl_set_translator_for_job);
  jQuery('.icl_assign_translator_cancel').click(icl_set_translator_for_job_cancel);
  jQuery('.icl_assign_translator_save').click(icl_set_translator_for_job_save);
  
  jQuery('.icl-cancel-job-submit').click(icl_cancel_translation_job);

  if (jQuery('#edit-services-local-translations').is(':checked')) {
    jQuery('#local_translations_add_translator_toggle').slideDown();
  }

  icl_add_translators_form_check_submit();
  Drupal.settings.icl_active_service = jQuery('input[name=services]').val();

  jQuery('input[name=services]').change(function() {
    if (jQuery('#edit-services-local-translations').is(':checked')) {
      jQuery('#local_translations_add_translator_toggle').slideDown();
    } else {
      jQuery('#local_translations_add_translator_toggle').slideUp();
    }
    Drupal.settings.icl_active_service = jQuery(this).val();
    icl_add_translators_form_check_submit();
  });

  jQuery('#edit-from').change(function() {
    icl_add_translators_form_check_submit();
  });

  jQuery('#edit-to').change(function() {
    icl_add_translators_form_check_submit();
  });

  jQuery('#icl_add_translator_submit').click(function() {
    var url = eval('Drupal.settings.icl_setup_translators_url.'+Drupal.settings.icl_active_service);
    if (url !== undefined) {
      url = url.replace(/from=(\D+)&/, 'from='+jQuery('#edit-from').val()+'&');
      url = url.replace(/to=(\D+)/, 'to='+jQuery('#edit-to').val());
      iclThickboxReopen(url);
      return false;
    }
  });
  
});

function icl_add_translators_form_check_submit() {
  if (jQuery('#edit-from').val() != 0 && jQuery('#edit-to').val() != 0 && jQuery('#edit-from').val() != jQuery('#edit-to').val()) {
    jQuery('#icl_add_translator_submit').attr('disabled', 0);
  } else {
    jQuery('#icl_add_translator_submit').attr('disabled', 1);
    return false;
  }
  
  if (jQuery('input[name=services]').is(':checked')) {
    jQuery('#icl_add_translator_submit').attr('disabled', 0);
  } else {
    jQuery('#icl_add_translator_submit').attr('disabled', 1);
    return false;
  }
}


function icl_set_translator_for_job(){
    var rid = jQuery(this).attr('id').replace(/^icl_assign_translator_rid_/,'');
    jQuery('#icl_assign_translator_buttons_'+rid).show();
}

function icl_set_translator_for_job_cancel(){
    var rid = jQuery(this).attr('id').replace(/^icl_assign_translator_cancel_/,'');
    jQuery('#icl_assign_translator_rid_'+rid).val(jQuery('#icl_assign_translator_rid_'+rid).data('oldValue')); 
    jQuery('#icl_assign_translator_buttons_'+rid).hide(); 
}

function icl_set_translator_for_job_save(){    
    var rid = jQuery(this).attr('id').replace(/^icl_assign_translator_for_/,'');
    jQuery('#icl_assign_translator_cancel_'+rid+', #icl_assign_translator_for_'+rid).attr('disabled', 'disabled');
    var uid = jQuery('#icl_assign_translator_rid_'+rid).val();  
    var data = {icl_translator_ajx_action:'set_translator', uid:uid, rid:rid};
    jQuery.ajax({
        type: "POST",
        url: location.pathname,
        data: data,
        cache: false,
        dataType: 'json',
        success: function(msg){
            if(!msg.error){                
                jQuery('#icl_assign_translator_cancel_'+rid+', #icl_assign_translator_for_'+rid).removeAttr('disabled', 'disabled');
                jQuery('#icl_assign_translator_buttons_'+rid).fadeOut();
                jQuery('#icl_assign_translator_rid_'+rid).data('oldValue', jQuery('#icl_assign_translator_rid_'+rid).val());
            }            
        }
    }); 
    
}


function icl_cancel_translation_job(){
  var answer = confirm("Are you sure you want to cancel this translation job?");
  if (answer) {
    var rid = jQuery(this).attr('id').replace(/^icl-cancel-submit-/,'');
    post_to_url(window.location, {'cancel-job' : rid}, 'post')
  }
}

function post_to_url(path, params, method) {
    method = method || "post"; // Set method to post by default, if not specified.

    // The rest of this code assumes you are not using a library.
    // It can be made less wordy if you use one.
    var form = document.createElement("form");
    form.setAttribute("method", method);
    form.setAttribute("action", path);

    for(var key in params) {
        var hiddenField = document.createElement("input");
        hiddenField.setAttribute("type", "hidden");
        hiddenField.setAttribute("name", key);
        hiddenField.setAttribute("value", params[key]);

        form.appendChild(hiddenField);
    }

    document.body.appendChild(form);    // Not entirely sure if this is necessary
    form.submit();
}

