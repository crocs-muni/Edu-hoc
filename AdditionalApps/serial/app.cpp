#include <Arduino.h>



void setup () {
  Serial.begin(57600);
}

int nodeID = 5;
int counter = 1;

void loop () {
  String message = "";
  message += "#";
  message += nodeID*11*counter;
  message += "#";
  message += random(500,999);
  message += random(100,999);
  Serial.println(message);

  counter++;
  //Serial.println(counter);


  char text[60];
  message.toCharArray(text,60);
  int count = 0;
  Serial.println(count);
  for (byte i = 0; i < message.length(); ++i) {
    //text[i] = rf12_data[i];
    if(text[i] == '#'){
      count++;
    }
  }
  //correct message
  Serial.println(count);
  if(count == 2){
    String payload = String(text);
    String head = payload.substring(1,payload.lastIndexOf('#'));
    Serial.print("head");
    Serial.println(head);
    String number = payload.substring(payload.lastIndexOf('#')+1,payload.length());
    Serial.print("number");
    Serial.println(number);
  }
  delay(1000);
}
