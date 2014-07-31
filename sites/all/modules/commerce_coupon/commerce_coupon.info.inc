<?php

/*
 * Implements hook_entity_property_info_alter().
 */
function commerce_coupon_entity_property_info_alter(&$info) {
  if (isset($info['commerce_discount'])) {
    $info['commerce_discount']['properties']['coupons'] = array(
      'type' => 'list<commerce_coupon>',
      'label' => t('Coupons'),
      'getter callback' => 'commerce_coupon_get_discount_properties'
    );
    $info['commerce_discount']['properties']['coupon_count'] = array(
      'type' => 'integer',
      'label' => t('Coupon count'),
      'getter callback' => 'commerce_coupon_get_discount_properties'
    );
  }
}

/**
 * Extend the defaults meta data properties for Commerce coupon entity.
 */
class CommerceCouponMetadataController extends EntityDefaultMetadataController {

  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];

    $properties['status']['type'] = 'boolean';

    $schema = drupal_get_schema('commerce_coupon');

    foreach ($properties as $name => $property) {
      if (isset($schema['fields'][$name])) {
        $properties[$name] += array(
          'setter callback' => 'entity_property_verbatim_set',
          'getter callback' => 'entity_property_verbatim_get'
        );
      }
    }

    return $info;
  }
}
