<?php
/**
 * @file
 * Ticket Type entity class.
 */

/**
 * Provides an entity class Ticket Type.
 */
class TicketTypeEntity extends Entity {

  // Allow access to Ticket Type properties.
  public $ttid;
  public $revision_id;
  public $entity_type;
  public $entity_id;
  public $field_name;
  public $status;
  public $created;
  public $changed;
  public $default_state;
  public $entity;
  public $bundle = 'ticket_type';

  /**
   * Construct.
   */
  public function __construct($values) {
    parent::__construct($values, 'ticket_type');
  }

  /**
   * Entity save method.
   */
  public function save() {
    parent::save();
    ticket_flush_caches();
  }

  /**
   * A helper funtion to get a type's host entity.
   */
  public function host($entity_type = NULL, $entity_id = NULL) {
    // Set the entity info.
    if ($entity_type && $entity_id) {
      $this->entity_type = $entity_type;
      $this->entity_id = $entity_id;
      $this->entity = NULL;
    }

    // Set the entity.
    if (empty($this->entity) && !empty($this->entity_type) && !empty($this->entity_id)) {
      $this->entity = entity_load_single($this->entity_type, $this->entity_id);
    }

    return $this->entity;
  }
}

class TicketTypeUIController extends EntityDefaultUIController {

  /**
   * Implements hook_menu().
   */
  public function hook_menu() {
    $items = array();
    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%entity_object';
    $plural_label = isset($this->entityInfo['plural label']) ? $this->entityInfo['plural label'] : $this->entityInfo['label'] . 's';

    $registration_path = ticket_get_admin_path('ticket_registration');
    $items[$registration_path . '/manage/' . $wildcard] = array(
      'title' => 'Ticket registrations',
      'title callback' => 'ticket_type_label',
      'title arguments' => array($this->id_count + 2),
      'page callback' => 'ticket_registration_view_page',
      'page arguments' => array($this->id_count + 2),
      'acces callback' => TRUE,
      'access callback' => 'entity_access',
      'access arguments' => array('update', $this->entityType, $this->id_count + 2),
      'file path' => drupal_get_path('module', 'ticket') . '/includes',
      'file' => 'ticket_registration.admin.inc',
    );
    $items[$registration_path . '/manage/' . $wildcard . '/registrations'] = array(
      'title' => 'Ticket registrations',
      'type' => MENU_DEFAULT_LOCAL_TASK,
    );

    foreach (ticket_get_entities() as $entity_type => $bundle) {
      $uri = ticket_get_entity_uri_pattern($entity_type);
      $argument = array_search('%', explode('/', $uri));
      $path = $uri . '/' . $this->path;

      // Give us a manage tickets list page.
      $items[$path] = array(
        'title' => 'Tickets',
        'page callback' => 'drupal_get_form',
        'page arguments' => array($this->entityType . '_overview_form', $this->entityType, $argument, $entity_type),
        'description' => 'Manage ' . $plural_label . '.',
        'access callback' => 'ticket_type_overview_access',
        'access arguments' => array($entity_type, $argument, 'update'),
        'file path' => drupal_get_path('module', 'entity') . '/includes',
        'file' => 'entity.ui.inc',
        'type' => MENU_LOCAL_TASK,
      );
    }
    return $items;
  }

  /**
   * Provides definitions for implementing hook_forms().
   *
   * Use per bundle form ids if possible, such that easy per bundle alterations
   * are supported too.
   *
   * Note that for performance reasons, this method is only invoked for forms,
   * which receive the entity_type as first argument. Thus any forms added, must
   * follow that pattern.
   *
   * @see entity_forms()
   */
  public function hook_forms() {
    $forms = parent::hook_forms();

    // Override the overview form.
    $forms[$this->entityType . '_overview_form'] = array(
      'callback' => 'ticket_overview_form',
      'wrapper_callback' => 'entity_ui_form_defaults',
    );

    return $forms;
  }

  /**
   * Builds the entity overview form.
   */
  public function overviewForm($form, &$form_state, $entity_id = NULL, $entity_type = NULL) {
    if (!empty($entity_type) && !empty($entity_id)) {
      // By default just show a simple overview for all entities.
      $conditions = array(
        'entity_type' => $entity_type,
        'entity_id' => $entity_id,
      );
      $form['table'] = $this->overviewTable($conditions);
      $form['pager'] = array('#theme' => 'pager');
    }
    return $form;
  }

  /**
   * Generates the render array for a overview table for arbitrary entities
   * matching the given conditions.
   *
   * @param array $conditions
   *   An array of conditions as needed by entity_load().
   *
   * @return array
   *   A renderable array.
   */
  public function overviewTable($conditions = array()) {

    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', $this->entityType);

    // Add all conditions to query.
    foreach ($conditions as $key => $value) {
      $query->propertyCondition($key, $value);
    }

    if ($this->overviewPagerLimit) {
      $query->pager($this->overviewPagerLimit);
    }

    $results = $query->execute();

    $ids = isset($results[$this->entityType]) ? array_keys($results[$this->entityType]) : array();
    $entities = $ids ? entity_load($this->entityType, $ids) : array();
    ksort($entities);

    $rows = array();
    foreach ($entities as $entity) {
      $additional_cols = array(
        ticket_type_registration_count($entity->ttid),
        ticket_type_available($entity) ? t('Yes') : t('No'),
      );
      $rows[] = $this->overviewTableRow($conditions, entity_id($this->entityType, $entity), $entity, $additional_cols);
    }

    // Add our custom headers.
    $additional_headers = array(
      t('Registrations'),
      t('Available'),
    );

    $render = array(
      '#theme' => 'table',
      '#header' => $this->overviewTableHeaders($conditions, $rows, $additional_headers),
      '#rows' => $rows,
      '#empty' => t('None.'),
    );
    return $render;
  }

  /**
   * Generates the table headers for the overview table.
   */
  protected function overviewTableHeaders($conditions, $rows, $additional_header = array()) {
    $header = $additional_header;
    array_unshift($header, t('Label'));
    if (!empty($this->entityInfo['exportable'])) {
      $header[] = t('Status');
    }
    // Add operations with the right colspan.
    $header[] = array('data' => t('Operations'), 'colspan' => $this->operationCount());
    return $header;
  }


  /**
   * Returns the operation count for calculating colspans.
   */
  protected function operationCount() {
    // Set count to 1 for view registrations link.
    $count = 1;
    $count += !empty($this->entityInfo['bundle of']) && entity_type_is_fieldable($this->entityInfo['bundle of']) && module_exists('field_ui') ? 2 : 0;
    $count += !empty($this->entityInfo['exportable']) ? 1 : 0;
    $count += !empty($this->entityInfo['i18n controller class']) ? 1 : 0;
    return $count;
  }


  /**
   * Generates the row for the passed entity and may be overridden in order to
   * customize the rows.
   *
   * @param array $additional_cols
   *   Additional columns to be added after the entity label column.
   */
  protected function overviewTableRow($conditions, $id, $entity, $additional_cols = array()) {
    $entity_uri = entity_uri($this->entityType, $entity);

    $row[] = array(
      'data' => array(
        '#theme' => 'entity_ui_overview_item',
        '#label' => entity_label($this->entityType, $entity),
        '#name' => !empty($this->entityInfo['exportable']) ? entity_id($this->entityType, $entity) : FALSE,
        '#url' => $entity_uri ? $entity_uri : FALSE,
        '#entity_type' => $this->entityType,
      ),
    );

    // Add in any passed additional cols.
    foreach ($additional_cols as $col) {
      $row[] = $col;
    }

    // Add a row for the exportable status.
    if (!empty($this->entityInfo['exportable'])) {
      $row[] = array(
        'data' => array(
          '#theme' => 'entity_status',
          '#status' => $entity->{$this->statusKey},
        ),
      );
    }
    // In case this is a bundle, we add links to the field ui tabs.
    $field_ui = !empty($this->entityInfo['bundle of']) && entity_type_is_fieldable($this->entityInfo['bundle of']) && module_exists('field_ui');
    // For exportable entities we add an export link.
    $exportable = !empty($this->entityInfo['exportable']);
    // If i18n integration is enabled, add a link to the translate tab.
    $i18n = !empty($this->entityInfo['i18n controller class']);

    /*
    Everything above is directly from the DefaultEntityUIController.
    Below is where we customize the links. Currently editing and
    deleting should be performed via the host entity's edit form
    (field ui). Also we do not have exporting, so cloning links
    were removed.
    */

    // Get the managing path for ticket_registrations.
    $path = ticket_get_admin_path('ticket_registration');
    $row[] = l(t('view registrations'), $path . '/manage/' . $id . '/registrations');

    // Add operations depending on the status.
    if (!entity_has_status($this->entityType, $entity, ENTITY_FIXED)) {
      if ($field_ui) {
        // Field management is on ticket registrations, not types.
        $row[] = l(t('manage fields'), $path . '/manage/' . $id . '/fields');
        $row[] = l(t('manage display'), $path . '/manage/' . $id . '/display');
      }
    }

    return $row;
  }

}
