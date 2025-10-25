// -----------------------------------------------------------------
// customScreens.h
//
// Header pantallas personalizadas;
//
// -----------------------------------------------------------------

#ifndef CUSTOMSCREENS_H
#define CUSTOMSCREENS_H

#include "setupFunctions.h"

// Declaración de los bitmaps (se definen en Pantallas.cpp)
extern const unsigned char epd_bitmap_user_stats[] PROGMEM; // pantalla de estadisticas al hacer press
extern const unsigned char epd_bitmap_imagen_logo[] PROGMEM; // pantalla de logo al encenderse
extern const unsigned char epd_bitmap_exercise_complete[] PROGMEM; // pantalla de ejercicio completado
extern const unsigned char epd_bitmap_meditation_complete[] PROGMEM; // pantalla de meditacion completada
extern const unsigned char epd_bitmap_meditation_mode[] PROGMEM; // pantalla de modo meditacion (al iniciar meditacion)
extern const unsigned char epd_bitmap_imagen_apagado [] PROGMEM; // pantalla de apagado (con el logo)

// Muestra la pantalla de estadísticas del usuario
void pantallaUserStats();

// Muestra la pantalla con el logo
void pantallaLogo();

// Muestra la pantalla de ejercicio completado
void pantallaEjerComp();

// Muestra la pantalla de meditacion completada
void pantallaMedComp();

// Muestra la pantalla de modo meditacion
void pantallaMedMode();

// Muestra la pantalla de apagado
void apagado();

// funcion helper (no implementada para animaciones):
void customAnimation(int cycles);

#endif // CUSTOMSCREENS_H