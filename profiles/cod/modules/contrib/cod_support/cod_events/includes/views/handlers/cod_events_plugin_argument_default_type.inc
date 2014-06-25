<?php

/**
 * @file
 * Holds the class defining the Views plugin loading the groups the acting user
 * is member of.
 */

/**
 * The class defining the Views plugin loading the groups of the acting user.
 */
class cod_events_plugin_argument_default_type extends views_plugin_argument_default {

  function get_argument() {
    foreach (range(1, 3) as $i) {
      $node = menu_get_object('node', $i);
      if (!empty($node)) {
        return $node->type;
      }
    }

    if (arg(0) == 'node' && arg(1) == 'add') {
      $type = arg(2);
      return str_replace('-', '_', $type) ;
    }
  }
}
