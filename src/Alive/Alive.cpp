#include <Arduino.h>
#include "RF12.h"
#include "RadioUtils.h"
#include "SerialUtils.h"
#include <../common.h>

int counter = 0; //
int msgCounter = 0;

int id = 0;
int group = 0;
int parent = 0;


RadioUtils ru = RadioUtils();
SerialUtils su = SerialUtils(SERIAL_FREQUENCY);

void setup () {
  Serial.begin(SERIAL_FREQUENCY);
  Serial.println("\n[Alive], node started");
  su.setUpNodeID( &id, &group, &parent);
#if !DEBUG
  rf12_initialize(id, RF12_868MHZ, group);
#endif
}

void loop () {  
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
      ru.setID(&header, parent);
      rf12_sendNow(header, (const void*)rf12_data, rf12_len);
    }
  }

  delay(10);
  counter++;

  if(counter%100 == 0){
    msgCounter++;
    //send still alive msg
    byte header;
    //fill header using radioUtils
    ru.resetAck(&header);
    ru.setID(&header, parent);
    rf12_sendNow(header, (const void*) &msgCounter, sizeof(msgCounter));
    counter = 0;
  }
}
