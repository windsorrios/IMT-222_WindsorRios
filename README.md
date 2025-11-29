Repositorio para la materia de sistemas embebidos

Sistema inteligente de administración de medicamentos para adultos mayores

Planteamiento del problema

En población adulta mayor, pacientes polimedicados y personas con rutinas exigentes, el olvido de tomas y los errores de dosificación son frecuentes. 

Esto reduce la adherencia terapéutica, aumenta descompensaciones y genera costos sanitarios. Las soluciones manuales (alarmas del teléfono, pastilleros semanales) dependen de la disciplina del usuario y no garantizan la entrega física de la dosis ni un registro de cumplimiento. Se requiere un dispositivo accesible, confiable y de bajo costo que combine recordatorio, control horario y mecanismo de dispensación para disminuir el error humano y mejorar la adherencia.

OBJETIVO GENERAL

Diseñar e implementar un pastillero inteligente basado en Arduino que avise la hora de toma y dispense automáticamente la medicación programada, registrando la confirmación del usuario.

Hardware
1 Arduino (Uno o Nano).
1 Pantalla LCD 16×2 con I2C (opcional pero recomendado para interfaz).
1 Buzzer activo 5 V.
2 LEDs (estado/alarma) + 2× resistencias 220–330 Ω.
1 Botón pulsador (confirmación) + 1× resistencia 10 kΩ (pull-down si no usas pull-up interno).
1 Módulo RTC (opcional, p.ej., DS3231) para mantener hora exacta.
1 Sensor de posición (switch de lámina reed + imán, o micro-switch de fin de carrera).
1 Driver de motor:
Opción DC: L298N / L293D (si usas motor DC con reductora).
1 Fuente: 5 V (Arduino y lógica) y, si el motor lo requiere, 12 V para potencia (o una única fuente con step-down).
Cables Dupont, protoboard o PCB.

