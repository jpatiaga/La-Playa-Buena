// $Id: icl_comments.js,v 1.3 2010/09/03 14:40:55 jozik Exp $
  
function select_default(n) {
  google.language.translate(n.html(), "", languages[0].code, function(result) {
    if (!result.error) {
      n.html(result.translation + source_language_message);
    } else {
      n.html(failed_translation_message);
    }
  });
}
          
jQuery(document).ready(function(){
    
  jQuery(".comment .content").each(function (i) {
    if(jQuery(this).find(".comment_sent").length == 0) {
      // duplicate the comment
      var temp = jQuery(this).clone().insertAfter(this);
      temp.html('<div class="icanlocalize_orig_comment">' + temp.html() + '</div>');
        
      // show translation below.
      select_default(jQuery(this));
    }
  });
});
