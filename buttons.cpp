#include "buttons.h"

char serialBuffer[50];
volatile bool bufferReady = false;
volatile bool gameRunning = false;
volatile bool timeToCheckGameStatus;
volatile int userNumber[100];
volatile int ROUND;
// Jokaisen napin debounce-seuranta
volatile unsigned long lastDebounceTime[5] = {0};  // 5 napille
volatile bool buttonState[5] = {HIGH, HIGH, HIGH, HIGH, HIGH};  // 5 napin tila

void initButtonsAndButtonInterrupts(void) {
  // Asetetaan napit tuloiksi ja aktivoidaan sisäinen pull-up
  for (byte pin = firstPin; pin <= lastPin; pin++) {
    pinMode(pin, INPUT_PULLUP);
  }

  // Pin Change Interrupt -asetukset: keskeytys rekisteröidään muutospinneille
  PCICR |= (1 << PCIE2);    // Aktivoi Pin Change Interrupt 2 (PCINT[16:23])
  PCMSK2 |= 0b01111100;     // Aktivoi PCINT18-22 (pinnit 2-6) keskeytyksille
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
        Serial.print("Nappia painettu: ");
        Serial.println(pin);
        // Tarkista, aloittaako nappi 6 pelin
        
        if (gameRunning==true){
          switch(pin){
            case BUTTON0:
             
              userNumber[ROUND]= 0;
              timeToCheckGameStatus = true;
              break;

            case BUTTON1:
              
              userNumber[ROUND]= 1;
              timeToCheckGameStatus = true;
              break;

            case BUTTON2:
              
              userNumber[ROUND]= 2;
              timeToCheckGameStatus = true;
              break;

            case BUTTON3:
              
              userNumber[ROUND]= 3;
              timeToCheckGameStatus = true;
              break;
            default:
              /*
              tästä voisi kutsua esim stopTheGame()
              
              */
              Serial.println("userNumber list:");
              for(int x = 0; x<100;x++){
            
                Serial.println(userNumber[x]);
              }
              Serial.println("end of: userNumber list");
              ROUND=ROUND-1;
          }
          Serial.println(userNumber[ROUND]);
          ROUND = ROUND+1;
        }
        else if (pin == 6&gameRunning==false) {
          gameRunning = true;  // Asetetaan pelin tila päälle
          ROUND=0;
        }
      }
    }
  }
}