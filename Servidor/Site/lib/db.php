<?php

include ("credentials.php");

#$host = "localhost";
#$user = "";
#$pass = "";
#$bd = "str_report";

// Mensagens de Erro
$msg[0] = "Conexão com o banco falhou!";
$msg[1] = "Não foi possível selecionar o banco de dados!";

// Fazendo a conexão com o servidor MySQL
$conexao = mysql_connect("$host","$user","$pass") or die($msg[0]);
mysql_select_db("$bd",$conexao) or die($msg[1]);

?>
