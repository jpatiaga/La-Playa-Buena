$ = jQuery;
$(document).ready( function() {
	// homepage slideshow
	$('.homepage-slideshow ul').cycle();

	// date fields datepicker
	$('#edit-check-in, #edit-check-out').datepicker();
});
