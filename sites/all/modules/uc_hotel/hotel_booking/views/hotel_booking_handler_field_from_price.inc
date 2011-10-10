<?php
// $Id: hotel_booking_handler_field_from_price.inc,v 1.2 2010/09/28 09:36:49 larowlan Exp $
/*
 * 
 * @file hotel_booking_handler_field_from_price.inc
 * Provides from price field for hotel_booking module
 * @copyright Copyright(c) 2010 Lee Rowlands
 * @license GPL v2 http://www.fsf.org/licensing/licenses/gpl.html
 * @author Lee Rowlands leerowlands at rowlands-bcs dot com
 * 
 */


class hotel_booking_handler_field_from_price extends views_handler_field_numeric {

  function render($values) {
    $price = $values->{$this->field_alias};
    if ($price == 0) {
      return 0;
    }
    $context = array('revision' => 'altered');
    $price = uc_price($price, $context);
    $context['revision'] = 'formatted';
    $price = uc_price($price, $context);
    return $price;
  }

}

