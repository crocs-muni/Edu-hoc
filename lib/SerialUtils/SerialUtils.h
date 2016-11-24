#ifndef SERIALUTILS_H
#define SERIALUTILS_H
#include <Arduino.h>

#include <../../src/common.h>


enum Priority{

    debug = 0,
    output = 1,
    error = 2
} ;

class SerialUtils
{
public:
    SerialUtils(long freq);

    void setUpNodeID(int* id, int* group, int* parent);

    void print(String text, Priority priority);
    
    void print(byte b, Priority priority);

    void print(String text, int format, Priority priority);
    
    void print(byte b, int format, Priority priority);
    
    //just calls print and adds newline
    void println(String text, Priority priority);
    
    void println(String text, int format, Priority priority);

    void println(byte b, Priority priority);

    void println(byte b, int format, Priority priority);
    
    void println();

    
    int getNumErrors();
private:
    long freq;
    int errors;

};



#endif // SERIALUTILS_H
