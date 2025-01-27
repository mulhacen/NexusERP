#include <SoftwareSerial.h>

//GPS tx -> Arduino rx (1) 
//GPS rx -> Arduino tx (3)
int RXPin = 4; // Pin Rx de Arduino
int TXPin = 3; // Pin Tx de Arduino

int GPSBaud = 9600; // Velocidad del puerto serie

SoftwareSerial gpsSerial(RXPin, TXPin);

void setup(){
  Serial.begin(9600); // Monitor serie
  gpsSerial.begin(GPSBaud); // Comunicación con NEO-6
}

void loop(){
// La información recuperada y que será visible en el monitor serie
// son sentencias NMEA (formato estándar para GPS)
  while (gpsSerial.available() > 0)
    Serial.write(gpsSerial.read());
}