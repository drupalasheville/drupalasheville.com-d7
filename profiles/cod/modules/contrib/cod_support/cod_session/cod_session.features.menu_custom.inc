<?php
/**
 * @file
 * cod_session.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function cod_session_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: main-menu.
  $menus['main-menu'] = array(
    'menu_name' => 'main-menu',
    'title' => 'Main menu',
    'description' => 'The <em>Main</em> menu is used on many sites to show the major sections of the site, often in a top navigation bar.',
  );
  // Exported menu: menu-menu-quick-links.
  $menus['menu-menu-quick-links'] = array(
    'menu_name' => 'menu-menu-quick-links',
    'title' => 'Quick links - Authenticated',
    'description' => 'Utility links that display on every page of the site, such as "Your account" and "Your schedule"',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Main menu');
  t('Quick links - Authenticated');
  t('The <em>Main</em> menu is used on many sites to show the major sections of the site, often in a top navigation bar.');
  t('Utility links that display on every page of the site, such as "Your account" and "Your schedule"');


  return $menus;
}
