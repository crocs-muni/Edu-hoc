#include <Arduino.h>
#include "RF12.h"
#include "RadioUtils.h"

#include "SerialUtils.h"
#include "../common.h"



void setup() {
  // initialize digital pin 13 as an output.
  pinMode(9, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(9, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(9, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}