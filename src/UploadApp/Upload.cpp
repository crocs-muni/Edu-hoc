#include <Arduino.h>
#include <EEPROM.h>
#include <avr/sleep.h>

#include "StackArray.h"
#include "SerialUtils.h"
#include "../common.h"

int address = 0;
int state = 0;

byte nodeID      = 0;
byte groupID     = 0;
byte parentID    = 0;

SerialUtils su = SerialUtils(57600);


enum tags{
    setup_tag, 
    nodeID_tag,
    groupID_tag,
    parentID_tag
} ;

static const char *tags[] = { "setup", "nodeID", "groupID", "parentID"};

int tagToInt(char* tagName){
    
    //TODO from string to enum tags
    return 0;
}

char* tagToString(int tagID){
    //currently not required
    //TODO from enum tags to string
    return "";
}


byte processNumber(char* param){ 
    //TODO process char to number with error handling
    return 0;
}

StackArray <int> stack;

char readTag [INPUT_TAG_LEN];
char readParam [INPUT_PARAM_LEN];


void setup () {
  Serial.begin(57600);
  
  
}

void loop () {  
    boolean finished = false;
    
    
    
    //read until first tag
    char input = 0;
    while(input != '<'){
            input = Serial.read();
    }
    
    //read until end tag
    while ( !finished && !stack.isEmpty()){
        
        
        
        Serial.readBytesUntil('>', readTag, INPUT_TAG_LEN);
        readTag[strlen(readTag)-1] = '\0'; //discard end of tag '>'
        if(readTag[0] == '/'){ // if endTag
            if(stack.peek() == tagToInt(readTag)){
                
                switch(stack.pop()){ //process parameters of current tag
                    case setup_tag:
                        break;
                    case nodeID_tag:
                        nodeID = processNumber(readParam);
                        break;
                    case groupID_tag:
                        groupID = processNumber(readParam);
                        break;
                    case parentID_tag:
                        parentID = processNumber(readParam);
                        break;
                    default:
                        su.println("Parser error, Tag not recognized", error);
                        break;
                }
                memset(readTag, 0, INPUT_TAG_LEN);
                memset(readParam, 0, INPUT_PARAM_LEN);
            } else {
                su.println("Parser error, wrong sequence", error);
            }
            
            stack.pop();
        } else {
            stack.push(tagToInt(readTag));
            memset(readTag, 0, INPUT_TAG_LEN);
            memset(readParam, 0, INPUT_PARAM_LEN);
            
            
        }
        Serial.readBytesUntil('<', readParam, INPUT_PARAM_LEN);
        
    }
    
    
    //update config in EEPROM, EEPROM has limited number of write-erase cycles, so only write when values are different
    if(EEPROM.read(0) != nodeID){
        EEPROM.write(0, nodeID);
    }
    if(EEPROM.read(0) != groupID){
        EEPROM.write(1, groupID);
    }
    if(EEPROM.read(0) != parentID){
        EEPROM.write(2, parentID);
    }
    
    
    //permanent sleep
    
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable(); 
    sleep_mode(); 
    
}