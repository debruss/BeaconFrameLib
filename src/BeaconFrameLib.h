#ifndef BEACONFRAMELIB_H
#define BEACONFRAMELIB_H

#include <Arduino.h>

// Stores the length of the beacon frame after it is build
extern int BeaconFrameLength;

// Prototypes
uint8_t* build_beacon_packet(char* beacon_name, int* mac_address, int beacon_channel);

#endif
