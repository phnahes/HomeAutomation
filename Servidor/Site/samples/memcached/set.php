<?php
//
// Paulo Nahes
// Exemplo de SET no memcached
//

require("lib/memcached.php"); // Inclui biblioteca de conexao com memcached

$name = $_GET['name']; // Nome da Chave
$value = $_GET['value']; // Valor da Chave
$name_full = ("web_" . "$name");  // variavel para adicionar prefixo 

memcache_set($memcache_obj, "$name_full", "$value_full", 0, 0); // Parametros definem que chave nunca expira

# Verifica valor inserido
#echo memcache_get($memcache_obj, "$name_full");

//header("Location: index.php");  // Caso utilizado por uma Pagina, usuario e enviado para algum lugar apos SET no memcached. (neste caso nao necessario)

?>

