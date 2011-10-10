var element_count;

jQuery(document).ready( function() {
	
  jQuery().ajaxComplete(function(ev, xhr, s) {
    // Show any replaced data returned by the ajax call
    jQuery('div[id^=result-]').each(function(){
      var temp = jQuery(this).html();
      if(jQuery(this).html() != "<!--- This will be replaced --->"){
        jQuery(this).parent().parent().show();
      }
                        
    })
  });
  icl_tb_init('.icl_thickbox');
  icl_tb_set_size('.icl_thickbox');
        
  //jQuery.get(Drupal.settings.ican_fetch.ican_url);
        
  element_count = jQuery('*').length;
        
  setInterval(check_new_elements, 1000);
        
  jQuery('#icl_menu_dismiss_all').click(icl_menu_dismiss_all);

  jQuery('a[id^=icl_menu_dismiss-]').click(icl_menu_dismiss_type);
        
  jQuery('#icl_dashboard_show_filter_link').click(function () {
    jQuery('#icl-dashboard-further').slideToggle('fast', function() {
      var show = jQuery('#icl-dashboard-further').is(':hidden') ? 1 : 0;
      jQuery.get(Drupal.settings.icl_dashboard_show_hide.ajax_url+'?icl_content_dashboard_hide_advanced_filter='+show);
      jQuery('#icl_dashboard_show_filter_link').html(iclDashboardHideFiltersTxt(show));
    });
  });
        
  jQuery('.icl_dashboard_hide_legend_link').click(function () {
    jQuery('#icl_dashboard_legend').slideToggle('fast', function() {
      var show = jQuery('#icl_dashboard_legend').is(':hidden') ? 1 : 0;
      jQuery.get(Drupal.settings.icl_dashboard_show_hide.ajax_url+'?icl_content_dashboard_hide_legend='+show);
      jQuery('.icl_dashboard_hide_legend_link').html(iclDashboardHideLegendTxt(show)).toggle();
    });
  });
        
  // align the selectors
  if (jQuery('#edit-search-text').length) {
    x = jQuery('#edit-search-text').offset().left;
    x = Math.max(x, jQuery('#edit-status-status').offset().left);
    x = Math.max(x, jQuery('#edit-type-type').offset().left);
		
    jQuery('#edit-search-text').css({
      "margin-left": x - jQuery('#edit-search-text').offset().left
      });
    jQuery('#edit-status-status').css({
      "margin-left": x - jQuery('#edit-status-status').offset().left
      });
    jQuery('#edit-type-type').css({
      "margin-left": x - jQuery('#edit-type-type').offset().left
      });
		
  /*x = jQuery('#edit-language').offset().left;
		x = Math.max(x, jQuery('#edit-to').offset().left);
		x = Math.max(x, jQuery('#edit-translation').offset().left);
		jQuery('#edit-language').css({'margin-left' : x - jQuery('#edit-language').offset().left});
		jQuery('#edit-to').css({'margin-left' : x - jQuery('#edit-to').offset().left});
		jQuery('#edit-translation').css({'margin-left' : x - jQuery('#edit-translation').offset().left});*/
  }
	
  // Render service info
  jQuery.ajax({
    type: "POST",
    url: Drupal.settings.icl_service_info.ajax_url,
    data: {
      icl_translator_ajx_action:'service_info'
    },
    cache: false,
    dataType: 'json',
    success: function(msg){
      if(!msg.error){
        jQuery('#icl_service_info_wrapper').html(msg.message).fadeIn();
      }  
    }
  });
  
  jQuery('.icl_dashboard_checkbox_send, .icl_dashboard_checkbox_translators').click(function() {
    if (Drupal.settings.icl_dashboard_send_disabled === undefined) {
      if (iclDashboardDisableSend('.icl_dashboard_checkbox_send') === false && iclDashboardDisableSend('.icl_dashboard_checkbox_translators') === false) {
        jQuery('#edit-translate-request').attr('disabled', 0);
      } else {
        jQuery('#edit-translate-request').attr('disabled', 1);
      }
    }
  });
  
  $('input[id^=edit-nodes-]').click(icl_node_select);
  $('th.select-all > input').click(icl_node_select_all);
	
});

function iclDashboardDisableSend(myClass) {
  var disable = true;
  jQuery(myClass).each(function() {
    if (jQuery(this).is(':checked')) {
      disable = false;
    }
  });
  return disable;
}

function check_new_elements() {

  if (element_count != jQuery('*').length) {
    element_count = jQuery('*').length;
    icl_tb_init('.icl_thickbox');
    icl_tb_set_size('.icl_thickbox');
                
  }
        
}

function icl_menu_dismiss_all() {
  jQuery('#icl_menu_warning').hide();

  jQuery.ajax({
    type: "POST",
    url: Drupal.settings.ican_ajax.ican_dismiss_warning_url,
    data: "command=dismiss_all",
    async: true,
    success: function(msg){
    }
  });
}

function icl_menu_dismiss_type() {
  node_type = jQuery(this).attr('id').substring(17);
  jQuery('#icl_row-' + node_type).remove();

  jQuery.ajax({
    type: "POST",
    url: Drupal.settings.ican_ajax.ican_dismiss_warning_url,
    data: "command=dismiss_type&type=" + node_type,
    async: true,
    success: function(msg){
    }
  });

  if (jQuery('tr[id^=icl_row-').length == 0) {
    jQuery('#icl_menu_warning').hide();
  }
}

function iclDashboardHideFiltersTxt(show) {
  if (!show) return Drupal.settings.icl_dashboard_show_hide.hide_filters_text;
  else return Drupal.settings.icl_dashboard_show_hide.show_filters_text;
}

function iclDashboardHideLegendTxt(show) {
  if (!show) return Drupal.settings.icl_dashboard_show_hide.hide_legend_text;
  else return Drupal.settings.icl_dashboard_show_hide.show_legend_text;
}

function icl_node_select() {
	var count = 0;
  $('input[id^=edit-nodes-]').each(function(index) {
    if ($(this).is(':checked')) {
			var node_id = $(this).attr("id").substring(11);
			var words = $('#' + node_id + '-words').html();
			count += parseInt(words);
		}
		
	});
	if (count > 0) {
		var cost = 0.07 * count;
		$('#icl_selected_word_count').html('. Selected word count = ' + count);
	} else {
		$('#icl_selected_word_count').html("");
	}
}

function icl_node_select_all() {
	var count = 0;
  if ($(this).is(':checked')) {
	  $('input[id^=edit-nodes-]').each(function(index) {
			var node_id = $(this).attr("id").substring(11);
			var words = $('#' + node_id + '-words').html();
			count += parseInt(words);
		});
	}
	
	if (count > 0) {
		var cost = 0.07 * count;
		$('#icl_selected_word_count').html('. Selected word count = ' + count);
	} else {
		$('#icl_selected_word_count').html("");
	}
}
