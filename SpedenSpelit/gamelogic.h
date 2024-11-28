#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <Arduino.h>

extern volatile bool gameRunning;            // Onko peli käynnissä
extern volatile int userNumber[100];         // Käyttäjän syötteet
extern volatile int randomNumbers[100];      // Arvotut numerot
extern volatile int roundNum;                   // Kierrosnumero
extern volatile bool timeToCheckGameStatus;  // Lippu pelin tarkistamiseen
extern volatile int gameSpeed;               // Pelin nopeus
extern volatile byte randomNumber;
extern volatile bool ledsSet;
extern volatile bool timerinterrupt;

void startTheGame(void);
void stopTheGame(void);
void initGame();
void checkGame();
void increaseGameSpeed();
#endif