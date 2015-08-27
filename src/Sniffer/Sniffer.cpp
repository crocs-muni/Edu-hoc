///Sniffer code used from http://forum.jeelabs.net/node/272.html
///author: jcw

/// some changes by LukeMcNemee

#include <Arduino.h>
#include "RF12.h"

#include "SerialUtils.h"
#include <../common.h>

//#include <Ports.h>
//#include <RF12.h>
//#include <../common.h>
//#include "SerialUtils.h"


#define GROUP 5

byte saveHdr, saveLen, saveData[RF12_MAXDATA];
word saveCrc;

SerialUtils su = SerialUtils(SERIAL_FREQUENCY);


void setup () {
    //saveLen = 255;
    Serial.begin(SERIAL_FREQUENCY);
    su.println("\n[sniffer] 868 MHz group 10", output);
    rf12_initialize(31, FREQUENCY, 10);
}

void loop () {

    if (rf12_recvDone()) {
        // quickly save a copy of all volatile data saveLen = rf12_len;
        saveLen = rf12_len;
        saveCrc = rf12_crc;
        saveHdr = rf12_hdr;
        memcpy(saveData, (const void*) rf12_data, sizeof saveData);
        rf12_recvDone();
        // release lock on info for next reception
        if (saveCrc != 0) {
            su.print("CRC error #", output);
            su.println(saveLen, DEC, output);
        }
        else {
            su.print("OK (", output);
            String header = "";
            for (byte i = 0; i < 8; ++i) {
                header.concat(bitRead(saveHdr, 7-i)); // read bytes of header individualy into string
            }
            su.print(header, output);
            su.print("b) ", output);
            su.print(saveHdr & RF12_HDR_ACK ? "REQ " : " ", output);
            su.print(saveHdr & RF12_HDR_CTL ? "ACK " : " ", output);
            su.print(saveHdr & RF12_HDR_DST ? "DST:" : "SRC:", output);
            su.print(saveHdr & RF12_HDR_MASK, output);
            su.print(" #", output);
            Serial.print(saveLen,DEC);
            // print out all data bytes, wrapping long lines byte pos = 0;
	    int pos = 0;
            for (byte i = 0; i < saveLen; ++i) {
                su.print(' ', output);
                Serial.print(saveData[i],HEX);
                pos += 2;
                if (saveData[i] >= 16) ++pos;
                if (pos > 75) {
                    su.println();
                    pos = 0;
                }
            }
            if (pos > 0) su.println();
        }
    }
}
