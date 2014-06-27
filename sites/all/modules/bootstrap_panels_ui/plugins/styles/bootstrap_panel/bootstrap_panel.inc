<?php

$plugin = array(
  'bootstrap_panel' => array(
    'title' => t('Bootstrap Panel'),
    'description'   => t('Example description'),
    'render pane' => 'bootstrap_panel_render_pane',
    'render region' => 'bootstrap_panel_render_region',
    'pane settings form' => 'bootstrap_panel_settings_form',
    'settings form' => 'bootstrap_panel_region_settings_form',
    'hook theme'    => array(
      'bootstrap_panel_theme_pane' => array(
        'template' => 'bootstrap-panel-pane',
         'path' => drupal_get_path('module', 'bootstrap_panels_ui') .'/plugins/styles/bootstrap_panel',
         'variables' => array(
           'content' => NULL,
           'settings' => NULL,
         ),
       ),
      'bootstrap_panel_theme_region' => array(
        'template' => 'bootstrap-panel-region',
         'path' => drupal_get_path('module', 'bootstrap_panels_ui') .'/plugins/styles/bootstrap_panel',
         'variables' => array(
           'content' => NULL,
           'settings' => NULL
         ),
       ),
    ),
  ),
);



function theme_bootstrap_panel_render_pane($vars) {
    $settings = $vars['settings'];
    $content = $vars['content'];
  return theme('bootstrap_panel_theme_pane', array('content' => $content, 'settings' => $settings));
}

function  theme_bootstrap_panel_render_region($vars) {
  $content = '';
 
  foreach ($vars['panes'] as $pane_id => $pane_output) {
 
    $content .= $pane_output;
  }
  if (empty($content)) {
    return;
  }
  $settings = $vars['settings'];
  return theme('bootstrap_panel_theme_region', array('content' => $content, 'settings' => $settings));
}
 
function bootstrap_panel_settings_form($settings) {
  $form['use_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Title'),
    '#default_value' => (isset($settings['use_title'])) ? $settings['use_title'] : 1,
  );
  $form['use_footer'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Footer'),
    '#default_value' => (isset($settings['use_footer'])) ? $settings['use_footer'] : 0,
  );
  $form['panel_body'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Panel Body'),
    '#description' => t('Wrap the panel content in a panel-body class. Remove this if you are including a table, list or menu for better styling.'),
    '#default_value' => (isset($settings['panel_body'])) ? $settings['panel_body'] : 1,
  );
  $form['footer_content'] = array(
    '#type' => 'textfield',
    '#title' => t('Footer Content'),
    '#default_value' => (isset($settings['footer_content'])) ? $settings['footer_content'] : '',
  );
  $form['context_class'] = array(
    '#type' => 'select',
    '#title' => t('Contextual Class'),
    '#options' => array(
      'panel-default' => t('-Default-'),
      'panel-primary' => t('Primary (solid blue)'),
      'panel-success' => t('Success (green)'),
      'panel-info' => t('Info (blue)'),
      'panel-warning' => t('Warning (yellow)'),
      'panel-danger' => t('Danger (red)'),
    ),
    '#default_value' => (isset($settings['context_class'])) ? $settings['context_class'] : 'panel-default',
  );
  return $form;
}

function bootstrap_panel_region_settings_form($settings) {
  $form['region_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Region Title'),
    '#default_value' => (!empty($settings['region_title'])) ? $settings['region_title'] : '',
    );
  $form['use_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Title'),
    '#default_value' => (isset($settings['use_title'])) ? $settings['use_title'] : 1,
  );
  $form['panel_body'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Panel Body'),
    '#description' => t('Wrap the panel content in a panel-body class. Remove this if you are including a table, list or menu for better styling.'),
    '#default_value' => (isset($settings['panel_body'])) ? $settings['panel_body'] : 1,
  );
  $form['context_class'] = array(
    '#type' => 'select',
    '#title' => t('Contextual Class'),
    '#options' => array(
      'panel-default' => t('-Default-'),
      'panel-primary' => t('Primary (solid blue)'),
      'panel-success' => t('Success (green)'),
      'panel-info' => t('Info (blue)'),
      'panel-warning' => t('Warning (yellow)'),
      'panel-danger' => t('Danger (red)'),
    ),
    '#default_value' => (isset($settings['context_class'])) ? $settings['context_class'] : 'panel-default',
  );
  $form['use_footer'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Footer'),
    '#default_value' => (isset($settings['use_footer'])) ? $settings['use_footer'] : 0,
  );
  $form['footer_content'] = array(
    '#type' => 'textfield',
    '#title' => t('Footer Content'),
    '#default_value' => (!empty($settings['footer_content'])) ? $settings['footer_content'] : '',
  );

  return $form;
}
