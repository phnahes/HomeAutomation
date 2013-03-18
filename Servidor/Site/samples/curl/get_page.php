<?php
//
// Paulo Nahes
// Exemplo de uso da lib para requisicao de paginas (curl)
//

require("lib/curl.php");

$curl_data = "var1=60&var2=test"; 
$url = "http://hangout.nahes.com.br"; 
$response = get_web_page($url,$curl_data); 

#print '<pre>'; 
print_r($response); 

?>
