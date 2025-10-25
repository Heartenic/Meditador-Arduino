// -----------------------------------------------------------------
// buttonInteractions.h
//
// Clase para distintas interacciones con un solo botón
// cun click, triple click, quintuple click y long press.
//
// Soporta debounce y tiempos configurables
// Se puede derivar para distintos dispositivos
//
// -----------------------------------------------------------------

class ButtonInteraction {
private:
  int _pin;
  unsigned long _lastDebounceTime = 0;
  unsigned long _pressTime = 0;
  unsigned long _releaseTime = 0;
  int _tapCounter = 0;
  int _timeDiff = 0;
  bool _longPressDetected = false; // Bandera para detectar long press

  // Variables configurables
  unsigned long _debounceDelay = 50;     // Tiempo mínimo entre clicks
  unsigned long _longPressDuration = 1600; // Duración mínima para un long press
  const unsigned long TAP_WINDOW = 700;    // Tiempo máximo entre clicks

  // Banderas renombradas para mayor claridad
  bool _releaseHandled = false;  // Indica si ya se ha procesado la liberación
  bool _pressHandled   = false;  // Indica si ya se ha procesado el presionado

  int lastButtonState = HIGH;

public:
  ButtonInteraction(int pin) : _pin(pin) {
    pinMode(_pin, INPUT_PULLUP);
  }

  void update() {
    int reading = digitalRead(_pin);
    unsigned long currentTime = millis();  // Evitamos múltiples llamadas a millis()

    // Actualiza el tiempo de debounce si el estado cambia
    if (reading != lastButtonState) {
      _lastDebounceTime = currentTime;
    }

    // Si ha pasado el tiempo de debounce, procesamos los eventos
    if ((currentTime - _lastDebounceTime) > _debounceDelay) {

      // Detección del presionado
      if (reading == LOW && !_pressHandled) {
        _pressTime = currentTime;
        _releaseHandled = false;
        _pressHandled = true;
        _tapCounter++;
        _longPressDetected = false; // Reinicia la bandera de long press
      }

      // Detección en tiempo real del long press
      if (reading == LOW && (currentTime - _pressTime) >= _longPressDuration) {
        if (!_longPressDetected) {
          onLongPress();
          _longPressDetected = true;
        }
      }

      // Detección de la liberación
      if (reading == HIGH) {
        if (!_releaseHandled) {
          _releaseTime = currentTime;
          _releaseHandled = true;
          _pressHandled = false;
          _timeDiff = currentTime - _pressTime;
        }
        // Procesa la interacción si ha excedido el TAP_WINDOW
        if ((currentTime - _pressTime) > TAP_WINDOW) {
          if (!_longPressDetected) { // Ignora si ya se detectó un long press
            if (_tapCounter == 1 && _timeDiff < TAP_WINDOW) {
              onSingleClick();
            } else if (_tapCounter == 3) {
              onTripleClick();
            } else if (_tapCounter == 5) {
              onQuintupleClick();
            }
          }
          _tapCounter = 0;
        }
      }
    }

    lastButtonState = reading;  // Actualiza el estado del botón
  }

  // Métodos virtuales para sobreescribir según la aplicación
  virtual void onSingleClick() {}
  virtual void onTripleClick() {}
  virtual void onQuintupleClick() {}
  virtual void onLongPress() {}

  // Setter para el tiempo de debounce
  void setDebounceDelay(unsigned long delay) {
    _debounceDelay = delay;
  }

  // Setter para la duración del long press
  void setLongPressDuration(unsigned long duration) {
    _longPressDuration = duration;
  }
};