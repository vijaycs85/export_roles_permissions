<?php

/**
 * @file
 */

/**
 * Form constructor for the export generation form.
 *
 * @see export_roles_permissions_form_submit()
 */
function export_roles_permissions_form(&$form_state) {
  $form = array(
    '#tree' => TRUE,
  );

  if (isset($form_state['code'])) {
    $form[] = array(
      '#type' => 'item',
      '#markup' => "Add the following code to " . $form_state['values']['module'] . ".install<br />If you already have a hook_install() implementation, you'll need to manually merge the 2 blocks of code.",
    );
    $form[] = array(
      '#type' => 'textarea',
      '#rows' => 30,
      '#cols' => 250,
      '#default_value' => implode("\n", $form_state['code']),
    );
  }
  else {
    $form['roles'] = array(
      '#type' => 'checkboxes',
      '#title' => 'Roles to export',
      '#options' => user_roles(TRUE),
      '#description' => t('Export all the permissions associated with roles.')
    );

    $form['module'] = array(
      '#type' => 'textfield',
      '#title' => 'Module name',
      '#description' => 'The machine name of the module, used in function names.',
      '#required' => TRUE,
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => 'Create',
    );
  }

  return $form;
}

/**
 * Form submission handler for export_roles_permissions_form().
 */
function export_roles_permissions_form_submit($form, &$form_state) {
  $code = array();
  $roles = user_roles(TRUE);

  $code[] = '/**';
  $code[] = ' * Implements hook_install().';
  $code[] = ' */';
  $code[] = 'function ' . $form_state['values']['module'] . '_install() {';

  foreach ($form_state['values']['roles'] as $rid) {
    if ($rid != 0) {
      $code[] = '  $role = export_roles_permissions_user_role_load_by_name(\'' . $roles[$rid] . '\');';
      $code[] = '  // Add the permissions to the role.';
      $code[] = '  $permissions = array(';

      $perms = export_roles_permissions_get_role_permissions(array($rid => $rid));
      foreach ($perms[$rid] as $perm) {
        $code[] = "    '" . trim($perm) . "',";
      }

      $code[] = '  );';
      $code[] = '  export_roles_permissions_grant_permissions($role->rid, $permissions);';
      $code[] = '';
    }
  }

  array_pop($code);
  $code[] = '}';

  $form_state['code'] = $code;
  $form_state['rebuild'] = TRUE;
}
