<?php
/**
 * @file
 * recruiter_job_application.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function recruiter_job_application_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'application_administration';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Application administration';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Application administration';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer nodes';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_job_application_job_ref_target_id']['id'] = 'field_job_application_job_ref_target_id';
  $handler->display->display_options['relationships']['field_job_application_job_ref_target_id']['table'] = 'field_data_field_job_application_job_ref';
  $handler->display->display_options['relationships']['field_job_application_job_ref_target_id']['field'] = 'field_job_application_job_ref_target_id';
  $handler->display->display_options['relationships']['field_job_application_job_ref_target_id']['required'] = TRUE;
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['relationship'] = 'field_job_application_job_ref_target_id';
  $handler->display->display_options['relationships']['uid']['label'] = 'recruiter';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['relationships']['uid_1']['table'] = 'node';
  $handler->display->display_options['relationships']['uid_1']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid_1']['label'] = 'Applicant';
  $handler->display->display_options['relationships']['uid_1']['required'] = TRUE;
  /* Relationship: User: Profile */
  $handler->display->display_options['relationships']['profile']['id'] = 'profile';
  $handler->display->display_options['relationships']['profile']['table'] = 'users';
  $handler->display->display_options['relationships']['profile']['field'] = 'profile';
  $handler->display->display_options['relationships']['profile']['relationship'] = 'uid_1';
  $handler->display->display_options['relationships']['profile']['label'] = 'Applicant profile';
  $handler->display->display_options['relationships']['profile']['required'] = TRUE;
  /* Relationship: Profile: Personal information (field_resume_personal_info) */
  $handler->display->display_options['relationships']['field_resume_personal_info_value']['id'] = 'field_resume_personal_info_value';
  $handler->display->display_options['relationships']['field_resume_personal_info_value']['table'] = 'field_data_field_resume_personal_info';
  $handler->display->display_options['relationships']['field_resume_personal_info_value']['field'] = 'field_resume_personal_info_value';
  $handler->display->display_options['relationships']['field_resume_personal_info_value']['relationship'] = 'profile';
  $handler->display->display_options['relationships']['field_resume_personal_info_value']['label'] = 'Applicant personal info';
  $handler->display->display_options['relationships']['field_resume_personal_info_value']['required'] = TRUE;
  $handler->display->display_options['relationships']['field_resume_personal_info_value']['delta'] = '-1';
  /* Relationship: Field collection item: Entity with the Personal information (field_resume_personal_info) */
  $handler->display->display_options['relationships']['field_resume_personal_info_profile2']['id'] = 'field_resume_personal_info_profile2';
  $handler->display->display_options['relationships']['field_resume_personal_info_profile2']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_resume_personal_info_profile2']['field'] = 'field_resume_personal_info_profile2';
  $handler->display->display_options['relationships']['field_resume_personal_info_profile2']['relationship'] = 'field_resume_personal_info_value';
  $handler->display->display_options['relationships']['field_resume_personal_info_profile2']['required'] = TRUE;
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['relationship'] = 'uid_1';
  $handler->display->display_options['fields']['uid']['label'] = '';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Date';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Application title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Field collection item: First name */
  $handler->display->display_options['fields']['field_resume_firstname']['id'] = 'field_resume_firstname';
  $handler->display->display_options['fields']['field_resume_firstname']['table'] = 'field_data_field_resume_firstname';
  $handler->display->display_options['fields']['field_resume_firstname']['field'] = 'field_resume_firstname';
  $handler->display->display_options['fields']['field_resume_firstname']['relationship'] = 'field_resume_personal_info_value';
  $handler->display->display_options['fields']['field_resume_firstname']['exclude'] = TRUE;
  /* Field: Field collection item: Last name */
  $handler->display->display_options['fields']['field_resume_lastname']['id'] = 'field_resume_lastname';
  $handler->display->display_options['fields']['field_resume_lastname']['table'] = 'field_data_field_resume_lastname';
  $handler->display->display_options['fields']['field_resume_lastname']['field'] = 'field_resume_lastname';
  $handler->display->display_options['fields']['field_resume_lastname']['relationship'] = 'field_resume_personal_info_value';
  $handler->display->display_options['fields']['field_resume_lastname']['label'] = 'Name';
  $handler->display->display_options['fields']['field_resume_lastname']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_resume_lastname']['alter']['text'] = '[field_resume_firstname] [field_resume_lastname]';
  $handler->display->display_options['fields']['field_resume_lastname']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_resume_lastname']['alter']['path'] = 'resume/[uid]';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
  $handler->display->display_options['fields']['name_1']['table'] = 'users';
  $handler->display->display_options['fields']['name_1']['field'] = 'name';
  $handler->display->display_options['fields']['name_1']['relationship'] = 'uid_1';
  $handler->display->display_options['fields']['name_1']['label'] = 'Applicant user';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'field_job_application_job_ref_target_id';
  $handler->display->display_options['fields']['title_1']['label'] = 'Job';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'Recruiter user';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'job_application' => 'job_application',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Application title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    30037204 => 0,
    244994979 => 0,
    100482362 => 0,
    115362423 => 0,
    139881272 => 0,
    29617163 => 0,
    2108160 => 0,
  );
  /* Filter criterion: Field collection item: Last name (field_resume_lastname) */
  $handler->display->display_options['filters']['field_resume_lastname_value']['id'] = 'field_resume_lastname_value';
  $handler->display->display_options['filters']['field_resume_lastname_value']['table'] = 'field_data_field_resume_lastname';
  $handler->display->display_options['filters']['field_resume_lastname_value']['field'] = 'field_resume_lastname_value';
  $handler->display->display_options['filters']['field_resume_lastname_value']['relationship'] = 'field_resume_personal_info_value';
  $handler->display->display_options['filters']['field_resume_lastname_value']['group'] = 1;
  $handler->display->display_options['filters']['field_resume_lastname_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_resume_lastname_value']['expose']['operator_id'] = 'field_resume_lastname_value_op';
  $handler->display->display_options['filters']['field_resume_lastname_value']['expose']['label'] = 'Last name';
  $handler->display->display_options['filters']['field_resume_lastname_value']['expose']['operator'] = 'field_resume_lastname_value_op';
  $handler->display->display_options['filters']['field_resume_lastname_value']['expose']['identifier'] = 'field_resume_lastname_value';
  $handler->display->display_options['filters']['field_resume_lastname_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    30037204 => 0,
    244994979 => 0,
    100482362 => 0,
    115362423 => 0,
    139881272 => 0,
    29617163 => 0,
    239386854 => 0,
  );
  /* Filter criterion: Field collection item: First name (field_resume_firstname) */
  $handler->display->display_options['filters']['field_resume_firstname_value']['id'] = 'field_resume_firstname_value';
  $handler->display->display_options['filters']['field_resume_firstname_value']['table'] = 'field_data_field_resume_firstname';
  $handler->display->display_options['filters']['field_resume_firstname_value']['field'] = 'field_resume_firstname_value';
  $handler->display->display_options['filters']['field_resume_firstname_value']['relationship'] = 'field_resume_personal_info_value';
  $handler->display->display_options['filters']['field_resume_firstname_value']['group'] = 1;
  $handler->display->display_options['filters']['field_resume_firstname_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_resume_firstname_value']['expose']['operator_id'] = 'field_resume_firstname_value_op';
  $handler->display->display_options['filters']['field_resume_firstname_value']['expose']['label'] = 'First name';
  $handler->display->display_options['filters']['field_resume_firstname_value']['expose']['operator'] = 'field_resume_firstname_value_op';
  $handler->display->display_options['filters']['field_resume_firstname_value']['expose']['identifier'] = 'field_resume_firstname_value';
  $handler->display->display_options['filters']['field_resume_firstname_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    30037204 => 0,
    244994979 => 0,
    100482362 => 0,
    115362423 => 0,
    139881272 => 0,
    29617163 => 0,
    239386854 => 0,
  );
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['relationship'] = 'uid_1';
  $handler->display->display_options['filters']['uid']['value'] = '';
  $handler->display->display_options['filters']['uid']['group'] = 1;
  $handler->display->display_options['filters']['uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'Applicant user';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
  $handler->display->display_options['filters']['uid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    30037204 => 0,
    244994979 => 0,
    100482362 => 0,
    115362423 => 0,
    139881272 => 0,
    29617163 => 0,
    2108160 => 0,
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title_1']['id'] = 'title_1';
  $handler->display->display_options['filters']['title_1']['table'] = 'node';
  $handler->display->display_options['filters']['title_1']['field'] = 'title';
  $handler->display->display_options['filters']['title_1']['relationship'] = 'field_job_application_job_ref_target_id';
  $handler->display->display_options['filters']['title_1']['operator'] = 'contains';
  $handler->display->display_options['filters']['title_1']['group'] = 1;
  $handler->display->display_options['filters']['title_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title_1']['expose']['operator_id'] = 'title_1_op';
  $handler->display->display_options['filters']['title_1']['expose']['label'] = 'Job title';
  $handler->display->display_options['filters']['title_1']['expose']['operator'] = 'title_1_op';
  $handler->display->display_options['filters']['title_1']['expose']['identifier'] = 'title_1';
  $handler->display->display_options['filters']['title_1']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    30037204 => 0,
    244994979 => 0,
    100482362 => 0,
    115362423 => 0,
    139881272 => 0,
    29617163 => 0,
    2108160 => 0,
  );
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['filters']['uid_1']['table'] = 'users';
  $handler->display->display_options['filters']['uid_1']['field'] = 'uid';
  $handler->display->display_options['filters']['uid_1']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid_1']['value'] = '';
  $handler->display->display_options['filters']['uid_1']['group'] = 1;
  $handler->display->display_options['filters']['uid_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid_1']['expose']['operator_id'] = 'uid_1_op';
  $handler->display->display_options['filters']['uid_1']['expose']['label'] = 'Recruiter user';
  $handler->display->display_options['filters']['uid_1']['expose']['operator'] = 'uid_1_op';
  $handler->display->display_options['filters']['uid_1']['expose']['identifier'] = 'uid_1';
  $handler->display->display_options['filters']['uid_1']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    30037204 => 0,
    244994979 => 0,
    100482362 => 0,
    115362423 => 0,
    139881272 => 0,
    29617163 => 0,
    2108160 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'admin/recruiter/job_applications/overview';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Application administration';
  $handler->display->display_options['menu']['description'] = 'Administer all applications.';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Job application administration';
  $handler->display->display_options['tab_options']['description'] = 'Administer all job applications.';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'management';
  $translatables['application_administration'] = array(
    t('Master'),
    t('Application administration'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Displaying @start - @end of @total'),
    t('Content entity referenced from field_job_application_job_ref'),
    t('recruiter'),
    t('Applicant'),
    t('Applicant profile'),
    t('Applicant personal info'),
    t('field_resume_personal_info'),
    t('Date'),
    t('Application title'),
    t('First name'),
    t('Name'),
    t('[field_resume_firstname] [field_resume_lastname]'),
    t('Applicant user'),
    t('Job'),
    t('Recruiter user'),
    t('Last name'),
    t('Job title'),
    t('Page'),
  );
  $export['application_administration'] = $view;

  $view = new view();
  $view->name = 'job_application_applicant';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Applicant Applications';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    115362423 => '115362423',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'You have not sent any application yet.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_job_application_job_ref_target_id']['id'] = 'field_job_application_job_ref_target_id';
  $handler->display->display_options['relationships']['field_job_application_job_ref_target_id']['table'] = 'field_data_field_job_application_job_ref';
  $handler->display->display_options['relationships']['field_job_application_job_ref_target_id']['field'] = 'field_job_application_job_ref_target_id';
  $handler->display->display_options['relationships']['field_job_application_job_ref_target_id']['label'] = 'Job';
  $handler->display->display_options['relationships']['field_job_application_job_ref_target_id']['required'] = TRUE;
  /* Field: Content: Job URL */
  $handler->display->display_options['fields']['job_url']['id'] = 'job_url';
  $handler->display->display_options['fields']['job_url']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['job_url']['field'] = 'job_url';
  $handler->display->display_options['fields']['job_url']['relationship'] = 'field_job_application_job_ref_target_id';
  $handler->display->display_options['fields']['job_url']['label'] = '';
  $handler->display->display_options['fields']['job_url']['exclude'] = TRUE;
  $handler->display->display_options['fields']['job_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['job_url']['display_as_link'] = FALSE;
  $handler->display->display_options['fields']['job_url']['link_to_entity'] = 0;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Date';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Job */
  $handler->display->display_options['fields']['field_job_application_job_ref']['id'] = 'field_job_application_job_ref';
  $handler->display->display_options['fields']['field_job_application_job_ref']['table'] = 'field_data_field_job_application_job_ref';
  $handler->display->display_options['fields']['field_job_application_job_ref']['field'] = 'field_job_application_job_ref';
  $handler->display->display_options['fields']['field_job_application_job_ref']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_job_application_job_ref']['alter']['path'] = '[job_url]';
  $handler->display->display_options['fields']['field_job_application_job_ref']['alter']['link_class'] = 'recruiter-job-link';
  $handler->display->display_options['fields']['field_job_application_job_ref']['settings'] = array(
    'link' => 0,
  );
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: User: Uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'users';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['relationship'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['uid']['validate']['type'] = 'user';
  $handler->display->display_options['arguments']['uid']['validate_options']['restrict_roles'] = TRUE;
  $handler->display->display_options['arguments']['uid']['validate_options']['roles'] = array(
    115362423 => '115362423',
  );
  $handler->display->display_options['arguments']['uid']['validate']['fail'] = 'ignore';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'job_application' => 'job_application',
  );

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['argument_input'] = array(
    'uid' => array(
      'type' => 'context',
      'context' => 'entity:user.uid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'User: Uid',
    ),
  );
  $translatables['job_application_applicant'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('You have not sent any application yet.'),
    t('author'),
    t('Job'),
    t('Date'),
    t('Title'),
    t('All'),
    t('Content pane'),
    t('View panes'),
  );
  $export['job_application_applicant'] = $view;

  $view = new view();
  $view->name = 'job_application_recruiter';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Recruiter Applications';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    30037204 => '30037204',
    100482362 => '100482362',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['label'] = 'Applicant';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
  /* Relationship: User: Profile */
  $handler->display->display_options['relationships']['profile']['id'] = 'profile';
  $handler->display->display_options['relationships']['profile']['table'] = 'users';
  $handler->display->display_options['relationships']['profile']['field'] = 'profile';
  $handler->display->display_options['relationships']['profile']['relationship'] = 'uid';
  $handler->display->display_options['relationships']['profile']['required'] = TRUE;
  $handler->display->display_options['relationships']['profile']['bundle_types'] = array(
    'resume' => 'resume',
  );
  /* Relationship: Profile: Personal information (field_resume_personal_info) */
  $handler->display->display_options['relationships']['field_resume_personal_info_value']['id'] = 'field_resume_personal_info_value';
  $handler->display->display_options['relationships']['field_resume_personal_info_value']['table'] = 'field_data_field_resume_personal_info';
  $handler->display->display_options['relationships']['field_resume_personal_info_value']['field'] = 'field_resume_personal_info_value';
  $handler->display->display_options['relationships']['field_resume_personal_info_value']['relationship'] = 'profile';
  $handler->display->display_options['relationships']['field_resume_personal_info_value']['label'] = 'Applicant personal info';
  $handler->display->display_options['relationships']['field_resume_personal_info_value']['required'] = TRUE;
  $handler->display->display_options['relationships']['field_resume_personal_info_value']['delta'] = '0';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_job_application_job_ref_target_id']['id'] = 'field_job_application_job_ref_target_id';
  $handler->display->display_options['relationships']['field_job_application_job_ref_target_id']['table'] = 'field_data_field_job_application_job_ref';
  $handler->display->display_options['relationships']['field_job_application_job_ref_target_id']['field'] = 'field_job_application_job_ref_target_id';
  $handler->display->display_options['relationships']['field_job_application_job_ref_target_id']['label'] = 'Job reference';
  $handler->display->display_options['relationships']['field_job_application_job_ref_target_id']['required'] = TRUE;
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['relationships']['uid_1']['table'] = 'node';
  $handler->display->display_options['relationships']['uid_1']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid_1']['relationship'] = 'field_job_application_job_ref_target_id';
  $handler->display->display_options['relationships']['uid_1']['label'] = 'Recruiter';
  $handler->display->display_options['relationships']['uid_1']['required'] = TRUE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Date';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Author uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'node';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  /* Field: Field collection item: First name */
  $handler->display->display_options['fields']['field_resume_firstname']['id'] = 'field_resume_firstname';
  $handler->display->display_options['fields']['field_resume_firstname']['table'] = 'field_data_field_resume_firstname';
  $handler->display->display_options['fields']['field_resume_firstname']['field'] = 'field_resume_firstname';
  $handler->display->display_options['fields']['field_resume_firstname']['relationship'] = 'field_resume_personal_info_value';
  $handler->display->display_options['fields']['field_resume_firstname']['exclude'] = TRUE;
  /* Field: Field collection item: Last name */
  $handler->display->display_options['fields']['field_resume_lastname']['id'] = 'field_resume_lastname';
  $handler->display->display_options['fields']['field_resume_lastname']['table'] = 'field_data_field_resume_lastname';
  $handler->display->display_options['fields']['field_resume_lastname']['field'] = 'field_resume_lastname';
  $handler->display->display_options['fields']['field_resume_lastname']['relationship'] = 'field_resume_personal_info_value';
  $handler->display->display_options['fields']['field_resume_lastname']['label'] = 'Submitted by';
  $handler->display->display_options['fields']['field_resume_lastname']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_resume_lastname']['alter']['text'] = '[field_resume_firstname] [field_resume_lastname]';
  $handler->display->display_options['fields']['field_resume_lastname']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_resume_lastname']['alter']['path'] = 'resume/[uid]';
  /* Field: Content: Job URL */
  $handler->display->display_options['fields']['job_url']['id'] = 'job_url';
  $handler->display->display_options['fields']['job_url']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['job_url']['field'] = 'job_url';
  $handler->display->display_options['fields']['job_url']['relationship'] = 'field_job_application_job_ref_target_id';
  $handler->display->display_options['fields']['job_url']['label'] = '';
  $handler->display->display_options['fields']['job_url']['exclude'] = TRUE;
  $handler->display->display_options['fields']['job_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['job_url']['display_as_link'] = FALSE;
  $handler->display->display_options['fields']['job_url']['link_to_entity'] = 0;
  /* Field: Content: Job */
  $handler->display->display_options['fields']['field_job_application_job_ref']['id'] = 'field_job_application_job_ref';
  $handler->display->display_options['fields']['field_job_application_job_ref']['table'] = 'field_data_field_job_application_job_ref';
  $handler->display->display_options['fields']['field_job_application_job_ref']['field'] = 'field_job_application_job_ref';
  $handler->display->display_options['fields']['field_job_application_job_ref']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_job_application_job_ref']['alter']['path'] = '[job_url]';
  $handler->display->display_options['fields']['field_job_application_job_ref']['alter']['link_class'] = 'recruiter-job-link';
  $handler->display->display_options['fields']['field_job_application_job_ref']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_job_application_job_ref']['settings'] = array(
    'link' => 0,
  );
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Author uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'node';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['relationship'] = 'field_job_application_job_ref_target_id';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['uid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['uid']['validate']['type'] = 'user';
  $handler->display->display_options['arguments']['uid']['validate_options']['restrict_roles'] = TRUE;
  $handler->display->display_options['arguments']['uid']['validate_options']['roles'] = array(
    100482362 => '100482362',
  );
  $handler->display->display_options['arguments']['uid']['validate']['fail'] = 'access denied';
  /* Contextual filter: Content: Author uid */
  $handler->display->display_options['arguments']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['arguments']['uid_1']['table'] = 'node';
  $handler->display->display_options['arguments']['uid_1']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid_1']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid_1']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['uid_1']['default_argument_options']['index'] = '1';
  $handler->display->display_options['arguments']['uid_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid_1']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'job_application' => 'job_application',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_job_application_job_ref_target_id']['id'] = 'field_job_application_job_ref_target_id';
  $handler->display->display_options['relationships']['field_job_application_job_ref_target_id']['table'] = 'field_data_field_job_application_job_ref';
  $handler->display->display_options['relationships']['field_job_application_job_ref_target_id']['field'] = 'field_job_application_job_ref_target_id';
  $handler->display->display_options['relationships']['field_job_application_job_ref_target_id']['label'] = 'Job reference';
  $handler->display->display_options['relationships']['field_job_application_job_ref_target_id']['required'] = TRUE;
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['relationships']['uid_1']['table'] = 'node';
  $handler->display->display_options['relationships']['uid_1']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid_1']['relationship'] = 'field_job_application_job_ref_target_id';
  $handler->display->display_options['relationships']['uid_1']['label'] = 'Recruiter';
  $handler->display->display_options['relationships']['uid_1']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Date';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Author uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'node';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'You have not received any application yet.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Author uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'node';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['relationship'] = 'field_job_application_job_ref_target_id';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['uid']['validate']['type'] = 'user';
  $handler->display->display_options['arguments']['uid']['validate_options']['roles'] = array(
    100482362 => '100482362',
  );
  $handler->display->display_options['arguments']['uid']['validate']['fail'] = 'access denied';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'field_job_application_job_ref_target_id';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['argument_input'] = array(
    'uid' => array(
      'type' => 'context',
      'context' => 'entity:user.uid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Content: Author uid',
    ),
    'nid' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 1,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Content: Nid',
    ),
  );
  $translatables['job_application_recruiter'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Applicant'),
    t('Profile'),
    t('Applicant personal info'),
    t('Job reference'),
    t('Recruiter'),
    t('Date'),
    t('Title'),
    t('Author uid'),
    t('First name'),
    t('Submitted by'),
    t('[field_resume_firstname] [field_resume_lastname]'),
    t('Job'),
    t('All'),
    t('Block'),
    t('Content pane'),
    t('You have not received any application yet.'),
    t('View panes'),
  );
  $export['job_application_recruiter'] = $view;

  return $export;
}
