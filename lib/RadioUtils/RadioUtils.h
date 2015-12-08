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

    int routeUpdateDistance(int d, byte p);

    int routeGetParent();

    int routeGetLength();

    int routeBroadcastLength();

    int routeParseDistance(String d);

    void enableDynamicRouting();

private:
    bool dynamicRouting;
    int distance;
    byte parent;
};

#endif // RADIOUTILS_H
