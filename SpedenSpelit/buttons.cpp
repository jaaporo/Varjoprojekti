#include "buttons.h"
#include "gamelogic.h"

char serialBuffer[50];
volatile bool bufferReady = false;
//volatile bool gameRunning = false;
//volatile bool timeToCheckGameStatus;
//volatile int userNumber[100];
//volatile int roundNum;
// Jokaisen napin debounce-seuranta
volatile unsigned long lastDebounceTime[5] = { 0 };               // 5 napille
volatile bool buttonState[5] = { HIGH, HIGH, HIGH, HIGH, HIGH };  // 5 napin tila

void initButtonsAndButtonInterrupts(void) {
  // Asetetaan napit tuloiksi ja aktivoidaan sisäinen pull-up
  for (byte pin = firstPin; pin <= lastPin; pin++) {
    pinMode(pin, INPUT_PULLUP);
  }

  // Pin Change Interrupt -asetukset: keskeytys rekisteröidään muutospinneille
  PCICR |= (1 << PCIE2);  // Aktivoi Pin Change Interrupt 2 (PCINT[16:23])
  PCMSK2 |= 0b01111100;   // Aktivoi PCINT18-22 (pinnit 2-6) keskeytyksille
}

ISR(PCINT2_vect) {
  unsigned long currentTime = millis();

  // Tarkistetaan kaikki napit
  for (byte pin = firstPin; pin <= lastPin; pin++) {
    byte buttonIndex = pin - firstPin;

    // Luetaan napin tila
    bool currentState = digitalRead(pin);

    // Jos tila on muuttunut ja debounce-viive on ylittynyt
    if (currentState != buttonState[buttonIndex] && (currentTime - lastDebounceTime[buttonIndex]) > debounceDelay) {
      lastDebounceTime[buttonIndex] = currentTime;
      buttonState[buttonIndex] = currentState;

      // Jos nappi on painettu alas (LOW)
      if (currentState == LOW) {
        /*
        Serial.print("Nappia painettu: ");
        Serial.println(pin-2);
        */
        // Tarkista, aloittaako nappi 6 pelin

        if (gameRunning == true) {
          switch (pin) {
            case BUTTON0:

              userNumber[roundNum] = 0;
              break;

            case BUTTON1:

              userNumber[roundNum] = 1;
              break;

            case BUTTON2:

              userNumber[roundNum] = 2;
              break;

            case BUTTON3:

              userNumber[roundNum] = 3;
              break;
            case BUTTON4:
              Serial.println("testi");
              stopTheGame();  // Lopetetaan peli virheen vuoksi
              break;
            default:
              Serial.println("Virheellinen syöte!");
              stopTheGame();  // Lopetetaan peli virheen vuoksi
              break;
          };
          timeToCheckGameStatus = true;
        }
      } else if (pin == 6 & gameRunning == false) {
        startTheGame();
      }
    }
  }
}
