<?php
/**
 * @file
 * recruiter_job_application.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function recruiter_job_application_user_default_permissions() {
  $permissions = array();

  // Exported permission: access rules link job_application_add.
  $permissions['access rules link job_application_add'] = array(
    'name' => 'access rules link job_application_add',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'applicant',
      3 => 'content admin',
      4 => 'job admin',
    ),
    'module' => 'rules_link',
  );

  // Exported permission: create job_application content.
  $permissions['create job_application content'] = array(
    'name' => 'create job_application content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: delete any job_application content.
  $permissions['delete any job_application content'] = array(
    'name' => 'delete any job_application content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own job_application content.
  $permissions['delete own job_application content'] = array(
    'name' => 'delete own job_application content',
    'roles' => array(
      0 => 'administrator',
      1 => 'applicant',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any job_application content.
  $permissions['edit any job_application content'] = array(
    'name' => 'edit any job_application content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own job_application content.
  $permissions['edit own job_application content'] = array(
    'name' => 'edit own job_application content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
