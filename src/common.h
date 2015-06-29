// common file for definitions, e.g. parameter lengths, possible node IDs, frequency settings, EEPROM locations etc.


#ifndef COMMON_H
#define COMMON_H

//ID ranges
#define MAX_NODE_ID 31
#define MAX_GROUP_ID 212

#define MIN_NODE_ID 0
#define MIN_GROUP_ID 1

//factory FREQUENCY of JeeLink nodes (radio modules are marked with yellow dot)
#define FREQUENCY RF12_868MHZ


//parser tag and param maximum lengths 
//TODO remove after upload app parser changed to string
#define INPUT_TAG_LEN 10
#define INPUT_PARAM_LEN 10


//EEPROM values locations
#define NODE_ID_LOCATION    0
#define GROUP_ID_LOCATION   1
#define PARENT_ID_LOCATION  2

//Serial output level 
// 0 - debug
// 1 - output
// 2 - error
#define OUTPUT_LEVEL 0


#endif //COMMON_H