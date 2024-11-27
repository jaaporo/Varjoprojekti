#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
enum BUTTONSTATES {
  NOTPRESSED = 10
};
enum BUTTONALIAS {
  BUTTON0 = 2,
  BUTTON1 = 3,
  BUTTON2 = 4,
  BUTTON3 = 5
};
const byte firstPin = 2;  // Ensimmäinen nappi
const byte lastPin = 6;   // Viimeinen nappi
const unsigned long debounceDelay = 40; // Debounce-viive millisekunneissa

extern char serialBuffer[50];
extern volatile bool bufferReady;

void initButtonsAndButtonInterrupts(void);

ISR(PCINT2_vect);  // Keskeytyspalvelija

#endif