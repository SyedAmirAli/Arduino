#ifndef RESOURCES_H
#define RESOURCES_H
#include <Arduino.h>

extern const char webpage[] PROGMEM;
extern void writeStringIntoEEPROM(int address, String str);
extern String readStringFromEEPROM(int address);

#endif
