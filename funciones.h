#ifndef FUNCIONES_PASTILLERO_H
#define FUNCIONES_PASTILLERO_H

#include <Arduino.h>
#include <LiquidCrystal.h>

// ------------------- Constantes / Pines -------------------
extern const int pinBuzzer;
extern const int pinLed1;
extern const int pinLed2;
extern const int pinBoton;

extern const int pinIntLamina;
extern const int pinIN1;
extern const int pinIN2;
extern const int pinPWM;

constexpr uint8_t NUM_TOMAS = 4;   // tamaño del arreglo de tomas

// ------------------- Variables de Alarma -------------------
extern volatile boolean banderaAlarma;
extern int rep;
extern const int numRep;
extern const int tiempoEnc;
extern const int tiempoApag;
extern const int tiempoEspera;

// ------------------- Variables de Motor --------------------
extern boolean estadoIntLamina;
extern int valorPWM;
extern long tiempoActivacion[NUM_TOMAS];
extern int  toma;

// ------------------- Variables de Tiempo/LCD ---------------
extern long tiempoMs;
extern long tiempoBase;
extern long tiempoActual;
extern long hora, minuto;
extern long horaActual, minActual;
extern const int tiempoRet;

extern LiquidCrystal lcd;

// ------------------- Prototipos ----------------------------
void ConversionHminMs();
void ConversionMsHmin();
void Despliegue();
void ActivaMotor();
void Alarma();
void Interruptor();
void DespliegueHoraToma();

#endif
