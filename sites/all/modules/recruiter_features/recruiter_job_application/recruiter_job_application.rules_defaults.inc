<?php
/**
 * @file
 * recruiter_job_application.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function recruiter_job_application_default_rules_configuration() {
  $items = array();
  $items['rules_job_application_rules'] = entity_import('rules_config', '{ "rules_job_application_rules" : {
      "LABEL" : "Job Application Rules",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "job_application" ],
      "REQUIRES" : [ "rules", "content_access_rules" ],
      "ON" : [ "node_insert" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "job_application" : "job_application" } }
          }
        },
        { "NOT data_is_empty" : { "data" : [ "node:field-job-application-job-ref" ] } },
        { "node_is_of_type" : {
            "node" : [ "node:field-job-application-job-ref" ],
            "type" : { "value" : {
                "job_per_file" : "job_per_file",
                "job_per_link" : "job_per_link",
                "job_per_template" : "job_per_template"
              }
            }
          }
        }
      ],
      "DO" : [
        { "mail" : {
            "to" : "[node:field-job-application-job-ref:author:mail], [node:field-job-application-job-ref:field-job-email]",
            "subject" : "New application for your job offer [node:field-job-application-job-ref:title]",
            "message" : "You have received a new application for the job offering [node:field-job-application-job-ref:title] at [node:field-job-application-job-ref:url]. You can read the application under: [node:url]. \\r\\n\\r\\nIn order to see the application you need to login with your username [node:field-job-application-job-ref:author:name].",
            "language" : [ "" ]
          }
        },
        { "content_access_action_user_grant" : {
            "node" : [ "node" ],
            "content_access_user_view" : [ "node:field-job-application-job-ref:author" ],
            "content_access_user_update" : [ "" ],
            "content_access_user_delete" : [ "" ]
          }
        },
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "job_application_recruiter",
              "param_user" : [ "node:author" ]
            },
            "PROVIDE" : { "entity_created" : { "new_message" : "New message" } }
          }
        },
        { "data_set" : {
            "data" : [ "new-message:field-message-audience:0" ],
            "value" : [ "node:field-job-application-job-ref:author" ]
          }
        },
        { "data_set" : { "data" : [ "new-message:field-job-application" ], "value" : [ "node" ] } }
      ]
    }
  }');
  $items['rules_link_condition_job_application_add'] = entity_import('rules_config', '{ "rules_link_condition_job_application_add" : {
      "LABEL" : "Rules link: Add job application condition",
      "PLUGIN" : "and",
      "REQUIRES" : [ "recruiter_job_application" ],
      "USES VARIABLES" : { "node" : { "label" : "node", "type" : "node" } },
      "AND" : [
        { "NOT recruiter_job_application_exists_job" : { "applicant" : [ "site:current-user" ], "job" : [ "node" ] } }
      ]
    }
  }');
  $items['rules_link_set_job_application_add'] = entity_import('rules_config', '{ "rules_link_set_job_application_add" : {
      "LABEL" : "Rules link: Add job application rules set",
      "PLUGIN" : "rule set",
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : { "node" : { "type" : "node", "label" : "node" } },
      "RULES" : [
        { "RULE" : {
            "DO" : [ { "redirect" : { "url" : "node\\/[node:nid]\\/apply" } } ],
            "LABEL" : "Redirect to job application"
          }
        }
      ]
    }
  }');
  return $items;
}
