<?php

/**
 * @file
 * This is the Form API Tutorial from the handbook.
 * TODO: Update this URL, and update it in the dynamic text below.
 * @see http://drupal.org/node/262422
 *
 * It goes through nine form examples in increasing complexity to demonstrate
 * Drupal 7 Form API.
 *
 * Links are provided inline for the related handbook pages.
 */

/**
 * Main Form tutorial page.
 *
 * @see registration_process_1()
 * @see registration_process_2()
 * @see registration_process_3()
 * @see registration_process_4()
 * @see registration_process_5()
 * @see registration_process_6()
 * @see registration_process_7()
 * @see registration_process_8()
 * @see registration_process_9()
 * @see registration_process_10()
 *
 * @ingroup registration
 */
function registration_process() {
  return t('This is a set of nine form tutorials tied to the <a href="http://drupal.org/node/262422">Drupal handbook</a>.');
}

//////////////// Tutorial Example 1 //////////////////////

/**
 * This first form function is from the @link http://drupal.org/node/717722 Form Tutorial handbook page @endlink
 *
 * It just creates a very basic form with a textfield.
 *
 * This function is called the "form constructor function". It builds the form.
 * It takes a two arguments, $form and $form_state, but if drupal_get_form()
 * sends additional arguments, they will be provided after $form_state.
 *
 * @ingroup registration
 */
function registration_process_1($form, &$form_state) {

  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('A form with nothing but a textfield'),
  );
  // This is the first form element. It's a textfield with a label, "Name"
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
  );
  return $form;
}


//////////////// Tutorial Example 2 //////////////////////

/**
 * This is Example 2, a basic form with a submit button.
 *
 * @see http://drupal.org/node/717726
 * @ingroup registration
 */
function registration_process_2($form, &$form_state) {
  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('A simple form with a submit button'),
  );

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
  );

  // Adds a simple submit button that refreshes the form and clears its
  // contents. This is the default behavior for forms.
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );
  return $form;
}

//////////////// Tutorial Example 3 //////////////////////

/**
 * Example 3: A basic form with fieldsets.
 *
 * We establish a fieldset element and then place two text fields within
 * it, one for a first name and one for a last name. This helps us group
 * related content.
 *
 * Study the code below and you'll notice that we renamed the array of the first
 * and last name fields by placing them under the $form['name']
 * array. This tells Form API these fields belong to the $form['name'] fieldset.
 *
 * @ingroup registration
 */
function registration_process_3($form, &$form_state) {
  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('A form with a fieldset'),
  );

  $form['name'] = array(
    '#type' => 'fieldset',
    '#title' => t('Name'),
  );
  $form['name']['first'] = array(
    '#type' => 'textfield',
    '#title' => t('First name'),
  );
  $form['name']['last'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
  );


  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );
  return $form;
}


//////////////// Tutorial Example 4 //////////////////////

/**
 * Example 4: Basic form with required fields.
 *
 * @ingroup registration
 */
function registration_process_4($form, &$form_state) {
  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('A form with validation'),
  );

  $form['name'] = array(
    '#type' => 'fieldset',
    '#title' => t('Name'),
    // Make the fieldset collapsible.
    '#collapsible' => TRUE, // Added
    '#collapsed' => FALSE,  // Added
  );

  // Make these fields required.
  $form['name']['first'] = array(
    '#type' => 'textfield',
    '#title' => t('First name'),
    '#required' => TRUE, // Added
  );
  $form['name']['last'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#required' => TRUE, // Added
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );
  return $form;
}


//////////////// Tutorial Example 5 //////////////////////

/**
 * Example 5: Basic form with additional element attributes.
 *
 * This demonstrates additional attributes of text form fields.
 *
 * For a more extensive example on element types
 * @see http://drupal.org/node/751826
 *
 * See the @link http://api.drupal.org/api/file/developer/topics/forms_api.html complete form reference @endlink
 *
 * @ingroup registration
 */
function registration_process_5($form, &$form_state) {
  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('A form with additional attributes'),
    '#description' => t('This one adds #default_value and #description'),
  );
  $form['name'] = array(
    '#type' => 'fieldset',
    '#title' => t('Name'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['name']['first'] = array(
    '#type' => 'textfield',
    '#title' => t('First name'),
    '#required' => TRUE,
    '#default_value' => "First name", // added default value.
    '#description' => "Please enter your first name.", // added description
    '#size' => 20, // added
    '#maxlength' => 20, // added
  );
  $form['name']['last'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );
  return $form;
}


//////////////// Tutorial Example 6 //////////////////////

/**
 * Example 6: A basic form with a validate handler.
 *
 * From http://drupal.org/node/717736
 * @see registration_process_6_validate()
 */
function registration_process_6($form, &$form_state) {
  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('A form with a validation handler'),
  );

  $form['name'] = array(
    '#type' => 'fieldset',
    '#title' => t('Name'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['name']['first'] = array(
    '#type' => 'textfield',
    '#title' => t('First name'),
    '#required' => TRUE,
    '#default_value' => "First name",
    '#description' => "Please enter your first name.",
    '#size' => 20,
    '#maxlength' => 20,
  );
  $form['name']['last'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#required' => TRUE,
  );

  // New form field added to permit entry of year of birth.
  // The data entered into this field will be validated with
  // the default validation function.
  $form['year_of_birth'] = array(
    '#type' => 'textfield',
    '#title' => "Year of birth",
    '#description' => 'Format is "YYYY"',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );
  return $form;
}



/**
 * Now we add a handler/function to validate the data entered into the
 * "year of birth" field to make sure it's between the values of 1900
 * and 2000. If not, it displays an error. The value report is
 * $form_state['values'] (see http://drupal.org/node/144132#form-state).
 *
 * Notice the name of the function. It is simply the name of the form
 * followed by '_validate'. This is always the name of the default validation
 * function. An alternate list of validation functions could have been provided
 * in $form['#validate'].
 *
 * @see registration_process_6()
 */
function registration_process_6_validate($form, &$form_state) {
  $year_of_birth = $form_state['values']['year_of_birth'];
  if ($year_of_birth && ($year_of_birth < 1900 || $year_of_birth > 2000)) {
    form_set_error('year_of_birth', t('Enter a year between 1900 and 2000.'));
  }
}


//////////////// Tutorial Example 7 //////////////////////

/**
 * Example 7: With a submit handler.
 *
 * From the handbook page:
 * http://drupal.org/node/717740
 *
 * @see registration_process_7_validate()
 * @see registration_process_7_submit()
 * @ingroup registration
 */
function registration_process_7($form, &$form_state) {
  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('A form with a submit handler'),
  );
  $form['name'] = array(
    '#type' => 'fieldset',
    '#title' => t('Name'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['name']['first'] = array(
    '#type' => 'textfield',
    '#title' => t('First name'),
    '#required' => TRUE,
    '#default_value' => "First name",
    '#description' => "Please enter your first name.",
    '#size' => 20,
    '#maxlength' => 20,
  );
  $form['name']['last'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#required' => TRUE,
  );
  $form['year_of_birth'] = array(
    '#type' => 'textfield',
    '#title' => "Year of birth",
    '#description' => 'Format is "YYYY"',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );
  return $form;
}


/**
 * Validation function for registration_process_7().
 */
function registration_process_7_validate($form, &$form_state) {
  $year_of_birth = $form_state['values']['year_of_birth'];
  if ($year_of_birth && ($year_of_birth < 1900 || $year_of_birth > 2000)) {
    form_set_error('year_of_birth', t('Enter a year between 1900 and 2000.'));
  }
}

/**
 * Submit function for registration_process_7().
 *
 * Adds a submit handler/function to our form to send a successful
 * completion message to the screen.
 */
function registration_process_7_submit($form, &$form_state) {
  drupal_set_message(t('The form has been submitted. name="@first @last", year of birth=@year_of_birth',
    array('@first' => $form_state['values']['first'], '@last' => $form_state['values']['last'], '@year_of_birth' => $form_state['values']['year_of_birth'])));
}


//////////////// Tutorial Example 8 //////////////////////

/**
 * Example 8: A simple multistep form with a Next and a Back button.
 *
 * Handbook page: http://drupal.org/node/717750.
 *
 * For more extensive multistep forms, see
 * @link registration_wizard.inc registration_wizard.inc @endlink
 *
 *
 * Adds logic to our form builder to give it two pages.
 * The @link ajax_example_wizard AJAX Example's Wizard Example @endlink
 * gives an AJAX version of this same idea.
 *
 * @see registration_process_8_submit()
 * @see registration_process_8_validate()
 * @see registration_process_8_page_two()
 * @see registration_process_8_page_two_submit()
 * @see registration_process_8_next_submit()
 * @see registration_process.inc
 * @ingroup registration
 */
function registration_process_8($form, &$form_state) {

  // Display page 2 if $form_state['page_num'] == 1
  if (!empty($form_state['page_num']) && $form_state['page_num'] == 2) {
    return registration_process_8_page_two($form, $form_state);
  }

  // Otherwise we build page 1.
  $form_state['page_num'] = 1;

  $form['description'] = array(
    '#type' => 'item',
  );
  $form['check_in'] = array(
	  '#type' => 'textfield',
	  '#title' => t('Check-in date'),
	  '#size' => 10,
	  '#maxlength' => 10,
	  '#required' => TRUE,
	  '#default_value' => isset($form_state['values']['check_in']) ? $form_state['values']['check_in'] : date('m/d/Y'),
  );
  $form['check_out'] = array(
	  '#type' => 'textfield',
	  '#title' => t('Check-out date'),
	  '#size' => 10,
	  '#maxlength' => 10,
	  '#required' => TRUE,
	  '#default_value' => isset($form_state['values']['check_out']) ? $form_state['values']['check_out'] : date('m/d/Y', time() + 24 * 60 * 60),
  );
  $roomsVal = isset($form_state['values']['rooms']) ? $form_state['values']['rooms'] : 1;
  $form['rooms'] = array(
		'#type' => 'select',
		'#title' => t('Rooms'),
		'#default_value' => $roomsVal,
		'#options' => array(
			1 => '1',
			2 => '2',
			3 => '3',
			4 => '4',
		),
	);
  $guestsVal = isset($form_state['values']['guests']) ? $form_state['values']['guests'] : $roomsVal;
  $guestsOpt = array();
//  for ($i = $roomsVal; $i <= 4 * $roomsVal; $i++) {
//	  $guestsOpt[$i] = $i;
//  }
  for ($i = 1; $i <= 16; $i++) {
	  $guestsOpt[$i] = $i;
  }
  $form['guests'] = array(
		'#type' => 'select',
		'#title' => t('Guests'),
		'#default_value' => $guestsVal,
		'#options' => $guestsOpt,
	);

  $form['next'] = array(
    '#type' => 'submit',
    '#value' => t('Next >>'),
    '#submit' => array('registration_process_8_next_submit'),
    '#validate' => array('registration_process_8_next_validate'),
  );
  return $form;
}

/**
 * Returns the form for the second page of registration_process_8().
 */
function registration_process_8_page_two($form, &$form_state) {
	global $language;
	$form['description'] = array(
		'#type' => 'item',
		'#title' => t('Please enter your contact information to complete the reservation'),
	);
	$form['dates_display'] = array(
		'#type' => 'item',
		'#prefix' => '<div class="reservation-info">',
		'#markup' => $form_state['input']['check_in'] . ($language->language == 'es' ? ' a ' : ' to ') . $form_state['input']['check_out'] . '<br />' .
			$form_state['input']['rooms'] . ($language->language == 'es' ? ' ' . ($form_state['input']['rooms'] == 1 ? 'habitación' : 'habitaciones') . ', ' : ' room' . ($form_state['input']['rooms'] == 1 ? '' : 's') . ', ') . $form_state['input']['guests'] . ($language->language == 'es' ? ' huésped' . ($form_state['input']['guests'] == 1 ? '' : 'es') : ' guest'. ($form_state['input']['guests'] == 1 ? '' : 's')),
		'#suffix' => '</div>',
	);
	$form['name'] = array(
		'#type' => 'textfield',
		'#title' => t('Your name'),
		'#required' => TRUE,
	);
	$form['email'] = array(
		'#type' => 'textfield',
		'#title' => t('E-mail address'),
		'#required' => TRUE,
	);
	$form['phone'] = array(
		'#type' => 'textfield',
		'#title' => t('Phone number'),
		'#required' => TRUE,
	);
  
  $form['back'] = array(
    '#type' => 'submit',
    '#value' => t('Modify reservation'),
    '#submit' => array('registration_process_8_page_two_back'),
    // We won't bother validating the required 'color' field, since they
    // have to come back to this page to submit anyway.
    '#limit_validation_errors' => array(),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Reserve now!'),
    '#submit' => array('registration_process_8_page_two_submit'),
	'#validate' => array('registration_process_8_page_two_next_validate'),
  );
  return $form;
}


/**
 * Validate handler for the next button on first page.
 */
function registration_process_8_next_validate($form, &$form_state) {
	if (!strtotime($form_state['values']['check_in'])) {
		form_set_error('check_in', t('Invalid date'));
	}
	if (!strtotime($form_state['values']['check_out'])) {
		form_set_error('check_out', t('Invalid date'));
	}
	if (strtotime($form_state['values']['check_out']) < strtotime($form_state['values']['check_in'])) {
		form_set_error('check_out', t('Check in date cannot be after the checkout date'));
	}
}

/**
 * Validate handler for the next button on second page.
 */
function registration_process_8_page_two_next_validate($form, &$form_state) {
	if (!valid_email_address($form_state['values']['email'])) {
		form_set_error('email', t('Please enter a valid e-mail address'));
	}
}

/**
 * Submit handler for registration_process_8() next button.
 *
 * Capture the values from page one and store them away so they can be used
 * at final submit time.
 */
function registration_process_8_next_submit($form, &$form_state) {

  // Values are saved for each page.
  // to carry forward to subsequent pages in the form.
  // and we tell FAPI to rebuild the form.
  $form_state['page_values'][1] = $form_state['values'];

  if (!empty($form_state['page_values'][2])) {
    $form_state['values'] = $form_state['page_values'][2];
  }

  // When form rebuilds, it will look at this to figure which page to build.
  $form_state['page_num'] = 2;
  $form_state['rebuild'] = TRUE;
}

/**
 * Back button handler submit handler.
 *
 * Since #limit_validation_errors = array() is set, values from page 2
 * will be discarded. We load the page 1 values instead.
 */
function registration_process_8_page_two_back($form, &$form_state) {
  $form_state['values'] = $form_state['page_values'][1];
  $form_state['page_num'] = 1;
  $form_state['rebuild'] = TRUE;
}

/**
 * The page 2 submit handler.
 *
 * This is the final submit handler. Gather all the data together and output
 * it in a drupal_set_message().
 */
function registration_process_8_page_two_submit($form, &$form_state) {
  global $language;
  // Normally, some code would go here to alter the database with the data
  // collected from the form. Instead sets a message with drupal_set_message()
  // to validate that the code worked.
  $page_one_values = $form_state['page_values'][1];
//  drupal_set_message(t('The form has been submitted. name="@first @last", year of birth=@year_of_birth',
//  array('@first' => $page_one_values['check_in'], '@last' => $page_one_values['check_out'], '@year_of_birth' => $page_one_values['guests'])));

//  if (!empty($page_one_values['first2'])) {
//    drupal_set_message(t('Second name: name="@first @last", year of birth=@year_of_birth',
//    array('@first' => $page_one_values['first2'], '@last' => $page_one_values['last2'], '@year_of_birth' => $page_one_values['year_of_birth2'])));
//  }
//  drupal_set_message(t('And the favorite color is @color', array('@color' => $form_state['values']['email'])));

  $screen_message = $language->language == 'es' ? 'Gracias por su reserva. Nos contactaremos con usted en las próximas 48 horas' :
		  'Thank you for your reservation. We will contact you in the next 48 hours.';
  drupal_set_message($screen_message);

  $site_email = variable_get('site_mail', 'info@laplayabuena.com');
  $message = "Han hecho una reservacion en Macedonia:\n\n
Fecha: " . date('l, F j, Y') . " " . date('d/m/Y') . "\n
Nombre: " . $form_state['values']['name'] . "\n
Email: " . $form_state['values']['email'] . "\n
Telf: " . $form_state['values']['phone'] . "\n\n
No. huespedes: " . $form_state['values']['guests'] . "\n
Habitaciones: " . $form_state['values']['rooms'] . "\n\n
Desde: " . $form_state['values']['check_in'] . "\n
Hasta: " . $form_state['values']['check_out'] . "\n\n
Por favor comunicarse en las proximas 48 horas\n\n
";
  mail($site_email, 'Reservacion Macedonia', $message);

//  drupal_mail('registration', 'reservation', 'info@laplayabuena.com', $language);

  // If we wanted to redirect on submission, set $form_state['redirect']
  // $form_state['redirect'] = 'node'; // Redirects the user to /node.
}

function registration_mail($key, &$message, $params) {
//	$data['user'] = $params['name'];
//	$options['language'] = $message['language'];
//	user_mail_tokens($variables, $data, $options);
	switch ($key) {
		case 'reservation':
//			$langcode = $message['language']->language;
			$message['subject'] = t('Notification from Macedonia');
			$message['body'][] = t("Han hecho una reservacion." . var_export($params,true));
			break;
	}
}