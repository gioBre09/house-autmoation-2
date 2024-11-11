#include <Espalexa.h> // Libreria per la compatibilità con Alexa
#include <ESP8266WiFi.h> // Libreria Wi-Fi per ESP8266 (o usa <WiFi.h> per ESP32)

// Credenziali Wi-Fi
const char* ssid = "IlTuoSSID";
const char* password = "LaTuaPassword";

// Definisci il pin del relè
#define RELAY_PIN D1 // Pin dove è collegato il relè

// Crea un'istanza di Espalexa
Espalexa espalexa;

// Variabile per lo stato della luce
bool lightOn = false;

// Funzione di callback per cambiare lo stato della luce
void lightChanged(uint8_t brightness) {
    if (brightness == 0) {
        lightOn = false;
        digitalWrite(RELAY_PIN, LOW); // Spegne la luce
    } else {
        lightOn = true;
        digitalWrite(RELAY_PIN, HIGH); // Accende la luce
    }
    Serial.println(lightOn ? "Luce Accesa" : "Luce Spenta");
}

void setup() {
    Serial.begin(115200);
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW); // Spegne la luce all'avvio

    // Connessione al Wi-Fi
    WiFi.begin(ssid, password);
    Serial.print("Connessione a Wi-Fi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connesso!");

    // Configura Espalexa con la funzione di callback
    espalexa.addDevice("Luce Salotto", lightChanged);

    // Inizializza Espalexa
    espalexa.begin();
}

void loop() {
    // Mantiene attiva la connessione con Alexa
    espalexa.loop();
}
