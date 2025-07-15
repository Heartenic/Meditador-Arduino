// ------------------------------------------------------------------------
// Este es el código del Respirador versión 0.9
// Esta version puede funcionar para ser un pmv
// ------------------------------------------------------------------------
// DESCRIPCION:
// Single Click: ejercicio de tres ciclos
// Triple Click: meditacion (max 99 ciclos)
// Hold: stats
// Usa NVS para guardar numero de ciclos historico.
// Utiliza "Modem sleep" para ahorro de bateria.
// Utiliza Bit Maps para pantallas custom (logo y stats).
// ------------------------------------------------------------------------
// CAMBIOS SOBRE 0.8:
// Meditacion muestra 1-2 en vez de mostrar numero de ciclos
// Meditacion con limite de 100 -> 1000 ciclos para hasta 2h de meditacion
// ejercicios cancelables
// ------------------------------------------------------------------------
// Dependencias
#include <Wire.h>
#include <Arduino.h>
#include "buttonInteractions.h"
#include "setupFunctions.h"
#include "animationFunctions.h"
#include "customScreens.h"
// ------------------------------------------------------------------------
#define BUTTON_PIN 0      // Pin al botón
// ------------------------------------------------------------------------
// funcion para calcular nivel del usuario
int calcularNivel() {
  int ciclos = persistentBreathCounter;
  int nivel = 0;
  if (ciclos < 300) {
    nivel = 1;
  } else if (ciclos < 750) {
    nivel = 2;
  } else if (ciclos < 1500) {
    nivel = 3;
  } else if (ciclos < 3000) {
    nivel = 4;
  } else {
    nivel = 5;
  }

  return nivel;
}
// ------------------------------------------------------------------------
// OBJETO DEL BUTTON MANAGER (Overrideado)
// Aquí se determina la acción de cada interacción
class MyCustomButton : public ButtonInteraction {
public:
  MyCustomButton(int pin) : ButtonInteraction(pin) {}

  // Pulsación simple: ejecuta el ejercicio de respiración
  void onSingleClick() override {
    bool completed = breathingExercise();
    if (completed) {
      pantallaEjerComp();
      delay(250);
    }
    else {
      display.clearDisplay();
      display.display();
      delay(250);
    }
  }

  // Triple pulsación: inicia el modo meditación
  void onTripleClick() override {
    pantallaMedMode();
    meditationMode();
    delay(250);
  }

  // Quintuple pulsación: "Apagado logico" con Deep-Sleep
  void onQuintupleClick() override {
    apagado();
  }

  // Pulsación larga: muestra las estadísticas (total de respiraciones)
  void onLongPress() override {
    pantallaUserStats();
    display.setTextSize(1);
    display.setCursor(5, 27);
    display.print("Total breaths:");
    display.setCursor(5, 37);
    display.print(persistentBreathCounter);
    display.setCursor(5, 52);
    display.print("User level: ");
    display.print(calcularNivel());

    display.display();

    delay(7500);
    display.clearDisplay();
    display.display();
    delay(250);
  }
};
// ------------------------------------------------------------------------
// CONSTRUCTOR DEL BUTTON MANAGER
MyCustomButton myButton(BUTTON_PIN);
// ------------------------------------------------------------------------
// SETUP & LOOP
void setup() {
  // Al encenderse:
  delay(250);
  setModemSleep();      // Mantener en modem sleep para ahorrar energía
  setupDisplay();       // Inicializar display
  setupNVS();           // Almacenamiento persistente
  pantallaLogo();        // Mostrar logo de Heartenic
}

void loop() {
  myButton.update(); // Actualizar continuamente el estado del botón
}

/*
                                                                  =++++                             
                                                        +++      ++****=                            
                                                     =+****=     =****+=                            
                                                    ++******+   =*****++                            
                                                     +*******++ +******=                            
                                                     ++*******+=*******++=+                         
                                                      =+*******+**********++++                      
                                                       +**********************++                    
                                                       =+***********************+                   
                                           +*************************************+  ****            
                                          ++**************************************#######*          
                                     ++++++***++++++++***********#########################*         
                                    =********+=======+####################################*         
                                    =********+=======+###################################**         
                         +*##*+      ++++++++++=======++++++++***#######################**          
                        +#####+                        =======+***##################****            
                        +*####+  =============+=++++++==++++++***#################**++              
                           +   =========++++***###############################*******++             
                               ========+******##############################**********++            
                               +=========++++++******#####################*************++           
                                                    +====++***###########***************+           
                                                    +=====+***##########****************+           
                    +##**********#+   ========+++++++****##############*****************+           
                    +##############+ ========+*******#################******************+           
                    +#############*+ +========+******#################*****************+            
                      *++*+*+*++++     ========++++++++*****##############************#+*           
                                                         +**############################**          
                          +============+++++++++++++++*****###############################+         
                         ====+************#################################################*        
                         ===++***********##################################################**       
          *+**++   ==========+++****########################################################*       
          *#####+  ============+***#########################################################*       
          *####*+  ============+***#########################################################*       
            +++      +===========++++*######################################################*       
                               =======*#####################################################*       
                                +==++++++++++++*+++**++++++*****############################*       
                                                           +*****##########################*        
                      ++           ***********************++*****##########################*        
                    +####*+     +*########################################################*         
                    *#####+     +########################################################*          
                    **###*       *######################################################*           
                                      **###############################################*            
                                       *##############################################*             
                       +############**  **##########################################**              
                      *##############*               *#############################*                
                      **#############*             +*#############################*                 
                                         **######################################*                  
                                         +######################################*                   
                                         +#####################################*#                   
                                                          +####################*                    
                                                          *###################*                     
                                           ******   ******##################*                       
                                           *####** +######################**                        
                                           *####*  +#################**#*                           
                                            *+++     *++++++*******                                 
*/