#include <Arduino.h>
#include "RF12.h"
#include "../common.h"

int msgCounter = 0;
byte header;

void setup () {

  rf12_initialize(10, RF12_868MHZ, 10);
  header = B11111111;
  byte txPower=5; //LOWEST possible
  rf12_control(0x9850 | (txPower > 7 ? 7 : txPower));
}

void loop () {
  //if incoming message received

  rf12_sendForceEnable();
  rf12_sendNow(header,(const void*) &msgCounter, sizeof(msgCounter) );
  msgCounter++;
  delay(random(5));
  byte txPower=random(8); //LOWEST possible
  rf12_control(0x9850 | (txPower > 7 ? 7 : txPower));
}
