<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function cable_broadcast_import_user_default_permissions() {
  $permissions = array();

  // Exported permission: clear cable_broadcast feeds
  $permissions['clear cable_broadcast feeds'] = array(
    'name' => 'clear cable_broadcast feeds',
    'roles' => array(
      '0' => 'Web Editor+',
      '1' => 'admin',
    ),
  );

  // Exported permission: import cable_broadcast feeds
  $permissions['import cable_broadcast feeds'] = array(
    'name' => 'import cable_broadcast feeds',
    'roles' => array(
      '0' => 'Media Services',
      '1' => 'Web Editor+',
      '2' => 'admin',
    ),
  );

  return $permissions;
}
