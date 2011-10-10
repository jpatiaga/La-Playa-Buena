function on_lang_from(n, lang) {
        if (n.attr('checked'))
        {
                jQuery("#dest_languages_" + lang).show();
                
        }
        else
        {
                jQuery("#dest_languages_" + lang).hide();
        }
}


function on_account_button() {
        if(jQuery("#edit-icl-core-password-wrapper").is(":hidden"))
        {
                jQuery("#edit-icl-core-password-wrapper").show();
                jQuery("#edit-icl-core-button").attr("value", "I need to create an account at ICanLocalize");
                jQuery("#edit-icl-core-first-name-wrapper").hide();
                jQuery("#edit-icl-core-last-name-wrapper").hide();
                jQuery("#edit-icl-core-do-create").attr("value", "0");
                jQuery("#icl_core_account_message").hide();
        }
        else
        {
                jQuery("#edit-icl-core-password-wrapper").hide();
                jQuery("#edit-icl-core-button").attr("value", "I already have an account at ICanLocalize");
                jQuery("#edit-icl-core-first-name-wrapper").show();
                jQuery("#edit-icl-core-last-name-wrapper").show();
                jQuery("#edit-icl-core-do-create").attr("value", "1");
                jQuery("#icl_core_account_message").show();
        }
}

function on_translator_select() {
        if(jQuery('#edit-icl-core-translator-selection-private-translators').attr('checked')) {
                jQuery('#icl_core_private_translator_message').show();
                jQuery('div').filter(function (index) {
                        var id = jQuery(this).attr('id');
                        if (id.match("-own-"))
                        {
                                var lang_id = id.replace("-own-", "-").replace("-wrapper", "");
                                if (jQuery('#' + lang_id).attr('checked')) {
                                        jQuery(this).show('slow');
                                } else {
                                        jQuery(this).hide();
                                }
                                
                        }
                        
                })
        } else {
                jQuery('#icl_core_private_translator_message').hide();
                jQuery('div').filter(function (index) {
                        var id = jQuery(this).attr('id');
                        if (id.match("-own-"))
                        {
                                jQuery(this).hide();
                        }
                        
                })
        }
        
}

jQuery(document).ready( function() {
        jQuery("#edit-icl-core-password-wrapper").hide();
        on_translator_select();
        icl_tb_init('.icl_thickbox');
        icl_tb_set_size('.icl_thickbox');
        
});