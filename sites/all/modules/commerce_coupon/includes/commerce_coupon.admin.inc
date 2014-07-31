<?php

/*
 * Form callback: general settings form
 */
function commerce_coupon_type_settings_form($form, &$form_state, $coupon_type) {
  $name = $coupon_type['type'];
  $form['commerce_coupon_' . $name . '_default_code_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Coupon Code Length'),
    '#default_value' => variable_get('commerce_coupon_' . $name . '_default_code_size', 8),
    '#description' => t('Set the coupon code length for auto generated codes of this type.'),
  );

  return system_settings_form($form);
}

/*
 * Menu callback: display an overview of available types.
 */
function commerce_coupon_types_overview_page() {
  $header = array(
    t('Name'),
    t('Operations'),
  );

  $rows = array();

  // Loop through all defined product types.
  foreach (commerce_coupon_get_types() as $type => $coupon_type) {
    // Build the operation links for the current product type.
    $links = menu_contextual_links('commerce-coupon-type', 'admin/commerce/coupons/types', array(strtr($type, array('_' => '-'))));
    $coupon_type['type'] = $type;

    // Add the product type's row to the table's rows array.
    $rows[] = array(
      theme('commerce_coupon_type_admin_overview', array('coupon_type' => $coupon_type, )),
      theme('links', array('links' => $links, 'attributes' => array('class' => 'links inline operations'))),
    );
  }

  return theme('table', array('header' => $header, 'rows' => $rows));
}

/*
 * Menu callback: display a list of product types that the user can create.
 */
function commerce_coupon_add_page() {
  $item = menu_get_item();
  $content = system_admin_menu_block($item);

  // Bypass the admin/commerce/products/add listing if only one product type is
  // available.
  if (count($content) == 1) {
    $item = array_shift($content);
    drupal_goto($item['href']);
  }

  return theme('commerce_coupon_add_list', array('content' => $content));
}

/**
 * Displays the list of available product types for product creation.
 *
 * @ingroup themeable
 */
function theme_commerce_coupon_add_list($variables) {
  $content = $variables['content'];
  $output = '';

  if ($content) {
    $output = '<dl class="commerce-coupon-type-list">';
    foreach ($content as $item) {
      $output .= '<dt>' . l($item['title'], $item['href'], $item['localized_options']) . '</dt>';
      $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
    }
    $output .= '</dl>';
  }
  else {
    $output = '<p>' . t('No coupon types have been created yet for you to use.') . '</p>';
  }

  return $output;
}

/**
 * Builds an overview of a product type for display to an administrator.
 *
 * @param $variables
 *   An array of variables used to generate the display; by default includes the
 *     type key with a value of the product type array.
 *
 * @ingroup themeable
 */
function theme_commerce_coupon_type_admin_overview($variables) {
  $coupon_type = $variables['coupon_type'];

  $output = check_plain($coupon_type['label']);
  $output .= ' <small>' . t('(Machine name: @type)', array('@type' => $coupon_type['type'])) . '</small>';

  return $output;
}

/*
 * Form callback: coupon add/edit form
 */
function commerce_coupon_form($form, &$form_state, $coupon) {
  // Ensure this include file is loaded when the form is rebuilt from the cache.
  $form_state['build_info']['files']['form'] = drupal_get_path('module', 'commerce_coupon') . '/includes/commerce_coupon.admin.inc';
  $form_state['commerce_coupon'] = $coupon;

  commerce_coupon_attach_coupon_entity_form($form, $form_state, $coupon, TRUE);

  // Add responsive disabling of code element based on state of generate.
  $form['code']['#states'] = array(
    'disabled' => array(
      ':input[name="generate"]' => array('checked' => TRUE)
    )
  );

  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 400,
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save coupon'),
    '#weight' => 40,
  );

  return $form;
}

/*
 * Form submit callback: submit coupon entity form
 */
function commerce_coupon_form_submit(&$form, &$form_state) {
  $coupon = &$form_state['commerce_coupon'];
  $coupon->code = !empty($form_state['values']['code']) ? $form_state['values']['code'] : commerce_coupon_generate_coupon_code($coupon->type);
  $coupon->status = $form_state['values']['status'];

  // Attach fields
  field_attach_submit('commerce_coupon', $coupon, $form, $form_state);

  // Save the coupon.
  commerce_coupon_save($coupon);
  $form_state['redirect'] = 'admin/commerce/coupons';

  // Rebuild rules defaults so that discount rules get updated.
  entity_defaults_rebuild(array('rules_config'));

  // Redirect based on the button clicked.
  drupal_set_message(t('Coupon saved.'));
}

/*
 * Form callback: coupon delete confirmation form
 */
function commerce_coupon_delete_form($form, &$form_state, $coupon) {
  $form_state['commerce_coupon'] = $coupon;

  // Ensure this include file is loaded when the form is rebuilt from the cache.
  $form_state['build_info']['files']['form'] = drupal_get_path('module', 'commerce_coupon') . '/includes/commerce_coupon.admin.inc';
  $form['#submit'][] = 'commerce_coupon_delete_form_submit';
  $form = confirm_form($form, t('Are you sure you want to delete the coupon with code %code?', array('%code' => $coupon->code)), 'admin/commerce/coupons', '<p>' . t('Deleting this coupon cannot be undone.') . '</p>', t('Delete'), t('Cancel'), 'confirm');

  // Get the orders referenced by the coupon.
  $query = new EntityFieldQuery();
  $query
    ->entityCondition('entity_type', 'commerce_order')
    ->fieldCondition('commerce_coupons', 'target_id', $coupon->coupon_id);
  $result = $query->execute();

  if (!empty($result)) {
    $description = t('This coupon is referenced by an order and therefore cannot be deleted. Disable it instead.');
    $form['description']['#markup'] .= '<p>' . $description . '</p>';
    $form['actions']['submit']['#disabled'] = TRUE;
  }

  return $form;
}

/*
 * Submit callback for commerce_coupon_delete_form().
 */
function commerce_coupon_delete_form_submit($form, &$form_state) {
  $coupon = $form_state['commerce_coupon'];
  $code = $coupon->code;

  if (commerce_coupon_delete($coupon->coupon_id)) {
    // Rebuild rules defaults so that discount rules get updated.
    entity_defaults_rebuild(array('rules_config'));

    drupal_set_message(t('%code has been deleted.', array('%code' => $code)));
    watchdog('commerce_coupon', 'Deleted coupon %code.', array('%code' => $code), WATCHDOG_NOTICE);
  }
  else {
    drupal_set_message(t('%code could not be deleted.', array('%code' => $code)), 'error');
  }
  $form_state['redirect'] = 'admin/commerce/coupons';
}

/*
 * Form validate callback: validate coupon entity form
 */
function commerce_coupon_form_validate($form, &$form_state) {
  field_attach_form_validate('commerce_coupon', $form_state['commerce_coupon'], $form, $form_state);
}
