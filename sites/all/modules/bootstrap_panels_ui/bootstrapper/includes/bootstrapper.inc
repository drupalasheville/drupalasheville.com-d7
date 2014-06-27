<?php

$plugin = array(
  'schema' => 'bootstrapper',
  'access' => 'administer bootstrapper',

  'menu' => array(
    'menu item' => 'bootstrapper',
    'menu title' => 'bootstrapper',
    'menu description' => 'Add, edit or delete bootstrapper styles.',
  ),

  'title singular' => t('style'),
  'title singular proper' => t('Style'),
  'title plural' => t('styles'),
  'title plural proper' => t('Styles'),

  'handler' => array(
    'class' => 'bootstrapper_ui',
  ),

  'strings' => array(
    'message' => array(
      'missing base type' => t('There are currently no style types available to add. You should enable a module that utilizes them, such as Panels.'),
    ),
  ),

  'use wizard' => TRUE,
  'form info' => array(
    'add order' => array(
      'admin' => t('Administrative settings'),
      'type' => t('Select style type'),
      'choose' => t('Select base style'),
    ),
    'order' => array(
      'admin' => t('Administrative settings'),
    ),
    'forms' => array(
      'choose' => array(
        'form id' => 'ctools_bootstrapper_edit_style_form_choose',
      ),
    ),
  ),
);

