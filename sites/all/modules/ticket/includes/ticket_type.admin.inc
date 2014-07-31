<?php
/**
 * @file
 * Ticket type admin file.
 */

/**
 * Admin form.
 */
function ticket_admin_form($form, &$form_state) {
  // There are currently no sitewide settings. We only needed a page to
  // attach the field ui tabs. Insert some placeholder information on
  // this page.
  $form['information'] = array(
    '#markup' => t('<p>Use the Manage Fields tab to add custom ticket type fields. These fields will be available to users who manage ticket types on entities (i.e. event creators/editors).</p><p>Use the Manage Display tab to customize which ticket type fields are visible to users who will be viewing the ticketed entities and registering for tickets.</p>'),
  );

  return $form;
}
