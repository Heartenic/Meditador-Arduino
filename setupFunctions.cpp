// -----------------------------------------------------------------
// setupFunctions.cpp
//
// Funciones para el setup del dispositivo (cada vez que se enciende)
//
// NVS (para el guardado persistente de datos), Modem Sleep (ahorro de energía),
// y configuración del display OLED
//
// -----------------------------------------------------------------

#include "setupFunctions.h"

// Definición de variables globales
Preferences preferences; // Objeto para manejar NVS
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
uint32_t persistentBreathCounter = 0; // Contador persistente

// Constante para la dirección del OLED
constexpr uint8_t OLED_ADDRESS = 0x3C;

void setModemSleep() {
    WiFi.mode(WIFI_OFF);    // Apagar WiFi
    btStop();               // Apagar Bluetooth
    setCpuFrequencyMhz(40); // Reducir la frecuencia del CPU (máx. 160)
}

void setupDisplay() {
    Wire.begin(OLED_SDA, OLED_SCL);                // Inicializar I2C para OLED
    display.begin(SSD1306_PAGEADDR, OLED_ADDRESS); // Iniciar el display con la dirección definida
    display.clearDisplay();                        // Limpiar el buffer del display
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.display();                             // Actualizar el display
}

void setupNVS() {
    preferences.begin("storage", false);                   // Inicializar NVS
    persistentBreathCounter = preferences.getUInt("breaths", 0); // Cargar el contador
}