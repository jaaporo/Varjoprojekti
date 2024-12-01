#include "buttons.h"
#include <Arduino.h>
#include "gamelogic.h"
#include "leds.h"
#include "display.h"

void setup() {

  randomSeed(analogRead(0));
  initializeGame();
  initButtonsAndButtonInterrupts();
  initializeLeds();
  initializeDisplay();

  Serial.begin(9600);
  while (!Serial) {
    ;  // Odotetaan sarjaporttia
  }
  Serial.println("Aloitetaan ohjelma.");
  // Alustetaan napit ja keskeytykset
}

void loop() {
  writeByte(6, true);
  /* 
    jos peli on aloitettu ja kierroksen ajastin on loppunut tarkistetaan vastaako listat toisiaan
    kutsutaan aina increasegamespeed joka nopeuttaa ajastinta 10 kierroksen välein
    tallennetaan uusi randomnumero taulukkoon ja sytytetään vastaava ledi.
  */
  if (gameRunning == true) {
    if (timerinterrupt == true & randomNumber != NOT_SET) { //odotetaan ajastimen asettavan ainakin yksi randomnumero
      timerinterrupt = false;  //Estetään looppaaminen
      checkGame();             //Kierros päättyy viimeistään tähän
      roundNum++;
      increaseGameSpeed(); //uusi kierros alkaa tästä
      randomNumbers[roundNum] = randomNumber;  // Tallennetaan numero taulukkoon
      clearAllLeds();
      setLed(randomNumbers[roundNum]);
    }
  }

  if (timeToCheckGameStatus == true) {
    if (gameRunning == false & buttonPressed == 4) {
      startTheGame();
   
    } else if (gameRunning == true & buttonPressed == 4) {
      stopTheGame();

    } else if (gameRunning == true) {
      userNumber[roundNum] = buttonPressed;
      checkGame();
      clearAllLeds();
       
    }
  }
  if (gameRunning == false){
    if (gameCorrect == false){
      show2();
    }
    else{
show1();
    }
    
  }
}