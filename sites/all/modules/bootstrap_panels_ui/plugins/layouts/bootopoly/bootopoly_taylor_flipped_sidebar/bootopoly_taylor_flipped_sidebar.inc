<?php
// Plugin definition
$plugin = array(
  'title' => t('Bootopoly Taylor Flipped Sidebar'),
  'icon' => 'bootopoly-taylor-flipped-sidebar.png',
  'category' => t('Bootopoly'),
  'theme' => 'bootopoly_taylor_flipped_sidebar',
  'regions' => array(
    'header' => t('Header'),
    'quarter1' => t('Quarter 1 Column'),
    'quarter2' => t('Quarter 2 Column'),
    'half' => t('Half Column'),
    'sidebar' => t('Sidebar'),
    'footer' => t('Footer'),
  ),
);
