///Sniffer code used from http://forum.jeelabs.net/node/272.html
///author: jcw

#include <Ports.h>
#include <RF12.h>

byte saveHdr, saveLen, saveData[RF12_MAXDATA];
word saveCrc;

void setup () {
    Serial.begin(57600);
    Serial.println("\n[sniffer] 868 MHz group 5");
    rf12_initialize(31, RF12_868MHZ, 5);
}

void loop () {

    if (rf12_recvDone()) {
        // quickly save a copy of all volatile data saveLen = rf12_len;
        saveCrc = rf12_crc;
        saveHdr = rf12_hdr;
        memcpy(saveData, (const void*) rf12_data, sizeof saveData);
        rf12_recvDone();
        // release lock on info for next reception
        if (saveCrc != 0) {
            Serial.print("CRC error #");
            Serial.println(saveLen, DEC);
        }
        else {
            Serial.print("OK (");
            for (byte i = 0;
                 i < 8;
                 ++i) Serial.print(bitRead(saveHdr, 7-i));
            Serial.print("b) ");
            Serial.print(saveHdr & RF12_HDR_ACK ? "REQ " : " ");
            Serial.print(saveHdr & RF12_HDR_CTL ? "ACK " : " ");
            Serial.print(saveHdr & RF12_HDR_DST ? "DST:" : "SRC:");
            Serial.print(saveHdr & RF12_HDR_MASK);
            Serial.print(" #");
            Serial.println(saveLen,DEC);
            // print out all data bytes, wrapping long lines byte pos = 0;
	    int pos = 0;
            for (byte i = 0; i < saveLen; ++i) {
                Serial.print(' ');
                Serial.print(saveData[i],HEX);
                pos += 2;
                if (saveData[i] >= 16) ++pos;
                if (pos > 75) {
                    Serial.println();
                    pos = 0;
                }
            }
            if (pos > 0) Serial.println();
        }
    }
}
