#include <Arduino.h>
#include <EEPROM.h>
#include <avr/sleep.h>

#include "SerialUtils.h"
#include "../common.h"

#define EEPROM_WRITE


int config = 0;

byte nodeID      = 0;
byte groupID     = 0;
byte parentID    = 0;

SerialUtils su = SerialUtils(57600);


void setup () {
  Serial.begin(57600);
  su.println("App started", debug);

}

String getValue(String data, char separator, int index){
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;
  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
      found++;
      strIndex[0] = strIndex[1]+1;
      strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void loop () {

    while (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');

        nodeID = getValue(input, ' ', 0).toInt();
        if(nodeID > MAX_NODE_ID ){
            su.println("Parser error, node ID out of bounds", error);
        }
        groupID = getValue(input, ' ', 1).toInt();
        if(groupID > MAX_GROUP_ID || groupID < MIN_GROUP_ID){
            su.println("Parser error, group ID out of bounds", error);
        }
        parentID = getValue(input, ' ', 2).toInt();
        if(parentID > MAX_NODE_ID ){
            su.println("Parser error, parent ID out of bounds", error);
        }
        su.println("setup completed", debug);
        config = 1;
    }
    if(config != 0){
        if(su.getNumErrors() > 0){

            //permanent sleep
            //TODO change to reset
            su.println("error, cannot save", error);
		su.println("results", debug);
       		su.println(nodeID, debug);
        	su.println(groupID, debug);
        	su.println(parentID, debug);
            Serial.flush();
            set_sleep_mode(SLEEP_MODE_PWR_DOWN);
            sleep_enable();
            sleep_mode();

        }

    #ifdef EEPROM_WRITE
        //update config in EEPROM, EEPROM has limited number of write-erase cycles, so only write when values are different
        su.println("EEPROM_WRITE", debug);
        if(EEPROM.read(NODE_ID_LOCATION) != nodeID){
            EEPROM.write(NODE_ID_LOCATION, nodeID);
        }
        if(EEPROM.read(GROUP_ID_LOCATION) != groupID){
            EEPROM.write(GROUP_ID_LOCATION, groupID);
        }
        if(EEPROM.read(PARENT_ID_LOCATION) != parentID){
            EEPROM.write(PARENT_ID_LOCATION, parentID);
        }

    #endif
        su.println("setup results", debug);
        su.println(nodeID, debug);
        su.println(groupID, debug);
        su.println(parentID, debug);


        //permanent sleep, node is configured, now waits for another app
        su.println("loop end", debug);
        Serial.flush();

        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_enable();
        sleep_mode();

    }
}
