<?PHP

header('Content-type: text/plain; charset=utf8', true);

function check_header($name, $value = false)
{
    if (!isset($_SERVER[$name])) {
        return false;
    }
    if ($value && $_SERVER[$name] != $value) {
        return false;
    }
    return true;
}

function sendFile($path)
{
    header($_SERVER["SERVER_PROTOCOL"] . ' 200 OK', true, 200);
    header('Content-Type: application/octet-stream', true);
    header('Content-Disposition: attachment; filename=' . basename($path));
    header('Content-Length: ' . filesize($path), true);
    header('x-MD5: ' . md5_file($path), true);
    readfile($path);
}

if (!check_header('HTTP_USER_AGENT', 'ESP8266-http-Update')) {
    header($_SERVER["SERVER_PROTOCOL"] . ' 403 Forbidden', true, 403);
    // echo "User-Agent:"+$_SERVER["User-Agent"];
    // var_dump($_SERVER);
    echo "only for igarden updater!\n";
    exit();
}
/*
if(
!check_header('x-ESP8266-STA-MAC') ||
!check_header('x-ESP8266-AP-MAC') ||
!check_header('x-ESP8266-free-space') ||
!check_header('x-ESP8266-sketch-size') ||
!check_header('x-ESP8266-sketch-md5') ||
!check_header('x-ESP8266-chip-size') ||
!check_header('x-ESP8266-sdk-version')
) {
header($_SERVER["SERVER_PROTOCOL"].' 403 Forbidden', true, 403);
echo "only for ESP8266 updater! (header)\n";
exit();
}
$db = array(
"18:FE:AA:AA:AA:AA" => "DOOR-7-g14f53a19",
"18:FE:AA:AA:AA:BB" => "TEMP-1.0.0",
"84:1F:E7:16:4B:AF" => "firmware"
);
if(!isset($db[$_SERVER['x-ESP8266-STA-MAC']])) {
header($_SERVER["SERVER_PROTOCOL"].' 500 ESP MAC not configured for updates', true, 500);
}
$localBinary = "./bin/".$db[$_SERVER['x-ESP8266-STA-MAC']].".bin";
*/
//Location of firmware file on http serer
$localBinary = "./bin/lastestFirmware.bin";


// Check if version has been set and does not match, if not, check if
// MD5 hash between local binary and ESP8266 binary do not match if not.
// then no update has been found.
/*if((!check_header('x-ESP8266-sdk-version') && $db[$_SERVER['x-ESP8266-STA-MAC']] != $_SERVER['x-ESP8266-version'])
    || $_SERVER["x-ESP8266-sketch-md5"] != md5_file($localBinary)) {
    sendFile($localBinary);
} else {
    header($_SERVER["SERVER_PROTOCOL"].' 304 Not Modified', true, 304);
}

header($_SERVER["SERVER_PROTOCOL"].' 500 no version for ESP MAC', true, 500);*/
/*$cliente = curl_init();
curl_setopt($cliente, CURLOPT_URL, "http://"+SERVER_NAM);
curl_setopt($cliente, CURLOPT_HEADER, 0);
curl_exec($cliente);
curl_close($cliente);
*/
//$fp = fopen("archivo.txt", "w");
$mac = $_SERVER['HTTP_X_ESP8266_AP_MAC'];
$mac = str_replace(":","",$mac);
//fwrite($fp, "MAC->".$mac."\n");
if ($mac!="") {
  /*  $url = "http://igarden.mulhacen.net/api/device/show/".$mac;
    $client = curl_init();
    curl_setopt($client, CURLOPT_URL, $url);
curl_setopt($client, CURLOPT_HEADER, true);    // we want headers
curl_setopt($client, CURLOPT_NOBODY, true);    // we don't need body
    curl_setopt($client, CURLOPT_HTTPGET,true);
    curl_setopt($client, CURLOPT_SAFE_UPLOAD, true); // requerido a partir de PHP 5.6.0
    curl_exec($client);
    $code = curl_getinfo($client, CURLINFO_HTTP_CODE);
    curl_close($client);
   fwrite($fp, "CODE HTTP->".$code."\n");
    switch ($code) {
        case 200: //http response ok    */     
           if ($_SERVER["HTTP_X_ESP8266_SKETCH_MD5"] != md5_file($localBinary)) {
                sendFile($localBinary);
             } else {
               header($_SERVER["SERVER_PROTOCOL"] . ' 304 Not Modified', true, 304);
         }
        /*    break;
        case 404: //http response ok
            header($_SERVER["SERVER_PROTOCOL"] . ' 404 Not found igarden device', true, 404);
            break;
        default:
            header($_SERVER["SERVER_PROTOCOL"] . ' 500 no version for igarden device mac', true, 500);
            break;
    }*/
} else {
    header($_SERVER["SERVER_PROTOCOL"] . ' 500 no version for igarden device mac', true, 500);
}
fclose($fp);
/*if((!check_header('x-ESP8266-sdk-version') && $db[$_SERVER['x-ESP8266-STA-MAC']] != $_SERVER['x-ESP8266-version'])
|| $_SERVER["x-ESP8266-sketch-md5"] != md5_file($localBinary)) {
sendFile($localBinary);
} else {
header($_SERVER["SERVER_PROTOCOL"].' 304 Not Modified', true, 304);
}*/
//header($_SERVER["SERVER_PROTOCOL"].' 500 no version for ESP MAC', true, 500);

/*
Header EXAMPLE
HTTP_X_ESP8266_CHIP_ID = '13716566'
HTTP_X_ESP8266_STA_MAC = '08:3A:8D:D1:4C:56'
HTTP_X_ESP8266_AP_MAC = '0A:3A:8D:D1:4C:56'
HTTP_X_ESP8266_FREE_SPACE = '1781760'
HTTP_X_ESP8266_SKETCH_SIZE = '313024'
HTTP_X_ESP8266_SKETCH_MD5 = '8e55372bad18ef64419e2484b9277d67'
HTTP_X_ESP8266_CHIP_SIZE = '4194304'
HTTP_X_ESP8266_SDK_VERSION = '2.2.2-dev(38a443e)'
HTTP_X_ESP8266_MODE = 'sketch'
*/