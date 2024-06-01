/*
* CONTROLADOR DE VENTILADOR CON UN ENCODER
*/

#include <Arduino.h> // INUTIL SI USAS ARDUINO IDE
#include <FanController.h> // https://github.com/GiorgioAresu/FanController (1.0.6)
#include "Encoder/Encoder.h" // https://github.com/PaulStoffregen/Encoder (1.4.4)

/*
* CONFIGURACION PINES
*/
#define pin_ventiladorSENSE 7 // PARA VENTILADORES DE 4 PINES (OPCIONAL)
#define pin_ventiladorPWM 6 //DEBE SER PWM
#define pin_encoder_1 2
#define pin_encoder_2 3


/*
* VENTILADOR PC BE LIKE...
* GND ==> NEGRO
* 12VCC ==> AMARILLO
* SENSE ==> VERDE (SI ESTA PRESENTE, SOLO VALE PARA VER SUS RPMs)
* CONTROL ==> AZUL
*/


/*
* OBJETOS Y VARIABLES
*/
FanController ventilador_1(pin_ventiladorSENSE, 2000, pin_ventiladorPWM);
Encoder encoder(pin_encoder_1, pin_encoder_2);
int estado_encoder_0 = 0;
int estado_encoder_1 = 0;
int velocidad = 0;

void setup() {
  Serial.begin(9600);
  ventilador_1.begin();
  }

void loop() {
  int estado_encoder_1 = estado_encoder_0;
  estado_encoder_1 = encoder.read();
  if (estado_encoder_1 > estado_encoder_0 && velocidad < 100) {
    velocidad += 5;
    }
  else if (estado_encoder_1 < estado_encoder_0 && velocidad > 0) {
    velocidad -= 5;
    }
  estado_encoder_0 = estado_encoder_1;
  Serial.print("Velocidad: ");
  Serial.println(velocidad);
  ventilador_1.setDutyCycle(velocidad);

  delay(250);
  }

