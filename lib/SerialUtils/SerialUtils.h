#ifndef SERIALUTILS_H
#define SERIALUTILS_H
#include <Arduino.h>

class SerialUtils
{
public:
    SerialUtils(int freq);

    void setUpNodeID(int* id, int* group, int* parent);

private:
    int freq;

};

#endif // SERIALUTILS_H
