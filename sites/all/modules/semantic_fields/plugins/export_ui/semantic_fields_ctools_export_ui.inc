<?php
/**
 * @file
 *  Export UI functions
 */

/**
 * Define this Export UI plugin.
 */
$plugin = array(
  'schema' => 'semantic_fields_preset',
  'access' => 'administer semantic fields',
  'menu' => array(
    'menu item' => 'semantic_fields',
    'menu title' => 'Semantic fields',
    'menu description' => 'Administer Semantic fields presets.',
  ),
  'load callback' => 'semantic_fields_preset_load',
  'title singular' => t('preset'),
  'title plural' => t('presets'),
  'title singular proper' => t('Semantic fields preset'),
  'title plural proper' => t('Semantic fields presets'),
  'form' => array(
    'settings' => 'semantic_fields_ctools_export_ui_form',
    'submit' => 'semantic_fields_ctools_export_ui_form_submit',
  ),
);


/**
* Define the preset add/edit form.
*/
function semantic_fields_ctools_export_ui_form(&$form, &$form_state) {
  $preset = $form_state['item'];

  if(isset($preset->id)) {
     $form['id'] = array(
    '#type' => 'hidden',
    '#value' => $preset->id,
  ); 
  }

  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#description' => t('A description of this field format.'),
    '#default_value' => isset($preset->description) ? $preset->description : '',
    '#required' => FALSE,
  );
  $form['semantic_field_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Semantic field settings'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
  );
  $form['semantic_field_settings']['field_container_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Field container'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#parents' => array('semantic_field_settings'),
  );
  $form['semantic_field_settings']['field_container_fieldset']['field_element'] = array(
    '#type' => 'textfield',
    '#title' => t('Surround the entire field with'),
    '#description' => t('Insert the desired <abbr title="Hyper Text Markup Language">HTML</abbr> element that will be the container for the entire field. Leave blank for no surrounding element.'),
    '#default_value' => isset($preset->data['field_element']) ? $preset->data['field_element'] : 'div',
    '#required' => FALSE,
    '#size' => 20,
  );
  $form['semantic_field_settings']['field_container_fieldset']['field_class'] = array(
    '#type' => 'textfield',
    '#title' => t('Choose field element class(es)'),
    '#description' => t('The field element automatically gets field, field type and specific field classes (ie. <em>field field-type-text field-field-my-field-name</em>).'),
    '#default_value' => isset($preset->data['field_class']) ? $preset->data['field_class'] : '',
    '#required' => FALSE,
  );
  $form['semantic_field_settings']['field_container_fieldset']['field_prefix'] = array(
    '#type' => 'textfield',
    '#title' => t('And a prefix of'),
    '#default_value' => isset($preset->data['field_prefix']) ? $preset->data['field_prefix'] : '',
    '#description' => t('Insert the desired character(s) to output before the field.'),
    '#required' => FALSE,
    '#size' => 20,
  );
  $form['semantic_field_settings']['field_container_fieldset']['field_suffix'] = array(
    '#type' => 'textfield',
    '#title' => t('And a suffix of'),
    '#default_value' => isset($preset->data['field_suffix']) ? $preset->data['field_suffix'] : '',
    '#description' => t('Insert the desired character(s) to output after the field.'),
    '#required' => FALSE,
  );
  $form['semantic_field_settings']['label_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Field label'),
    '#description' => t('<strong>Please note that the placement or appearance of the label is still determined by the field display settings.</strong>'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#attributes' => array('class' => array('semantic-fields-labels')),
  );
  $form['semantic_field_settings']['label_fieldset']['above'] = array(
    '#type' => 'fieldset',
    '#title' => t('Labels above field value(s)'),
    '#description' => t('How to render the label when located above the field value(s).'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('semantic-fields-labels-above')),
    '#parents' => array('semantic_field_settings'),
  );
  $form['semantic_field_settings']['label_fieldset']['above']['label_element_above'] = array(
    '#type' => 'textfield',
    '#title' => t('Surround the label with'),
    '#description' => t('Insert the desired <abbr title="Hyper Text Markup Language">HTML</abbr> element that will surround the label.'),
    '#default_value' => isset($preset->data['label_element_above']) ? $preset->data['label_element_above'] : 'h3',
    '#required' => TRUE,
    '#size' => 20,
  );
  $form['semantic_field_settings']['label_fieldset']['above']['label_class_above'] = array(
    '#type' => 'textfield',
    '#title' => t('And a class of'),
    '#description' => t('The label automatically gets a class of <em>field-label</em>.'),
    '#default_value' => isset($preset->data['label_class_above']) ? $preset->data['label_class_above'] : '',
    '#required' => FALSE,
    '#size' => 20,
  );
  $form['semantic_field_settings']['label_fieldset']['above']['label_suffix_above'] = array(
    '#type' => 'textfield',
    '#title' => t('And a suffix of'),
    '#description' => t('Insert the desired suffix character, eg. a colon'),
    '#default_value' => isset($preset->data['label_suffix_above']) ? $preset->data['label_suffix_above'] : '',
    '#required' => FALSE,
    '#size' => 20,
  );
  $form['semantic_field_settings']['label_fieldset']['inline'] = array(
    '#type' => 'fieldset',
    '#title' => t('Inline labels'),
    '#description' => t('How to render the label when located inline with the field value(s).'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('semantic-fields-labels-inline')),
    '#parents' => array('semantic_field_settings'),
  );
  $form['semantic_field_settings']['label_fieldset']['inline']['label_element_inline'] = array(
    '#type' => 'textfield',
    '#title' => t('Surround the label with'),
    '#description' => t('Insert the desired <abbr title="Hyper Text Markup Language">HTML</abbr> element that will surround the label.'),
    '#default_value' => isset($preset->data['label_element_inline']) ? $preset->data['label_element_inline'] : 'span',
    '#required' => TRUE,
    '#size' => 20,
  );
  $form['semantic_field_settings']['label_fieldset']['inline']['label_class_inline'] = array(
    '#type' => 'textfield',
    '#title' => t('And a class of'),
    '#description' => t('The label automatically gets a class of <em>field-label-inline</em>.'),
    '#default_value' => isset($preset->data['label_class_inline']) ? $preset->data['label_class_inline'] : '',
    '#required' => FALSE,
    '#size' => 20,
  );
  $form['semantic_field_settings']['label_fieldset']['inline']['label_suffix_inline'] = array(
    '#type' => 'textfield',
    '#title' => t('And a suffix of'),
    '#description' => t('Insert the desired suffix character, eg. a colon'),
    '#default_value' => isset($preset->data['label_suffix_inline']) ? $preset->data['label_suffix_inline'] : ':',
    '#required' => FALSE,
    '#size' => 20,
  );
  $form['semantic_field_settings']['items_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Field value(s)'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#attributes' => array('class' => array('semantic-fields-multiple-values')),
  );
  $form['semantic_field_settings']['items_fieldset']['multivalue'] = array(
    '#type' => 'fieldset',
    '#title' => t('Multiple value field'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('field-values', 'semantic-fields-multiple-values-all')),
  );
  $form['semantic_field_settings']['items_fieldset']['multivalue']['items_element'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('semantic-fields-multiple-values-fields')),
    '#parents' => array('semantic_field_settings'),
  );
  $form['semantic_field_settings']['items_fieldset']['multivalue']['items_element']['multiple_items_element'] = array(
    '#type' => 'textfield',
    '#title' => t('Surround all field values with'),
    '#description' => t('Insert the desired <abbr title="Hyper Text Markup Language">HTML</abbr> element that will be the container for all field values. Leave blank for no surrounding element.'),
    '#default_value' => isset($preset->data['multiple_items_element']) ? $preset->data['multiple_items_element'] : 'div',
    '#required' => FALSE,
    '#size' => 20,
  );
  $form['semantic_field_settings']['items_fieldset']['multivalue']['items_element']['multiple_items_class'] = array(
    '#type' => 'textfield',
    '#title' => t('And a class of'),
    '#description' => t('The surrounding fields element automatically gets the <em>field-items</em> class.'),
    '#default_value' => isset($preset->data['multiple_items_class']) ? $preset->data['multiple_items_class'] : '',
    '#required' => FALSE,
  );
  $form['semantic_field_settings']['items_fieldset']['multivalue']['item_element'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('semantic-fields-multiple-values-field')),
    '#parents' => array('semantic_field_settings'),
  );
  $form['semantic_field_settings']['items_fieldset']['multivalue']['item_element']['multiple_item_element'] = array(
    '#type' => 'textfield',
    '#title' => t('Surround each field value with'),
    '#description' => t('Insert the desired <abbr title="Hyper Text Markup Language">HTML</abbr> element that will be the container for each field value. Leave blank for no surrounding element.'),
    '#default_value' => isset($preset->data['multiple_item_element']) ? $preset->data['multiple_item_element'] : 'div',
    '#required' => FALSE,
    '#size' => 20,
  );
  $form['semantic_field_settings']['items_fieldset']['multivalue']['item_element']['multiple_item_class'] = array(
    '#type' => 'textfield',
    '#title' => t('And a class of'),
    '#description' => t('Each field instance automatically gets the <em>field-item</em> class. Insert a # where you want enumeration (ie field-item-#).'),
    '#default_value' => isset($preset->data['multiple_item_class']) ? $preset->data['multiple_item_class'] : '',
    '#required' => FALSE,
  );
  $form['semantic_field_settings']['items_fieldset']['multivalue']['item_element']['multiple_item_separator'] = array(
    '#type' => 'textfield',
    '#title' => t('Separate each field value with'),
    '#description' => t('Insert the desired character(s) to use as a separator between each field value. For example, this could be used to display the field values as a comma separated list.'),
    '#default_value' => isset($preset->data['multiple_item_separator']) ? $preset->data['multiple_item_separator'] : '',
    '#required' => FALSE,
    '#size' => 20,
  );
  $form['semantic_field_settings']['items_fieldset']['singlevalue'] = array(
    '#type' => 'fieldset',
    '#title' => t('Single value field'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('semantic-fields-single-values-settings')),
    '#parents' => array('semantic_field_settings'),
  );
  $form['semantic_field_settings']['items_fieldset']['singlevalue']['use_singlevalue_settings'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use the following settings when the field contains only one value'),
    '#description' => t('Leave this unchecked to use multiple value field settings when the field contains only one value.'),
    '#return_value' => 1,
    '#default_value' => isset($preset->data['use_singlevalue_settings']) ? $preset->data['use_singlevalue_settings'] : 0,
    '#required' => FALSE,
    '#size' => 20,
  );
  $form['semantic_field_settings']['items_fieldset']['singlevalue']['singlevalues'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('semantic-fields-single-values-item')),
    '#parents' => array('semantic_field_settings'),
  );
  $form['semantic_field_settings']['items_fieldset']['singlevalue']['singlevalues']['single_item_element'] = array(
    '#type' => 'textfield',
    '#title' => t('Surround field value with'),
    '#description' => t('Insert the desired <abbr title="Hyper Text Markup Language">HTML</abbr> element that will be the container for a single field value. Leave blank for no surrounding element.'),
    '#default_value' => isset($preset->data['single_item_element']) ? $preset->data['single_item_element'] : 'div',
    '#required' => FALSE,
    '#size' => 20,
  );
  $form['semantic_field_settings']['items_fieldset']['singlevalue']['singlevalues']['single_item_class'] = array(
    '#type' => 'textfield',
    '#title' => t('And a class of'),
    '#default_value' => isset($preset->data['single_item_class']) ? $preset->data['single_item_class'] : '',
    '#description' => t('The field instance will automatically get a <em>field-item</em> class.'),
    '#required' => FALSE,
  );
  $form['semantic_field_settings']['items_fieldset']['nth_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('First and last classes'),
    '#description' => t('If the <em>FIRST/LAST every n<sup>th</sup></em> option is empty or zero, the <em>FIRST class attribute</em> and <em>LAST class attribute</em> are added once to only the first and last field values. If this option is greater than or equal to 1, these classe are added to every n<sup>th</sup> row, which may be useful for grid layouts where the initial and final unit\'s lateral margins must be 0.'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('semantic-fields-nth-settings')),
    '#parents' => array('semantic_field_settings'),
  );
  $form['semantic_field_settings']['items_fieldset']['nth_fieldset']['last_every_nth'] = array(
    '#type' => 'textfield',
    '#title' => t('FIRST/LAST every n<sup>th</sup>'),
    '#default_value' => isset($preset->data['last_every_nth']) && is_numeric($preset->data['last_every_nth']) ? $preset->data['last_every_nth'] : '0',
    '#required' => FALSE,
    '#size' => 20,
  );
  $form['semantic_field_settings']['items_fieldset']['nth_fieldset']['first_class'] = array(
    '#type' => 'textfield',
    '#title' => t('FIRST class attribute'),
    '#default_value' => isset($preset->data['first_class']) ? $preset->data['first_class'] : 'first',
    '#required' => FALSE,
    '#size' => 20,
  );
  $form['semantic_field_settings']['items_fieldset']['nth_fieldset']['last_class'] = array(
    '#type' => 'textfield',
    '#title' => t('LAST class attribute'),
    '#default_value' => isset($preset->data['last_class']) ? $preset->data['last_class'] : 'last',
    '#required' => FALSE,
    '#size' => 20,
  );
  $form['semantic_field_settings']['items_fieldset']['striping_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Striping'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('semantic-fields-striping-settings')),
    '#parents' => array('semantic_field_settings'),
  );
  $form['semantic_field_settings']['items_fieldset']['striping_fieldset']['striping_classes'] = array(
    '#type' => 'textfield',
    '#title' => t('Striping class attributes'),
    '#description' => t('One striping class attribute is applied to each row. Separate multiple attributes with a space.'),
    '#default_value' => isset($preset->data['striping_classes']) ? $preset->data['striping_classes'] : 'odd even',
    '#required' => FALSE,
  );
  $form['semantic_field_settings']['tokens_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tokens'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#attributes' => array('class' => array('semantic-fields-tokens-fieldset')),
    '#parents' => array('semantic_field_settings'),
  );
  if (module_exists('token') == TRUE) {
    $form['semantic_field_settings']['tokens_fieldset']['info'] = array(
      '#markup' => t('You could use tokens, like
        <em>[node:title]</em> and <em>[node:url]</em>' .
           theme('token_tree', array(
          'token_types' => 'all', 
          'click_insert' => FALSE, 
          'show_restricted' => TRUE))),
    );
  }
  else {
    $form['semantic_field_settings']['tokens_fieldset']['info'] = array(
      '#markup' => '<p>If you enable the token module you could use tokens in </p>',
    );
  }
  return $form;
}

/**
* Submit handler for the preset edit form.
*/
function semantic_fields_ctools_export_ui_form_submit($form, &$form_state) {
  $form_state['values']['data'] = $form_state['values']['semantic_field_settings'];
}
