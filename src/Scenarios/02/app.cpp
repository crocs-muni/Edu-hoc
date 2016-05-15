#include <Arduino.h>
#include <EEPROM.h>
#include "RF12.h"
#include "RadioUtils.h"
#include "SerialUtils.h"
#include "Time.h"

#include <../../common.h>
#include <../scenarios.h>

int counter = 1; //
int msgCounter = 0;
int led = HIGH;
int nodeID;

RadioUtils ru = RadioUtils();
SerialUtils su = SerialUtils(SERIAL_FREQUENCY);

void setup () {
  Serial.begin(SERIAL_FREQUENCY);
  Serial.println("\n[Scenario 02], node started");


  pinMode(9, OUTPUT);

  ru.initialize();
  ru.enableDynamicRouting();

  nodeID = ru.getNodeID();
  Serial.println(ru.getNodeID());
  Serial.println(ru.getGroupID());
  Serial.println(ru.getParentID());


  if(ru.getNodeID() == ru.getParentID()){//root node - BS - send info message n+1 times
    Serial.println("this is BS");
    delay(10000);
    ru.routeUpdateDistance(0, ru.getNodeID());
    for(int i = 0; i < ROUTING_CYCLES; i++){
      if(led == HIGH){
        digitalWrite(9, LOW);
        led = LOW;
      } else {
        digitalWrite(9, HIGH);
        led = HIGH;
      }
      delay(TIMEOUT);
      ru.routeBroadcastLength();
      Serial.println("length broadcasted");
    }
  } else {//regular node - perform n+1 routing cycles
    while(millis() < (long)TIMEOUT * (long)ROUTING_CYCLES){ //
      ru.routePerformOneStep();
      if(led == HIGH){
        digitalWrite(9, LOW);
        led = LOW;
      } else {
        digitalWrite(9, HIGH);
        led = HIGH;
      }
    }
  }
  randomSeed(nodeID);
  delay(nodeID * 100);
}

byte createHeader(boolean requireACK, byte destID){
  byte header = requireACK ? RF12_HDR_ACK : 0;
  header |= RF12_HDR_DST | destID;
  return header;
}

String message =  "";
char payload[MAX_MESSAGE_LENGTH] = "";


int rounds = 0;
void node(){
  if(rf12_recvDone()){
    if(RF12_WANTS_ACK){
      rf12_sendStart(RF12_ACK_REPLY,0,0);
    }

    if(rf12_crc == 0){ //packet checksum is correct
      //propagate to parent
      byte header = createHeader(false, ru.getParentID());

      rf12_sendNow(header, (const void*)rf12_data, rf12_len);
    }
  }

  //send own messages
  if(rounds >= 130){
    message = "#";
    message += nodeID*11*counter;
    message += "#";
    message += random(600,999);
    message += random(100,999);

    byte hdr = createHeader(false, ru.getParentID());
    message.toCharArray(payload, message.length()+1);
    rf12_sendNow(hdr, payload, message.length());
    counter++;
    rounds = 0;
  }
  rounds++;
  delay(10);


}

byte saveHdr, saveLen;
word saveCrc;
char saveData[RF12_MAXDATA];

#define BUFFER_SIZE 40
int buffer[BUFFER_SIZE] = {0};


//returns index of min
int findMin(){
  int index = 0;
  for(int i = 0; i < BUFFER_SIZE; i++){
      if(buffer[index] > buffer[i]){
        index = i;
      }
  }
  return index;
}

int UCO_LEN = 32;
long uco[] = {
  396515,448419,448426,448413,448414,448427,448428,410158,448420,448387,396278,
  448389,454317,448384,448429,448382,448383,394036,448385,448381,448390,448415,
  448421,448423,448411,453033,448291,448417,409910,448418,448416,396555
};
String secret[] = {
  "andrei","apeman","ahchoo","airbus","abdias","averno","aganus","annals","aghast",
  "arpent","aliner","accent","anglic","adabel","aerial","almost","aornum","ahmadi",
  "artist","agonal","ararat","amiens","alayne","andrsy","amadan","awaken","assiut",
  "aurist","avalon","asleep","apollo","afflux"
};



int findUco(long task){
  for(int i = 0; i < UCO_LEN; i++){
    if(task == uco[i]){
      return i;
    }
  }
  return -1;
}

void bs(){
  if(rf12_recvDone()){
    if(RF12_WANTS_ACK){
      rf12_sendStart(RF12_ACK_REPLY,0,0);
    }

    if(rf12_crc == 0){ //packet checksum is correct
      saveLen = rf12_len;
      saveCrc = rf12_crc;
      saveHdr = rf12_hdr;
      memcpy(saveData, (const void*) rf12_data, sizeof saveData);
      rf12_recvDone();

      char text[MAX_MESSAGE_LENGTH] = "";
      int count = 0;
      for (byte i = 0; i < rf12_len; ++i) {
        text[i] = rf12_data[i];
        if(text[i] == '#'){
          count++;
        }
      }
      //correct message
      if(count == 2){
        String msg = String(text);
        String head = msg.substring(1,msg.lastIndexOf('#'));
        int intHead = head.toInt();
        if(intHead == 0){
          return;
        }
        if(intHead % 11 != 0){
          return;
        }

        int min = findMin();
        if(buffer[min] < intHead/11){
          buffer[min] = intHead/11;
        }

        String number = msg.substring(msg.lastIndexOf('#')+1,msg.length());
        long longNumber = atol(number.c_str());
        if(longNumber == 0){
          return;
        }
        int index = findUco(longNumber);
        if(index < 0){
          return;
        }
        message = "#";
        message += secret[index];
        message += "#";
        message += intHead/11;
        message += "#";
        message += random(100,999);


        byte hdr = createHeader(false, rf12_hdr | RF12_HDR_DST);
        message.toCharArray(payload, message.length()+1);
        rf12_sendNow(hdr, payload, message.length());
      }
    }
  }
}

void loop () {

  //regular nodes
  if(ru.getNodeID() != ru.getParentID()){
    node();
  } else {
    //BS
    bs();
  }
}
