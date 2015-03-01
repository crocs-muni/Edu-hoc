#include "SerialUtils.h"
#include <RF12.h>
#include <Arduino.h>

SerialUtils::SerialUtils(int freq){
    this->freq = freq;
}

void SerialUtils::setUpNodeID(int* id, int* group, int* parent){
    *id = Serial.parseInt();
    *group = Serial.parseInt();
    *parent = Serial.parseInt();
}
