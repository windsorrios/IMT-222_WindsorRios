#include "funciones.h"

// ------------------- Definiciones de pines -----------------
const int pinBuzzer = 15;
const int pinLed1   = 16;
const int pinLed2   = 17;
const int pinBoton  = 2;

const int pinIntLamina = 5;
const int pinIN1 = 7;
const int pinIN2 = 8;
const int pinPWM = 9;

// ------------------- Variables globales --------------------
volatile boolean banderaAlarma = HIGH;
int rep = 0;
const int numRep       = 10;
const int tiempoEnc    = 600;   // ms
const int tiempoApag   = 400;   // ms
const int tiempoEspera = 9900;  // ms

boolean estadoIntLamina = LOW;
int valorPWM = 230;

long tiempoActivacion[NUM_TOMAS] = {0,0,0,0};
int  toma = 0;

long tiempoMs     = 0;
long tiempoBase   = 0;
long tiempoActual = 0;
long hora = 0, minuto = 0;
long horaActual = 0, minActual = 0;

const int tiempoRet = 19000; // ms

// LCD: RS=4, E=6, D4=11, D5=12, D6=13, D7=14
LiquidCrystal lcd(4, 6, 11, 12, 13, 14);

// ------------------- Funciones ------------------------------
void ConversionHminMs() {
  // Convierte HH:MM a milisegundos
  long minTot = minuto + hora * 60;
  tiempoMs = minTot * 60000L;
}

void ConversionMsHmin() {
  // Convierte ms a HH:MM
  horaActual = tiempoActual / (60L * 60000L);
  minActual  = (tiempoActual / 60000L) - horaActual * 60L;
}

void Despliegue() {
  // Calcula tiempo actual relativo al tiempo base
  tiempoActual = millis() + tiempoBase;

  // Convierte a HH:MM y muestra
  ConversionMsHmin();
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("                ");   // limpia fila
  lcd.setCursor(0, 0);
  lcd.print("Hora ");
  lcd.print(horaActual);
  lcd.print(":");
  if (minActual < 10) lcd.print('0');
  lcd.print(minActual);
}

void ActivaMotor() {
  // Hace avanzar una posición usando el interruptor de lámina
  do {
    digitalWrite(pinIN1, HIGH);
    estadoIntLamina = digitalRead(pinIntLamina);
    Serial.println(pinIntLamina);
  } while (estadoIntLamina == HIGH);

  delay(75);  // desbouncing mecánico

  do {
    digitalWrite(pinIN1, HIGH);
    estadoIntLamina = digitalRead(pinIntLamina);
  } while (estadoIntLamina == LOW);

  digitalWrite(pinIN1, LOW);
}

void Alarma() {
  for (rep = 0; rep < numRep; rep++) {
    digitalWrite(pinBuzzer, HIGH);
    digitalWrite(pinLed1,   HIGH);
    digitalWrite(pinLed2,   HIGH);
    delay(tiempoEnc);
    digitalWrite(pinBuzzer, LOW);
    digitalWrite(pinLed1,   LOW);
    digitalWrite(pinLed2,   LOW);
    delay(tiempoApag);
  }
  delay(tiempoEspera);
}

void Interruptor() {   // marca IRAM_ATTR es opcional (ESP); en AVR se ignora
  banderaAlarma = LOW;
}

void DespliegueHoraToma() {
  // Muestra la hora programada de la toma actual (2a línea)
  Despliegue();                           // 1a línea con hora actual
  tiempoActual = tiempoActivacion[toma];  // hora de la toma relativa a base
  ConversionMsHmin();

  lcd.setCursor(0, 1);
  lcd.print("                ");           // limpia fila
  lcd.setCursor(0, 1);
  lcd.print(toma + 1);
  lcd.print("a toma ");
  lcd.print(horaActual);
  lcd.print(":");
  if (minActual < 10) lcd.print('0');
  lcd.print(minActual);
}
