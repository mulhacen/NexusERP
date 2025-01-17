#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266httpUpdate.h>
#include <ESP8266HTTPClient.h>

//FIRMWARE version
#define FIRMWARE_VERSION "1.03"
/************************ NETWORK CONFIGURATION ************************/
//WIFI Settings: SSID&PASS
#ifndef APSSID
#define APSSID "HOOK"
#define APPSK  "NRWN6gh1U"
#endif
// Net Identity
const char* userAgentDevice = "igarden-IoT-Device/";
//Mac of Device (whitout :)
String mac;

/************************ IRRIGATION CONFIGURATION ************************/
unsigned int  pinsSensors[] = {0,1,2,3,4};// Analogs pins
unsigned char pinsPumps[] = {D3, D4, D5, D6, D7};//Digital pins
unsigned lastSensRead[] = {0,0,0,0,0};//last reeding sensors
int lowHumidityLevel = 400;// humidity value when to irrigate
int secondsIrrigation = 30;// seconds pump irrigation

/************************ SERVER CONFIGURATION ***************************/
//URL API Server
const char* serverApiName = "http://igarden.mulhacen.net/api/";
//Frequency to report data to server (segundos)
const int frequency = 1800;// 600 seconds -> 10 minutes
//PORT Webserver Local - Local request
ESP8266WebServer server(80);


void setup() {
  Serial.begin(115200);  //Baudrate
 //All pins out and set to low(off)
  inicializationPumps();

  Serial.println("\niGarden Device Starting...");

  WiFi.begin(APSSID, APPSK);
  Serial.print("Conecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {  //Loop which makes a point every 500ms until the connection process has finished
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Conectado! IP-Address: ");
  Serial.println(WiFi.localIP());  //Displaying the IP Address

  //Extract MAC address
  mac = direccionMac();
  //define hostname
  WiFi.setHostname(("IGAR"+mac.substring(7)).c_str()); 

  // Show Firmware Version Device
  Serial.print(F("Firmware version "));
  Serial.println(FIRMWARE_VERSION);
  delay(2000);
 
  /** Functions for webserver LOCAL**/
  /*
  if (MDNS.begin("nerd-corner")) {
    Serial.println("DNS started, available with: ");
    Serial.println("http://igarden.local/");
  }
  server.onNotFound([]() {
    server.send(404, "text/plain", "Link was not found!");
  });

  server.on("/", []() {
    server.send(200, "text/plain", "Landing page!");
  });

  server.on("/on", []() {
    server.send(200, "text/plain", "Switching LED on!");
    switchLedOn();
  });
  server.on("/off", []() {
    server.send(200, "text/plain", "Switching LED off!");
    switchLedOff();
  });
  server.begin();
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);*/


 
}

void loop() {

  // Wakeup and conecting WIFI
  WiFi.mode(WIFI_STA);
  WiFi.begin (APSSID, APPSK );
  while (WiFi.status() != WL_CONNECTED) {  //Loop which makes a point every 500ms until the connection process has finished
    delay(500);
    Serial.print(".");
  }

  // start server
  //server.handleClient();
  //MDNS.update();
   Serial.println("Sensor humedad:"+String(analogRead(0)));

  //Check for firmware updates
  //checkForUpgradeFirmware() ;

  // IF WiFi connection is connected
  if ((WiFi.status() == WL_CONNECTED)) {
    //CheckForUpgradeFirmware
    Serial.println("Check for firmware update...");
    checkForUpgradeFirmware();
    // Check if device is installed
    if (isInstallDevice()) {
      Serial.println("Device " + mac + " is INSTALLED!!");
      //update the device installation
      updateDevice();
      Serial.println("Device " + mac + "  update to Server!!");
      checkSensorAndSubmit();
      //check for irrigation
      checkSensorAndIrrigation();
    } else {  //Install device
      Serial.println("Attemp to install...");
      if (installDevice()) {
        Serial.println("Device " + mac + " is now installed!!");
      }
    }
  } else {
    Serial.println("Not connected to WIFI");
  }
  //Shutting down wifi
  WiFi.disconnect();
  delay(1);
  WiFi.mode( WIFI_OFF );
  delay(1);

  //Entering on DeepSleep
  Serial.println("Entering on DeepSleep...");
  //Only wake up each 10 minutes
  // For this work, is mandatory pin "RST" is connected with "D0"
  ESP.deepSleep(frequency * 1000000);// more energy efficient
  Serial.println("...WakeUp!!");
}

void switchLedOff() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the D1 LED off
}
void switchLedOn() {
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED on
}

boolean isInstallDevice() {
  boolean install = false;
  HTTPClient http;

  WiFiClient client;
  //Set userAgent
  http.setUserAgent(userAgentDevice+ String("v"+String(FIRMWARE_VERSION)+"/") + direccionMac());

  // configure traged server and url
  http.begin(client, "http://igarden.mulhacen.net/api/device/show/" + direccionMac());  // HTTP
  http.addHeader("Content-Type", "application/json");

  // start connection and send HTTP header and body
  int httpCode = http.GET();
  // if status 200
  if (httpCode == 200) {
    install = true;
  }

  http.end();
  return install;
}

boolean installDevice() {
  boolean install = false;
  HTTPClient http;

  WiFiClient client;
  //Set userAgent
  http.setUserAgent(userAgentDevice+ String("v"+String(FIRMWARE_VERSION)+"/") + direccionMac());

  // configure traged server and url
  http.begin(client, "http://igarden.mulhacen.net/api/device/add/");  // HTTP
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Data to send with HTTP POST
  String httpRequestData = "mac=" + direccionMac() + "&latitude=0&longitude=0&frequency=10";
  // Send HTTP POST request
  int httpCode = http.POST(httpRequestData);
  // if status 200
  if (httpCode == 200) {
    install = true;
  } else {
    install = false;
  }

  http.end();
  return install;
}

boolean updateDevice() {
  boolean update = false;
  HTTPClient http;

  WiFiClient client;
  //Set userAgent
  http.setUserAgent(userAgentDevice+ String("v"+String(FIRMWARE_VERSION)+"/") + direccionMac());

  // configure traged server and url
  http.begin(client, "http://igarden.mulhacen.net/api/device/update/");  // HTTP
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Data to send with HTTP POST
  String httpRequestData = "mac=" + direccionMac() + "&latitude=0&longitude=0&frequency=10";
  // Send HTTP POST request
  int httpCode = http.POST(httpRequestData);
  // if status 200
  if (httpCode == 200) {
    update = true;
  } else {
    update = false;
  }

  http.end();
  return update;
}

boolean submitMesureSensor(int numSensor, int typeSensor, int value) {
  boolean submitted = false;
  HTTPClient http;

  WiFiClient client;
  //Set userAgent
  http.setUserAgent(userAgentDevice+ String("v"+String(FIRMWARE_VERSION)+"/") + direccionMac());

  // configure traged server and url
  http.begin(client, "http://igarden.mulhacen.net/api/mesure/add/");  // HTTP
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Data to send with HTTP POST
  String httpRequestData = "mac=" + direccionMac() + "&sensorId=" + numSensor + "&sensorType=" + typeSensor + "&value=" + value + "";
  // Send HTTP POST request
  int httpCode = http.POST(httpRequestData);
  // if status 200
  if (httpCode == 200) {
    submitted = true;
  } else {
    submitted = false;
  }

  http.end();
  return submitted;
}

void checkSensorAndIrrigation() {
  for (int i = 0; i < 5; i++) {
    if (lastSensRead[i] > lowHumidityLevel) {
      submitMesureSensor(i, 3, 1);
      startIrrigationPump(i, secondsIrrigation);
      submitMesureSensor(i, 3, 0);
    }
  }
}

void startIrrigationPump(int numPump, int seconds) {
  Serial.println("Regando "+String(numPump) + " salida:"+String(pinsPumps[numPump]));
  digitalWrite(pinsPumps[numPump], 0);
  delay(seconds * 1000);
  digitalWrite(pinsPumps[numPump], 1);
}

int checkSensorAndSubmit() {
  int numSensor = 0;  //number of sensors whith non-zero value
  int value = 0;
  for (int i = 0; i < sizeOfArrayInt(pinsSensors); i++) {
    value = analogRead(pinsSensors[i]);
    //Serial.println("Sensor "+String(pinsSensors[i])+" value:"+String(value));
    if (value > 5 && value < 1022) {  // avoid false positives
      lastSensRead[i] = value;
      submitMesureSensor(pinsSensors[i], 2, value);  //humidity type 2
      Serial.println("\nSubmitted!! Sensor " + String(pinsSensors[i]) + " value:" + String(value));
      numSensor++;
    }
  }
  Serial.println("\n\nReported " + String(numSensor) + " sensor reads");
  return numSensor;
}

String direccionMac() {
  //Extraemos la mac del dispositivo
  String mac = WiFi.softAPmacAddress();
  //Quitamos los :
  mac.replace(":", "");
  return mac;
}


int sizeOfArrayInt(unsigned int array[]) {
  return (sizeof(array) / sizeof(array[0]));
}
int sizeOfArrayChar(unsigned char array[]) {
  return (sizeof(array) / sizeof(array[0]));
}

void inicializationPumps() {
  for (int i = 0; i < sizeOfArrayChar(pinsPumps); i++) {
    Serial.print("\nPut OUTPUT mode on digitalpin -> " + String(pinsPumps[i]));
    pinMode(pinsPumps[i], OUTPUT);
    digitalWrite(pinsPumps[i], 1);
  }
}

  /**Functions for manage upgrade firmware**/
  void update_started() {
  Serial.println("CALLBACK:  HTTP update process started");
}
 
void update_finished() {
  Serial.println("CALLBACK:  HTTP update process finished");
}
 
void update_progress(int cur, int total) {
  Serial.printf("CALLBACK:  HTTP update process at %d of %d bytes...\n", cur, total);
}
 
void update_error(int err) {
  Serial.printf("CALLBACK:  HTTP update fatal error code %d\n", err);
}


void checkForUpgradeFirmware() {
   WiFiClient client;
    // Add optional callback notifiers
    ESPhttpUpdate.onStart(update_started);
    ESPhttpUpdate.onEnd(update_finished);
    ESPhttpUpdate.onProgress(update_progress);
    ESPhttpUpdate.onError(update_error);
    
 
    ESPhttpUpdate.rebootOnUpdate(false); // remove automatic update
 
    Serial.println(F("Update start now!"));
 
 t_httpUpdate_return ret = ESPhttpUpdate.update(client, "http://igarden.mulhacen.net/api/device/firmware/update/");
     //t_httpUpdate_return ret = ESPhttpUpdate.update(client, "http://igarden.mulhacen.net/api/device/firmware/bin/lastestFirmware.bin");
    // Or:
  // t_httpUpdate_return ret = ESPhttpUpdate.update(client, "http://192.168.1.150/igarden/api", 80, "/device/firmware/update/", FIRMWARE_VERSION);
 
    switch (ret) {
      case HTTP_UPDATE_FAILED:
        Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
        Serial.println(F("Retry in 10secs!"));
        delay(10000); // Wait 10secs
        break;
 
      case HTTP_UPDATE_NO_UPDATES:
        Serial.println("HTTP_UPDATE_NO_UPDATES");
        Serial.println("Your code is up to date!");
          delay(10000); // Wait 10secs
        break;
 
      case HTTP_UPDATE_OK:
        Serial.println("HTTP_UPDATE_OK");
        delay(1000); // Wait a second and restart
        ESP.restart();
        break;
    }
}
  