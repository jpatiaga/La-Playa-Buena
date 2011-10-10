<?php
/*
 * $Id: icl_core.wrapper.inc,v 1.54 2010/12/15 04:11:29 brucepearson Exp $
 * 
 * @file D6 to D7 migration wrapper.
 */

/*
 * Global wrapper functions have '_icl_wrapper' prefix.
 * Module specific wrapper functions have '_icl_$module_wrapper' prefix
 * and stored in icl_$module_wrapper.inc.
 *
 * NOTES:
 * Try to keep function name close to original Drupal's function name.
 * Use D6 function name if possible.
 */

define('ICL_D7', TRUE);

/**
 * @todo Where to add this?
 */
function _icl_core_wrapper_init() {
  drupal_add_js(array('icl_D7' => 1), 'setting');
  drupal_add_js('var icl_D7 = 1;', 'inline');
}

/**
 * Create roles.
 * @see http://drupal.org/node/283261
 * @todo D7 wait for user_role_set_permissions() to be added
 * @todo Check if works D7
 *
 * @param array $roles
 *   'icanlocalize translator' => array(
 *     'title' => 'ICanLocalize translator',
 *     'variable' => 'icl_translate_role'
 *     'variable_check' => 'icl_creating_translate_role'
 *     'permission' => 'can do translation jobs');
 */
function _icl_wrapper_create_roles($roles = array(), $module = 'icl_translate') {
  foreach ($roles as $lowercase_name => $role) {
    require_once(drupal_get_path('module', 'user') . "/user.admin.inc");
    $key = array_search($lowercase_name, user_roles());
    if ($key) {
      variable_set($role['variable'], $key);
      if (variable_get($role['variable_check'], 0) == 1) {
        // we have created the role.
        // we can safely set the permissions

        //user_role_set_permissions(); // not documented yet, can't find it in D7 code
        _icl_wrapper_db_query("INSERT INTO {role_permission} (rid, permission, module) VALUES ( %d, '%s', '%s' )", $key, $role['permission'], $module);
        variable_set($role['variable_check'], 0);
      }
    } else {
      variable_set($role['variable_check'], 1);
      $role = (object) $role;
      $role->name = $lowercase_name;
      user_role_save($role);
    }
  }
}

/**
 * db_result() wrapper.
 * Fetches one field.
 *
 * @param mixed $query Database query result resource
 * @return mixed Resulting field or FALSE
 */
function _icl_wrapper_db_result($query) {
  
  return $query->fetchField();
}

/**
 * DB table name wrapper.
 *
 * @param string $table_name D6 table name
 * @return string D6|D7 table name
 */
function _icl_wrapper_table_name($table_name) {

  switch ($table_name) {
    case 'permission':
      return 'role_permission';
      break;

    case 'term_data':
      return 'taxonomy_term_data';
      break;

    case 'blocks':
      return 'block';
      break;

    case 'blocks_roles':
      return 'block_role';
      break;

    case 'boxes':
      return 'block_custom';
      break;

    case 'node_revisions';
      return 'node_revision';
    
    case 'comments';
      return 'comment';
    
    default:
      return $table_name;
      break;
  }
}

/**
 * Form markup wrapper.
 * @todo Reconsider unsetting #value
 *
 * @param array $element
 * @return array Form element array
 */
function _icl_wrapper_form_create_markup($element) {
  if (isset($element['#value'])) {
    $element['#markup'] = $element['#value'];
  }
  //unset($element['#value']);
  unset($element['#type']);
  return $element;
}

/**
 * Converts form element's ahah to ajax.
 *
 * @param array $element Form element
 * @return array
 */
function _icl_wrapper_form_convert_ahah_to_ajax($element) {
  $element['#ajax'] = $element['#ahah'];
  unset($element['#ahah']);
}

/**
 * Creates form redirection element.
 * @todo Check if parsing works for D7
 *
 * @param array $form
 * @param array $goto
 */
function _icl_wrapper_form_create_redirect(&$form, &$form_state, $goto = array()) {
  $options = array();
  if (isset($goto[1]) && is_string($goto[1])) {
    parse_str($goto[1], $options);
    $goto = array($goto[0], array('query' => $options));
  }
  
  $form_state['redirect'] = $goto;
}

/**
 * Creates D7 attributes array
 * 
 * @param array $attributes
 * @return array
 */
function _icl_wrapper_form_create_attributes($attributes) {

  foreach ($attributes as $attribute => $value) {
    $attributes[$attribute] = array($value);
  }

  return $attributes;
}

/**
 * drupal_get_form() wrapper
 *
 * @param string $name
 * @param array $array
 * @return string
 */
function _icl_wrapper_drupal_get_form($name, $arg = NULL) {

  return drupal_render(drupal_get_form($name, $arg));
}

/**
 * drupal_to_js() wrapper.
 * Function name has changed.
 *
 * @param mixed $var
 * @return string JSON encoded
 */
function _icl_wrapper_drupal_to_js($var) {

  return drupal_json_encode($var);
}

/**
 * drupal_json() wrapper.
 * Function name has changed.
 *
 * @param mixed $var
 */
function _icl_wrapper_drupal_json($var) {

  drupal_json_output($var);
}

/**
 * drupal_http_request() wrapper.
 * Parameters changed.
 *
 * @param string $request_uri
 * @param array $headers
 * @param string $method
 * @param string $data
 * @param int $retry
 * @return object Response object
 */
function _icl_wrapper_drupal_http_request(
        $request_uri,
        $headers = array(),
        $method = 'GET',
        $data = NULL,
        $retry = 3)
{

  return drupal_http_request(
    $request_uri,
    array(
      'headers' => $headers,
      'method' => $method,
      'data' => $data,
      'method' => $method
    )
   );
}

/**
 * drupal_set_header() wrapper.
 * Function name has changed.
 * Uses D7 parametres
 * 
 * @param string $name HTTP header name
 * @param string $value
 */
function _icl_wrapper_drupal_set_header($name, $value, $append = FALSE) {
  drupal_add_http_header($name, $value, $append);
}

/**
 * drupal_set_html_head() wrapper.
 * Function name has changed.
 * @todo Check if this works
 *
 * @param mixed $data
 * @param string $key Unique identifier
 */
function _icl_wrapper_drupal_set_html_head($data, $key = NULL) {
  drupal_add_html_head($data, $key);
}

/**
 * drupal_goto() wrapper.
 * Parameters changed, follows D6 parameter order.
 * @todo Check if parsing works for D7
 *
 * @param string $path
 * @param string $query
 * @param int $http_response_code
 * @param string $fragment
 * @param array $options Extra options for D7
 */
function _icl_wrapper_drupal_goto(
  $path,
  $query = NULL,
  $fragment = NULL,
  $http_response_code = 302,
  $options = array()
  )
{

  if (!is_null($query)) {
    parse_str($query, $query_array);
    $options['query'] = $query_array;
  }

  if (!is_null($fragment)) {
    $options['fragment'] = $fragment;
  }

  drupal_goto($path, $options, $http_response_code);
}

/**
 * drupal_clone() wrapper.
 *
 * @param object $object
 * @return object
 */
function _icl_wrapper_drupal_clone($object) {
  return clone($object);
}

/**
 * url() wrapper.
 * Parameters changed.
 * @todo Check parsing and URL encoding
 *
 * @param string $path
 * @param array $options
 * @return string
 */
function _icl_wrapper_url($path, $options = array()) {

  if (isset($options['query']) && !is_array($options['query'])) {
    parse_str(str_replace('&amp;', '&', $options['query']), $query_array);
    $options['query'] = $query_array;
  }

  return url($path, $options);
}

/**
 * book_toc() wrapper.
 * Parameters changed order. Follows D6 order.
 *
 * @param int $bid Book ID
 * @param array $exclude Optional mlid values
 * @param int $depth_limit
 * @return array of mlid
 */
function _icl_wrapper_book_toc($bid, $exclude = array(), $depth_limit) {

  return book_toc($bid, $depth_linit, $exclude);
}

/**
 * node_get_types() wrapper.
 * Function replaced.
 * @todo Check if D7 call works
 *
 * @param string $op
 * @param object|array|string $node
 * @param boolean $reset
 * @return mixed
 */
function _icl_wrapper_node_get_types($op = 'types', $node = NULL, $reset = FALSE) {
  $function = 'node_type_get_' . $op;
  return call_user_func($function, $node);
}

/**
 * block_box_get() wrapper.
 * Function name has changed.
 *
 * @param int $bid Block ID
 * @return array
 */
function _icl_wrapper_block_box_get($bid) {

  return block_custom_block_get($bid);
}

/**
 * module_rebuild_cache() wrapper.
 * Function name has changed.
 */
function _icl_wrapper_module_rebuild_cache() {
  system_rebuild_module_data();
}

/**
 * taxonomy_get_term() wrapper.
 * Function name has changed.
 *
 * @param int $tid Term's ID
 * @param boolean $reset
 * @return object Term object
 */
function _icl_wrapper_taxonomy_get_term($tid, $reset = FALSE) {
  return taxonomy_term_load($tid);
}

/**
 * taxonomy_save_term() wrapper.
 * Function name has changed.
 *
 * @param array $form_values
 */
function _icl_wrapper_taxonomy_save_term(&$form_values) {

  taxonomy_term_save($form_values);
}

/**
 * theme() wrapper.
 * Parameters changed.
 * @todo Check if custom compatibility works with D7
 *
 * @param string $hook
 * @param array $variables
 */
function _icl_wrapper_theme($hook, $variables = array()) {

//  Keep compatibility with our custom hooks
  if (strpos($hook, 'icl_') === 0) {
    $args = array();
    $args[0] = $hook;

    foreach ($variables as $key => $value) {
      $args[] = $value;
    }

    return call_user_func_array('theme', $args);
  } else {
    return theme($hook, $variables);
  }
}

/**
 * Undocumented
 * @todo wait to see drupal.org docs
 * @param string $hook
 * @param <type> $param
 * @return <type> 
 */
function _icl_wrapper_table_select_header_cell($hook, $param) {

  return theme($hook, $param);
}

/**
 * hook_theme() wrapper.
 * @todo Check if works for D7
 *
 * @param array $array
 * @return array
 */
function _icl_wrapper_hook_theme($array) {

  foreach ($array as $key => $value) {
    if (is_array($value) && isset($value['arguments']) && is_array($value['arguments'])) {
       if (array_key_exists('form', $value['arguments'])) {
         $array[$key]['render element'] = 'form';
       }
       else {
         $array[$key]['variables'] = $value['arguments'];
       }
       unset($array[$key]['arguments']);
    }
  }

  return $array;
}

/**
 * Implements hook_permission().
 *
 * @return array
 */
function icl_core_permission() {
  return array(
    ICL_PERM_ADMINISTER => array(
      'title' => t('Administer Translation Management module'),
      'description' => ''
    )
  );
}

/**
 * Implements hook_element_info().
 *
 * @return array
 */
function icl_core_element_info() {
  $type = array();
  $type['checkbox_columns'] = array(
    '#input' => TRUE,
    '#process' => array('icl_core_expand_checkbox_columns'),
    '#tree' => TRUE
  );
  return $type;
}

/**
 * Implements drupal_set_session
 * @todo Wait to be available in D7
 */

function _icl_wrapper_drupal_set_session($name, $value) {
  $_SESSION[$name] = $value;
  //drupal_set_session($name, $value);
}

/**
 * db_rewrite_sql wrapper
 * @todo Figure this out for D7
 * @param <type> $table_name
 * @param <type> $name
 * @param <type> $vid
 * @return <type>
 */
function _icl_wrapper_fetch_term($table_name, $name, $vid) {
  // D6 - we can use db_rewrite_sql
  //return db_fetch_object ( db_query ( db_rewrite_sql ( "SELECT t.tid, t.* FROM {" . $table_name . "} t WHERE LOWER(t.name) = LOWER('%s') AND vid = %d", 't', 'tid' ), $name, $vid ) );
  
  // D7 - http://drupal.org/update/modules/6/7#db_rewrite_sql
  // We need to use the new dynamic query and tag it "term_access"
  // ?????
}

/**
 * Undocumented
 * @param string $string
 */
function _icl_wrapper_add_locale_source($string) {
  t($string, array(), array('langcode' => 'es')); // add to the locale sources. We can use any $langcode for this except 'en'
}

/**
 * Language neutral wrapper
 * @param string $lang
 * @return <type>
 */
function _icl_wrapper_is_language_neutral($lang) {
  if (!isset($lang)) {
    return LANGUAGE_NONE;
  }
}

/**
 * check to see if the required i18n mdules are installed
 *
 * @return a list of modules not installed.
 */

function _icl_wrapper_check_i18n_installed() {
  $not_installed = array();

  // D7 should return an empty array for now.
  // When the the i18n module has been ported to D7 we should then show the warnings if required.

  return $not_installed;
}

/**
 * Returns ICL modules root menu
 *
 * @param string $menu_item Menu item appended to root
 * @return string
 */
function _icl_wrapper_get_root_menu($menu_item) {

  return 'admin/config/regional/' . $menu_item;
}

/**
 * Gets right arg
 *
 * @param int $arg Level from root e.g translation-management/edit/% - 3
 * @return mixed
 */
function _icl_wrapper_root_arg($arg) {
  $arg = 2+$arg;
  return arg($arg);
}

/**
 * Returns right admin links
 * 
 * @param string $menu_item
 * @return string
 */
function _icl_wrapper_get_drupal_menu($menu_item) {

  $aliases = array(
      // Exceptions
      'admin/build/modules' => 'admin/modules',
      'admin/build/themes' => 'admin/appearance',
      'admin/build/path' => 'admin/config/search/path',
      'admin/build/block/configure/block' => 'admin/structure/block/manage/block',
      'admin/build/block' => 'admin/structure/block',
      'admin/build/menu' => 'admin/structure/menu',
      'admin/content/types' => 'admin/structure/types',
      'admin/content/taxonomy' => 'admin/structure/taxonomy',
      'admin/content/forum' => 'admin/structure/forum',
      'admin/build/testing' => 'admin/config/development/testing',
      'admin/settings/site-maintenance' => 'admin/config/development/maintenance',
      'admin/settings/performance' => 'admin/config/development/performance',
      'admin/settings/contact' => 'admin/structure/contact/settings',
      'admin/settings/filters' => 'admin/config/content/formats',
      'admin/user/user' => 'admin/people',
      'admin/user/permissions' => 'admin/people/permissions',
      'admin/user/roles' => 'admin/people/permissions/roles',
      'admin/content/node-type' => 'admin/structure/types/manage',
      'admin/content/translation-management' => 'admin/config/regional/translation-management',
      // Generic
      'admin/settings' => 'admin/config',
      'admin/build' => 'admin/structure/',
  );

  foreach ($aliases as $d6 => $d7) {
    if (strpos($menu_item, $d6) === 0) {
      $menu_item = substr_replace($menu_item, $d7, 0, strlen($d6));
      return $menu_item;
    }
  }

  return $menu_item;
}

// DB TESTS
//$result = _icl_wrapper_db_query("INSERT INTO {role} (name, weight) VALUES ('%s', %d)", 'node_content2', 23);
//$result = _icl_wrapper_db_query("UPDATE {role} SET weight=%d WHERE name='%s'", 2, 'administrator');
//$result = _icl_wrapper_db_query("SELECT * FROM {role} WHERE name!='%s'", 'administrator');
//$result = _icl_wrapper_db_query("SELECT * FROM {role} WHERE weight = %d OR name = '%s'", 'administrator', 0);
//$result = _icl_wrapper_db_query("SELECT * FROM {role} WHERE weight = %d OR name LIKE '%%s%'", 'administrator', 0);
//$result = _icl_wrapper_db_query("SELECT n.nid, n.type, n.language, n.status, n.title FROM {node} n WHERE language='en'");


//while ($record = db_fetch_array($result)) {
//  echo $record['name'];
//}

//while ($record = db_fetch_object($result)) {
//  echo $record->type;
//}

/**
 * D7 compatibility wrapper
 *
 * Function has been removed.
 * @staticvar string $records
 * @staticvar int $count
 * @param <type> $result
 * @return <type>
 */
function db_fetch_array($result) {
  
  static $records = array();
  static $count = array();

  $key = md5($result->queryString);
  
  if (!isset($records[$key])) {
    $records[$key] = array();
    foreach ($result as $record) {
      $records[$key][] = (array)$record;
    }
    $count[$key] = 0;
  }

  if (empty($records[$key]) || !isset($records[$key][$count[$key]])) {
    unset($records[$key]);
    unset($count[$key]);
    return FALSE;
  }

  $temp = $records[$key][$count[$key]];
  $count[$key] += 1;

  return $temp;
}

/**
 * D7 compatibility wrapper
 *
 * Function has been removed.
 * @staticvar string $records
 * @staticvar int $count
 * @param <type> $result
 * @return <type>
 */
function db_fetch_object($result) {
  
  static $records = NULL;
  static $count = 0;

  if (is_null($records)) {
    $records = array();
    foreach ($result as $record) {
      $records[] = $record;
    }
  }

  if (empty($records) || !isset($records[$count])) {
    $records = NULL;
    $count = 0;
    return FALSE;
  }

  $temp = $records[$count];
  $count += 1;

  return $temp;
}

/**
 * db_query() wrapper
 * @todo Write better regex
 * @return <type>
 */
function _icl_wrapper_db_query() {

  $args = func_get_args();
  $sql = array_shift($args);
  $args_new = array();
  $index = 1;
  $sql_new = trim($sql);

  $array_found = FALSE;
  foreach ($args as $key => $value) {
    if (is_array($value)) {
      $array_found = TRUE;
    }
    $key = ':' . chr(64+$index);
    $sql_new = preg_replace('/(%d|\'%d\'|"%d"|\'%s\'|"%s"|\'%%%s%%\'|"%%%s%%"|\'%%s%\'|"%%s%"|%s)/', $key, $sql_new, 1, $found);
    $args_new[$key] = $value;
    $index += 1;
  }
  
  if (!$array_found && strpos($sql, "IN (") > 0) {
    drupal_set_message('No array sent when using "IN" in sql: <br >' . $sql, 'error');
  }

  //drupal_set_message($sql . '<br /> Converted to <br />' . $sql_new . '');
  //drupal_set_message($sql . '<br /><br />' . print_r($args, TRUE) . '<br /><br /><br /> Converted to <br />' . $sql_new . '<br /><br />' . print_r($args_new, TRUE) . '<br /><br />');

  return db_query(trim($sql_new), $args_new);
}

function _icl_wrapper_db_query_range() {
  $args = func_get_args();
  $sql = array_shift($args);
  $count = array_pop($args);
  $from = array_pop($args);
  $args_new = array();
  $index = 1;
  $sql_new = trim($sql);

  foreach ($args as $key => $value) {
    $key = ':' . chr(64+$index);
    $sql_new = preg_replace('/(%d|\'%d\'|"%d"|\'%s\'|"%s"|\'%%%s%%\'|"%%%s%%"|\'%%s%\'|"%%s%"|%s)/', $key, $sql_new, 1, $found);
    $args_new[$key] = $value;
    $index += 1;
  }
  
  return db_query_range(trim($sql_new), $from, $count, $args_new);
}
/**
 * @todo Fix this
 */
function pager_query($query, $limit = 10, $element = 0, $count_query = NULL) {
  return _icl_wrapper_db_query($query);

  $query = _icl_wrapper_db_query($query);
//  $query = $query->limit(10);
  $query->limit($limit);
  return $query->execute();


  global $pager_page_array, $pager_total, $pager_total_items;
  $page = isset($_GET['page']) ? $_GET['page'] : '';

  // Substitute in query arguments.
  $args = func_get_args();
  $args = array_slice($args, 4);
  // Alternative syntax for '...'
  if (isset($args[0]) && is_array($args[0])) {
    $args = $args[0];
  }

  // Construct a count query if none was given.
  if (!isset($count_query)) {
    $count_query = preg_replace(array('/SELECT.*?FROM /As', '/ORDER BY .*/'), array('SELECT COUNT(*) FROM ', ''), $query);
  }

  // Convert comma-separated $page to an array, used by other functions.
  $pager_page_array = explode(',', $page);

  // We calculate the total of pages as ceil(items / limit).
  $pager_total_items[$element] = _icl_wrapper_db_result(_icl_wrapper_db_query($count_query, $args));
  $pager_total[$element] = ceil($pager_total_items[$element] / $limit);
  $pager_page_array[$element] = max(0, min((int)$pager_page_array[$element], ((int)$pager_total[$element]) - 1));
  //return db_query_range($query, $args, $pager_page_array[$element] * $limit, $limit);
  return db_query_range($query, $pager_page_array[$element] * $limit, $count_query, $args, array());
}

/*
 http://drupal.org/node/224333#locale_context
*/

function _icl_wrapper_t($string, $args = array(), $langcode = NULL) {
  return t($string, $args, array('langcode' => $langcode));
}


function _icl_wrapper_user_mail_tokens($account, $language) {
  $variables = array();
  user_mail_tokens($variables, array('user' => $account), array());
  return $variables;
  // D6
  //return user_mail_tokens($account, $language);
}

function _icl_wrapper_check_node_body(&$node) {
  if (isset($node->body[$node->language])) {
    $body = $node->body[$node->language][0]['value'];
    $format = $node->body[$node->language][0]['format'];
    
    $node->body = $body;
    $node->format = $format;
  } else {
    $node->body = '';
    $node->format = '';
  }
}

function _icl_wrapper_is_line_break_filter($filter) {
  return $filter->name == 'filter_autop';
}

function icl_wrapper_node_teaser($text) {
  return text_summary($text);
}