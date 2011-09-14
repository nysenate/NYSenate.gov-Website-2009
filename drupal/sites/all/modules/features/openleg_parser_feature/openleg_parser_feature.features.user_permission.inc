<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function openleg_parser_feature_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer feeds
  $permissions['administer feeds'] = array(
    'name' => 'administer feeds',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: clear openleg feeds
  $permissions['clear openleg feeds'] = array(
    'name' => 'clear openleg feeds',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: import openleg feeds
  $permissions['import openleg feeds'] = array(
    'name' => 'import openleg feeds',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  return $permissions;
}
