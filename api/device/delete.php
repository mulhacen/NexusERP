<?php
$requestMethod = $_SERVER["REQUEST_METHOD"];
include('../class/Rest.php');
$api = new Rest();
switch($requestMethod) {
	case 'GET':
		$devMac = '';	
		if($_GET['mac']) {
			$devMac = $_GET['mac'];
		}
		$api->deleteDevice($devMac);
		break;
	default:
	header("HTTP/1.0 405 Method Not Allowed");
	break;
}
?>