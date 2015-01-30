#ifndef RADIOUTILS_H
#define RADIOUTILS_H
#include <Arduino.h>

class RadioUtils
{
public:
    RadioUtils();

    int setAck(byte* hdr);

    int resetAck(byte* hdr);

    int setBroadcast(byte* hdr);

    int setID(byte* hdr, byte id);

    int getID(byte* hdr, byte* id);
};

#endif // RADIOUTILS_H
