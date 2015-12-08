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

    int routePerformOneStep();

    int routeUpdateDistance(int d, byte p);

    int routeGetParent();

    int routeGetLength();

    void routeBroadcastLength();

    int routeParseDistance(String d);

    void enableDynamicRouting();

//how many times does sleep(10) cycle run before it ends
//can be used for various timeouts (routing, etc.)
    const static int TIMEOUT = 1000;
private:
    bool dynamicRouting;
    int distance;
    byte parent;
};

#endif // RADIOUTILS_H
