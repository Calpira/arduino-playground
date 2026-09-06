// Juego de luces rgb con tres modos
 
const int pinRojo  = 9;
const int pinVerde = 10;
const int pinAzul  = 11;
const int pinBoton = 2;
 
const unsigned long UMBRAL_PULSACION_LARGA = 500; // ms para que cuente como "sostenido" y activar modo fiesta
const unsigned long VENTANA_DOBLE_CLICK = 350;    // ms de espera para detectar doble click
 
enum TipoPulsacion { NINGUNA, CLICK_SIMPLE, DOBLE_CLICK, PULSACION_LARGA };
 
int modoActual = 0; // 0 = calmado, 2 = fuego 
bool encendido = true;
 
void setup() {
  pinMode(pinRojo, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAzul, OUTPUT);
  pinMode(pinBoton, INPUT_PULLUP);
  randomSeed(analogRead(A0)); // dejar A0 sin conectar
}
 
// Detecta si el botón fue un click simple, doble click o pulsación sostenida
TipoPulsacion clasificarPulsacion() {
  unsigned long inicio = millis();
 
  while (digitalRead(pinBoton) == LOW) {
    if (millis() - inicio >= UMBRAL_PULSACION_LARGA) {
      while (digitalRead(pinBoton) == LOW) delay(5);
      delay(50);
      return PULSACION_LARGA;
    }
  }
 
  delay(50); // antirebote
 
  unsigned long tiempoSuelto = millis();
  while (millis() - tiempoSuelto < VENTANA_DOBLE_CLICK) {
    if (digitalRead(pinBoton) == LOW) {
      while (digitalRead(pinBoton) == LOW) delay(5);
      delay(50);
      return DOBLE_CLICK;
    }
  }
 
  return CLICK_SIMPLE;
}
 
void loop() {
  if (!encendido) {
    apagarLED();
    if (digitalRead(pinBoton) == LOW) {
      TipoPulsacion tipo = clasificarPulsacion();
      if (tipo == DOBLE_CLICK) {
        encendido = true;
        modoActual = 0;
      }
    }
    return;
  }
 
  switch (modoActual) {
    case 0:
      modoCalmado();
      break;
    case 2:
      modoFuego();
      break;
  }
 
  if (digitalRead(pinBoton) == LOW) {
    TipoPulsacion tipo = clasificarPulsacion();
 
    switch (tipo) {
      case CLICK_SIMPLE:
        modoActual = (modoActual == 0) ? 2 : 0;
        apagarLED();
        delay(150);
        break;
 
      case DOBLE_CLICK:
        encendido = false;
        apagarLED();
        break;
 
      case PULSACION_LARGA: {
        bool interrumpido = ejecutarCargaDePoder();
        if (!interrumpido) {
          modoFiesta();
        }
        modoActual = 0; // al salir del modoFiesta, siempre vuelve al azul
        apagarLED();
        delay(150);
        break;
      }
 
      case NINGUNA:
        break;
    }
  }
}
 
void fijarColor(int r, int g, int b) {
  analogWrite(pinRojo, r);
  analogWrite(pinVerde, g);
  analogWrite(pinAzul, b);
}
 
void apagarLED() {
  fijarColor(0, 0, 0);
}
 
// Respiración en tono azulado
void modoCalmado() {
  for (int i = 10; i <= 150; i++) {
    fijarColor(0, i * 0.3, i);
    if (digitalRead(pinBoton) == LOW) return;
    delay(15);
  }
  for (int i = 150; i >= 10; i--) {
    fijarColor(0, i * 0.3, i);
    if (digitalRead(pinBoton) == LOW) return;
    delay(15);
  }
}
 
// Flash creciente en intensidad y velocidad, de blanco a violeta, termina en explosión de modoFiesta
// Devuelve true si se interrumpió antes de terminar
bool ejecutarCargaDePoder() {
  const int pasos = 30;
  const int esperaInicial = 140;
  const int esperaFinal = 15;
 
  for (int i = 0; i <= pasos; i++) {
    float progreso = (float)i / pasos;
 
    int r = 255 + progreso * (150 - 255);
    int g = 255 + progreso * (0   - 255);
    int b = 255;
 
    float intensidad = 0.2 + progreso * 0.8;
    int espera = esperaInicial + progreso * (esperaFinal - esperaInicial);
 
    fijarColor(r * intensidad, g * intensidad, b * intensidad);
    delay(espera);
    if (digitalRead(pinBoton) == LOW) return true;
 
    apagarLED();
    delay(espera);
    if (digitalRead(pinBoton) == LOW) return true;
  }
 
  fijarColor(255, 255, 255);
  delay(180);
  apagarLED();
  delay(60);
  fijarColor(255, 255, 255);
  delay(250);
  return false;
}
 
// Colores random rápidos, con fade-in de brillo al arrancar
void modoFiesta() {
  unsigned long inicioFiesta = millis();
  const unsigned long DURACION_RAMPA = 1500; // ms hasta brillo completo
 
  while (true) {
    int r = random(0, 2) * 255;
    int g = random(0, 2) * 255;
    int b = random(0, 2) * 255;
 
    if (r == 0 && g == 0 && b == 0) r = 255;
 
    unsigned long transcurrido = millis() - inicioFiesta;
    float factor = (transcurrido >= DURACION_RAMPA)
                     ? 1.0
                     : (0.05 + (float)transcurrido / DURACION_RAMPA * 0.95);
 
    fijarColor(r * factor, g * factor, b * factor);
 
    for (int i = 0; i < 20; i++) {
      if (digitalRead(pinBoton) == LOW) return;
      delay(10);
    }
  }
}
 
// Llama con chispas y caídas
void modoFuego() {
  static int brilloR = 220;
  static int brilloG = 40;
 
  brilloR += random(-25, 26);
  brilloG += random(-10, 11);
 
  brilloR = constrain(brilloR, 160, 255);
  brilloG = constrain(brilloG, 15, 65);
 
  int r = brilloR;
  int g = brilloG;
  int b = 0;
 
  if (random(0, 8) == 0) { // chispa
    fijarColor(255, 60, 0);
    delay(random(20, 50));
  }
 
  if (random(0, 12) == 0) { // caída
    fijarColor(brilloR / 3, brilloG / 3, 0);
    delay(random(30, 80));
  }
 
  fijarColor(r, g, b);
  delay(random(30, 90));
}
 