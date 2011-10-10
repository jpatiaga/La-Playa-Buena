function icl_content_lang_propagate(lang, speed) {
	var id = '#icl-content-translate-' + lang;    
	jQuery('#icl-content').show('slow');
	jQuery('#icl-content fieldset').hide();
        
        if ( jQuery('#edit-minor-edit')) {
                if(jQuery('#edit-minor-edit').attr('checked')) {
                	jQuery(id).hide(speed);
                } else {
                	jQuery(id).show(speed);
                }
        }
        else {
        	jQuery(id).show(speed);
        }
        
	if (jQuery('#edit-icl-content-skip').val() == 'not') {
		jQuery('#icl-content fieldset').hide();
	}
	if (lang.length == 0) {
                jQuery('#edit-icl-content-skip').attr('disabled','disabled');
		jQuery('#no_language_error').show('fast');
	} else {
                if(jQuery(id).html()!=null){
                    jQuery('#edit-icl-content-skip').removeAttr('disabled');
                }else{
                    jQuery('#edit-icl-content-skip').attr('disabled','disabled');
                }        
		jQuery('#no_language_error').hide('fast');
	}
}

jQuery(document).ready( function() {
	jQuery('#edit-icl-content-skip').change( function() {
		if (this.value == 'not') {
			jQuery('#icl-content fieldset').hide('slow');
		} else {
			icl_content_lang_propagate(jQuery('#edit-language').val(), 'slow');
		}
	});

	jQuery('#edit-language').change( function() {
		icl_content_lang_propagate(this.value, '');
	});

	jQuery('#edit-minor-edit').change( function() {
		if(jQuery('#edit-minor-edit').attr('checked')) {
                        jQuery('#edit-icl-content-skip-wrapper').hide('slow');
			icl_content_lang_propagate(jQuery('#edit-language').val(), 'slow');
                } else {
                        jQuery('#edit-icl-content-skip-wrapper').show('fast');
			icl_content_lang_propagate(jQuery('#edit-language').val(), 'fast');
                        
                }
	});

	icl_content_lang_propagate(jQuery('#edit-language').val(), '');
});