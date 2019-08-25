#include "LXS_Config.h"
#include "HardwareSerial.h"

#if LXS_DEBUGPRINT    //Macros are usually in all capital letters.
#define LXS_DEBUGINIT(serial, baud) serial.begin(baud)
#define LXS_DPRINT(...)    Serial.print(__VA_ARGS__)     //DPRINT is a macro, debug print
#define LXS_DPRINTLN(...)  Serial.println(__VA_ARGS__)   //DPRINTLN is a macro, debug print with new line
#else
#define LXS_DEBUGINIT(serial, baud)
#define LXS_DPRINT(...)     //now defines a blank line
#define LXS_DPRINTLN(...)   //now defines a blank line
#endif