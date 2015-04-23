#include "SerialUtils.h"
//#include <RF12.h>
#include <Arduino.h>

SerialUtils::SerialUtils(long freq){
    this->freq = freq;
    errors = 0;
}

void SerialUtils::setUpNodeID(int* id, int* group, int* parent){
    *id = Serial.parseInt();
    *group = Serial.parseInt();
    *parent = Serial.parseInt();
}

void SerialUtils::print(String text, Priority priority){
    //TODO priority filtering
    if(priority == error){
        errors++;
    }
    
    Serial.print(text);
}
    
void SerialUtils::println(String text, Priority priority){
    print(text, priority);
    Serial.println();
}

int SerialUtils::getNumErrors(){
    return errors;
}