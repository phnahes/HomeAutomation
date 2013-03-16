<?php
//
// Paulo Nahes
// Exemplo de GET no memcached
//

require("lib/memcached.php"); // Inclui biblioteca de conexao com memcached

$prefix = "web_"; // Prefixo para chave

	$item = "luz";
	$name_full = "$prefix" . "$item"; // Junta prefixo com Variavel retornada do Banco

	$var = memcache_get($memcache_obj, "$name_full"); // Procura no Memcache por chave especifica no caso: "web_luz"

	print "$var\n\n"; // debug
}

?>

