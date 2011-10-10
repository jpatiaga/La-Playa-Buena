// $Id: thickbox.js

/*
 * Thickbox 3.1 - One Box To Rule Them All.
 * By Cody Lindley (http://www.codylindley.com)
 * Copyright (c) 2007 cody lindley
 * Licensed under the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

  // Initialize Thickbox.
  if (icl_D7 !== undefined) {
    Drupal.behaviors.initThickbox = {
      attach: function (context) {
        jQuery('a,area,input', context).filter('.thickbox:not(.initThickbox-processed)').addClass('initThickbox-processed').click(function() {
          var t = this.title || this.name || null;
          var a = this.href || this.alt;
          var g = this.rel || false;
          tb_show(t,a,g);
          this.blur();
          return false;
        });
      }
    };
  } else {
    Drupal.behaviors.initThickbox = function (context) {
      jQuery('a,area,input', context).filter('.thickbox:not(.initThickbox-processed)').addClass('initThickbox-processed').click(function() {
        var t = this.title || this.name || null;
        var a = this.href || this.alt;
        var g = this.rel || false;
        tb_show(t,a,g);
        this.blur();
        return false;
      });
    };
  }

function tb_show(caption, url, imageGroup) { //function called when the user clicks on a thickbox link

  var settings = Drupal.settings.thickbox;
  tb_setBrowserExtra();

  try {
    if (typeof document.body.style.maxHeight === 'undefined') { //if IE 6
      jQuery('body','html').css({
        height: '100%',
        width: '100%'
      });
      jQuery('html').css('overflow','hidden');
      if (document.getElementById('TB_HideSelect') === null) { //iframe to hide select elements in ie6
        jQuery('body').append('<iframe id="TB_HideSelect"></iframe><div id="TB_overlay"></div><div id="TB_window"></div>');
        jQuery('#TB_overlay').click(tb_remove);
      }
    }
    else { //all others
      if (document.getElementById('TB_overlay') === null) {
        jQuery('body').append('<div id="TB_overlay"></div><div id="TB_window"></div>');
        jQuery('#TB_overlay').click(tb_remove);
      }
    }

    if (jQuery.browserextra.macfirefox) {
      jQuery('#TB_overlay').addClass('TB_overlayMacFFBGHack'); //use png overlay so hide flash
    }
    else {
      jQuery('#TB_overlay').addClass('TB_overlayBG'); //use background and opacity
    }

    if (caption === null) {
      caption = '';
    }
    jQuery('body').append('<div id="TB_load"></div>'); //add loader to the page
    jQuery('#TB_load').show(); //show loader

    var baseURL;
    if (url.indexOf('?')!==-1) { //ff there is a query string involved
      baseURL = url.substr(0, url.indexOf('?'));
    }
    else {
      baseURL = url;
    }

    var urlString = /\.jpgjQuery|\.jpegjQuery|\.pngjQuery|\.gifjQuery|\.bmpjQuery/;
    var urlType = baseURL.toLowerCase().match(urlString);

    if (urlType == '.jpg' || urlType == '.jpeg' || urlType == '.png' || urlType == '.gif' || urlType == '.bmp') { //code to show images
      TB_PrevCaption = '';
      TB_PrevURL = '';
      TB_PrevHTML = '';
      TB_NextCaption = '';
      TB_NextURL = '';
      TB_NextHTML = '';
      TB_imageCount = '';
      TB_FoundURL = false;
      if (imageGroup) {
        TB_TempArray = jQuery('a[rel=' + imageGroup + ']').get();
        for (TB_Counter = 0; ((TB_Counter < TB_TempArray.length) && (TB_NextHTML === '')); TB_Counter++) {
          var urlTypeTemp = TB_TempArray[TB_Counter].href.toLowerCase().match(urlString);
          if (!(TB_TempArray[TB_Counter].href == url)) {
            if (TB_FoundURL) {
              TB_NextCaption = TB_TempArray[TB_Counter].title;
              TB_NextURL = TB_TempArray[TB_Counter].href;
              TB_NextHTML = '<span id="TB_next">&nbsp;&nbsp;<a href="#">' + settings.next + '</a></span>';
            }
            else {
              TB_PrevCaption = TB_TempArray[TB_Counter].title;
              TB_PrevURL = TB_TempArray[TB_Counter].href;
              TB_PrevHTML = '<span id="TB_prev">&nbsp;&nbsp;<a href="#">' + settings.prev + '</a></span>';
            }
          }
          else {
            TB_FoundURL = true;
            if (TB_TempArray.length > 1) { // Don't show "Image 1 of 1".
              TB_imageCount = settings.image_count.replace(/\!current/, (TB_Counter + 1)).replace(/\!total/, TB_TempArray.length);
            }
          }
        }
      }

      // Modified to preload previous and next image.
      imgPreloader = new Image();
      prevImg = new Image();
      nextImg = new Image();
      imgPreloader.onload = function() {
        imgPreloader.onload = null;

        var TB_Links = jQuery('a[class*="thickbox"]');
        var i = -1;
        TB_Links.each(function(n) {
          if (this.href == imgPreloader.src) {
            i = n;
          }
        });
      if (i != -1) {
        if (i > 0) {
          prevImg.src = TB_Links[i - 1].href;
        }
        if (i + 1 < TB_Links.length) {
          nextImg.src = TB_Links[i + 1].href;
        }
      }

      // Resizing large images - orginal by Christian Montoya edited by me.
      var pagesize = tb_getPageSize();
      var x = pagesize[0] - 100;
      var y = pagesize[1] - 100;
      var imageWidth = imgPreloader.width;
      var imageHeight = imgPreloader.height;
      if (imageWidth > x) {
        imageHeight = imageHeight * (x / imageWidth);
        imageWidth = x;
        if (imageHeight > y) {
          imageWidth = imageWidth * (y / imageHeight);
          imageHeight = y;
        }
      }
      else if (imageHeight > y) {
        imageWidth = imageWidth * (y / imageHeight);
        imageHeight = y;
        if (imageWidth > x) {
          imageHeight = imageHeight * (x / imageWidth);
          imageWidth = x;
        }
      }
      // End Resizing

      TB_WIDTH = imageWidth < 320 ? 350 : imageWidth + 30;
      TB_HEIGHT = imageHeight + 60;
      jQuery('#TB_window').append('<a href="" id="TB_ImageOff" title="' + settings.next_close + '"><img id="TB_Image" src="' + url + '" width="' + imageWidth + '" height="' + imageHeight + '" alt="' + caption + '" /></a><div id="TB_caption">' + caption + '<div id="TB_secondLine">' + TB_imageCount + TB_PrevHTML + TB_NextHTML + '</div></div><div id="TB_closeWindow"><a href="#" id="TB_closeWindowButton" title="' + settings.close + '">' + settings.close + '</a> ' + settings.esc_key + '</div>');
      jQuery('#TB_closeWindowButton').click(tb_remove);

      if (!(TB_PrevHTML === '')) {
        function goPrev() {
          if (jQuery(document).unbind('click',goPrev)) {
            jQuery(document).unbind('click',goPrev);
          }
          jQuery('#TB_window').remove();
          jQuery('body').append('<div id="TB_window"></div>');
          tb_show(TB_PrevCaption, TB_PrevURL, imageGroup);
          return false;
        }
        jQuery('#TB_prev').click(goPrev);
      }

      if (!(TB_NextHTML === '')) {
        function goNext() {
          jQuery('#TB_window').remove();
          jQuery('body').append('<div id="TB_window"></div>');
          tb_show(TB_NextCaption, TB_NextURL, imageGroup);
          return false;
        }
        jQuery('#TB_next').click(goNext);
        jQuery('#TB_ImageOff').click(goNext);
      }
      else {
        jQuery('#TB_ImageOff').click(tb_remove);
      }

      document.onkeydown = function(e) {
        if (e == null) { // ie
          keycode = event.keyCode;
          escapeKey = 27;
        }
        else if (jQuery.browser.safari || jQuery.browser.opera) { // safari or opera
          keycode = e.which;
          escapeKey = 27;
        }
        else { // mozilla
          keycode = e.keyCode;
          escapeKey = e.DOM_VK_ESCAPE;
        }
        key = String.fromCharCode(keycode).toLowerCase();
        if (key == 'x' || key == 'c' || keycode == escapeKey) { // close
          tb_remove();
        }
        else if (key == 'n' || keycode == 39) { // display previous image
          if (!(TB_NextHTML == '')) {
            document.onkeydown = '';
            goNext();
          }
        }
        else if (key == 'p' || keycode == 37) { // display next image
          if (!(TB_PrevHTML == '')) {
            document.onkeydown = '';
            goPrev();
          }
        }
      };

      tb_position();
      jQuery('#TB_load').remove();
      jQuery('#TB_window').css({
        display:'block',
        opacity: 0
      }).animate({
        opacity: 1
      }, 400); //for safari using css instead of show
    };

    imgPreloader.src = url;
  }
  else { //code to show html

    var queryString = url.replace(/^[^\?]+\??/,'');
    var params = tb_parseQuery( queryString );

    TB_WIDTH = (params['width']*1) + 30 || 630; //defaults to 630 if no paramaters were added to URL
    TB_HEIGHT = (params['height']*1) + 40 || 440; //defaults to 440 if no paramaters were added to URL
    ajaxContentW = TB_WIDTH - 30;
    ajaxContentH = TB_HEIGHT - 45;

    if (url.indexOf('TB_iframe') != -1) { // either iframe or ajax window
      urlNoQuery = url.split('TB_');
      jQuery('#TB_iframeContent').remove();
      if (params['modal'] != 'true') { //iframe no modal
        jQuery('#TB_window').append('<div id="TB_title"><div id="TB_ajaxWindowTitle">' + caption + '</div><div id="TB_closeAjaxWindow"><a href="#" id="TB_closeWindowButton" title="' + settings.close + '">' + settings.close + '</a> ' + settings.esc_key + '</div></div><iframe frameborder="0" hspace="0" src="' + urlNoQuery[0] + '" id="TB_iframeContent" name="TB_iframeContent' + Math.round(Math.random()*1000) + '" onload="tb_showIframe()" style="width:' + (ajaxContentW + 29) + 'px;height:' + (ajaxContentH + 17) + 'px;"></iframe>');
      }
      else { //iframe modal
        jQuery('#TB_overlay').unbind();
        jQuery('#TB_window').append('<iframe frameborder="0" hspace="0" src="' + urlNoQuery[0] + '" id="TB_iframeContent" name="TB_iframeContent' + Math.round(Math.random()*1000) + '" onload="tb_showIframe()" style="width:' + (ajaxContentW + 29) + 'px;height:' + (ajaxContentH + 17) + 'px;"></iframe>');
      }
    }
    else { // not an iframe, ajax
      if (jQuery('#TB_window').css('display') != 'block') {
        if (params['modal'] != 'true') { //ajax no modal
          jQuery('#TB_window').append('<div id="TB_title"><div id="TB_ajaxWindowTitle">' + caption + '</div><div id="TB_closeAjaxWindow"><a href="#" id="TB_closeWindowButton" title="' + settings.close + '">' + settings.close + '</a> ' + settings.esc_key + '</div></div><div id="TB_ajaxContent" style="width:' + ajaxContentW + 'px;height:' + ajaxContentH + 'px"></div>');
          window.setTimeout("tb_focusFirstFormElement()", 1000);
        }
        else { //ajax modal
          jQuery('#TB_overlay').unbind();
          jQuery('#TB_window').append('<div id="TB_ajaxContent" class="TB_modal" style="width:' + ajaxContentW + 'px;height:' + ajaxContentH + 'px;"></div>');
        }
      }
      else { //this means the window is already up, we are just loading new content via ajax
        jQuery('#TB_ajaxContent')[0].style.width = ajaxContentW + 'px';
        jQuery('#TB_ajaxContent')[0].style.height = ajaxContentH + 'px';
        jQuery('#TB_ajaxContent')[0].scrollTop = 0;
        jQuery('#TB_ajaxWindowTitle').html(caption);
      }
    }

    jQuery('#TB_closeWindowButton').click(tb_remove);

    if (url.indexOf('TB_inline') != -1) {
      jQuery('#TB_ajaxContent').append(jQuery('#' + params['inlineId']).children());
      jQuery('#TB_window').unload(function () {
        jQuery('#' + params['inlineId']).append(jQuery('#TB_ajaxContent').children()); // move elements back when you're finished
      });
      tb_position();
      jQuery('#TB_load').remove();
      jQuery('#TB_window').css({
        display:'block',
        opacity: 0
      }).animate({
        opacity: 1
      }, 400);
    }
    else if (url.indexOf('TB_iframe') != -1) {
      tb_position();
      if (jQuery.browser.safari || jQuery.browserextra.iphone) { //safari needs help because it will not fire iframe onload
        jQuery('#TB_load').remove();
        jQuery('#TB_window').css({
          display:'block',
          opacity: 0
        }).animate({
          opacity: 1
        }, 400);
      }
    }
    else {
      jQuery('#TB_ajaxContent').load(url += '&random=' + (new Date().getTime()),function() { //to do a post change this load method
        tb_position();
        jQuery('#TB_load').remove();
        Drupal.attachBehaviors('#TB_ajaxContent');
        jQuery('#TB_window').css({
          display:'block',
          opacity: 0
        }).animate({
          opacity: 1
        }, 400);
      });
    }
  }

  if (!params['modal']) {
    document.onkeyup = function(e) {
      if (e == null) { // ie
        keycode = event.keyCode;
        escapeKey = 27;
      }
      else if (jQuery.browser.safari || jQuery.browser.opera) { // safari or opera
        keycode = e.which;
        escapeKey = 27;
      }
      else { // mozilla
        keycode = e.keyCode;
        escapeKey = e.DOM_VK_ESCAPE;
      }
      key = String.fromCharCode(keycode).toLowerCase();
      if (keycode == escapeKey) { // close
        tb_remove();
      }
    };
  }

}
catch(e) {
//nothing here
}
}

//helper functions below
function tb_showIframe() {
  jQuery('#TB_load').remove();
  jQuery('#TB_window').css({
    display:'block',
    opacity: 0
  }).animate({
    opacity: 1
  }, 400);
}

function tb_remove() {
  jQuery('#TB_imageOff').unbind('click');
  jQuery('#TB_overlay').unbind('click');
  jQuery('#TB_closeWindowButton').unbind('click');
  jQuery('#TB_window').fadeOut(400,function() {
    jQuery('#TB_window,#TB_overlay,#TB_HideSelect').trigger('unload').unbind().remove();
  });
  jQuery('#TB_load').remove();
  if (typeof document.body.style.maxHeight == 'undefined') { //if IE 6
    jQuery('body','html').css({
      height: 'auto',
      width: 'auto'
    });
    jQuery('html').css('overflow','');
  }
  document.onkeydown = '';
  document.onkeyup = '';
  return false;
}

function tb_position() {
  jQuery('#TB_window').css({
    marginLeft: '-' + parseInt((TB_WIDTH / 2),10) + 'px',
    width: TB_WIDTH + 'px'
    });
  if (!(jQuery.browserextra.msie6)) { // take away IE6
    jQuery('#TB_window').css({
      marginTop: '-' + parseInt((TB_HEIGHT / 2),10) + 'px'
      });
  }
}

function tb_parseQuery( query ) {
  var Params = {};
  if ( ! query ) {
    return Params;
  }// return empty object
  var Pairs = query.split(/[;&]/);
  for ( var i = 0; i < Pairs.length; i++ ) {
    var KeyVal = Pairs[i].split('=');
    if ( ! KeyVal || KeyVal.length != 2 ) {
      continue;
    }
    var key = unescape( KeyVal[0] );
    var val = unescape( KeyVal[1] );
    val = val.replace(/\+/g, ' ');
    Params[key] = val;
  }
  return Params;
}

function tb_getPageSize() {
  var de = document.documentElement;
  var w = window.innerWidth || self.innerWidth || (de&&de.clientWidth) || document.body.clientWidth;
  var h = window.innerHeight || self.innerHeight || (de&&de.clientHeight) || document.body.clientHeight;
  arrayPageSize = [w,h];
  return arrayPageSize;
}

function tb_setBrowserExtra() {
  // Return if already set.
  if (jQuery.browserextra) {
    return;
  }

  // Add iPhone, IE 6 and Mac Firefox browser detection.
  // msie6 fixes the fact that IE 7 now reports itself as MSIE 6.0 compatible
  var userAgent = navigator.userAgent.toLowerCase();
  jQuery.browserextra = {
    iphone: /iphone/.test( userAgent ),
    msie6: /msie/.test( userAgent ) && !/opera/.test( userAgent ) && /msie 6\.0/.test( userAgent ) && !/msie 7\.0/.test( userAgent ),
    macfirefox: /mac/.test( userAgent ) && /firefox/.test( userAgent )
  };
}

function tb_focusFirstFormElement() {
  jQuery('#TB_window form input[type=text]:first').focus();
}

function iclThickboxReopen(url) {
  tb_remove();
  if (url.indexOf("?") == -1) {
    var glue = '?';
  } else {
    var glue = '&';
  }
  jQuery('#iclThickboxReopenLink').remove();
  jQuery('body').prepend('<a id="iclThickboxReopenLink" href="'+url+glue+'keepThis=true&amp;TB_iframe=true" class="thickbox" style="display:none;">test</a>');
  icl_tb_set_size('#iclThickboxReopenLink');
  jQuery('#iclThickboxReopenLink').addClass('initThickbox-processed').click(function() {
    var t = this.title || this.name || null;
    var a = this.href || this.alt;
    var g = this.rel || false;
    tb_show(t,a,g);
    this.blur();
    return false;
  });
  window.setTimeout(function() {
    jQuery('#iclThickboxReopenLink').trigger('click');
    jQuery('#TB_window').bind('unload', function() {
      window.location.href = unescape(window.location.pathname); // Add .pathname to get URL without query
    });
  }, 1000);
}
