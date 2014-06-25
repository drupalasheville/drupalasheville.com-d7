<?php
/**
 * @file
 * cod_profile_optional.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function cod_profile_optional_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_dietary_needs'
  $field_bases['field_dietary_needs'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_dietary_needs',
    'field_permissions' => array(
      'type' => 0,
    ),
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'Vegetarian' => 'Vegetarian',
        'Vegan' => 'Vegan',
        'Gluten free' => 'Gluten free',
        'Halal' => 'Halal',
        'Kosher' => 'Kosher',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_t_shirt_size'
  $field_bases['field_t_shirt_size'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_t_shirt_size',
    'field_permissions' => array(
      'type' => 0,
    ),
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'Womens XS' => 'Womens XS',
        'Womens S' => 'Womens S',
        'Womens M' => 'Womens M',
        'Womens L' => 'Womens L',
        'Womens XL' => 'Womens XL',
        'Mens XS' => 'Mens XS',
        'Mens S' => 'Mens S',
        'Mens M' => 'Mens M',
        'Mens L' => 'Mens L',
        'Mens XL' => 'Mens XL',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  return $field_bases;
}
