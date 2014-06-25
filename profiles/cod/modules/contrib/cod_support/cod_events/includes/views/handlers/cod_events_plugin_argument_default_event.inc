<?php

/**
 * @file
 * Contains a default argument plugin to return the current user's cart order ID.
 */

/**
 * Default argument plugin to get the current user's cart order ID.
 */
class cod_events_plugin_argument_default_event extends views_plugin_argument_default {
  function get_argument() {

    /* Check first to see if there is an og_group_ref being passed in via url */
    if(isset($_GET['og_group_ref']) && is_numeric($_GET['og_group_ref'])) {
      return check_plain($_GET['og_group_ref']);
    }

    /* Next, check to see if the node itself defines an event */
    foreach (range(1, 3) as $i) {
      $node = menu_get_object('node', $i);
      if (!empty($node)) {
        return $node->og_group_ref[LANGUAGE_NONE][0]['target_id'];
      }
    }

    // Return an explicit 0 if not found instead of FALSE or NULL, as the
    // argument provided will be used to attempt a commerce_order_load() that
    // must accept an integer as the order ID.
    return variable_get('cod_events_default_event', 0);
  }
}
