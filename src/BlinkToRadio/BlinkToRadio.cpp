#include <Arduino.h>
#include "RF12.h"
#include "RadioUtils.h"
#include "SerialUtils.h"
#include <EEPROM.h>


#include "../common.h"

RadioUtils ru = RadioUtils();
SerialUtils su = SerialUtils(SERIAL_FREQUENCY);


int counter = 0; //
int msgCounter = 0; 

int nodeID = 0;
int groupID = 0;
int parentID = 0;

char payload[MAX_MESSAGE_LENGTH] = "";
String message =  "";

boolean even = false;

void setup() {
  Serial.begin(SERIAL_FREQUENCY);
  
  nodeID = EEPROM.read(NODE_ID_LOCATION);

  groupID = EEPROM.read(GROUP_ID_LOCATION);

  parentID = EEPROM.read(PARENT_ID_LOCATION);
  
  rf12_initialize( nodeID , FREQUENCY, groupID);

  // initialize digital pin 13 as an output.
  pinMode(9, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  if(counter % 10 == 0){
    byte hdr = 0;

    //counter to message
    sprintf(payload, "%d", counter);

    //send counter broadcast    
    ru.setBroadcast(&hdr);
    ru.resetAck(&hdr);
    rf12_sendNow(hdr, payload, message.length());

    //increment counter
    
  }
  counter++;
  if (rf12_recvDone()) {
    if(even){
        digitalWrite(9, HIGH);   // turn the LED on (HIGH is the voltage level)
    } else {
        digitalWrite(9, LOW);    // turn the LED off by making the voltage LOW
    }
    even = !even;
    rf12_recvDone();
  }
  delay(10);
}