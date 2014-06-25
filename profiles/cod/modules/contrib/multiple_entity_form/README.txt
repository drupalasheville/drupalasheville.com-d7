Multiple entity form
====================

Provides helper functions for creating forms that display multiple entities, of multiple types, showing multiple fields.

Example:

function my_form($form, &$form_state) {
  $entity_data = array();
  $entity_data[] = array(
    'entity_type' => 'node',
    'entity' => node_load(1),
    'fields' => array('field_foo', 'field_bar'),
    'fieldset' => t('My First Node'),
  );
  $entity_data[] = array(
    'entity_type' => 'node',
    'entity' => node_load(2),
    // 'fields' not given: all fields shown.
  );

  $form += multiple_entity_form($form, $form_state, $entity_data);

  // Add your submit button and other form elements you need.
}

function my_form_validate($form, &$form_state) {
  multiple_entity_form_validate($form, $form_state);
}

function my_form_submit($form, &$form_state) {
  multiple_entity_form_submit($form, $form_state);
}
