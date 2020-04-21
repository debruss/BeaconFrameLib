#ifndef BEACONFRAMELIB_H
#define BEACONFRAMELIB_H

#include <Arduino.h>

extern int BeaconFrameLength;
uint8_t* build_beacon_packet(char* beacon_name, int* mac_address, int beacon_channel);

#endif
