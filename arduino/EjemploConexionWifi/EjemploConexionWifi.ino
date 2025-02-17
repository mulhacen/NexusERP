#include <ESP8266WiFi.h>

// Configuración de la red WiFi
const char* ssid = "HOOK";       
const char* password = "contraseña"; 

void setup() {
  // Iniciar comunicación puerto serie
    Serial.begin(115200); 
    
    WiFi.begin(ssid, password); 
    Serial.print("Conectando a WiFi");

    // Esperar hasta que se conecte
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConectado a WiFi!");
    Serial.print("Dirección IP: ");
     // Mostrar la IP asignada
    Serial.println(WiFi.localIP());
    Serial.print("Dirección MAC: ");
    Serial.println(WiFi.macAddress() );
}

void loop() {
    // Verificar si aún está conectado
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Conexión perdida, reconectando...");
        WiFi.disconnect();
        WiFi.begin(ssid, password);
    }
    // Verifica la conexión cada 5 segundos
    delay(5000); 
}