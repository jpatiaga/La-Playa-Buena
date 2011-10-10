// $Id: icl_translate.js,v 1.5 2010/09/03 14:40:56 jozik Exp $

var icl_intval = "";

function iclAjaxAutoSave(form, time) {
  icl_inval = setInterval(function () {
        iclAjaxSubmit(form);
    }, time);
}

function iclAjaxSubmit(form) {
    jQuery(form).ajaxSubmit({
      //target:, 
      //url:,
      type: "POST",
      data: ({icl_ajax:1, save_translation:Drupal.settings[form].submit}),
			//forceSync: true,
      success: function() { 
        //
      }
    });
}

                	