# BeaconFrameLib
BeaconFrameLib is a library that can be used to create beacon frames, which can be used to fake a WiFi network. Currently this library supports custom SSID's and custom/random MAC addresses. This will be expanded to information like security for example. 

## Contribute
In the case of any issues that might occur, please send them via the [Issues tab](https://github.com/debruss/BeaconFrameESP8266/issues). Also, pull requests with new/improved features are always welcome :) 

## Documentation
Currently this, and the comments in the code are the only available documentation.

BeaconFrameLib includes two things when included:
- `int BeaconFrameLength`: this variable stores the length of the beacon frame; changing it is not recommended
- `uint8_t* build_beacon_packet(char* beacon_name, int* mac_address, int beacon_channel, bool random_mac)`: this function builds the beaconpacket (and meanwhile sets `int BeaconFrameLength` accordingly). It returns the address of the start of the beacon.

## Libraries
This library depends on:
- [ESP8266WiFi.h](https://github.com/esp8266/Arduino)

## Examples
Currently I have only an example that is suitable for the ESP8266. If you have an example for other devices, please send them via a pull request. I will be more than happy to include it :)


## License
This program is available under the [MIT License](https://github.com/debruss/BeaconFrameLib/blob/master/LICENSE).
