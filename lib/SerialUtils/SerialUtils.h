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

    void print(String text, Priority priority);
    
    //just calls print and adds newline
    void println(String text, Priority priority);
    
    int getNumErrors();
private:
    long freq;
    int errors;

};



#endif // SERIALUTILS_H
