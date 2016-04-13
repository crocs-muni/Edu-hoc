#include <Arduino.h>
#include <EEPROM.h>
#include "RF12.h"
#include "RadioUtils.h"
#include "SerialUtils.h"

#include <../../common.h>
#include <../scenarios.h>

int msgCounter = 0;

int nodeID = 0;
int groupID = 0;
int parentID = 0;

String message =  "";
char payload[MAX_MESSAGE_LENGTH] = "";

RadioUtils ru = RadioUtils();
SerialUtils su = SerialUtils(57600);

void setup () {
  Serial.begin(57600);
  su.println("\n[Scenario 05], node started", debug);

  nodeID = EEPROM.read(NODE_ID_LOCATION);
  groupID = EEPROM.read(GROUP_ID_LOCATION);


  rf12_initialize(nodeID, FREQUENCY, 10);
}

void loop () {
  /*
  if (Serial.available() > 0) {
  // read the incoming byte:
    message = Serial.readStringUntil('\n');
    message.toCharArray(payload, message.length()+1);
    byte header = B00000000;
    //fill header using radioUtils
    ru.resetAck(&header);
    ru.setID(&header, parentID);
    rf12_sendNow(header, payload, message.length());
    su.print("message send: ", debug);
    su.print(payload, debug);
  }

  //if incoming message received

  if(rf12_recvDone()){
    if(RF12_WANTS_ACK){
      rf12_sendStart(RF12_ACK_REPLY,0,0);
    }

    if(rf12_crc == 0){ //packet checksum is correct
      //propagate to parent
      byte header = B00000000;
      //fill header using radioUtils
      ru.resetAck(&header);
      ru.setID(&header, parentID);
      rf12_sendNow(header, (const void*)rf12_data, rf12_len);
      su.print("message forwarded: ", debug);
      su.print(payload, debug);
    }
  }
  */
}
