
## EthernetEspAT library

This library creates standard Arduino Ethernet networking API over ESP8266 or ESP32 AT commands. The Arduino Ethernet networking API was established by Arduino Ethernet library.

EthernetEspAT extends the [WiFiEspAT](https://github.com/JAndrassy/WiFiEspAT) library with Ethernet object and Ethernet named aliases for WiFiClient, WiFiUDP and WiFiServer from WiFiEspAT.

The library is for all Arduino MCU architectures. It enables secure connection (https) over wired network even for 8-bit architecture boards.

### AT firmware with Ethernet support

Standard AT firmware builds by Espressif don't support Ethernet.

ESP32 AT firmware supports Ethernet commands but they have to be [enabled](https://docs.espressif.com/projects/esp-at/en/latest/esp32/Compile_and_Develop/How_to_enable_ESP_AT_Ethernet.html) in build configuration and build from sources.

The ESP32 AT firmware source only supports Ethernet PHY modules: LAN8720, IP101, DP83848 and RTL8201. A modified AT firmware supporting W5500 will be available soon.

ESP8266 AT firmware by Espressif doesn't support Ethernet. Jiri Bilek's [ESP_ATMod firmware](https://github.com/JiriBilek/ESP_ATMod#description) for ESP8266 will support Ethernet with Ethernet chips supported by the ESP8266 Arduino platform.

* [ESP32 AT firmware binaries with Ethernet support](https://github.com/Networking-for-Arduino/EthernetEspAT/wiki/ESP32-firmware)
* [esp8266 ESP_ATMod sketch with Ethernet support](https://github.com/JAndrassy/ESP_ATMod/tree/ethernet_support)

For installing and testing the AT firmware see the WiFiEspAT [documentation](https://github.com/JAndrassy/WiFiEspAT?tab=readme-ov-file#getting-started).
