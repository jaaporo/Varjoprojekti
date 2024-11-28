#include "gamelogic.h"
#include <Arduino.h>
#include "buttons.h"
#include <Arduino.h>
#include <avr/interrupt.h>
#include "leds.h"

volatile bool gameRunning = false;  // Onko peli käynnissä
volatile int userNumber[100];       // Käyttäjän syötteet
volatile int randomNumbers[100];    // Satunnaiset numerot
volatile int roundNum = 0;             // Kierrosnumero
volatile bool timeToCheckGameStatus = false;
volatile int gameSpeed = 15624;  // Alustettu nopeus (1 Hz)
volatile byte randomNumber = 10;
volatile bool ledsSet = false;
volatile bool timerinterrupt = false;

void initGame() {
  roundNum = 0;
  gameRunning = false;
  timeToCheckGameStatus = false;
  randomSeed(analogRead(0));
}

void startTheGame() {

roundNum = 0;
randomNumber= NOT_SET;
gameSpeed = 15624;
  // Set Timer1 to CTC mode (WGM12 = 1, WGM13:0 = 0)

  for (int i = 0; i < 100; i++) {
    userNumber[i] = NOT_SET;  // Set each element to 
    randomNumbers[i] = NOT_SET;
  }

  Serial.println("Peli alkaa!");
  gameRunning = true;
  TIMSK1 = (1 << OCIE1A);  //Timer 1 keskeytys
}

void stopTheGame() {
  gameRunning = false;
  
  TIMSK1 &= ~(1 << OCIE1A);  // Poistetaan Timer1:n ylivuotokeskeytys
  //TIMSK1 &= ~(1 << TOIE1);  // Poistetaan Timer1:n ylivuotokeskeytys
  Serial.println("Peli päättyy!");
}

void checkGame() {
  bool gameCorrect = true;

  // Vertaillaan käyttäjän syötteitä ja arvottuja numeroita
  for (int i = 0; i < 99; i++) {
    if (userNumber[i] != randomNumbers[i]) {
      gameCorrect = false;
      Serial.println("mismatch");
      Serial.println(i);
      Serial.println(userNumber[i]);
      Serial.println(randomNumbers[i]);
    }
  }

  if (gameCorrect == true) {
    // Jos kaikki on oikein, peli jatkuu
    Serial.print("Peli jatkuu, kierros: ");
    Serial.println(roundNum);
    // Kasvatetaan kierrosnumeroa
  } else {
    // Jos syöte oli virheellinen, peli loppuu
    stopTheGame();
  }

  // Resetoi tarkistuslippu
  timeToCheckGameStatus = false;
}

// Funktio pelin nopeuden lisäämiselle
void increaseGameSpeed() {
  if (roundNum % 10 == 0 && roundNum > 0) {  // Nopeutetaan peliä joka kymmenennellä oikealla syötteellä
    Serial.println("Vauhti kasvaa!");
    gameSpeed *= 0.9;                  // Lisätään nopeutta 10%
    OCR1A = gameSpeed;                 // Päivitetään Timer1:n vertaustarkistus (kompensoidaan keskeytysnopeus)
  }
}
ISR(TIMER1_COMPA_vect) {
    randomNumber = random(0, 4);
    timerinterrupt = true;  // Arvotaan satunnainen luku 0-3

    /*
    Serial.print("Arvottu numero: ");
    Serial.println(randomNumber);
    Serial.println(randomNumbers[roundNum]);
    */
}