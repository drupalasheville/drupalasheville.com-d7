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
