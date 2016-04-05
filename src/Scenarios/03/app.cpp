#include <Arduino.h>
#include <EEPROM.h>
#include "RF12.h"
#include "RadioUtils.h"
#include "SerialUtils.h"
#include "Time.h"

#include <../../common.h>
#include <../scenarios.h>

int counter = 0; //
int msgCounter = 0;

RadioUtils ru = RadioUtils();
SerialUtils su = SerialUtils(SERIAL_FREQUENCY);

void setup () {
  Serial.begin(SERIAL_FREQUENCY);
  Serial.println("\n[Scenario 02], node started");

  ru.initialize();
  ru.enableDynamicRouting();

  if(ru.getNodeID() == ru.getParentID()){//root node - BS - send info message n+1 times
    ru.routeUpdateDistance(0, ru.getNodeID());
    for(int i = 0; i < ROUTING_CYCLES; i ++){
      delay(TIMEOUT);
      ru.routeBroadcastLength();
    }
  } else {//regular node - perform n+1 routing cycles
    for(int i = 0; i < ROUTING_CYCLES + 1; i ++){ //
      ru.routePerformOneStep();

    }
  }
}

void loop () {

  if(ru.getNodeID() == ru.getParentID()){//root node - BS - send info message n+1 times
    ru.routeUpdateDistance(0, ru.getNodeID());
    for(int i = 0; i < ROUTING_CYCLES; i ++){
      delay(TIMEOUT*100);
      ru.routeBroadcastLength();
    }
  } else {//regular node - perform n+1 routing cycles
    for(int i = 0; i < ROUTING_CYCLES + 1; i ++){ //
      ru.routePerformOneStep();

    }
  }
  /*
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
      ru.setID(&header, ru.getParentID());
      rf12_sendNow(header, (const void*)rf12_data, rf12_len);
    }
  }

  delay(10);

  //only for regular nodes, not BS
  if(ru.getNodeID() != ru.getParentID()){
    counter++;

    if(counter%100 == 0){
      msgCounter++;
      //send counter msg
      byte header;
      //fill header using radioUtils
      ru.resetAck(&header);
      ru.setID(&header, ru.getParentID());
      rf12_sendNow(header, (const void*) &msgCounter, sizeof(msgCounter));
      counter = 0;
    }
  }*/
}
