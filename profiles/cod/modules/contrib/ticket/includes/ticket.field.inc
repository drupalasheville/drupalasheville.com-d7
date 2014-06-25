<?php
/**
 * @file
 * Ticket field include file.
 */

// Define some things.
define('TICKET_PREFIX', 'ticket_');
define('TICKET_QUANTITY_PREFIX', TICKET_PREFIX . 'quantity_');

/**
 * Implements hook_field_info().
 */
function ticket_field_info() {
  return array(
    'ticket_type' => array(
      'label' => t('Ticket Type'),
      'description' => t('This field stores information on the ticket types available for the entity to which it is attached.'),
      'default_widget' => 'ticket_type',
      'default_formatter' => 'ticket_type',
    ),
  );
}

/**
 * Implements hook_field_validate().
 */
function ticket_field_validate($entity_type, $entity, $field, $instance, $langcode, $items, &$errors) {
}

/**
 * Implements hook_field_load().
 */
function ticket_field_load($entity_type, $entities, $field, $instances, $langcode, &$items) {

}

/**
 * Implements hook_field_is_empty().
 */
function ticket_field_is_empty($item, $field) {
  // Existing item with an id.
  if (!empty($item['ttid'])) {
    return FALSE;
  }
  elseif (isset($item['entity'])) {
    return ticket_type_is_empty($item['entity']);
  }
  return TRUE;
}

/**
 * Determines whether a ticket type entity is empty based on the fields.
 */
function ticket_type_is_empty(TicketTypeEntity $item) {
  // Get a list of the fields on a ticket type and check for non-empty fields.
  $instances = field_info_instances('ticket_type', 'ticket_type');
  $is_empty = TRUE;

  foreach ($instances as $instance) {
    // It's impossible for date selects to be empty, so don't check it.
    if ($instance['widget']['type'] == 'date_select') {
      continue;
    }

    $field_name = $instance['field_name'];
    $field_info = field_info_field($field_name);

    // Determine the list of languages to iterate on.
    $languages = field_available_languages('ticket_type', $field_info);

    foreach ($languages as $langcode) {
      if (!empty($item->{$field_name}[$langcode])) {

        // If at least one collection-field is not empty; the
        // ticket type is not empty.
        foreach ($item->{$field_name}[$langcode] as $field_item) {
          // If a field has a default and it's not changed, ignore it.
          if (isset($instance['default_value'][0]) && $instance['default_value'][0] == $field_item) {
            continue;
          }

          if (!module_invoke($field_info['module'], 'field_is_empty', $field_item, $field_info)) {
            $is_empty = FALSE;
          }
        }
      }
    }
  }

  // Allow other modules a chance to alter the value before returning.
  drupal_alter('ticket_type_is_empty', $is_empty, $item);
  return $is_empty;
}

/**
 * Implements hook_field_formatter_info().
 */
function ticket_field_formatter_info() {
  return array(
    'ticket_type' => array(
      'label' => t('Ticket Type'),
      'field types' => array('ticket_type'),
      'settings' => array(
        'submit_text' => t('Register'),
        'show_unavailable' => 0,
      ),
    ),
  );
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function ticket_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $element['submit_text'] = array(
    '#title' => t('Submit text'),
    '#description' => t('Provide the text for the submit button users will click to register.'),
    '#type' => 'textfield',
    '#default_value' => $settings['submit_text'],
  );

  $element['show_unavailable'] = array(
    '#title' => t('Show unavailable ticket types'),
    '#description' => t('Select this option to show ticket types that are unavailable (e.g. outside date range or quantity exhausted). Disabled ticket types will not be displayed.'),
    '#type' => 'checkbox',
    '#default_value' => $settings['show_unavailable'],
    '#attributes' => array(
      'class' => array('ticket-field-show_unavailable'),
    ),
  );

  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function ticket_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $summary[] = t('Submit text: @submit', array('@submit' => check_plain($settings['submit_text'])));

  $unavailable = ($settings['show_unavailable']) ? t('Yes') : t('No');
  $summary[] = t('Show unavailable ticket types: %unavailable', array('%unavailable' => $unavailable));

  return implode('<br/>', $summary);
}

/**
 * Implements hook_field_formatter_view().
 */
function ticket_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  $settings = $display['settings'];

  if ($display['type'] == 'ticket_type') {
    $ticket_types = ticket_get_entity_ticket_types($entity_type, $entity);

    $form_ticket_types = array();
    foreach ($items as $delta => $item) {
      // Ensure the ticket type field matches in case there are multiple
      // ticket type fields.
      $ticket_type = $ticket_types[$item['value']];
      if ($ticket_type->field_name == $field['field_name']) {

        // If we show unavailable or the ticket type is available.
        if ((isset($settings['show_unavailable']) && $settings['show_unavailable']) || ticket_type_available($ticket_type)) {
          $form_ticket_types[$ticket_type->ttid] = $ticket_type;
        }

      }
    }

    if (count($form_ticket_types)) {
      $vars = array(
        'entity_type' => $entity_type,
        'entity' => $entity,
        'ticket_types' => $form_ticket_types,
        'submit_text' => $settings['submit_text'],
        'langcode' => $langcode,
      );
      $element = drupal_get_form('ticket_field_formatter_view_form', $vars);
    }
  }

  return $element;
}

/**
 * Ticket formatter view form callback.
 */
function ticket_field_formatter_view_form($form, &$form_state, $vars = NULL) {
  // Store our vars, so we can use them later.
  $form_state['storage']['vars'] = $vars;

  // Generate the displays.
  foreach ($vars['ticket_types'] as $ticket_type) {
    $wrapper = entity_metadata_wrapper('ticket_type', $ticket_type);

    // Output the ticket type entity.
    $form[TICKET_PREFIX . $ticket_type->ttid] = entity_view('ticket_type', array($ticket_type), 'default', $vars['langcode']);

    $form[TICKET_QUANTITY_PREFIX . $ticket_type->ttid] = array(
      '#title' => t('Quantity'),
      '#description' => t('Enter the number of tickets you would like to register for.'),
      '#type' => 'textfield',
    );

    if (ticket_type_available($ticket_type)) {
      $form[TICKET_QUANTITY_PREFIX . $ticket_type->ttid] += array(
        '#element_validate' => array(
          'element_validate_integer',
          'ticket_field_formatter_view_form_quantity_validate',
        ),
        // Custom properties used for validation.
        '#default_value' => count($vars['ticket_types']) > 1 ? NULL : (int) $wrapper->ticket_type_order_min->value(),
        '#ticket_type' => $ticket_type->ttid,
        '#ticket_registration_quantity_min' => (int) $wrapper->ticket_type_order_min->value(),
        '#ticket_registration_quantity_max' => (int) $wrapper->ticket_type_order_max->value(),
      );
    }
    else {
      $form[TICKET_QUANTITY_PREFIX . $ticket_type->ttid]['#disabled'] = TRUE;
    }
  }

  // General submit button.
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => check_plain($vars['submit_text']),
  );

  return $form;
}

/**
 * First page form submit.
 */
function ticket_field_formatter_view_form_submit($form, &$form_state) {
  // Collate the ticket types and quantities into an easy array.
  $build_forms = array();
  foreach ($form_state['values'] as $form_field => $value) {
    if (strpos($form_field, TICKET_QUANTITY_PREFIX) === 0 && !empty($value)) {
      $ttid = str_replace(TICKET_QUANTITY_PREFIX, '', $form_field);
      $build_forms[$ttid] = $value;
    }
  }

  if (!empty($build_forms)) {
    $_SESSION['ticket']['build_forms'] = $build_forms;
    $_SESSION['ticket']['submit_text'] = $form_state['storage']['vars']['submit_text'];
    $_SESSION['ticket']['return_url'] = current_path();
    $form_state['redirect'] = 'ticket/register';
  }
}

/**
 * Registration form quantity validation.
 */
function ticket_field_formatter_view_form_quantity_validate($element, &$form_state, $form) {
  // If the number is zero, change it to be empty.
  if ($element['#value'] == 0) {
    form_set_value($element, '', $form_state);
  }
  else {
    $max = FALSE;
    if (!empty($element['#ticket_registration_quantity_max']) && $element['#ticket_registration_quantity_max'] > $element['#ticket_registration_quantity_min']) {
      $max = $element['#value'] > $element['#ticket_registration_quantity_max'];
    }

    if ($element['#value'] < $element['#ticket_registration_quantity_min'] || $max) {
      form_error($element, t('The %title must be between @min and @max', array(
        '%title' => $element['#title'],
        '@min' => $element['#ticket_registration_quantity_min'],
        '@max' => $element['#ticket_registration_quantity_max'],
      )));
    }
  }
}

/**
 * Implements hook_field_widget_info().
 */
function ticket_field_widget_info() {
  return array(
    'ticket_type' => array(
      'label' => t('Ticket Type'),
      'field types' => array('ticket_type'),
      'behaviors' => array(
        'multiple values' => FIELD_BEHAVIOR_DEFAULT,
        'default value' => FIELD_BEHAVIOR_NONE,
      ),
    ),
  );
}

/**
 * Implements hook_field_widget_form().
 */
function ticket_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  if ($instance['widget']['type'] == 'ticket_type') {

    $field_parents = $element['#field_parents'];
    $field_name = $element['#field_name'];
    $language = $element['#language'];

    // Nest the ticket type entity form in a dedicated parent space,
    // by appending [field_name, langcode, delta] to the current parent space.
    // That way the form values of the ticket type are separated.
    $parents = array_merge($field_parents, array($field_name, $language, $delta));

    $element += array(
      '#element_validate' => array('ticket_type_field_validate'),
      '#parents' => $parents,
    );

    // If there's only one value, make this a fieldset so it's organized.
    if ($field['cardinality'] == 1) {
      $element['#type'] = 'fieldset';
    }

    $field_state = field_form_get_state($field_parents, $field_name, $language, $form_state);

    // Try to get the ticket type from the field state.
    if (isset($field_state['entity'][$delta])) {
      $ticket_type = $field_state['entity'][$delta];
    }
    else {
      // Try to get the ticket type from the field items.
      if (isset($items[$delta])) {
        $ticket_type = entity_load('ticket_type', $items[$delta]);
        if (!empty($ticket_type)) {
          $ticket_type = array_shift($ticket_type);
        }
      }

      // No ticket type, stub out an empty ticket type to generate the form.
      if (empty($ticket_type)) {
        list($entity_id, $revision_id, $bundle) = entity_extract_ids($element['#entity_type'], $element['#entity']);
        $values = array(
          'entity_type' => $element['#entity_type'],
          'entity_id' => $entity_id,
          // Set the default status to enabled.
          'status' => 1,
        );
        $ticket_type = entity_create('ticket_type', $values);
      }

      // Put our entity in the form state, so FAPI callbacks can access it.
      $field_state['entity'][$delta] = $ticket_type;
    }

    // Attach the entity form.
    field_form_set_state($field_parents, $field_name, $language, $form_state, $field_state);
    field_attach_form('ticket_type', $ticket_type, $element, $form_state, $language);

    // Add a status field.
    $element['status'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enabled'),
      '#default_value' => $ticket_type->status,
      '#weight' => 999,
    );

    // If not required, then adjust validation.
    if (empty($element['#required'])) {
      $element['#after_build'][] = 'ticket_type_field_delay_required_validation';
    }

    if ($field['cardinality'] == FIELD_CARDINALITY_UNLIMITED) {
      // Add a remove button.
      $element['remove_button'] = array(
        '#delta' => $delta,
        '#name' => implode('_', $parents) . '_remove_button',
        '#type' => 'submit',
        '#value' => t('Remove'),
        '#validate' => array(),
        '#submit' => array('ticket_type_remove_submit'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'path' => 'ticket_type/ajax',
          'effect' => 'fade',
        ),
        '#weight' => 1000,
      );

      // Add js to warn users that removing ticket types deletes
      // corresponding registrations.
      // TODO: Finish this up.
      /*
      static $add_once = TRUE;
      if ($add_once) {
        $element['#attached']['js'] = array(
          drupal_get_path('module', 'ticket') . '/js/ticket_type_remove.js' => array(
            'type' => 'file',
          ),
        );
        $add_once = FALSE;
      }
      */
    }

    return $element;
  }
}

/**
 * FAPI #after_build of a ticket type to delay the validation of #required.
 */
function ticket_type_field_delay_required_validation(&$element, &$form_state) {
  // If the process_input flag is set, the form and its input is going to be
  // validated. Prevent #required (sub)fields from throwing errors while
  // their non-#required field collection item is empty.
  if ($form_state['process_input']) {
    _ticket_type_collect_required_elements($element, $element['#ticket_type_required_elements']);
  }
  return $element;
}

/**
 * Create an array of required fields.
 */
function _ticket_type_collect_required_elements(&$element, &$required_elements) {
  // Recurse through all children.
  foreach (element_children($element) as $key) {
    if (isset($element[$key]) && $element[$key]) {
      _ticket_type_collect_required_elements($element[$key], $required_elements);
    }
  }
  if (!empty($element['#required'])) {
    $element['#required'] = FALSE;
    $required_elements[] = &$element;
    $element += array('#pre_render' => array());
    array_unshift($element['#pre_render'], 'ticket_type_field_widget_render_required');
  }
}

/**
 * The #pre_render callback ensures elements rendered as being required.
 */
function ticket_type_field_widget_render_required($element) {
  $element['#required'] = TRUE;
  return $element;
}


/**
 * Ticket type field validation callback.
 */
function ticket_type_field_validate($element, &$form_state, $form) {
  $instance = field_widget_instance($element, $form_state);
  $field = field_widget_field($element, $form_state);
  $field_parents = $element['#field_parents'];
  $field_name = $element['#field_name'];
  $language = $element['#language'];

  $field_state = field_form_get_state($field_parents, $field_name, $language, $form_state);
  $ticket_type = $field_state['entity'][$element['#delta']];

  // Attach field API validation of the embedded form.
  field_attach_form_validate('ticket_type', $ticket_type, $element, $form_state);

  // Now validate required elements if the entity is not empty. This is set
  // in the ticket_type_field_delay_required_validation.
  if (!ticket_type_is_empty($ticket_type) && !empty($element['#ticket_type_required_elements'])) {
    foreach ($element['#ticket_type_required_elements'] as &$elements) {

      // Copied from _form_validate().
      if (isset($elements['#needs_validation'])) {
        $is_empty_multiple = (!count($elements['#value']));
        $is_empty_string = (is_string($elements['#value']) && drupal_strlen(trim($elements['#value'])) == 0);
        $is_empty_value = ($elements['#value'] === 0);
        if ($is_empty_multiple || $is_empty_string || $is_empty_value) {
          if (isset($elements['#title'])) {
            form_error($elements, t('!name field is required.', array('!name' => $elements['#title'])));
          }
          else {
            form_error($elements);
          }
        }
      }
    }
  }

  // Only if the form is being submitted, finish the ticket type entity and
  // prepare it for saving.
  if ($form_state['submitted'] && !form_get_errors()) {

    field_attach_submit('ticket_type', $ticket_type, $element, $form_state);

    // Load initial form values into $item, so any other form values below the
    // same parents are kept.
    $item = drupal_array_get_nested_value($form_state['values'], $element['#parents']);

    // Set the _weight if it is a multiple field.
    if (isset($element['_weight']) && ($field['cardinality'] > 1 || $field['cardinality'] == FIELD_CARDINALITY_UNLIMITED)) {
      $item['_weight'] = $element['_weight']['#value'];
    }

    // Put the ticket type in $item['entity'], so it is saved with
    // the host entity via hook_field_presave() / field API if it is not empty.
    // @see ticket_field_presave()
    $item['entity'] = $ticket_type;
    form_set_value($element, $item, $form_state);
  }
}


/**
 * Order max validation callback.
 */
function ticket_type_order_max_validate($element, &$form_state, $form) {
  if (!empty($element['#value'])) {
    static $parent;
    if (empty($parent)) {
      // Get this field's direct parent.
      $field_index = array_search($element['#field_name'], $element['#parents']);
      $parent_path_array = array_slice($element['#parents'], 0, $field_index + 1);
      $parent = drupal_array_get_nested_value($form_state['values'], $parent_path_array);
    }

    // If the ticket type has a minimum...
    if (isset($parent['ticket_type_order_min'][$element['#language']][0]) && !empty($parent['ticket_type_order_min'][$element['#language']][0])) {
      // Ensure that the max is greater than the minimum.
      if ($parent['ticket_type_order_min'][$element['#language']][0]['value'] > $element['#value']) {
        form_error($element, t('The order maximum must be greater than or equal to the minimum.'));
      }
    }
  }
}

/**
 * Gets a ticket type entity for a given field item.
 *
 * @return object
 *   The entity object or FALSE.
 */
function ticket_type_get_entity(&$item) {
  if (isset($item['entity'])) {
    return $item['entity'];
  }
  elseif (isset($item['value'])) {
    // By default always load the default revision, so caches get used.
    $entity = entity_load_single('ticket_type', $item['value']);
    if ($entity->revision_id != $item['revision_id']) {
      // A non-default revision is a referenced, so load this one.
      // TODO: revisioning should be tested. I don't think this works
      // at the moment.
      $entity = entity_revision_load('ticket_type', $item['revision_id']);
    }
    $item['entity'] = $entity;
    return $entity;
  }
  elseif (!isset($item['entity'])) {
    $item['entity'] = entity_create('ticket_type', array());
    return $item['entity'];
  }
  return FALSE;
}

/**
 * Implements hook_field_presave().
 *
 * Support saving ticket types in @code $item['entity'] @endcode. This
 * may be used to seamlessly create ticket types during host-entity
 * creation or to save changes to the host entity and its ticket types at once.
 */
function ticket_field_presave($entity_type, $entity, $field, $instance, $langcode, &$items) {
  foreach ($items as &$item) {
    // In case the entity has been changed / created, save it and set the id.
    // If the host entity creates a new revision, save new item-revisions as
    // well.
    if (isset($item['entity']) || !empty($entity->revision)) {

      if ($ticket_type = ticket_type_get_entity($item)) {

        // If we're creating a new ticket type, then we set the entity info.
        // Note that the entity_id may be 0 if the entity is also new.
        if (!empty($ticket_type->is_new)) {
          list($entity_id, $revision_id, $bundle) = entity_extract_ids($entity_type, $entity);
          $ticket_type->entity_type = $entity_type;
          $ticket_type->entity_id = $entity_id;
          $ticket_type->field_name = $field['field_name'];
          $ticket_type->created = REQUEST_TIME;
        }
        $ticket_type->status = $item['status'];
        $ticket_type->changed = REQUEST_TIME;

        // If the host entity is saved as new revision, do the same for the
        // item.
        if (!empty($entity->revision)) {
          $ticket_type->revision = TRUE;
          $is_default = entity_revision_is_default($entity_type, $entity);

          // If an entity type does not support saving non-default entities,
          // assume it will be saved as default.
          if (!isset($is_default) || $is_default) {
            $ticket_type->default_revision = TRUE;
          }

          // If the ticket type is not new, create a new revision.
          if (!isset($ticket_type->is_new) || !$ticket_type->is_new) {
            $ticket_type->is_new = FALSE;
            $ticket_type->is_new_revision = TRUE;
          }

        }
        $ticket_type->save();

        // Allow submodules to respond to the item info.
        module_invoke_all('ticket_field_item_presave', $item);

        // Store the info back to the field item.
        $item = array(
          'value' => $ticket_type->ttid,
          'revision_id' => $ticket_type->revision_id,
          'entity' => $ticket_type,
        );
      }
    }
  }
}

/**
 * Implements hook_field_insert().
 */
function ticket_field_insert($entity_type, $entity, $field, $instance, $langcode, &$items) {
  foreach ($items as &$item) {
    // If the ticket type was created at the same time as the host,
    // its entity_id will be blank and we need to fix that.
    if (empty($item['entity']->entity_id)) {

      if (!isset($entity_id)) {
        list($entity_id, $revision_id, $bundle) = entity_extract_ids($entity_type, $entity);
      }

      $item['entity']->entity_id = $entity_id;
      $item['entity']->save();
    }
  }
}

/**
 * Implements hook_field_update().
 */
function ticket_field_update($entity_type, $entity, $field, $instance, $langcode, &$items) {
  $new_tts = array();
  foreach ($items as $new_tt) {
    $new_tts[] = $new_tt['value'];
  }

  $old_tts = array();
  $original_types = field_get_items($entity_type, $entity->original, $field['field_name'], $langcode);
  if (!empty($original_types)) {
    foreach ($original_types as $old_tt) {
      $old_tts[] = $old_tt['value'];
    }
  }

  $delete_tts = array_diff($old_tts, $new_tts);
  if (count($delete_tts)) {
    entity_delete_multiple('ticket_type', $delete_tts);
  }

  list($entity_id, $revision_id, $bundle) = entity_extract_ids($entity_type, $entity);
  ticket_flush_caches($entity_type, $entity_id);
}

/**
 * Implements hook_field_delete().
 */
function ticket_field_delete($entity_type, $entity, $field, $instance, $langcode, &$items) {
  $ticket_types = array();
  foreach ($items as $item) {
    $ticket_types[] = $item['value'];
  }

  if (!empty($ticket_types)) {
    entity_delete_multiple('ticket_type', $ticket_types);
  }
}

/**
 * Page callback to handle AJAX for removing a ticket type item.
 *
 * This is a direct page callback. The actual job of deleting the item is
 * done in the submit handler for the button, so all we really need to
 * do is process the form and then generate output. We generate this
 * output by doing a replace command on the id of the entire form element.
 */
function ticket_type_remove_js() {
  // drupal_html_id() very helpfully ensures that all html IDS are unique
  // on a page. Unfortunately what it doesn't realize is that the IDs
  // we are generating are going to replace IDs that already exist, so
  // this actually works against us.
  if (isset($_POST['ajax_html_ids'])) {
    unset($_POST['ajax_html_ids']);
  }

  list($form, $form_state) = ajax_get_form();
  drupal_process_form($form['#form_id'], $form, $form_state);

  // Get the information on what we're removing.
  $button = $form_state['triggering_element'];
  // Go two levels up in the form, to the whole widget.
  $element = drupal_array_get_nested_value($form, array_slice($button['#array_parents'], 0, -3));
  // Now send back the proper AJAX command to replace it.
  $return = array(
    '#type' => 'ajax',
    '#commands' => array(
      ajax_command_replace('#' . $element['#id'], drupal_render($element)),
    ),
  );

  // Because we're doing this ourselves, messages aren't automatic. We have
  // to add them.
  $messages = theme('status_messages');
  if ($messages) {
    $return['#commands'][] = ajax_command_prepend('#' . $element['#id'], $messages);
  }

  return $return;
}

/**
 * Submit callback to remove an item from the field UI multiple wrapper.
 *
 * When a remove button is submitted, we need to find the item that it
 * referenced and delete it. Since field UI has the deltas as a straight
 * unbroken array key, we have to renumber everything down. Since we do this
 * we *also* need to move all the deltas around in the $form_state['values']
 * and $form_state['input'] so that user changed values follow. This is a bit
 * of a complicated process.
 */
function ticket_type_remove_submit($form, &$form_state) {
  $button = $form_state['triggering_element'];
  $delta = $button['#delta'];

  // Where in the form we'll find the parent element.
  $address = array_slice($button['#array_parents'], 0, -2);

  // Go one level up in the form, to the widgets container.
  $parent_element = drupal_array_get_nested_value($form, $address);
  $field_name = $parent_element['#field_name'];
  $langcode = $parent_element['#language'];
  $parents = $parent_element['#field_parents'];

  $field_state = field_form_get_state($parents, $field_name, $langcode, $form_state);

  // Go ahead and renumber everything from our delta to the last
  // item down one. This will overwrite the item being removed.
  for ($i = $delta; $i <= $field_state['items_count']; $i++) {
    $old_element_address = array_merge($address, array($i + 1));
    $new_element_address = array_merge($address, array($i));

    $moving_element = drupal_array_get_nested_value($form, $old_element_address);
    $moving_element_value = drupal_array_get_nested_value($form_state['values'], $old_element_address);
    $moving_element_input = drupal_array_get_nested_value($form_state['input'], $old_element_address);

    // Tell the element where it's being moved to.
    $moving_element['#parents'] = $new_element_address;

    // Move the element around.
    form_set_value($moving_element, $moving_element_value, $form_state);
    drupal_array_set_nested_value($form_state['input'], $moving_element['#parents'], $moving_element_input);

    // Move the entity in our saved state.
    if (isset($field_state['entity'][$i + 1])) {
      $field_state['entity'][$i] = $field_state['entity'][$i + 1];
    }
    else {
      unset($field_state['entity'][$i]);
    }
  }

  // Replace the deleted entity with an empty one. This helps to ensure that
  // trying to add a new entity won't ressurect a deleted entity from the
  // trash bin.
  $count = count($field_state['entity']);
  $field_state['entity'][$count] = entity_create('ticket_type', array());

  // Then remove the last item. But we must not go negative.
  if ($field_state['items_count'] > 0) {
    $field_state['items_count']--;
  }

  // Fix the weights. Field UI lets the weights be in a range of
  // (-1 * item_count) to (item_count). This means that when we remove one,
  // the range shrinks; weights outside of that range then get set to
  // the first item in the select by the browser, floating them to the top.
  // We use a brute force method because we lost weights on both ends
  // and if the user has moved things around, we have to cascade because
  // if I have items weight weights 3 and 4, and I change 4 to 3 but leave
  // the 3, the order of the two 3s now is undefined and may not match what
  // the user had selected.
  $input = drupal_array_get_nested_value($form_state['input'], $address);
  // Sort by weight.
  uasort($input, '_field_sort_items_helper');

  // Reweight everything in the correct order.
  $weight = -1 * $field_state['items_count'];
  foreach ($input as $key => $item) {
    if ($item) {
      $input[$key]['_weight'] = $weight++;
    }
  }

  drupal_array_set_nested_value($form_state['input'], $address, $input);
  field_form_set_state($parents, $field_name, $langcode, $form_state, $field_state);

  $form_state['rebuild'] = TRUE;
}
