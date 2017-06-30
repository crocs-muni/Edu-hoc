#include <EEPROM.h>

#include "common.h"

#define EEPROM_WRITE


int config = 0;

byte nodeID      = 0;
byte groupID     = 0;
byte parentID    = 0;

//SerialUtils su = SerialUtils(57600);


void setup () {
  Serial.begin(9600);


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

        Serial.println("setup results");
        Serial.println(nodeID);
        Serial.println(groupID);
        Serial.println(parentID);


        //permanent sleep, node is configured, now waits for another app
        Serial.println("loop end");
        Serial.flush();

        while(true){
          delay(1000);
        }


    }
}
