// -----------------------------------------------------------------
// animationFunctions.cpp
//
// Funciones de para ejercicios de respiración y meditación
// controla motor de vibración, muestra animaciones en pantalla OLED
// & actualiza contador persistente en NVS 
//
// Logica de meditacion y ejercicios
//
// -----------------------------------------------------------------


#include "animationFunctions.h"
#include "setupFunctions.h"
#include "customScreens.h"

// Parámetros globales del ejercicio
int inhale_time, hold_time, exhale_time, rest_time;

// -----------------------------------------------------------------
// FUNCIONES AUXILIARES
// -----------------------------------------------------------------

// Dibuja el contorno del círculo y lo llena en función del progreso
void drawProgressCircle(int x0, int y0, int radius, int currentRadius) {
  display.drawCircle(x0, y0, radius, SSD1306_WHITE);
  display.fillCircle(x0, y0, currentRadius, SSD1306_WHITE);
}

// Dibuja el cronómetro (o contador) en pantalla
void drawTimer(const char* state, float timeLeft) {
  display.setTextSize(1);
  display.setCursor(TEXT_X, TEXT_Y - 5);
  display.print(state);
  display.print(":");
  display.setCursor(TEXT_X, TEXT_Y + 5);
  display.print(timeLeft, 0);
  display.print(" sec's");
}

// Realiza un pulso en el motor: activa con 'highVal' durante 'duration' ms y luego baja a 'lowVal'
inline void pulseMotor(uint8_t highVal, uint8_t lowVal, unsigned long duration) {
  analogWrite(MOTOR_PIN, highVal);
  delay(duration);
  analogWrite(MOTOR_PIN, lowVal);
}

// Muestra el contador (usado en meditación) en la posición correspondiente
void displayBreathPhase(int phase) {
  display.setTextSize(3);           // Tamaño de texto 3
  display.setCursor(95, 20);        // Posicion
  display.print(phase);             // Imprime 1 para inhalación, 2 para exhalación
}

// -----------------------------------------------------------------
// EJERCICIO DE RESPIRACIÓN (3 ciclos) CON FEEDBACK TÁCTIL
// -----------------------------------------------------------------
bool breathingExercise() {
  // Configuramos tiempos para el ejercicio
  // 12.5 segundos por ciclo
  inhale_time = 4000;
  hold_time   = 3000;
  exhale_time = 4000;
  rest_time   = 1500;
  int cycles = 0;
  bool interrupted = false; // Para detectar interrupción
  
  // Aseguramos que el motor inicie apagado
  analogWrite(MOTOR_PIN, 0);
  const int pulseInterval = 5;  // Pulso cada 4 actualizaciones
  
  while (digitalRead(BUTTON_PIN) == HIGH && cycles < 3 && !interrupted) {  // 3 ciclos
    // Fase de descanso (sin vibración)
    display.clearDisplay();
    display.drawCircle(CIRCLE_X, CIRCLE_Y, CIRCLE_RADIUS, SSD1306_WHITE);
    display.display();
    for (int t = rest_time; t >= 0 && !interrupted; t -= 50) {
      if (digitalRead(BUTTON_PIN) == LOW) {
        interrupted = true;
        analogWrite(MOTOR_PIN, 0);
        break;
      }
      delay(50);
    }
    
    // Fase de inhalación con feedback táctil intermitente
    if (!interrupted) {
      unsigned long inhaleStep = inhale_time / (CIRCLE_RADIUS + 1);
      for (int r = 0; r <= CIRCLE_RADIUS && !interrupted; r++) {
        unsigned long stepStart = millis();
        display.clearDisplay();
        drawProgressCircle(CIRCLE_X, CIRCLE_Y, CIRCLE_RADIUS, r);
        drawTimer("Inhale", (CIRCLE_RADIUS - r) * inhaleStep / 1000.0);
        display.display();
        
        if (r % pulseInterval == 0) {
          pulseMotor(255, 10, 35);
        }
        
        unsigned long elapsed = millis() - stepStart;
        if (elapsed < inhaleStep) {
          delay(inhaleStep - elapsed);
        }
        if (digitalRead(BUTTON_PIN) == LOW) {
          interrupted = true;
          analogWrite(MOTOR_PIN, 0);
          break;
        }
      }
      analogWrite(MOTOR_PIN, 0);
    }
    
    // Fase de retención (hold) sin vibración
    if (!interrupted) {
      for (int t = hold_time; t >= 0 && !interrupted; t -= 100) {
        display.clearDisplay();
        display.fillCircle(CIRCLE_X, CIRCLE_Y, CIRCLE_RADIUS, SSD1306_WHITE);
        drawTimer("Hold", t / 1000.0);
        display.display();
        delay(100);
        if (digitalRead(BUTTON_PIN) == LOW) {
          interrupted = true;
          analogWrite(MOTOR_PIN, 0);
          break;
        }
      }
    }
    
    // Fase de exhalación con feedback táctil constante
    if (!interrupted) {
      unsigned long exhaleStep = exhale_time / (CIRCLE_RADIUS + 1);
      for (int r = CIRCLE_RADIUS; r >= 0 && !interrupted; r--) {
        display.clearDisplay();
        drawProgressCircle(CIRCLE_X, CIRCLE_Y, CIRCLE_RADIUS, r);
        drawTimer("Exhale", r * exhaleStep / 1000.0);
        display.display();
        
        analogWrite(MOTOR_PIN, 135);
        delay(exhaleStep);
        if (digitalRead(BUTTON_PIN) == LOW) {
          interrupted = true;
          analogWrite(MOTOR_PIN, 0);
          break;
        }
      }
      analogWrite(MOTOR_PIN, 0);
    }

    if (!interrupted) {
      cycles++;  // Incrementa solo si se completó el ciclo
    }
  }
  
  // Actualizamos el contador persistente y lo guardamos en NVS solo con ciclos completados
  persistentBreathCounter += cycles;
  preferences.putUInt("breaths", persistentBreathCounter);
  return !interrupted && cycles == 3;
}

// -----------------------------------------------------------------
// MODO MEDITACIÓN CON FEEDBACK TÁCTIL E INTERRUPCIÓN POR BOTÓN
// -----------------------------------------------------------------
void meditationMode() {
  // Configuramos tiempos para la meditación
  // 7 segundos por ciclo
  inhale_time = 2700; // + 43ms x ciclo
  hold_time   = 800;  // + 73ms x ciclo
  exhale_time = 2700; // + 43ms x ciclo
  rest_time   = 800; // + 20 ms x ciclo
  
  int cycles = 1;           // Para evitar mostrar -1
  bool interrupted = false; // Para detectar interrupción
  
  analogWrite(MOTOR_PIN, 0);
  const int pulseInterval = 7;  // Pulso cada 6 actualizaciones
  
  // Intro Delay (sin vibración)
  display.clearDisplay();
  display.drawCircle(CIRCLE_X, CIRCLE_Y, CIRCLE_RADIUS, SSD1306_WHITE);
  display.display();
  delay(2500);
  display.clearDisplay();

  // Iniciamos el ciclo
  while (digitalRead(BUTTON_PIN) == HIGH && cycles < 1000) {  // Máximo 1000 ciclos (2 Horas de meditacion)
    
    // Fase de inhalación con feedback táctil intermitente
    unsigned long inhaleStep = inhale_time / (CIRCLE_RADIUS + 1);
    for (int r = 0; r <= CIRCLE_RADIUS; r++) {
      if (digitalRead(BUTTON_PIN) == LOW) { 
        interrupted = true; 
        break; 
      }
      unsigned long stepStart = millis();
      display.clearDisplay();
      drawProgressCircle(CIRCLE_X, CIRCLE_Y, CIRCLE_RADIUS, r);
      displayBreathPhase(1);
      display.display();
      
      if (r % pulseInterval == 0) {
        pulseMotor(255, 10, 35);
      }
      
      unsigned long elapsed = millis() - stepStart;
      if (elapsed < inhaleStep) {
        delay(inhaleStep - elapsed);
      }
    }
    if (interrupted){
      analogWrite(MOTOR_PIN, 0);
      break;
    }
    
    // Fase de retención (hold) sin vibración
    for (int t = hold_time; t >= 0; t -= 100) {
      if (digitalRead(BUTTON_PIN) == LOW) { 
        interrupted = true; 
        break; 
      }
      display.clearDisplay();
      display.fillCircle(CIRCLE_X, CIRCLE_Y, CIRCLE_RADIUS, SSD1306_WHITE);
      displayBreathPhase(1);
      display.display();
      
      for (int wait = 0; wait < 100; wait += 50) {
        if (digitalRead(BUTTON_PIN) == LOW) { 
          interrupted = true; 
          break; 
        }
        delay(50);
      }
      if (interrupted) break;
    }
    if (interrupted){
      analogWrite(MOTOR_PIN, 0);
      break;
    }
    
    // Fase de exhalación con feedback táctil constante
    unsigned long exhaleStep = exhale_time / (CIRCLE_RADIUS + 1);
    for (int r = CIRCLE_RADIUS; r >= 0; r--) {
      if (digitalRead(BUTTON_PIN) == LOW) { 
        interrupted = true; 
        break; 
      }
      display.clearDisplay();
      drawProgressCircle(CIRCLE_X, CIRCLE_Y, CIRCLE_RADIUS, r);
      displayBreathPhase(2);
      display.display();
      
      analogWrite(MOTOR_PIN, 135);
      delay(exhaleStep);
    }
    analogWrite(MOTOR_PIN, 0);
    if (interrupted){
      analogWrite(MOTOR_PIN, 0);
      break;
    }
    
    cycles++;  // Incrementa si se completó el ciclo

        // Fase de descanso (sin vibración)
    display.clearDisplay();
    display.drawCircle(CIRCLE_X, CIRCLE_Y, CIRCLE_RADIUS, SSD1306_WHITE);
    displayBreathPhase(2);
    display.display();
    
    for (int t = 0; t < rest_time; t += 50) {
      if (digitalRead(BUTTON_PIN) == LOW) { 
        interrupted = true; 
        break; 
      }
      delay(50);
    }
    if (interrupted){
      analogWrite(MOTOR_PIN, 0);
      break;
    }

    // incrementando tiempos despues de cada ciclo
    if (inhale_time < 4000){
      inhale_time += 43; // + 43ms x ciclo : max 4033ms ~ 4s
      hold_time += 73;  // + 73ms x ciclo : max 3063ms ~ 3s
      exhale_time += 43; // + 43ms x ciclo : max 4033ms ~ 4s
      rest_time += 40; // + 40 ms x ciclo : max 2000ms ~ 2s
    }
  }
  
  // Actualizamos la NVS con los ciclos completados
  persistentBreathCounter += (cycles - 1);
  preferences.putUInt("breaths", persistentBreathCounter);
  
  pantallaMedComp();
  display.setTextSize(2);
  display.setCursor(49, 20);
  display.print(cycles - 1);
  display.display();
  delay(8500);
  display.setTextSize(1);
  display.clearDisplay();
  display.display();
}