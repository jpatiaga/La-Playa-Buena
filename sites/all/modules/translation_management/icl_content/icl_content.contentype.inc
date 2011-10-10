<?php

/*
 * $Id: icl_content.contentype.inc,v 1.3 2010/11/15 08:37:44 brucepearson Exp $
 * 
 * @file This is the ICanLocalize Content type settings screen 
 */

/**
 * Returns the fields available for translation.
 * This is used on content type edit administration page.
 *
 * @param string $type A valid node type
 * @return array The fields available for translation
 */
function icl_content_get_node_type_fields($type) {
  $raw_form = icl_content_get_node_add_form ( $type );
  
  $fields = array ();
  icl_content_walk_node_form ( $raw_form, $fields );
  
  foreach ($fields as $index => $field) {
    if ($field == '') {
      $fields[$index] = $index;
    }
  }
  
  return $fields;
}

/**
 * Retrieves the node/add form for a given node type $type.
 * We need this info to extract possibly translatable fields.
 * Used on the content type editig administration page.
 *
 * @param string $type A valid node type
 * @return array The raw form array half processed [already includes all visible fields]
 */
function icl_content_get_node_add_form($type) {
  global $user;
  
  module_load_include ( 'inc', 'node', 'node.pages' );
  
  $form_id = $type . '_node_form';
  $form_state = array (
      'storage' => NULL, 
      'submitted' => FALSE, 
      'post' => array () );
  $type = isset($type) ? str_replace('-', '_', $type) : NULL;
  $node = (object) array('uid' => $user->uid, 'name' => (isset($user->name) ? $user->name : ''), 'type' => $type, 'language' => LANGUAGE_NONE);
  
  $form_state['values'] = array();

  $form_state['build_info']['args'] = array($node);
  $form = drupal_retrieve_form ( $form_id, $form_state, $node );
  drupal_prepare_form ( $form_id, $form, $form_state );
  $form = form_builder($form_id, $form, $form_state);


  
  return $form;
}

/**
 * This is a variation of array_walk_recursive() but it walks the array from the top
 * not from the bottom(leafs). It is also calling a specific collector function in 
 * this module.
 *
 * @param array $input The input array
 * @param array $elements The gathered elements.
 * @param mixed $key The actual array key. You must leave it to null, used internally.
 */
function icl_content_walk_node_form($input, &$elements, $key = NULL) {
  static $data = array();
  
  if (sizeof($data) > 10) {
    return;
  }
  
  if (!is_numeric($key) && is_array ( $input )) {
    foreach ( $input as $key => $value ) {
      icl_content_retrieve_translatable_node_elements ( $value, $key, $elements );
      $data[] = $key;
      icl_content_walk_node_form ( $value, $elements, $key );
      array_pop($data);
    }
  }
  
}

/**
 * This is a collector callback for icantranslate_walk_node_form().
 * It collects the elements for content type administration page
 *
 * @param array $element The element in question
 * @param mixed $key The array key of the element
 * @param array $extracted The array to put results in
 */
function icl_content_retrieve_translatable_node_elements($element, $key, &$extracted) {
  if (is_array ( $element )) { 
    if (isset ( $element ['#type'] ) ) {
      if (isset ( $element ['#title'] ) && $key !== 'taxonomy') {
        // Extend the switch with #type options to include more possible field type
        switch ($element ['#type']) {
          case 'textfield' :
          case 'textarea' :
          case 'text_textfield' :
          case 'text_textarea' :
          case 'optionwidgets_select' :
          case 'optionwidgets_buttons' :
          case 'optionwidgets_onoff' :
            if (isset ( $element ['#field_name'] )) {
              // CCK field
              $extracted [$element ['#field_name']] = $element ['#title'];
            } else if (! is_numeric ( $key )) {
              // Drupal field
              $extracted [$key] = $element ['#title'];
            }
            break;
          default :
            break;
        }
      } else if ($key == 'taxonomy' && module_exists ( 'i18ntaxonomy' )) { // Taxonomy
        foreach ( $element as $vid => $vocabulary ) {
          if ($vid == 'tags') { // Taxonomy tags [special taxonomy array member]
            foreach ( $vocabulary as $tag_id => $tag ) {
              if (is_numeric ( $tag_id )) {
                //$terms = explode ( ', ', $tag );
                $extracted ['taxonomy[' . $tag_id . ']'] = $tag ['#title'];
              }
            }
          } else if (is_numeric ( $vid )) {
            $extracted ['taxonomy[' . $vid . ']'] = $vocabulary ['#title'];
          }
        }
      } else if ($key == 'nodewords') {
        $extracted ['nodewords'] = $element['label'];
      } else if ($element['#type'] == 'container') {
        // this is probably a cck field (including the body)
        $title = _icl_content_retrieve_title($key, $element);
        if ($title) {
          $extracted[$key] = $title;
        }
      }
      
    }
  }
}

function _icl_content_retrieve_title($key, $element) {
  if (is_array($element)) {
    if (isset ($element['#field_name'])) {
      if ($element['#field_name'] == $key) {
        return $element['#title'];
      }
    }
  }
  
  foreach ($element as $item) {
    if (is_array($item)) {
      $title = _icl_content_retrieve_title($key, $item);
      if ($title) {
        return $title;
      }
    }
  }
  return NULL;
}