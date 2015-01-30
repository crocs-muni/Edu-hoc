#include "RadioUtils.h"
#include <RF12.h>
#include <Arduino.h>

RadioUtils::RadioUtils(){

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
