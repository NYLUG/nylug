<?php
/**
 * @file
 * recruiter_job_application.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function recruiter_job_application_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function recruiter_job_application_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_default_message_type().
 */
function recruiter_job_application_default_message_type() {
  $items = array();
  $items['job_application_recruiter'] = entity_import('message_type', '{
    "name" : "job_application_recruiter",
    "description" : "Job application",
    "argument_keys" : [],
    "argument" : [],
    "category" : "message_type",
    "data" : { "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" } },
    "language" : "en",
    "arguments" : null,
    "message_text" : {
      "en" : [
        {
          "value" : "\\u003Ca href=\\u0022[message:user:profile-resume:url]\\u0022\\u003E[message:user:profile-resume:field-resume-personal-info:field_resume_firstname] [message:user:profile-resume:field-resume-personal-info:field_resume_lastname]\\u003C\\/a\\u003E has sent you a new application \\u003Ca href=\\u0022[message:field-job-application:url]\\u0022\\u003E[message:field-job-application:title]\\u003C\\/a\\u003E.",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003E\\u003Ca href=\\u0022[message:user:profile-resume:url]\\u0022\\u003E[message:user:profile-resume:field-resume-personal-info:field_resume_firstname] [message:user:profile-resume:field-resume-personal-info:field_resume_lastname]\\u003C\\/a\\u003E has sent you a new application \\u003Ca href=\\u0022[message:field-job-application:url]\\u0022\\u003E[message:field-job-application:title]\\u003C\\/a\\u003E.\\u003C\\/p\\u003E\\n"
        }
      ],
      "und" : [
        {
          "value" : "\\u003Cp\\u003E[message:field_applicant_resume_link] has sent you a new application [message:field_application_link].\\u003C\\/p\\u003E",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003E[message:field_applicant_resume_link] has sent you a new application [message:field_application_link].\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  return $items;
}

/**
 * Implements hook_node_info().
 */
function recruiter_job_application_node_info() {
  $items = array(
    'job_application' => array(
      'name' => t('Job application'),
      'base' => 'node_content',
      'description' => t('Create a new job application for job offering.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implements hook_default_rules_link().
 */
function recruiter_job_application_default_rules_link() {
  $items = array();
  $items['job_application_add'] = entity_import('rules_link', '{
    "settings" : {
      "text" : "Apply",
      "link_type" : "token",
      "bundles" : {
        "job_per_file" : "job_per_file",
        "job_per_link" : "job_per_link",
        "job_per_template" : "job_per_template"
      },
      "entity_link" : 1
    },
    "name" : "job_application_add",
    "label" : "Add job application",
    "path" : "job_application_add",
    "entity_type" : "node",
    "rdf_mapping" : []
  }');
  return $items;
}
