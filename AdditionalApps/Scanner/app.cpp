#include <Arduino.h>
#include "RF12.h"

byte saveHdr, saveLen;
word saveCrc;
char saveData[RF12_MAXDATA];

int group = 1;
int messages = 0;
int counter = 0;

void change_group(){
  group++;
  if(group > 255){
    Serial.println("Nothing found");
  } else {
    messages = 0;
    counter = 0;
    rf12_initialize(31, RF12_868MHZ, group);
    Serial.print("New group: ");
    Serial.println(group);
  }
}

void setup () {
    //saveLen = 255;
    Serial.begin(57600);
    Serial.println("\n[Scanner] 868 MHz");
    rf12_initialize(31, RF12_868MHZ, group);
}

void loop () {
    if (rf12_recvDone()) {
      if(rf12_crc == 0){
        //if I receive a message and crc is ok, then conut is as valid
        messages++;
      }
    }
    counter++;
    delay(10);
    if(counter >= 500){ //five seconds elapsed
      //five seconds should be enough to get few messages
      if(messages > 3){ //treshold that the channel is active,
        //depends on message frequency and network size, 3 works for single node 2 msgs/sec
        Serial.print("group found: ");
        Serial.println(group);
      }
      change_group();
    }
  }
