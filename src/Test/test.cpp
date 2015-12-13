
#include <Arduino.h>
#include "RF12.h"

const byte LED = 9;
byte counter;

// turn the on-board LED on or off
static void led (bool on) {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, on ? 0 : 1); // inverted logic
}

void setup () {
  // this is node 1 in net group 10 on the 868 MHz band
  rf12_initialize(2, RF12_868MHZ, 10);
  // !mp,90kHz,last byte=power level: 0=highest, 7=lowest
byte txPower=7; //LOWEST possible
rf12_control(0x9850 | (txPower > 7 ? 7 : txPower));
}

void loop () {
  led(true);

  // actual packet send: broadcast to all, current counter, 1 byte long
  rf12_sendNow(0, &counter, 1);
  rf12_sendWait(1);

  led(false);

  // increment the counter (it'll wrap from 255 to 0)
  ++counter;
  // let one second pass before sending out another packet
  delay(1000);
}
