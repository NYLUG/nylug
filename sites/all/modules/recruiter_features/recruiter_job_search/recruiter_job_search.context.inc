<?php
/**
 * @file
 * recruiter_job_search.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function recruiter_job_search_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'job_search_block';
  $context->description = 'Provides the fulltext and region search block for jobs';
  $context->tag = 'recruiter_job_search';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
      ),
    ),
    'views' => array(
      'values' => array(
        'job_search' => 'job_search',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views--exp-job_search-search_page' => array(
          'module' => 'views',
          'delta' => '-exp-job_search-search_page',
          'region' => 'content',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Provides the fulltext and region search block for jobs');
  t('recruiter_job_search');
  $export['job_search_block'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'job_search_facets';
  $context->description = 'Display search api facets in job search';
  $context->tag = 'recruiter_job_search';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'job_search' => 'job_search',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'current_search-recruiter_current_search' => array(
          'module' => 'current_search',
          'delta' => 'recruiter_current_search',
          'region' => 'sidebar_second',
          'weight' => '-10',
        ),
        'facetapi-GZ56lerwiyYjFURDhaGRJXJBvjdaumAD' => array(
          'module' => 'facetapi',
          'delta' => 'GZ56lerwiyYjFURDhaGRJXJBvjdaumAD',
          'region' => 'sidebar_second',
          'weight' => '-9',
        ),
        'facetapi-PE57RfU6JaWBJC3FFCu7iidegBzDJCMx' => array(
          'module' => 'facetapi',
          'delta' => 'PE57RfU6JaWBJC3FFCu7iidegBzDJCMx',
          'region' => 'sidebar_second',
          'weight' => '-8',
        ),
        'facetapi-v3NKwi4cgrJI5BhGVl3K6y1dktYkhuo8' => array(
          'module' => 'facetapi',
          'delta' => 'v3NKwi4cgrJI5BhGVl3K6y1dktYkhuo8',
          'region' => 'sidebar_second',
          'weight' => '-7',
        ),
        'facetapi-IzmJzjOerbieKFXpXetvXQNCqhkAH8GM' => array(
          'module' => 'facetapi',
          'delta' => 'IzmJzjOerbieKFXpXetvXQNCqhkAH8GM',
          'region' => 'sidebar_second',
          'weight' => '-6',
        ),
        'facetapi-fknTj1lNko0YBn9qkfWwlhCx0XCi0niU' => array(
          'module' => 'facetapi',
          'delta' => 'fknTj1lNko0YBn9qkfWwlhCx0XCi0niU',
          'region' => 'sidebar_second',
          'weight' => '-5',
        ),
        'facetapi-plRdR3L5yjuALKnX3l09E70IsBWbyyiY' => array(
          'module' => 'facetapi',
          'delta' => 'plRdR3L5yjuALKnX3l09E70IsBWbyyiY',
          'region' => 'sidebar_second',
          'weight' => '-4',
        ),
        'facetapi-GPKIRB6X2D0QOMoO6ldpQS739bPh6Zru' => array(
          'module' => 'facetapi',
          'delta' => 'GPKIRB6X2D0QOMoO6ldpQS739bPh6Zru',
          'region' => 'sidebar_second',
          'weight' => '-3',
        ),
        'facetapi-SZ9qoxuugBBvUZ39HNC99AUUIkZtp592' => array(
          'module' => 'facetapi',
          'delta' => 'SZ9qoxuugBBvUZ39HNC99AUUIkZtp592',
          'region' => 'sidebar_second',
          'weight' => '-2',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Display search api facets in job search');
  t('recruiter_job_search');
  $export['job_search_facets'] = $context;

  return $export;
}
