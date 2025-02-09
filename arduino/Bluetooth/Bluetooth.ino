#include <SoftwareSerial.h>

SoftwareSerial mySerial(14, 12); // RX, TX

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  delay(100);
  mySerial.begin(9600);
  delay(100);
  mySerial.print("AT\r\n");
  delay(100);
  mySerial.print("AT+VERSION\r\n");
  delay(100);
  mySerial.print("AT+NAME\r\n");
  delay(100);
  mySerial.print("AT+PIN\r\n");
  delay(100);
  mySerial.print("AT+HELP\r\n");
  delay(100);

}

void loop() { // run over and over
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
    }
}