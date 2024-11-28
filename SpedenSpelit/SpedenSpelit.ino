#include "buttons.h"
#include <Arduino.h>
#include "gamelogic.h"
#include "leds.h"
void setup() {
  cli();       // Disable global interrupts
  TCCR1A = 0;  // Ensure TCCR1A is cleared
  TCCR1B = (1 << WGM12);
  OCR1A = 15624;  // For 1 Hz with 16 MHz clock and 1024 prescaler

  roundNum = 0;
  // TCNT1 = 0;              //nollataan laskuri
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 = (1 << OCIE1A);  //ylivuoto-keskeytyksen salliminen Timer1:lle
  sei();                   // Enable global interrupts


  Serial.begin(9600);
  randomSeed(analogRead(0));

  while (!Serial) {
    ;  // Odotetaan sarjaporttia
  }

  Serial.println("Aloitetaan ohjelma.");
  initButtonsAndButtonInterrupts();  // Alustetaan napit ja keskeytykset
  pinMode(A2, OUTPUT);
  digitalWrite(A2, HIGH);
  pinMode(A3, OUTPUT);
  digitalWrite(A3, HIGH);
  pinMode(A4, OUTPUT);
  digitalWrite(A4, HIGH);
  pinMode(A5, OUTPUT);
  digitalWrite(A5, HIGH);
}

void loop() {
  if (gameRunning == true) {
    if (timerinterrupt == true & randomNumber != NOT_SET) {
      timerinterrupt = false; //Estetään looppaaminen
      checkGame();    //Kierros päättyy viimeistään tähän
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