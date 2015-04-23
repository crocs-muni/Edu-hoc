#include "SerialUtils.h"
//#include <RF12.h>
#include <Arduino.h>

SerialUtils::SerialUtils(long freq){
    this->freq = freq;
}

void SerialUtils::setUpNodeID(int* id, int* group, int* parent){
    *id = Serial.parseInt();
    *group = Serial.parseInt();
    *parent = Serial.parseInt();
}

void SerialUtils::print(char* text, Priority priority){
    //TODO priority filtering
    Serial.print(text);
}
    
void SerialUtils::println(char* text, Priority priority){
    //TODO priority filtering
    Serial.println(text);
}