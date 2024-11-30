#include "leds.h"
#include "gamelogic.h"

void initializeLeds() {
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  
}

void setLed(byte ledNumber) {
  clearAllLeds();
  switch (ledNumber) {
    case 0:
      digitalWrite(A2, HIGH);  // Sytytetään ledi 0 (A2)
      break;
    case 1:
      digitalWrite(A3, HIGH);  // Sytytetään ledi 1 (A3)
      break;
    case 2:
      digitalWrite(A4, HIGH);  // Sytytetään ledi 2 (A4)
      break;
    case 3:
      digitalWrite(A5, HIGH);  // Sytytetään ledi 3 (A5)
      break;
    default:
      Serial.println("default case");
      // Jos annettu arvo ei ole 0-3, ei tehdä mitään
      break;
  }
  ledsSet = true;
}


void clearAllLeds() {
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  ledsSet = false;
}

void setAllLeds() {
}


void show1() {
  // Näytetään binäärilukuja 0-15 ledeillä
  for (byte i = 0; i < 16; i++) {
    // Käytetään binääriesitystä
    for (byte bit = 0; bit < 4; bit++) {
      if (i & (1 << bit)) {
        setLed(bit);  // Sytytetään vastaava ledi
      } else {
        clearAllLeds();  // Sammutetaan kaikki ledit
      }
      delay(500);  // Viivästys, jotta binääriluku näkyy
    }
  }
}
void show2(int rounds) {
  // Tehdään "valoshow", jossa ledit syttyvät vuorotellen
  for (int i = 0; i < rounds; i++) {
    for (byte led = 0; led < 4; led++) {
      setLed(led);  // Sytytetään ledit yksi kerrallaan
      delay(500);   // Viive
    }
    delay(500);  // Pieni viive ennen toistoa
  }
}