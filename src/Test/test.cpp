
#include <Arduino.h>
#include <EEPROM.h>
#include "RF12.h"
#include "RadioUtils.h"
#include "SerialUtils.h"

#include <../common.h>


const byte LED = 9;
byte counter;

RadioUtils ru = RadioUtils();


// turn the on-board LED on or off
static void led (bool on) {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, on ? 0 : 1); // inverted logic
}

void setup () {
  // this is node 1 in net group 100 on the 868 MHz band
  rf12_initialize(25, RF12_868MHZ, 10);
}

void loop () {
  led(true);
  byte hdr = 0;
  // actual packet send: broadcast to all, current counter, 1 byte long
  String message = String("distance:-10");
  char payload[15] = "";
  message.toCharArray(payload, message.length()+1);
  ru.setBroadcast(&hdr);
  ru.resetAck(&hdr);
  rf12_sendNow(hdr, payload, message.length());

  led(false);

  // increment the counter (it'll wrap from 255 to 0)
  ++counter;
  // let one second pass before sending out another packet
  delay(1000);
}
