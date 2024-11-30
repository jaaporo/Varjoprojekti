#include "buttons.h"
#include <Arduino.h>
#include "gamelogic.h"
#include "leds.h"

void setup() {

  randomSeed(analogRead(0));
  initializeTimer();
  initButtonsAndButtonInterrupts();
  initializeLeds();

  Serial.begin(9600);
  while (!Serial) {
    ;  // Odotetaan sarjaporttia
  }
  Serial.println("Aloitetaan ohjelma.");
  // Alustetaan napit ja keskeytykset
}

void loop() {
  if (gameRunning == true) {
    if (timerinterrupt == true & randomNumber != NOT_SET) {
      timerinterrupt = false;  //Estetään looppaaminen
      checkGame();             //Kierros päättyy viimeistään tähän
      roundNum++;
      increaseGameSpeed();
      randomNumbers[roundNum] = randomNumber;  // Tallennetaan numero taulukkoon
      setLed(randomNumbers[roundNum]);
      //timeToCheckGameStatus = true;
    }
  }

  if (timeToCheckGameStatus == true) {
    checkGame();
    clearAllLeds();
  }

  /*
  if (timer_interrupt == 1) {
    Serial.println(timer_interrupt);
    timer_interrupt = 0 ;
  }
  */
}