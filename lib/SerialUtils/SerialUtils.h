#ifndef SERIALUTILS_H
#define SERIALUTILS_H
#include <Arduino.h>

#include <../../src/common.h>


enum Priority{
    error, 
    output,
    debug    
} ;

class SerialUtils
{
public:
    SerialUtils(long freq);

    void setUpNodeID(int* id, int* group, int* parent);

    void print(char* text, Priority priority);
    
    void println(char* text, Priority priority);
private:
    long freq;

};



#endif // SERIALUTILS_H
