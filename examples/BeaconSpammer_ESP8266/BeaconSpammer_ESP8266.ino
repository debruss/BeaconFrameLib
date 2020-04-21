// BeaconFrameESP8266
// Year: 2020
// Place: Quarantine


/* 
 *  ===== HOW TO USE =====
 *  1. Enter number of networks in: num_of_networks
 *  2. Enter the SSID's in: ssids[]
 *  3. Choose whether you have custom MAC Addresses or not at: const bool use_random_mac
 *  4. If you have custom MAC's, add them at: MACAddresses[]
 *  5. Let's go...
 */


#include <ESP8266WiFi.h>
#include <BeaconFrameLib.h>

extern "C" {
  #include "user_interface.h"
}


// === SETTINGS === 
const int num_of_networks = 6;
const bool use_random_mac = true;
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
  //Serial.begin(115200);
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(1);
}



void loop() {
  for(int k = 0; k < num_of_networks; k++)
  {
    uint8_t* packet = build_beacon_packet(ssids[k], MACAddresses[k], 1, use_random_mac); // false --> use predefined MAC's, true --> create random MAC's
    for(int i = 0; i < 3; i++) wifi_send_pkt_freedom(packet, BeaconFrameLength, 0);
    delay(1);
  }
}
