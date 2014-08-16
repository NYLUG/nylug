<?php

$aliases['dev'] = array(
  'root' => '/home/nylug.org',
  'uri' => 'nylug',
  'path-aliases' =>
    array (
      '%drush' => '/usr/share/drush',
      '%drush-script' => '/usr/bin/drush',
      '%dump-dir' => '/tmp',
      '%dump' => '/tmp/nylug-dump.sql',
    ),
  'databases' =>
    array (
      'default' =>
        array (
          'default' =>
            array (
              'driver' => 'mysql',
              'username' => 'nylug_db_usr',
              'password' => 'BYXSbRZPp9Kt9h/AXR7',
              'host' => 'localhost',
              'database' => 'nylug_db',
            ),
        ),
    ),
);
$aliases['prod'] = array(
  'root' => '/var/www/nylug',
  'uri' => 'dev1.nylug.org',
  'remote-host' => 'dev1.nylug.org',
  'remote-user' => 'nylug.org',
  'ssh-options' => '-i /home/nylug.org/.ssh/id_nylug_rsa',
  'path-aliases' => 
    array (
      '%drush' => '/usr/share/php/likewhoa-drush',
      '%drush-script' => '/usr/bin/drush',
      '%dump-dir' => '/tmp',
      '%dump' => '/tmp/nylug-dump.sql',
    ),
  'databases' => 
    array (
      'default' =>
        array (
          'default' =>
	    array (
	      'driver' => 'mysql',
	      'username' => 'nylug_db_usr',
	      'password' => 'BYXSbRZPp9Kt9h/AXR7',
              'host' => 'localhost',
	      'database' => 'nylug_db',
	    ),
        ),
    ),   
);  

