#ifndef ANIMATIONFUNCTIONS_H
#define ANIMATIONFUNCTIONS_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Preferences.h>
#include "customScreens.h"

// Parámetros globales del ejercicio (definir en un único .cpp)
extern int inhale_time;
extern int hold_time;
extern int exhale_time;
extern int rest_time;

// Parámetros
#define CIRCLE_RADIUS 29
#define CIRCLE_X (CIRCLE_RADIUS + 10)
#define CIRCLE_Y (SCREEN_HEIGHT / 2)  // Asegúrate de definir SCREEN_HEIGHT previamente
#define TEXT_X (CIRCLE_X + CIRCLE_RADIUS + 15)
#define TEXT_Y (SCREEN_HEIGHT / 2)
#define INTRO_TIME 3000
#define COMPLETED_TIME 3000
#define BUTTON_PIN 0
#define MOTOR_PIN 1

// Declaración de funciones

// Función unificada para dibujar el progreso del círculo
void drawProgressCircle(int x0, int y0, int radius, int currentRadius);

// Aliases para mantener compatibilidad con el código existente
inline void drawFillingCircle(int x0, int y0, int radius, int currentRadius) {
    drawProgressCircle(x0, y0, radius, currentRadius);
}

inline void drawEmptyingCircle(int x0, int y0, int radius, int currentRadius) {
    drawProgressCircle(x0, y0, radius, currentRadius);
}

// Dibuja el cronómetro en pantalla
void drawTimer(const char* state, float timeLeft);

// Funciones del ejercicio de respiración y modo meditación
bool breathingExercise();
void meditationMode();

#endif  // ANIMATIONFUNCTIONS_H