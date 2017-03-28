#include <Arduino.h>
#include <EEPROM.h>
#include <avr/sleep.h>

#include "SerialUtils.h"
#include "../common.h"



byte nodeID      = 0;
byte groupID     = 0;
byte parentID    = 0;

SerialUtils su = SerialUtils(SERIAL_FREQUENCY);


void setup () {
  Serial.begin(57600);
  delay(1000);
  su.println("App started", debug);

}

void loop () {  

    nodeID = EEPROM.read(NODE_ID_LOCATION);

    groupID = EEPROM.read(GROUP_ID_LOCATION);

    parentID = EEPROM.read(PARENT_ID_LOCATION);

    su.println("setup results", debug);
    su.print("node id = ", debug);
    su.println(nodeID, debug);
    su.print("group id = ", debug);
    su.println(groupID, debug);
    su.print("parent id = ", debug);
    su.println(parentID, debug);

    //permanent sleep, node is configured, now waits for another app
    su.println("loop end", debug);
    Serial.flush(); 
    
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable(); 
    sleep_mode(); 
    
}
