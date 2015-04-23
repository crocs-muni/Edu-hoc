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

#define NUM_TAGS 4

enum tags{
    setup_tag, 
    nodeID_tag,
    groupID_tag,
    parentID_tag
} ;

static const String tags[] = { "setup", "nodeID", "groupID", "parentID"};

int tagToInt(String tagName){
    
#ifdef IGNORE_CASE
    for(int i = 0; i < NUM_TAGS; i++){
        if(tagName. equalsIgnoreCase(tags[i])){
            return i;
        }
    }
#else // do not ignore case
    for(int i = 0; i < NUM_TAGS; i++){
        if(tagName. equals(tags[i])){
            return i;
        }
    }
#endif 
    su.println("Parser error, tag not recognized", error);
    return -1;
}

/*
String tagToString(int tagID){
    //currently not required
    //TODO from enum tags to string
    return "";
}
*/

byte processNumber(String param){ 
    for (unsigned int i = 0; i < param.length(); i++ ){
        
       //check if all are numbers
       if(!isDigit(param.charAt(i))){
           su.println("Parser error, parameter not numeric", error);
           return 0;
       }
    }
    
    //convert to number
    return param.toInt();
}

StackArray <int> stack;

//TODO change to String intead of char array
char readTag [INPUT_TAG_LEN];
char readParam [INPUT_PARAM_LEN];


void setup () {
  Serial.begin(57600);
  
  
}

void loop () {  
    
    //read until first tag
    char input = 0;
    while(input != '<'){
            input = Serial.read();
    }
    
    //push bottom into stack
    stack.push(-1);
    //read until end tag
    while ( stack.isFull()){
        
        Serial.readBytesUntil('>', readTag, INPUT_TAG_LEN);
        readTag[strlen(readTag)-1] = '\0'; //discard end of tag '>'
        if(readTag[0] == '/'){ // if endTag
            if(stack.peek() == tagToInt(readTag)){
                
                switch(stack.pop()){ //process parameters of current tag
                    case setup_tag:
                        break;
                    case nodeID_tag:
                        nodeID = processNumber(readParam);
                        if(nodeID > MAX_NODE_ID ){
                            su.println("Parser error, node ID out of bounds", error);
                        }
                        break;
                    case groupID_tag:
                        groupID = processNumber(readParam);
                        if(groupID > MAX_GROUP_ID || groupID < MIN_GROUP_ID){
                            su.println("Parser error, group ID out of bounds", error);
                        }
                        break;
                    case parentID_tag:
                        parentID = processNumber(readParam);
                        if(parentID > MAX_NODE_ID ){
                            su.println("Parser error, parent ID out of bounds", error);
                        }
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
            if(stack.peek() == -1){
                stack.pop();
                continue;
            }
        } else {
            stack.push(tagToInt(readTag));
            memset(readTag, 0, INPUT_TAG_LEN);
            memset(readParam, 0, INPUT_PARAM_LEN);
            
            
        }
        Serial.readBytesUntil('<', readParam, INPUT_PARAM_LEN);
        
    }
    
    
    if(su.getNumErrors() > 0){
        
        //permanent sleep
        //TODO change to reset
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_enable(); 
        sleep_mode();
    }
    
    //update config in EEPROM, EEPROM has limited number of write-erase cycles, so only write when values are different
    if(EEPROM.read(NODE_ID_LOCATION) != nodeID){
        EEPROM.write(NODE_ID_LOCATION, nodeID);
    }
    if(EEPROM.read(GROUP_ID_LOCATION) != groupID){
        EEPROM.write(GROUP_ID_LOCATION, groupID);
    }
    if(EEPROM.read(PARENT_ID_LOCATION) != parentID){
        EEPROM.write(PARENT_ID_LOCATION, parentID);
    }
    
    
    //permanent sleep
    
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable(); 
    sleep_mode(); 
    
}