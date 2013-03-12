<?php
//
// Paulo Nahes
// Exemplo de SET no memcached
//

require("memcached.php");

$name = $_GET['name']; // Nome da Chave
$value = $_GET['value']; // Valor da Chave
$name_full = ("web_" . "$name");  // variavel para adicionar prefixo 

memcache_set($memcache_obj, "$name_full", "$value_full", 0, 0); // Parametros definem que chave nunca expira

# Verifica valor inserido
#echo memcache_get($memcache_obj, "$name_full");

//header("Location: index.php");  // Caso utilizado por uma Pagina, usuario e enviado para algum lugar apos SET no memcached. (neste caso nao necessario)

?>

