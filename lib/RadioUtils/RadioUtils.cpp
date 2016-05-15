#include "RadioUtils.h"

#include <EEPROM.h>
#include "../../src/common.h"

#include <RF12.h>

RadioUtils::RadioUtils(){
    dynamicRouting = false;
    distance = 100;

    nodeID = 5;
    groupID = 42;
    parentID = 5;
}

void RadioUtils::initialize(){
  nodeID = EEPROM.read(NODE_ID_LOCATION);
  //groupID = EEPROM.read(GROUP_ID_LOCATION);
  parentID = EEPROM.read(PARENT_ID_LOCATION);

  rf12_initialize(nodeID, FREQUENCY, groupID);
}

int RadioUtils::getNodeID(){
  return nodeID;
}

void RadioUtils::setTransmitPower(byte txPower){
  rf12_control(0x9850 | (txPower > 7 ? 7 : txPower));
}

int RadioUtils::getGroupID(){
  return groupID;
}

int RadioUtils::getParentID(){
  return parentID;
}

int RadioUtils::routeUpdateDistance(int d, byte p){
    if(d < distance){
      distance = d;
      parentID = p;
      return 1;
    } else if(d == distance){
      return 2;
    } else {
      return 0;
    }
}



int RadioUtils::routeGetLength(){
    return distance;
}

int RadioUtils::routePerformOneStep(){
  for(int i = 0; i < TIMEOUT/10; i++) {
    if(rf12_recvDone()){
      if(RF12_WANTS_ACK){
        rf12_sendStart(RF12_ACK_REPLY,0,0);
      }
      if(rf12_crc == 0){
        char text[MAX_MESSAGE_LENGTH] = "";
        for (byte i = 0; i < rf12_len; ++i) {
          text[i] = rf12_data[i];
        }
        String payload = String(text);
        int d = routeParseDistance(payload);
        byte id = 0;
        byte saveHdr;
        saveHdr = rf12_hdr;
        getID(&saveHdr, &id);
        int result = routeUpdateDistance(d+1, id);
        if(result >= 1){
          //TODO print

          //make it deterministic, so that nodes send messages in same order
	  delay(nodeID * 100);
          routeBroadcastLength();	
        }
        
        
        return 1;
      }
    }
    delay(10);
  }
  routeBroadcastLength();
  return -1;
}


void RadioUtils::routeBroadcastLength(){
    byte hdr = 0;
    String d = String(distance, DEC);
    String message = String("distance:" + d);
    char payload[15] = "";
    message.toCharArray(payload, message.length()+d.length()+1);

    setBroadcast(&hdr);
    //setAck(&hdr);
    rf12_sendNow(hdr, payload, message.length());
}

int RadioUtils::routeParseDistance(String d){
    String head = d.substring(0,d.indexOf(':'));
    if(head == "distance"){
      String body = d.substring(d.indexOf(':')+1);
      return body.toInt();
    } else {
      return -1;
    }
}



int RadioUtils::setAck(byte* hdr){
    byte ackOr = B10000000;
    *hdr = (*hdr | ackOr);
    return 0;
}

int RadioUtils::resetAck(byte* hdr){
    byte ackOr = B10000000;
    *hdr =(*hdr & ~ackOr);
    return 0;
}

int RadioUtils::setBroadcast(byte* hdr){
    byte broadOr = B10111111;
    *hdr = (*hdr & broadOr);
    return 0;
}

int RadioUtils::setID(byte* hdr, byte id){
    byte idAnd = B00011111;
    id = (id & idAnd);
    *hdr = (*hdr & ~idAnd);
    *hdr = (*hdr | id);
    return 0;
}

int RadioUtils::getID(byte* hdr, byte* id){
    byte idAnd = B00011111;
    *id = *hdr & idAnd;
    return 0;
}

void RadioUtils::enableDynamicRouting(){
    dynamicRouting = true;
}
