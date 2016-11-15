#include <Arduino.h>
#include "RF12.h"
#include "../common.h"

int msgCounter = 0;
byte header;

void setup () {

  rf12_initialize(5, RF12_868MHZ, 5);
  header = B11111111;
}

void loop () {
  //if incoming message received

  rf12_sendForceEnable();
  rf12_sendStart(header,(const void*) &msgCounter, sizeof(msgCounter) );
  msgCounter++;
  delay(random(60));
}
