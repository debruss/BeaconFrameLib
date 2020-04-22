#include "BeaconFrameLib.h"
#include <ESP8266WiFi.h>


// In BeaconFrameLib.h this variable is defined as an extern one
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





// Supported rates (it is not changeable for now; if security features are added, this one will also change)
const uint8_t tail[] = {0x01, 0x08, 0x82, 0x84, 0x8b, 0x96, 0x24, 0x30, 0x48, 0x6c, 0x03, 0x01}; 





/**
 * Build the beacon frame.
 *
 * This function build a beacon frame and assigns the length of it to the extern integer BeaconFrameLength.
 * 
 * @param beacon_name Pointer to the SSID of the beacon frame.
 * @param mac_address Pointer to the MAC Address that the user wants to set (if set to NULL, it will create a random MAC).
 * @param beacon_channel Integer that specifies which channel. If 0, a random channel is chosen.
 * @return pointer to the start of the beacon frame.
 */
uint8_t* build_beacon_packet(char* beacon_name, int* mac_address, int beacon_channel)
{
  if(mac_address == NULL)
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

  

  // Set the channel
  if(beacon_channel == 0) beacon_channel = random(12);
  
  // This should not be here, but it is a neccessary thing to set
  // I don't want the user to have to remember this step.
  wifi_set_channel(beacon_channel);
  
  // Determine the length of the SSID and save it in int q.
  // This will be neccessary to calculate the length of the beacon frame.
  int ssid_length = 0;
  do {
    ssid_length++;
  } while(beacon_name[ssid_length] != '\0');

  packet[37] = ssid_length;
  for(int i = 0; i < ssid_length; i++) packet[38+i] = beacon_name[i];
  for(int i = ssid_length; i < ssid_length+12; i++) packet[i+38] = tail[i-ssid_length];
  packet[50+ssid_length] = beacon_channel; // 38+12+q

  BeaconFrameLength = 48 + ssid_length;  // 38+12+q-2;
  return packet;
}






/**
 * Build a simple beacon frame.
 *
 * This function builds a simple beacon frame. This function is extra useful for getting to know this library, since it only needs an SSID.
 * 
 * @param beacon_name Pointer to the SSID of the beacon frame.
 * @return pointer to the start of the beacon frame.
 */
uint8_t* build_simple_beacon_packet(char* beacon_name)
{
  return build_beacon_packet(beacon_name, NULL, 0);
}
