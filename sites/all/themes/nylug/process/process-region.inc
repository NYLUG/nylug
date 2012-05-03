<?php /**
* Implements hook_process_region().
*/
function nylug_alpha_process_region(&$vars) {
  $theme = alpha_get_theme();
 
  if ($vars['elements']['#region'] == 'content') {
    $vars['messages'] = $theme->page['messages'];
    $vars['breadcrumb'] = $theme->page['breadcrumb'];
  }
}
