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

    int routeGetLength();

    void routeBroadcastLength();

    int routeParseDistance(String d);

    void enableDynamicRouting();

    void initialize();

    int getNodeID();

    int getGroupID();

    int getParentID();

    \**
    * txPower range from 0 to 7, 0=highest, 7=lowest
    *\
    void setTransmitPower(byte txPower);

//how many times does sleep(10) cycle run before it ends
//can be used for various timeouts (routing, etc.)

private:
    bool dynamicRouting;
    int distance;
    byte parent;

    int nodeID;
    int groupID;
    int parentID;
};

#endif // RADIOUTILS_H
