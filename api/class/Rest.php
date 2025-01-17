<?php
class Rest{
	//Configuration for Acces to DB
    private $host  = 'localhost';
    private $user  = 'sge_user';
    private $password = 'nexusERPGRX25';
    private $database  = 'sge_nexus-erp';      
    private $devTable = 'erp_devices';	
    private $mesTable = 'erp_mesures';	
	private $dbConnect = false;

	public function __construct(){
        if(!$this->dbConnect){ 
            $conn = new mysqli($this->host, $this->user, $this->password, $this->database);
            if($conn->connect_error){
                die("Error failed to connect to MySQL: " . $conn->connect_error);
            }else{
                $this->dbConnect = $conn;
            }
        }
    }

	private function getData($sqlQuery) {
		$result = mysqli_query($this->dbConnect, $sqlQuery);
		if(!$result){
			die('Error in query: '. mysqli_error());
		}
		$data= array();
		while ($row = mysqli_fetch_array($result, MYSQL_ASSOC)) {
			$data[]=$row;            
		}
		return $data;
	}
	private function getNumRows($sqlQuery) {
		$result = mysqli_query($this->dbConnect, $sqlQuery);
		if(!$result){
			die('Error in query: '. mysqli_error());
		}
		$numRows = mysqli_num_rows($result);
		return $numRows;
	}

/****************************************************** */
/** 				DEVICE  METHODS 					*/
/****************************************************** */
	// we get the device attributes from its mac
	public function showDevice($devMac) {		
		$sqlQuery = '';
		if($devMac) {
			$sqlQuery = "WHERE mac = '".$devMac."'";
		}	
		$empQuery = "
			SELECT id, mac, latitude, longitude, frequency, last_connection 
			FROM ".$this->devTable." $sqlQuery
			ORDER BY id DESC";	
		$resultData = mysqli_query($this->dbConnect, $empQuery);
		$devData = array();
		while( $devRecord = mysqli_fetch_assoc($resultData) ) {
			$devData[] = $devRecord;
		}
		if(sizeof($devData) == 0){// No encontrado
			header("HTTP/1.0 404 Not found");
			echo json_encode("404 Not found device");	
		}else{
			header('Content-Type: application/json');
			echo json_encode($devData);	
		}
	}
/** Add a device to DB */
function addDevice($devData){ 		
	// receive the parameter data
	$devMac=$devData["mac"];
	$devLatitude=$devData["latitude"];
	$devLongitude=$devData["longitude"];
	$devFrequency=$devData["frequency"];		
	//  submit the query to the db server
	$devQuery="
		INSERT INTO ".$this->devTable." 
		SET mac='".$devMac."', latitude='".$devLatitude."', longitude='".$devLongitude."', frequency='".$devFrequency."'";
	if( mysqli_query($this->dbConnect, $devQuery)) {
		$message = "Device created Successfully.";
		$status = 1;			
	} else {
		$message = "Device creation failed.";
		$status = 0;			
	}
	$devResponse = array(
		'status' => $status,
		'status_message' => $message
	);
	header('Content-Type: application/json');
	echo json_encode($devResponse);
}
// we update the device's location and connection data
function updateDevice($devData){ 		
	if($devData["mac"]) {
		$devLatitude=$devData["latitude"];
		$devLongitude=$devData["longitude"];
		$devFrequency=$devData["frequency"];
		$devQuery="
			UPDATE ".$this->devTable." 
			SET latitude='".$devLatitude."', longitude='".$devLongitude."', frequency='".$devFrequency."' , last_connection=NOW()  
			WHERE mac = '".$devData["mac"]."'";
		if( mysqli_query($this->dbConnect, $devQuery)) {
			$message = "Device updated successfully.";
			$status = 1;			
		} else {
			$message = "Device update failed.";
			$status = 0;			
		}
	} else {
		$message = "Invalid request.";
		$status = 0;
	}
	$devResponse = array(
		'status' => $status,
		'status_message' => $message
	);
	header('Content-Type: application/json');
	echo json_encode($devResponse);
}
//delete a device from its mac address
public function deleteDevice($devMac) {		
	if($devMac) {			
		$devQuery = "
			DELETE FROM ".$this->devTable." 
			WHERE mac = '".$devMac."'";	
		if( mysqli_query($this->dbConnect, $devQuery)) {
			$message = "Device delete Successfully.";
			$status = 1;			
		} else {
			$message = "Device delete failed.";
			$status = 0;			
		}		
	} else {
		$message = "Invalid request.";
		$status = 0;
	}
	$devResponse = array(
		'status' => $status,
		'status_message' => $message
	);
	header('Content-Type: application/json');
	echo json_encode($devResponse);	
}

/****************************************************** */
/** 				SENSOR  METHODS 					*/
/****************************************************** */
function addMesure($mesData){ 		
	// receive the parameter data
	$mesDeviceMac=$mesData["mac"];
	//$mesDeviceId=$this->getData("SELECT id from ".$this->devTable." where mac='".$mesDeviceMac."'");
	//echo "ID ->".$mesDeviceId;
	$mesSensorId=$mesData["sensorId"];
	$mesSensorType=$mesData["sensorType"];
	$mesSensorValue=$mesData["value"];		
	//  submit the query to the db server
	$mesQuery="
		INSERT INTO ".$this->mesTable." 
		SET id_device = (SELECT id from ".$this->devTable." where mac='".$mesDeviceMac."'), id_sensor='".$mesSensorId."', id_sensor_type='".$mesSensorType."', value='".$mesSensorValue."'";
	if( mysqli_query($this->dbConnect, $mesQuery)) {
		$message = "Mesure registered Successfully.";
		$status = 1;			
	} else {
		$message = "Mesure registration failed.";
		$status = 0;			
	}
	$devResponse = array(
		'status' => $status,
		'status_message' => $message
	);
	header('Content-Type: application/json');
	echo json_encode($devResponse);
}

}

?>