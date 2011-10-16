$ = jQuery;

function updateGuests(selected) {
	$('#edit-guests').html('');
	var currVal = parseInt($('#edit-rooms').val());
	for (var i = currVal; i <= 4 * currVal; i++) {
		$('#edit-guests').append('<option val="' + i + '">' + i + '</option>');
	}
	if (selected) {
		$('#edit-guests').val(selected);
	}
}

$(document).ready( function() {
	// homepage slideshow
	$('.homepage-slideshow ul').cycle();

	// date fields datepicker
	$('#edit-check-in').datepicker({
		minDate: new Date(),
		onSelect: function(dateText, inst) {
			$('#edit-check-out').datepicker('option', 'minDate', new Date($('#edit-check-in').datepicker('getDate')));
		}
	});
	$('#edit-check-out').datepicker({
		minDate: new Date()
	});

	// reservation form
	$('#edit-rooms').change(updateGuests);

	updateGuests($('#edit-guests').val());
});

jQuery(function($){
	$.datepicker.regional['es'] = {
		clearText: 'Borrar',
		clearStatus: '',
		closeText: 'Cerrar',
		closeStatus: 'Cerrar sin modificar',
		prevText: 'Anterior',
		prevStatus: 'Ver el mes anterior',
		nextText: 'Siguiente',
		nextStatus: 'Ver el mes siguiente',
		currentText: 'Actual',
		currentStatus: 'Ver el mes actual',
		monthNames: ['Enero','Febrero','Marzo','Abril','Mayo','Junio',
		'Julio','Agosto','Septiembre','Octubre','Noviembre','Diciembre'],
		monthNamesShort: ['Ene','Feb','Mar','Abr','Mau','Jun',
		'Jul','Ago','Sep','Oct','Nov','Dec'],
		monthStatus: 'Ver otro mes',
		yearStatus: 'Ver otro año',
		weekHeader: 'Sm',
		weekStatus: '',
		dayNames: ['Domingo','Lunes','Martes','Miércoles','Jueves','Viernes','Sábado'],
		dayNamesShort: ['Dom','Lun','Mar','Mié','Jue','Vie','Sáb'],
		dayNamesMin: ['Do','Lu','Ma','Mi','Ju','Vi','Sa'],
		dayStatus: 'Utilizar DD como el primer día de la semana',
		dateStatus: 'Escoger el DD, MM d',
		dateFormat: 'mm/dd/yy',
		firstDay: 0,
		initStatus: 'Escoger la fecha', 
		isRTL: false
	};
});