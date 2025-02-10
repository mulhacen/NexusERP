#include <SoftwareSerial.h>

SoftwareSerial ble(14, 12); // RX, TX (GPIO no etiqueta placa)
char caracter;

void setup() {
  // Instancia Serie Consola IDE
  Serial.begin(9600);
  // Instancia Serie Modulo Bluetooth
  ble.begin(9600);
  // Imprimo y se muetra en la consola IDE - (Peticiones)
  Serial.println("Version 8 - IDE");
  // Imprimo y se muetra en el modulo bluetooth - (Respuestas)
  ble.println("Version 8 - Movil");
  // Peticion Nombre
  ble.write("AT+NAME\r\n");
}

void loop() { // run over and over
    //Bucle para leer de la consola del IDE Arduino(Serial) y enviaro al modulo bluetooth(ble)
    while(Serial.available()){
      caracter = Serial.read();
      ble.write(caracter);
    }
    //Bucle para leer del modulo bluetooth(ble) y mostrarlo en la consola del IDE(Serial)
    while(ble.available()){
      caracter = ble.read();
      Serial.write(caracter);
    }

}