<?php

//
// Paulo Nahes
// Biblioteca para conexao com Memcached (Simples)
//

$memcached_host = "localhost";
$memcached_port = "11211";

$Memcached = new Memcached();
$Memcached->addServer($memcached_host, $memcached_port);

#$memcache_obj = memcache_connect("$memcached_host", "$memcached_port");

?>

