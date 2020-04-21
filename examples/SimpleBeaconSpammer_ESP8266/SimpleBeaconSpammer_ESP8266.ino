// BeaconFrameESP8266
// Year: 2020
// Place: Quarantine


/* 
 *  ===== HOW TO USE =====
 *  1. Enter number of networks in: num_of_networks
 *  2. Enter the SSID's in: ssids[]
 *  3. Let's go...
 */


#include <ESP8266WiFi.h>
#include <BeaconFrameLib.h>

// Adding the good stuff
extern "C" {
  #include "user_interface.h"
}


// === SETTINGS === 
const int num_of_networks = 5;
char* ssids[num_of_networks] =
{
  "It burns when IP",
  "NSA Surveillance Pigeon",
  "McDonald's Free WiFi",
  "Shout \"MONKEY\" for password",
  "NSA Surveillance Flower"
};          



void setup() {
  delay(500);
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(1);
}



void loop() {
  for(int k = 0; k < num_of_networks; k++)
  {
	// Make the packet, and store the start address of the packet in uint8_t* packet
    uint8_t* packet = build_simple_beacon_packet(ssids[k]);
	
	// Send every packet 3 times
	// BeaconFrameLength get a value automatically; changing it is not recommended
    for(int i = 0; i < 3; i++) wifi_send_pkt_freedom(packet, BeaconFrameLength, 0);

    delay(1);
  }
}
