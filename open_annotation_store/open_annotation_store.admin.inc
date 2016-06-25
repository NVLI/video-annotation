<?php

/**
 * @file
 * Content builder functions for VideoAnnotations.
*/ 

function videoanno_data($form, $form_state) {

  $admin_access = user_access('administer video annotations');

 // Build the 'Update options' form.
  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update options'),
    '#attributes' => array('class' => array('container-inline')),
  );
  $form['options']['operation'] = array(
    '#type' => 'select',
    '#title' => t('Operation'),
    '#title_display' => 'invisible',
    '#options' => array('delete' => ('Delete')),
    '#default_value' => 'approve',
  );
  $form['options']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
  );
  // Build the sortable table header.
  $header = array(
    'text' => array('data' => t('Text')),
    'type' => array('data' => t('Type')),
    'uri' => array('data' => t('Uri')),
    'author' => t('Author'),
    'created' => array('data' => t('created')),
    'timestamp' => array('data' => t('Updated'), 'field' => 'a.updated', 'sort' => 'desc'),
    'operations' => array('data' => t('Operations')),
  );
  // Fetching the required fields from table.
  $query = db_select('video_annotation', 'a')->extend('PagerDefault')->extend('TableSort');
  $result = $query
    ->fields('a', array('id', 'uid'))
    ->limit(50)
    ->orderByHeader($header)
    ->execute()
    ->fetchAllKeyed();
  $annotations = entity_load_multiple_by_name('VideoAnnotation', array_keys($result));
  $accounts = user_load_multiple(array_unique($result));
  $destination = drupal_get_destination();
  $options = array();
  foreach ($annotations as $annotation) {
    $options[$annotation->id] = array(
      'text' => $annotation->text,
      'type' => $annotation->type,
      'uri' => l($annotation->uri, $annotation->uri),
      'author' => theme('username', array('account' => $accounts[$annotation->uid])),
      'created' => format_date($annotation->created, 'short'),
      'timestamp' => format_date($annotation->updated, 'short'),
      'operations' => array(),
   );
    $operations = array();
    if ($admin_access) {
    $operations['delete'] = array(
        'title' => t('Delete'),
        'href' => 'annotation/' . $annotation->id . '/delete',
        'query' => $destination,
      );
    }
    if (count($operations) > 1) {
      // Render an unordered list of operations links.
      $options[$annotation->id]['operations'] = array(
        'data' => array(
          '#theme' => 'links__file_entity_operations',
          '#links' => $operations,
          '#attributes' => array('class' => array('links', 'inline')),
        ),
      );
    }
    elseif (!empty($operations)) {
      // Render the first and only operation as a link.
      $link = reset($operations);
      $options[$annotation->id]['operations'] = array(
        'data' => array(
          '#type' => 'link',
          '#title' => $link['title'],
          '#href' => $link['href'],
          '#options' => array('query' => $link['query']),
        ),
      );
    }
  }
  if ($admin_access) {
    $form['annotations'] = array(
      '#type' => 'tableselect',
      '#header' => $header,
      '#options' => $options,
      '#empty' => t('No annotation available.'),
    );
  }
  else {
    $form['annotations'] = array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $options,
      '#empty' => t('No annotation available.'),
    );
  }
  $form['pager'] = array('#markup' => theme('pager'));
  return $form;
}
/**
 * Function call to delete the annotations.
 */
function video_annotation_delete_form($form, &$form_state, $annotation) {
  $form_state['annotation'] = $annotation;
  $form['id'] = array(
    '#type' => 'value',
    '#value' => $annotation,
  );
  $description = t('This action cannot be undone.');

  return confirm_form($form,
    t('Are you sure you want to delete the annotation %id?', array(
      '%id' => $annotation,
    )),
    'annotation/' . $annotation,
    $description,
    t('Delete')
  );
}

/**
 * Form submit
 */
function  video_annotation_delete_form_submit($form, &$form_state) {
  if ($form_state['values']['confirm'] && $annotation = entity_object_load($form_state['values']['id'], 'VideoAnnotation')) {
    entity_delete('VideoAnnotation', array($form_state['values']['id']));
    $args = array(
      '@type' => $annotation->type,
      '%id' => $annotation->id,
    );
    watchdog('VideoAnnotation', '@type: deleted %id.', $args);
    drupal_set_message(t('Annotation %id has been deleted.', $args));
  }
  $form_state['redirect'] = '<front>';

  // Clear the page and block caches.
  cache_clear_all();
}


