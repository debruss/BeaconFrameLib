#include "BeaconFrameLib.h"
#include <ESP8266WiFi.h>


int BeaconFrameLength = 0;


// Beacon Packet buffer 128
// Look into: https://core.ac.uk/download/pdf/14699804.pdf
uint8_t packet[128] = { 0x80, 0x00, 0x00, 0x00,                           // Frame Control
                /*4*/   0xff, 0xff, 0xff, 0xff, 0xff, 0xff,               // Destination (but it is a broadcast)
                /*10*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,               // Source address
                /*16*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,               // Source address
                /*22*/  0xc0, 0x6c,                                       // Fragment and sequence
                /*24*/  0x83, 0x51, 0xf7, 0x8f, 0x0f, 0x00, 0x00, 0x00,   // Timestamp
                /*32*/  0x64, 0x00,                                       // Interval
                /*34*/  0x01, 0x04,                                       // Capabilities
                /* SSID */
                /*36*/  0x00}; // More information is added in the build_beacon_packet() function         

// Supported rates
uint8_t tail[] = {0x01, 0x08, 0x82, 0x84, 0x8b, 0x96, 0x24, 0x30, 0x48, 0x6c, 0x03, 0x01}; 


uint8_t* build_beacon_packet(char* beacon_name, int* mac_address, int beacon_channel, bool random_mac)
{ 
  //int beacon_index = 0;
  //while(strcmp(beacon_name, ssids[beacon_index]) != 0) beacon_index++;
  // Randomize SRC MAC (for now)
  if(random_mac)
  {
    packet[10] = packet[16] = random(256);
    packet[11] = packet[17] = random(256);
    packet[12] = packet[18] = random(256);
    packet[13] = packet[19] = random(256);
    packet[14] = packet[20] = random(256);
    packet[15] = packet[21] = random(256);
  } else {
    for(int i = 0; i < 6; i++)
    {
      packet[10+i] = packet[16+i] = mac_address[i];
    }
  }

  

  // Set the channel:
  if(beacon_channel == 0) beacon_channel = random(12);
  wifi_set_channel(beacon_channel);
  
  int q = 0;
  do {
    q++;
  } while(beacon_name[q] != '\0');

  packet[37] = q;
  for(int i = 0; i < q; i++) packet[38+i] = beacon_name[i];
  for(int i = q; i < q+12; i++) packet[i+38] = tail[i-q];
  packet[50+q] = beacon_channel; // 38+12+q

  BeaconFrameLength = 48+q;  // 38+12+q-2;
  return packet;
}
