/* ****************************************************
 * ****                                           *****
 * ****               neoARC_reactor              *****
 * ****                                           *****
 * ****                VER: 1 FINAL               *****
 * ****                                           *****
 * ****************************************************/

#include <Adafruit_NeoPixel.h>  // https://github.com/adafruit/Adafruit_NeoPixel

// ######### ZONA DE CONFIGRACION #########

#define pin_centro 3
#define pin_circunferencia 2

#define num_pixels_centro 1
#define num_pixels_circunferencia 4

int valor_verde = 4;  // 204
int valor_rojo = 0;   // 0
int valor_azul = 5;   // 255


// ##### Variables internas del programa ####

Adafruit_NeoPixel centro = Adafruit_NeoPixel(num_pixels_centro, pin_centro, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel circunferencia = Adafruit_NeoPixel(num_pixels_circunferencia, pin_circunferencia, NEO_GRB + NEO_KHZ800);
int brillo_centro = 0;
bool inicio = true;
bool up = false;
void setup() {
  Serial.begin(9600);
  centro.begin();
  circunferencia.begin();
  centro.clear();
  circunferencia.clear();
  centro.show();
  circunferencia.show();
}

void loop() {
  int tiempo = 100;
  for (int i = 0; i <= num_pixels_circunferencia; i++) {
    circunferencia.setPixelColor(i, valor_rojo, valor_verde, valor_azul);
    circunferencia.setPixelColor(i - 1, valor_rojo, map(valor_verde, 4, 204, 4, 150), map(valor_azul, 4, 204, 4, 160));
    centro.setPixelColor(0, 0, 204, 255);
    centro.setBrightness(brillo_centro);
    circunferencia.show();
    centro.show();
    delay(tiempo);
    if (valor_azul <= 255 && valor_verde < 204) {
      valor_azul += 5;
      valor_verde += 4;
    }
    if (tiempo > 50) { tiempo--; }
    if (brillo_centro <= 255 && valor_azul == 255 && valor_verde == 204 && inicio == true) {
      brillo_centro += 5;
      if (brillo_centro >= 255) { inicio = false; }
    }
    // FINAL INICIO
    if (brillo_centro >= 100 && valor_azul == 255 && valor_verde == 204 && inicio == false && up == false) {
      brillo_centro -= 15;
      if (brillo_centro <= 100) {
        up = true;
      }
      Serial.println(brillo_centro);
    }
    if (brillo_centro <= 255 && valor_azul == 255 && valor_verde == 204 && inicio == false && up == true) {
      brillo_centro += 15;
      if (brillo_centro >= 255) {
        up = false;
      }
       Serial.println(brillo_centro);
    }
  }
}
