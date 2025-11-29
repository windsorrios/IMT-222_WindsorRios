/* Programa para pastillero inteligente v1.0 (modular) */

#include "funciones.h"

void setup() {
  // Hora de reinicio (HH:MM)
  hora   = 8;
  minuto = 34;

  // Cálculo del tiempo base
  ConversionHminMs();
  tiempoBase = tiempoMs;

  // LCD y E/S
  lcd.begin(16, 2);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinLed1,   OUTPUT);
  pinMode(pinLed2,   OUTPUT);
  pinMode(pinBoton,  INPUT);
  attachInterrupt(digitalPinToInterrupt(pinBoton), Interruptor, RISING);

  // Puente H e interruptor de lámina
  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);
  pinMode(pinIntLamina, INPUT);

  // --------- Programación de tomas (ejemplo del código original) ----------
  // 1ra toma
  hora = 8;  minuto = 35; ConversionHminMs();
  tiempoActivacion[0] = tiempoMs - tiempoBase;

  // 2da toma  (en el original sobrescribía [0]; se respeta intención)
  hora = 8;  minuto = 36; ConversionHminMs();
  tiempoActivacion[1] = tiempoMs - tiempoBase;

  // 3ra toma
  hora = 8;  minuto = 37; ConversionHminMs();
  tiempoActivacion[2] = tiempoMs - tiempoBase;

  // 4ta toma (si no se usa, se puede ignorar)
  // hora = 23; minuto = 59; ConversionHminMs();
  // tiempoActivacion[3] = tiempoMs - tiempoBase;
  // -----------------------------------------------------------------------

  Serial.begin(9600);
}

void loop() {
  // Señales iniciales al puente H: motor detenido
  digitalWrite(pinIN1, LOW);
  digitalWrite(pinIN2, LOW);
  analogWrite(pinPWM, valorPWM);

  Despliegue();
  delay(tiempoRet);

  // Espera activa hasta la siguiente toma (despliega hora)
  do {
    Despliegue();
    delay(tiempoRet);
    tiempoActual = millis() + tiempoBase;
  } while (tiempoActual < tiempoActivacion[toma]);

  // Llega la toma: activa motor, muestra hora de toma y alarma
  ActivaMotor();
  banderaAlarma = HIGH;
  do {
    DespliegueHoraToma();
    Alarma();
  } while (banderaAlarma == HIGH);

  // Limpia y avanza a la siguiente toma
  lcd.clear();
  toma++;
  if (toma >= NUM_TOMAS) toma = 0;   // opcional: volver a la primera
}
