#include <Arduino.h>
#include <EEPROM.h>


#include "StackArray.h"
#include "SerialUtils.h"
#include "../common.h"

int address = 0;
int state = 0;

int nodeID      = 0;
int groupID     = 0;
int parentID    = 0;

SerialUtils su = SerialUtils(57600);


static const char *tags[] = { "setup", "nodeID", "groupID", "parentID"};

int tagToInt(char* tagName){
    
    //TODO
    return 0;
}

char* tagToString(int tagID){
    //TODO
    return "";
}

StackArray <int> stack;


void setup () {
  Serial.begin(57600);
  
  
}

void loop () {  
    boolean finished = false;
    
    //read until end tag
    while ( !finished && !stack.isEmpty()){
        
        
        
        
    }
    
    
    //update config in EEPROM
    
    
}