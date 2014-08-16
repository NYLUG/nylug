<?php
/**
 * @file
 * X-ray module settings UI.
 */

/**
 * Form builder; Configure which X-ray information is shown.
 *
 * This form provides feeds the menu callback for the X-ray settings page.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function xray_admin_settings() {
  $form = array();
  // X-ray output visibility settings.
  $form['display'] = array(
    '#type' => 'fieldset',
    '#title' => t('Display options'),
  );
  $form['display']['xray_show_section_summaries'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show summaries on administration sections.'),
    '#default_value' => variable_get('xray_show_section_summaries', TRUE),
    '#description' => t('If unchecked, the summaries will still be visible on the <a href="@xray-overview">X-ray reports</a> page.',
      array('@xray-overview' => url('admin/reports/xray'))
    ),
  );
  $form['display']['xray_show_callback_function'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show the page callback function on all pages.'),
    '#default_value' => variable_get('xray_show_callback_function', TRUE),
  );
  $form['display']['xray_show_formid'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show form ID in all forms.'),
    '#default_value' => variable_get('xray_show_formid', TRUE),
  );
  return system_settings_form($form);
}
