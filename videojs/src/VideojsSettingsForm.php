<?php

namespace Drupal\videojs;

use Drupal\Core\Form\ConfigFormBase;
use Drupal\Core\Form\FormStateInterface;

class VideojsSettingsForm extends ConfigFormBase {
  
  function getFormId() {
     return 'videojs_settings_form';
    }
    
  protected function getEditableConfigNames() {
    return [
      'videojs.settings',
    ];
  }
  
  function buildForm(array $form, FormStateInterface $form_state) {
    $contentTypes = \Drupal::service('entity.manager')->getStorage('node_type')->loadMultiple();
    $contentTypesList = [];
    foreach ($contentTypes as $contentType) {
      $contentTypesList[$contentType->id()] = $contentType->label();
    }
   $config = $this->config('videojs.settings');
   $form['title'] = array(
    '#markup' => t('<p>Control to load Open video Annotation Plugin js/css files on specific content types.</p><p><b>Enable or Disable Content types to allow Open Video Annotation Plugin</b></p>'),
   );
   foreach ($contentTypesList as $key => $value) {
        $form['content_type_'.$key] = array(
          '#type' => 'checkboxes',
          '#options' => array($key => $value),
          '#default_value' => $config->get('content_type_'.$key),
        );
        
   }
    return parent::buildForm($form, $form_state);
    }
    
    public function submitForm(array &$form, FormStateInterface $form_state) {
    $contentTypes = \Drupal::service('entity.manager')->getStorage('node_type')->loadMultiple();
    $contentTypesList = [];
    foreach ($contentTypes as $contentType) {
      $contentTypesList[$contentType->id()] = $contentType->label();
    }
   $config = $this->config('videojs.settings');
   foreach ($contentTypesList as $key => $value) {
    $this->config('videojs.settings')
      ->set('content_type_'.$key, $form_state->getValue('content_type_'.$key))
      ->save();
    parent::submitForm($form, $form_state);
   }
   }
}