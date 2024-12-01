#include "display.h"


const byte digits[10] = {
  B00111111,  // 0
  B00000110,  // 1
  B01011011,  // 2
  B01001111,  // 3
  B01100110,  // 4
  B01101101,  // 5
  B01111101,  // 6
  B00000111,  // 7
  B01111111,  // 8
  B01101111   // 9
};

void initializeDisplay(void) {
  for (byte pin = d_firstPin; pin <= d_lastPin; pin++) {
    pinMode(pin, OUTPUT);
  }
  // See requirements for this function from display.h
}


void writeByte(uint8_t bits, bool last) {
  digitalWrite(rclkPin, LOW);
  digitalWrite(srclrPin, LOW);
  delay(100);
  digitalWrite(srclrPin, HIGH);  //tyhjennetään näyttö

  uint8_t bitState;
  bits = digits[bits];

  for (int bit = 7; bit >= 0; bit--) {
    bitState = (bits >> bit) & 1;
    
    digitalWrite(serPin, bitState);
    digitalWrite(rclkPin, LOW);
    digitalWrite(srclkPin, HIGH);

    
    delay(10);
    digitalWrite(srclkPin, LOW);

    digitalWrite(rclkPin, HIGH);
    digitalWrite(serPin, LOW);
    delay(10);
    
  }

  delay(1000);
  if (last == true) {
    Serial.print("tallenna tai älä tallenna");
  }
}


void writeHighAndLowNumber(uint8_t tens, uint8_t ones) {
  // See requirements for this function from display.h
}

void showResult(byte number) {
  // See requirements for this function from display.h
}
