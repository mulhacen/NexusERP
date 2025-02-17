#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Configuración de la red WiFi
const char* ssid = "SSIDredWifi";        
const char* password = "PasswordWifi";

// URL del servidor que contiene la api de subir datos
const char* server = "http://ejemplo.com/api"; 

void setup() {
    //Iniciamos comunicacion serie a 115200 baudios
    Serial.begin(115200); 

    // Conectar a WiFi
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

    // Hacer petición HTTP GET después de conectar
    sendHttpRequest();
}

void loop() {
    // Verificar si aún está conectado
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Conexión perdida, reconectando...");
        WiFi.disconnect();
        WiFi.begin(ssid, password);
    }

    delay(10000); // Realizar petición cada 10 segundos
    sendHttpRequest();
}

// Función para realizar una petición HTTP GET
void sendHttpRequest() {
    // Verificamos conexión WiFi OK
    if (WiFi.status() == WL_CONNECTED) {  
        HTTPClient http;
        
        // URL con parámetro GET
        String url = String(server) + "?parametro=valor"; 
        Serial.print("Solicitando: ");
        Serial.println(url);
        
        //Iniciamos conexion y realizamos peticion
        http.begin(url); 
        int httpCode = http.GET();

        //Comprobamos el codigo devuelto en la peticion
        if (httpCode > 0) { // Si la petición es exitosa
            String payload = http.getString(); // Obtener respuesta del servidor
            Serial.println("Respuesta del servidor:");
            Serial.println(payload);
        } else {
            Serial.println("Error en la petición HTTP");
        }
        //Cerramos conexion
        http.end(); 
    } else {
        Serial.println("No conectado a WiFi");
    }
}