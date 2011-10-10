jQuery(document).ready( function() {
        jQuery('.icl_add_link').click(on_add_edit_click);
        jQuery('.icl_edit_link').click(on_add_edit_click);
        jQuery('.icl_save').click(on_save_click);
        jQuery('.icl_cancel').click(on_cancel_click);
        jQuery('.icl_delete').click(on_delete_click);
});


function on_add_edit_click() {
        jQuery('.icl_edit').each(function() {
                jQuery(this).hide();
        });
        id = jQuery(this).attr('id');
        edit_id = id.replace('add_edit', 'edit');
        jQuery('#' + edit_id).show();
        jQuery('.icl_add_link').each(function() {
                if (id == jQuery(this).attr('id')) {
                        jQuery(this).hide();
                } else {
                        jQuery(this).show();
                }
        });
        jQuery('.icl_edit_link').each(function() {
                if (id == jQuery(this).attr('id')) {
                        jQuery(this).hide();
                } else {
                        jQuery(this).show();
                }
        });
};

function on_save_click() {
        
        id = jQuery(this).attr('id');
        text_id = id.replace('save', 'text');

        jQuery(this).after(jQuery('#icl_throbber'));
        jQuery('#icl_throbber').show();        
        jQuery.ajax({
                type: "POST",
                url: Drupal.settings.ican_ajax.ican_image_replace_url,
                data: "icl_image_cmd=icl_save&icl_id=" + id + "&icl_file_name=" + jQuery("#" + text_id).val(),
                async: false,
                success: function(msg){
                        if (msg.split('|')[0] == '1') {
                                // change 'add' to 'edit'
                                add_id = id.replace('save', 'add_edit');
                                //jQuery("#" + add_id).text(Drupal.settings.ican_ajax.ican_edit_text);
                                jQuery("#" + add_id).removeClass('icl_add_link');
                                jQuery("#" + add_id).addClass('icl_edit_link');
                                // show delete button
                                delete_id = id.replace('save', 'delete');
                                jQuery('#' + delete_id).show();
                                jQuery('#icl_changes_message').show();
                                jQuery('#icl_changes_message_2').show();
                        }
                        jQuery('#icl_throbber').hide();        
                }
        });

        jQuery('.icl_edit').each(function() {
                jQuery(this).hide();
        });
        jQuery('.icl_add_link').each(function() {
                jQuery(this).show();
        });
        jQuery('.icl_edit_link').each(function() {
                jQuery(this).show();
        });
};

function on_cancel_click() {

        jQuery('.icl_edit').each(function() {
                jQuery(this).hide();
        });
        jQuery('.icl_add_link').each(function() {
                jQuery(this).show();
        });
        jQuery('.icl_edit_link').each(function() {
                jQuery(this).show();
        });
};

function on_delete_click() {
        
        id = jQuery(this).attr('id');

        jQuery(this).after(jQuery('#icl_throbber'));
        jQuery('#icl_throbber').show();        
        jQuery.ajax({
                type: "POST",
                url: Drupal.settings.ican_ajax.ican_image_replace_url,
                data: "icl_image_cmd=icl_delete&icl_id=" + id,
                async: false,
                success: function(msg){
                        if (msg.split('|')[0] == '1') {
                                add_id = id.replace('delete', 'add_edit');
                                //jQuery("#" + add_id).text(Drupal.settings.ican_ajax.ican_add_text);
                                jQuery("#" + add_id).removeClass('icl_edit_link');
                                jQuery("#" + add_id).addClass('icl_add_link');
                                jQuery("#" + id).hide();
                                jQuery('#icl_changes_message').show();
                                jQuery('#icl_changes_message_2').show();
                        }
                        jQuery('#icl_throbber').hide();        
                }
        });

        jQuery('.icl_edit').each(function() {
                jQuery(this).hide();
        });
        jQuery('.icl_add_link').each(function() {
                jQuery(this).show();
        });
        jQuery('.icl_edit_link').each(function() {
                jQuery(this).show();
        });
};