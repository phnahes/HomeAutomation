<?php
/*
*
* Polling Page - Include Other Components
*
*/
?>

<?php
	/* Include Configs */
	include ("config/general.php");
	include ("lib/curl.php");
	include ("lib/memcached.php");
?>

<?php
	$curl_data = ""; 
	$response = get_web_page($url_status,$curl_data); 
	#print_r($response);  // used to debug

	/* Read XML */
	$xml = simplexml_load_string($response); 
	#print_r($xml); // used to debug

?>

<?php

#	$disp = $xml->disp[$ID]->id; 
#	print_r($disp);

	$oXML = new SimpleXMLElement($response);

	foreach($oXML->disp as $Disps){
		echo "Device: " . $Disps->id . " ";
		echo "Status: " . $Disps->status . "\n";

		$mKey = "Dev_$Disps->id" ;
		$mValue = "$Disps->status";

		#echo $mKey . " " . $mValue . "\n";
		$Memcached->set($mKey, $mValue, 0);

		echo "checking...\n";
		echo "Key $mKey :: Value " . $Memcached->get("$mKey"); 
	}
?>

<?php
	/* Criar conexãcom banco e tabelas */
?>
