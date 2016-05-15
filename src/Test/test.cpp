
#include <Arduino.h>
#include <EEPROM.h>
#include "RF12.h"
#include "RadioUtils.h"
#include "SerialUtils.h"

#include <../common.h>


const byte LED = 9;
byte counter;

//RadioUtils ru = RadioUtils();


// turn the on-board LED on or off
static void led (bool on) {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, on ? 0 : 1); // inverted logic
}

void setup () {
  Serial.begin(57600);

  rf12_initialize(31, RF12_868MHZ, 42);



  for(int i = 0; i < 10; i++){
    String message = "distance:-1";
    char payload[14] = "";

    message.toCharArray(payload, message.length()+1);
    rf12_sendNow(0, payload, message.length());
    delay(500);
  }
}

void loop () {
  led(true);
  Serial.print("loop ");



  //rf12_sendWait(1);

  if(rf12_recvDone()){
    Serial.print("new msg ");

    if(rf12_crc == 0){

      //not a distance message
    //  if(rf12_data[0] == '#'){

        char text[60] = "";
        int count = 0;
        for (byte i = 0; i < rf12_len; ++i) {
          text[i] = rf12_data[i];
          if(text[i] == '#'){
            count++;
          }
        }

        String msg = String(text);
        Serial.print("received: ");
        Serial.println(text);
      //}
    }
  } else {
      /*
        String head = msg.substring(1,msg.lastIndexOf('#'));
*/
        delay(500);

        String message = "#";
        message += "1111";
        message += "#";
        message += "394036";

        char payload[14] = "";

        message.toCharArray(payload, message.length()+1);
        Serial.print("send: ");
        Serial.println(payload);
        //5 is BS
        Serial.println(message.length());
        if(rf12_canSend){
          rf12_sendStart(0, payload, message.length());
        }

      //}
      led(false);
    }
  //}
}
