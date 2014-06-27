<?php

$plugin = array(
  'bootstrap_affix' => array(
    'title' => t('Bootstrap Affix'),
    'description'   => t('Affix that shit'),
    'render pane' => 'bootstrap_affix_render_pane',
    'render region' => 'bootstrap_affix_render_region',
    'pane settings form' => 'bootstrap_affix_settings_form',
    'settings form' => 'bootstrap_affix_region_settings_form',
    'hook theme'    => array(
      'bootstrap_affix_theme_pane' => array(
        'template' => 'bootstrap-affix-pane',
         'path' => drupal_get_path('module', 'bootstrap_panels_ui') .'/panels/styles/bootstrap_affix',
         'variables' => array(
           'content' => NULL,
           'settings' => NULL,
         ),
       ),
      'bootstrap_affix_theme_region' => array(
        'template' => 'bootstrap-affix-region',
         'path' => drupal_get_path('module', 'bootstrap_panels_ui') .'/panels/styles/bootstrap_affix',
         'variables' => array(
           'content' => NULL,
           'settings' => NULL
         ),
       ),
    ),
  ),
);

function theme_bootstrap_affix_render_pane($vars) {
    $settings = $vars['settings'];
    $content = $vars['content'];
  return theme('bootstrap_affix_theme_pane', array('content' => $content, 'settings' => $settings));
}

function  theme_bootstrap_affix_render_region($vars) {
  $content = '';
 
  foreach ($vars['panes'] as $pane_id => $pane_output) {
 
    $content .= $pane_output;
  }
  if (empty($content)) {
    return;
  }
  $settings = $vars['settings'];
  $settings['region_id'] = $vars['region_id'];

  $jsdata = array(
    'file' => drupal_get_path('theme', 'speaksdrupal') .'/panels/styles/bootstrap_affix/bootstrap_affix.js',
    'setting' => $settings,
    );

  drupal_add_js($data = $jsdata);
  return theme('bootstrap_affix_theme_region', array('content' => $content, 'settings' => $settings));
}

function bootstrap_affix_region_settings_form($settings){
    $form['affix_class'] = array(
      '#type' => 'select',
      '#title' => t('Affix Class'),
      '#description' => t('The class applied to the element.'),
      '#options' => array(
        'affix' => 'affix',
        'affix-top' => 'affix-top',
        'affix-bottom' => 'affix-bottom',
        ),
      '#default_value' => (isset($settings['affix_class'])) ? $settings['affix_class'] : 'affix',
      );
    $form['offset_top'] = array(
      '#type' => 'textfield',
      '#title' => t('Offset Top (px)'),
      '#default_value' => (!empty($settings['offset_top'])) ? $settings['offset_top'] : '',
    );
     $form['offset_bottom'] = array(
      '#type' => 'textfield',
      '#title' => t('Offset Bottom (px)'),
      '#default_value' => (!empty($settings['offset_bottom'])) ? $settings['offset_bottom'] : '',
    );
  
  
    return $form;
}
