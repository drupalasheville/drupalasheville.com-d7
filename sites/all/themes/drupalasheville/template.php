<?php

/**
 * Implements hook_preprocess_page
 */
function drupalasheville_preprocess_page(&$vars) {  
  drupal_add_js(drupal_get_path('theme', 'drupalasheville') . '/js/custom-2014.js',array(
    'scope' => 'footer',
    'weight' => 99,
  ));    
}

function drupalasheville_preprocess_menu_local_task(&$variables) {
  $link = &$variables['element']['#link'];
  // check for $_GET['destination'] because drupal_get_destination() always contains at least the current page
  if ($link['tab_root'] === 'user' && !empty($_GET['destination'])) {
    $link['localized_options']['query'] = drupal_get_destination();
  }
}