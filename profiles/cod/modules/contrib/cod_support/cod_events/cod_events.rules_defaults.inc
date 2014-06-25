<?php
/**
 * @file
 * cod_events.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function cod_events_default_rules_configuration() {
  $items = array();
  $items['rules_default_event_flag'] = entity_import('rules_config', '{ "rules_default_event_flag" : {
      "LABEL" : "Default event flag",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "flag" ],
      "ON" : { "flag_flagged_default_event" : [] },
      "DO" : [
        { "flag_trim" : {
            "flag" : "default_event",
            "flagging_user" : [ "flagging-user" ],
            "cutoff_size" : "1",
            "trim_newest" : 0,
            "permission_check" : 0
          }
        }
      ]
    }
  }');
  return $items;
}