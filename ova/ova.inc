<?php

function template_preprocess_ova(&$variables) {
  $annotation_settings = array();
  $entity = $variables['entity'];
  $resource_entity_id = $entity->id();
  $variables['#attached']['drupalSettings']['ova_annotation']['annotation_settings'] = $resource_entity_id;
}