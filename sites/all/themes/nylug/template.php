<?php

/**
 * @file
 * Template overrides as well as (pre-)process and alter hooks for the
 * nylug theme.
 */

function nylug_breadcrumb($variables) {
   if (count($variables['breadcrumb']) > 0) {
     $lastitem = sizeof($variables['breadcrumb']);
     $title = drupal_get_title();
     $crumbs = '<ul class="breadcrumb">';
     $a=1;
     $sep = ' &raquo; ';
     foreach($variables['breadcrumb'] as $value) {
         if ($a!=$lastitem){
          $crumbs .= '<li class="breadcrumb-'.$a.'">'. $value . ' '. $sep .' ' . '</li>';
          $a++;
         }
         else {
             $crumbs .= '<li class="breadcrumb-last">'.$value.'</li>';
         }
     }
     $crumbs .= '</ul>';
   return $crumbs;
   }
   else {
     return t('Home', array('@url' => url('node')));
   }
 }
