#include "buttons.h"

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Odotetaan sarjaporttia
  }

  Serial.println("Aloitetaan ohjelma.");
  initButtonsAndButtonInterrupts();  // Alustetaan napit ja keskeytykset
}

void loop() {

}