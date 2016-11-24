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

    if(priority >= OUTPUT_LEVEL){
        Serial.print(text);
    }
}

void SerialUtils::print(byte b, Priority priority){
    //TODO priority filtering
    if(priority == error){
        errors++;
    }
    if(priority >= OUTPUT_LEVEL){
        Serial.print(b);
    }
}

void SerialUtils::print(String text, int format, Priority priority){
    //TODO priority filtering
    if(priority == error){
        errors++;
    }
    if(priority >= OUTPUT_LEVEL){
        Serial.print(text);
    }
}

void SerialUtils::print(byte b, int format, Priority priority){
    //TODO priority filtering
    if(priority == error){
        errors++;
    }
    if(priority >= OUTPUT_LEVEL){
        Serial.print(b);
    }
}

void SerialUtils::println(String text, Priority priority){
    print(text, priority);
    Serial.println();
}

void SerialUtils::println(String text, int format, Priority priority){
    print(text, priority);
    Serial.println();
}

void SerialUtils::println(byte b, Priority priority){
    print(b, priority);
    Serial.println();
}

void SerialUtils::println(byte b, int format, Priority priority){
    print(b, priority);
    Serial.println();
}

void SerialUtils::println(){
    Serial.println();
}

int SerialUtils::getNumErrors(){
    return errors;
}
