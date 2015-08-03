<?php

/**
* @file
* Admin page
*/

/**
 * Create page with information about setting of Google reCAPTCHA
 * Is keys were input?
 * List of all protected forms
 * Statistics data - if was enabled (default)
 * Where to get additional information about Google reCAPTCHA
 *
 */
function google_recaptcha_summary() {
    $google_recaptcha = variable_get('google_recaptcha');
    $output = theme_render_template(drupal_get_path('module', 'google_recaptcha') . '/google-recaptcha-summary.tpl.php', $google_recaptcha);
    return $output;
}

/**
 * Create form for managing Google reCAPTCHA keys
 *
 * @param $form
 * @param $form_state
 */
function google_recaptcha_keys($form, &$form_state) {
    $google_recaptcha = variable_get('google_recaptcha');

    $form['#prefix'] = t('
Both keys You can create on <a href="@google-recaptcha-official-site" target="_blank">Google reCAPTCHA site.</a><br/>
Be careful if You have several sites - check that this pair of keys exactly for THIS site.', array('@google-recaptcha-official-site' => 'https://www.google.com/recaptcha'));

    $form['public_key'] = array(
        '#title' => t('Google reCAPTCHA public key'),
        '#type' => 'textfield',
        '#default_value' => empty($google_recaptcha['public_key']) ? '' : $google_recaptcha['public_key'], // may be without additional check?
        '#size' => 40,
        '#maxlength' => 40,
        '#required' => TRUE,
    );
    $form['secret_key'] = array(
        '#title' => t('Google reCAPTCHA secret key'),
        '#type' => 'textfield',
        '#default_value' => empty($google_recaptcha['secret_key']) ? '' : $google_recaptcha['secret_key'],
        '#size' => 40,
        '#maxlength' => 40,
        '#required' => TRUE,
    );
    $form['collect_statistics'] = array(
        '#title' => t('Collect statistics'),
        '#type' => 'checkbox',
        '#default_value' => $google_recaptcha['statistics']['status'],
        '#description' => t('
Count requests to Google reCAPTCHA servers and their responses. Useful for mainly understanding about the effectiveness this protection system<br/>
More detailed statistics data You may found in Your <a href="@google-recaptcha-control-panel" target="_blank">control panel</a>.', array('@google-recaptcha-control-panel' => 'https://www.google.com/recaptcha/admin#list')),
    );

    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save')
    );

    return $form;
}

/**
 * Validate handler
 *
 * @param $form
 * @param $form_state
 */
function google_recaptcha_keys_validate($form, &$form_state) {
    if (strlen($form_state['values']['public_key']) < 40) {
        form_set_error('public_key', t('Length of public key must be 40 symbols long.'));
    }
    if (strlen($form_state['values']['secret_key']) < 40) {
        form_set_error('secret_key', t('Length of secret key must be 40 symbols long.'));
    }
}

/**
 * Submit handler
 *
 * @param $form
 * @param $form_state
 */
function google_recaptcha_keys_submit($form, &$form_state) {
    $google_recaptcha = variable_get('google_recaptcha');
    $google_recaptcha['public_key'] = $form_state['values']['public_key'];
    $google_recaptcha['secret_key'] = $form_state['values']['secret_key'];
    $google_recaptcha['statistics']['status'] = $form_state['values']['collect_statistics'];

    // reset statistics data if was disabled
    if ($form_state['values']['collect_statistics'] == 0) {
        $google_recaptcha['statistics']['requests'] = 0;
        $google_recaptcha['statistics']['success'] = 0;
        $google_recaptcha['statistics']['fails'] = 0;
    }

    variable_set('google_recaptcha', $google_recaptcha);
    drupal_set_message(t('Google reCAPTCHA keys and settings were saved'));
    $form_state['redirect'] = 'admin/config/spam_protection/google_recaptcha';
}

/**
 * Create form for managing list of protected forms.
 *
 * @param $form
 * @param $form_state
 */
function google_recaptcha_forms($form, &$form_state) {
    $google_recaptcha = variable_get('google_recaptcha');

    // collect all form names
    $available_forms = array();

    if (module_exists('comment')) {
        // by default
        $available_forms['comment_'] = t('Comment');
    }
    if (module_exists('contact')) {
        // by default
        $available_forms['contact_site_form'] = t('Contact');
    }
    if (module_exists('poll')) {
        // by default
        $available_forms['poll_'] = t('Poll');
    }
    if (module_exists('search')) {
        $available_forms['search_'] = t('Search');
    }
    if (module_exists('webform')) {
        $q = db_select('node', 'n');
        $webforms = $q
            ->condition('n.type', 'webform')
            ->condition('n.status', 1)
            ->fields('n', array('nid', 'title'))
            ->execute()
            ->fetchAll();

        if (!empty($webforms)) {
            foreach ($webforms as $webform) {
                $available_forms['webform_client_form_' . $webform->nid] = $webform->title;
            }
        }
    }

    // create form
    $form['#prefix'] = '<p>' . t('Check forms which You want to protect with Google reCAPTCHA') . '</p>';
    $form['#prefix'] .= '<div class="description">' . t('For security usability reasons - forms for user registration, recovery pass and login always protected!') . '</div>';

    foreach ($available_forms as $available_form_name => $available_form_title) {
        $form['available_forms'][$available_form_name] = array(
            '#title' => $available_form_title,
            '#type' => 'checkbox',
            '#default_value' => in_array($available_form_name, $google_recaptcha['protected_forms']) ? 1 : 0,
        );
    }

    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save')
    );

    $form['#tree'] = true;

    return $form;
}

/**
 * Validate handler
 *
 * @param $form
 * @param $form_state
 */
function google_recaptcha_forms_validate($form, &$form_state) {}

/**
 * Submit handler
 *
 * @param $form
 * @param $form_state
 */
function google_recaptcha_forms_submit($form, &$form_state) {
    $google_recaptcha = variable_get('google_recaptcha');

    // reset list with proetected forms
    // useful if some module which provided forms was disabled
    $google_recaptcha['protected_forms'] = array();

    foreach ($form_state['values']['available_forms'] as $available_form_name => $available_form_status) {
        if ($available_form_status == 1) {
             $google_recaptcha['protected_forms'][] = $available_form_name;
        }
    }

    drupal_set_message('Settings were saved.');

    variable_set('google_recaptcha', $google_recaptcha);
}
