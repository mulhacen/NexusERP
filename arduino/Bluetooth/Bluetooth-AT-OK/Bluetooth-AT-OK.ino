#include <SoftwareSerial.h>

SoftwareSerial ble(14, 12); // RX, TX
char caracter;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("Imprime en Serial Monitor");

  ble.begin(9600);
  ble.println("Imprime en el movil");

  ble.write("AT+NAME\r\n");
  

}

void loop() { // run over and over
    //ble.println("Leido de serie y enviado a ble:");
//    while(Serial.available()){
  if(Serial.available()){
      //caracter = Serial.read();
      ble.write(Serial.read());
    }
    //ble.println("\n");
    //Serial.println("Leido de BLE y enviado a serie:");
    //while(ble.available()){
    if(ble.available()){
     // caracter = ble.read();
      Serial.write(ble.read());
    }
    //Serial.println("\n");

}