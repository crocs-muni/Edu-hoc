#include "RadioUtils.h"
#include <RF12.h>
#include <Arduino.h>

RadioUtils::RadioUtils(){
    dynamicRouting = false;
    distance = 100;
    parent = 0;
}

int RadioUtils::routeUpdateDistance(int d, byte p){
    if(d < distance){
      distance = d;
      parent = p;
      return 1;
    } else {
      return 0;
    }
}

int RadioUtils::routeGetParent(){
    return parent;
}

int RadioUtils::routeGetLength(){
    return distance;
}

int RadioUtils::routeBroadcastLength(){
    byte hdr = 0;

    String message = String("distance:" + distance);
    char payload[15] = "";
    message.toCharArray(payload, message.length()+1);

    setBroadcast(&hdr);
    resetAck(&hdr);
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
