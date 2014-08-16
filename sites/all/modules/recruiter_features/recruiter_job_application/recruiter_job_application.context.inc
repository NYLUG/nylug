<?php
/**
 * @file
 * recruiter_job_application.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function recruiter_job_application_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'recruiter_job_application_resume';
  $context->description = '';
  $context->tag = 'recruiter_job_application';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'resume/*' => 'resume/*',
      ),
    ),
    'user' => array(
      'values' => array(
        'administrator' => 'administrator',
        'content admin' => 'content admin',
        'recruiter' => 'recruiter',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-baad1fc124f8f019180057ab858bae7c' => array(
          'module' => 'views',
          'delta' => 'baad1fc124f8f019180057ab858bae7c',
          'region' => 'sidebar_second',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('recruiter_job_application');
  $export['recruiter_job_application_resume'] = $context;

  return $export;
}
