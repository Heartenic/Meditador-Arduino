# 🧘‍♂️ Meditador de Bolsillo - Heartenic
# Version 0.9 del codigo

Pequeño dispositivo portátil diseñado para guiar ejercicios de respiración y sesiones de meditación de forma sencilla y natural. Con un solo botón y una pantalla OLED minimalista, el Meditador de Bolsillo te ayuda a conectar con tu respiración en cualquier momento y lugar.

---

## ✨ Características

- Basado en **ESP32-C3 Supermini** o **ESP32-C6 Supermini**.
- Pantalla OLED **0.96" 128x64px (SSD1306)**.
- Feedback háptico con motor de vibración.
- Interfaz minimalista: **un solo botón físico**.
- Alimentado por batería LiPo con BMS (TP4056 con USB-C). **solo con ESP32-C3 Supermini**
- Carcasa ergonómica impresa en 3D.
- Modos de respiración y meditación.

---

## ⚙️ Especificaciones Técnicas

### Hardware Principal
| Componente | Descripción |
|---|---|
| Microcontrolador | ESP32-C3 Supermini o ESP32-C6 Supermini (genérico Aliexpress) |
| Pantalla | OLED 0.96" 128x64 (SSD1306) |
| Motor | Motor de vibración de cepillo eléctrico |
| BMS | TP4056 (ESP32-C3 Supermini) o BMS integrado ESP32-C6 Supermini|
| Batería | LiPo (150-500 mAh) |
| Botón | Único botón físico para todas las interacciones |
| Carcasa | Impresa en 3D, diseño ergonómico y compacto |

### Pines de Conexión si se utiliza ESP32-C3 Supermini
| Componente | Pin |
|---|---|
| Botón | GPIO 0 |
| Motor | GPIO 1 |
| OLED SDA | GPIO 7 |
| OLED SCL | GPIO 9 |

### Pines de Conexión si se utiliza ESP32-C6 Supermini
| Componente | Pin |
|---|---|
| Botón | GPIO 0 |
| Motor | GPIO 1 |
| OLED SDA | GPIO 6 |
| OLED SCL | GPIO 7 |

### Consumo Aproximado
| Estado | Consumo |
|---|---|
| Light Sleep | ~10 mA |
| Activo (OLED + Motor) | ~85 mA |

---

## 🎮 Modos de Uso e Interacciones

| Acción | Función |
|---|---|
| 1 clic | Ejercicio breve de respiración (3 ciclos) |
| 1 clic (en ejercicio) | cancela el ejercicio (no se cuentan las respiraciones) |
| 3 clics | Modo meditación (indefinido, hasta 1000 ciclos o interrupción) |
| 1 clic (en meditación) | Termina la meditación |
| Mantener presionado | Muestra estadísticas de uso |

---

## 📊 Tiempos de Respiración

### Ejercicio Breve (3 ciclos)
| Fase | Duración (ms) |
|---|---|
| Inhalar | 4000 |
| Sostener | 3000 |
| Exhalar | 4000 |
| Descanso | 1500 |

### Meditación (hasta 99 ciclos)
| Fase | Duración (ms) |
|---|---|
| Inhalar | 2700 |
| Sostener | 800 |
| Exhalar | 2700 |
| Descanso | 800 |

---

## 🗃️ Almacenamiento y Estadísticas

- El dispositivo almacena en **NVS (Non-Volatile Storage)** el número total de ciclos completados.
- **Se actualiza al final de cada sesión:**
    - Ejercicio breve suma 3 ciclos.
    - Meditación suma el número de ciclos completados.
- El ESP32 tiene **aproximadamente 100,000 ciclos de escritura por celda de memoria**, lo que debería ser suficiente para años de uso regular.

---

## 🔋 Consideraciones de Energía

- Switch físico corta la alimentación completa al ESP32 para ahorro máximo.
- El BMS protege de sobrecarga y sobredescarga.
- En light sleep (modo standby), el consumo es ~10mA.
- En uso activo (OLED + motor), el consumo es ~85mA.

---

## 📥 Proceso de Flasheo y Configuración Inicial

El flasheo de los **ESP32-C3 Supermini** puede ser confuso si nunca has trabajado con esta versión. En muchas placas, el modo de flasheo (upload mode) **no entra automáticamente**, por lo que debes forzarlo manualmente.
El flasheo de los **ESP32-C6 Supermini** suele ser mas sencillo.

### 🔌 Pasos para Flashear ESP32-C3 Supermini

1. Conecta el **ESP32-C3 Supermini** a tu PC por USB-C.
2. Despues de conectar, mantén presionado el botón **BOOT**.
3. Sin soltar **BOOT**, presiona brevemente el botón **RESET**.
4. Ahora sí, suelta el botón **BOOT**.
5. El ESP32-C3 entrará en modo de flasheo (el puerto COM debería aparecer correctamente).
6. En el IDE (Arduino o PlatformIO), selecciona la placa:
    - **Board:** `ESP32C3 Dev Module`
    - **Upload Speed:** `115200`
    - **Partition Scheme:** `Default 4MB with spiffs`
    - **Encender USB CDC On Boot:** en caso de utilizar el monitor serial
7. Flashea el firmware.

---

## 🐛 Problemas Comunes y Debugging Tips para ESP32-C3 Super Mini / ESP32-C6 Super Mini

| Problema | Posible Causa | Solución |
|---|---|---|
| No reconoce el puerto COM | Drivers USB CH340 o CP210x faltantes | Instala los drivers correspondientes |
| puerto COM se conoecta y desconecta constantemente | No entró al modo de flasheo | Repetir proceso manual (BOOT + RESET) |
| Serial Monitor no muestra nada | USB CDC On Boot desactivado | Encender USB CDC On Boot |

---

## 🔗 Nota Importante

Muchos **ESP32-C3 Supermini** baratos (Aliexpress) no tienen auto-bootloader bien configurado, por lo que este proceso manual es "normal". No significa que tu placa esté defectuosa.

En Windows, el **Administrador de Dispositivos** puede ayudarte a ver si el puerto está presente o no.

---
