#ifndef CUSTOMSCREENS_H
#define CUSTOMSCREENS_H

#include "setupFunctions.h"

// Declaración de los bitmaps (se definen en Pantallas.cpp)
extern const unsigned char epd_bitmap_user_stats[] PROGMEM;
extern const unsigned char epd_bitmap_imagen_logo[] PROGMEM;
extern const unsigned char epd_bitmap_exercise_complete[] PROGMEM;
extern const unsigned char epd_bitmap_meditation_complete[] PROGMEM;
extern const unsigned char epd_bitmap_meditation_mode[] PROGMEM;
extern const unsigned char epd_bitmap_imagen_apagado [] PROGMEM;

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

#endif // CUSTOMSCREENS_H