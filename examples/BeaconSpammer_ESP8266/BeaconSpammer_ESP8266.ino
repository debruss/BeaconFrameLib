// BeaconFrameESP8266
// Year: 2020
// Place: Quarantine


/* 
 *  ===== HOW TO USE =====
 *  1. Enter number of networks in: num_of_networks
 *  2. Enter the SSID's in: ssids[]
 *  3. If you have custom MAC's, add them at: MACAddresses[]. If you want random MAC's enter NULL
 *  4. Let's go...
 */


#include <ESP8266WiFi.h>
#include <BeaconFrameLib.h>

extern "C" {
  #include "user_interface.h"
}


// === SETTINGS === 
const int num_of_networks = 6;
char* ssids[num_of_networks] =
{
  "DeBruss",
  "It burns when IP",
  "NSA Surveillance Pigeon",
  "McDonald's Free WiFi",
  "Shout \"MONKEY\" for password",
  "NSA Surveillance Flower"
};
int MACAddresses[num_of_networks][6] = 
{
  {random(256),random(256),random(256),random(256),random(256),random(256)},
  {random(256),random(256),random(256),random(256),random(256),random(256)},
  {random(256),random(256),random(256),random(256),random(256),random(256)},
  {random(256),random(256),random(256),random(256),random(256),random(256)},
  {random(256),random(256),random(256),random(256),random(256),random(256)},
  {random(256),random(256),random(256),random(256),random(256),random(256)}
};            



void setup() {
  delay(500);
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(1);
}



void loop() {
  for(int k = 0; k < num_of_networks; k++)
  {
    uint8_t* packet = build_beacon_packet(ssids[k], MACAddresses[k], 1);
    for(int i = 0; i < 3; i++) wifi_send_pkt_freedom(packet, BeaconFrameLength, 0);
    delay(1);
  }
}
