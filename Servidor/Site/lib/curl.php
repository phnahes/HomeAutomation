<?php 
//
// Paulo Nahes
// Funcao para requisitar uma URL (necessita do modulo php5-curl)
//

function get_web_page( $url,$curl_data ) 
{ 
	$options = array( 
			CURLOPT_RETURNTRANSFER => true,				// return web page 
			CURLOPT_HEADER         => false,        		// don't return headers 
			CURLOPT_FOLLOWLOCATION => false,         		// follow redirects 
			CURLOPT_ENCODING       => "",           		// handle all encodings 
			CURLOPT_USERAGENT      => "HomeAutomationServer",     	// who am i 
			CURLOPT_AUTOREFERER    => true,         		// set referer on redirect 
			CURLOPT_CONNECTTIMEOUT => 120,          		// timeout on connect 
			CURLOPT_TIMEOUT        => 120,          		// timeout on response 
			CURLOPT_MAXREDIRS      => 1,            		// stop after 10 redirects 
			CURLOPT_POST           => 1,            		// i am sending post data 
			CURLOPT_POSTFIELDS     => $curl_data,   		// this are my post vars 
			CURLOPT_SSL_VERIFYHOST => 0,            		// don't verify ssl 
			CURLOPT_SSL_VERIFYPEER => false,        		// don't verify ssl
			CURLOPT_VERBOSE        => 0             		// enable/disable verbose
			); 

	$ch      = curl_init($url); 
	curl_setopt_array($ch,$options); 
	$content = curl_exec($ch); 
	$err     = curl_errno($ch); 
	$errmsg  = curl_error($ch) ; 
	$header  = curl_getinfo($ch); 
	curl_close($ch); 

	//  $header['errno']   = $err; 
	//  $header['errmsg']  = $errmsg; 
	//  $header['content'] = $content; 
	//   return $header; 
	return $content;
} 

/*
$curl_data = "var1=60&var2=test"; 
$url = "https://www.example.com"; 
$response = get_web_page($url,$curl_data); 

print '<pre>'; 
print_r($response); 
*/

?>
