#ifndef SETUPFUNCTIONS_H
#define SETUPFUNCTIONS_H

#include <WiFi.h>
#include <esp_bt.h>
#include <Preferences.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

// Pines para el display OLED
#define OLED_SDA 7 // 6 en C6  -  7 en C3
#define OLED_SCL 9 // 6 en C6  -  9 en C3
#define SCREEN_WIDTH 128  // Resolución X del display
#define SCREEN_HEIGHT 64  // Resolución Y del display

// Declaraciones de funciones
void setModemSleep();
void setupDisplay();
void setupNVS();

// Variables globales (declaración)
extern Preferences preferences; // Para NVS
extern Adafruit_SSD1306 display; // Para el display OLED
extern uint32_t persistentBreathCounter; // Contador persistente

#endif