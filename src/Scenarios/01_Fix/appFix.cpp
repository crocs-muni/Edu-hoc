#include <Arduino.h>
#include <EEPROM.h>
#include "RF12.h"
#include "RadioUtils.h"
#include "SerialUtils.h"
#include "StackArray.h"
#include <../../common.h>
#include <../scenarios.h>

int msgCounter = 0; 

int nodeID = 0;
int groupID = 0;
int parentID = 0;

//APP FIX - hardcoded encryption key
const uint8_t key[16] =    
   {0x0f, 0xb0, 0xc0, 0x0f,
    0xa0, 0xa0, 0xa0, 0xa0,
    0x00, 0x00, 0xa0, 0xa0,
    0x00, 0x00, 0x00, 0x00};

String message =  "";
char payload[MAX_MESSAGE_LENGTH] = "";

RadioUtils ru = RadioUtils();
SerialUtils su = SerialUtils(57600);

void setup () {
  Serial.begin(57600);
  su.println("\n[Scenario 01], node started", debug);
  
  nodeID = EEPROM.read(NODE_ID_LOCATION);
  groupID = EEPROM.read(GROUP_ID_LOCATION);
  

  rf12_initialize(nodeID, FREQUENCY, groupID);
  
  //APP FIX - enable encryption or you can implement encryption using some AES lib or something else.
  rf12_encrypt(key);

}

void loop () {  
    
  if (Serial.available() > 0) {
  // read the incoming byte:
    message = Serial.readStringUntil('\n');
    
    byte hdr = 0;
    message.toCharArray(payload, message.length()+1);
    
    ru.setBroadcast(&hdr);
    ru.resetAck(&hdr);
    rf12_sendNow(hdr, payload, message.length());
    msgCounter++;
    
    su.print("message send: ", debug);    
    su.print(payload, debug);
    su.print(" ", debug);
    su.println(msgCounter, debug);
   
  }
}