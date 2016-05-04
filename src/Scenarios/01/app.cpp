#include <Arduino.h>
#include <EEPROM.h>
#include "RF12.h"
#include "RadioUtils.h"
#include "SerialUtils.h"

#include <../../common.h>
#include <../scenarios.h>

int msgCounter = 0;

int nodeID = 0;
int groupID = 0;
int parentID = 0;

String message =  "";
char payload[MAX_MESSAGE_LENGTH] = "";

char* words[]={"time","person","year","way","day","thing","world","life","hand","part","eye","place","case","point",
"feel","try","leave","call","large","old","from","early","random","love","number","live","start","jump","use","break","secret"};

RadioUtils ru = RadioUtils();
SerialUtils su = SerialUtils(57600);

void setup () {
  Serial.begin(57600);
  su.println("\n[Scenario 01], node started", debug);

  nodeID = EEPROM.read(NODE_ID_LOCATION);
  groupID = EEPROM.read(GROUP_ID_LOCATION);

  rf12_initialize(nodeID, FREQUENCY, 10);
  randomSeed(nodeID);
}

void loop () {

  //if (Serial.available() > 0) {
  // read the incoming byte:
    //message = Serial.readStringUntil('\n');
    message = "#";
    message += random(1000,9999);
    message += "#";
    message += words[random(30)];
    message += " ";
    message += words[random(30)];
    byte hdr = 0;
    message.toCharArray(payload, message.length()+1);

    ru.setBroadcast(&hdr);
    ru.resetAck(&hdr);
    rf12_sendNow(hdr, payload, message.length());
    msgCounter++;
    delay(1000);
    //su.print("message send: ", debug);
    //su.print(payload, output);
    //su.print(" ", debug);
    //su.println(msgCounter, debug);

  //}
}
