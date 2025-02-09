#include <SoftwareSerial.h>

SoftwareSerial ble(14, 12); // RX, TX
char caracter;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);


  ble.begin(9600);
  Serial.println("Version 7 - IDE");
  ble.println("Version 7 - Movil");

  ble.write("AT+NAME\r\n");
  

}

void loop() { // run over and over
 //  Serial.println("Leido de serie y enviado a ble:");
    while(Serial.available()){
 // if(Serial.available()){
      caracter = Serial.read();
      ble.write(caracter);
    }
    //ble.println("\n");
   // Serial.println("Leido de BLE y enviado a serie:");
    while(ble.available()){
    //if(ble.available()){
      caracter = ble.read();
      Serial.write(caracter);
    }
    //Serial.println("\n");

}