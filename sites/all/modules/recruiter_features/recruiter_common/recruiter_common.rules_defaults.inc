<?php
/**
 * @file
 * recruiter_common.rules_defaults.inc
 */

/**
 * Implementation of hook_default_rules_configuration().
 */
function recruiter_common_default_rules_configuration() {
  $items = array();
  $items['rules_unset_test'] = entity_import('rules_config', '{ "rules_unset_test" : {
      "LABEL" : "unset test",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "REQUIRES" : [ "rules" ],
      "ON" : [ "node_update" ],
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "article" : "article" } } } }
      ],
      "DO" : [
        { "data_set" : { "data" : [ "node:field-user" ], "value" : [ "site:current-user" ] } },
        { "data_set" : { "data" : [ "node:field-erer" ], "value" : "3" } }
      ]
    }
  }');
  return $items;
}
