/*
  This file is part of the EthernetEspAT library for Arduino
  https://github.com/Networking-for-Arduino/EthernetEspAT
  Copyright 2024 Juraj Andrassy

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _ETHERNET_ESPAT_H_
#define _ETHERNET_ESPAT_H_

#include <Arduino.h>
#include <IPAddress.h>
#include "WiFiEspAtConfig.h"
#include "utility/EspAtDrvTypes.h"
#include "WiFiClient.h"
#include "WiFiServer.h"
#include "WiFiUdp.h"
#include "WiFiSSLClient.h"

enum EthernetLinkStatus {
  Unknown, LinkON, LinkOFF
};

enum EthernetHardwareStatus {
  EthernetNoHardware, EthernetHardwareFound
};

class EthernetClass {

public:

  EthernetClass();

  bool init(Stream& serial, int8_t resetPin = -1);
  bool setPersistent(bool persistent = true);

  int begin(uint8_t *mac, unsigned long timeout = 60000);
  bool begin(uint8_t *mac, IPAddress ip, IPAddress dns = INADDR_NONE, IPAddress gateway = INADDR_NONE, IPAddress subnet = INADDR_NONE);

  int begin(unsigned long timeout = 60000);
  bool begin(IPAddress ip, IPAddress dns = INADDR_NONE, IPAddress gateway = INADDR_NONE, IPAddress subnet = INADDR_NONE);

  void end();
  int maintain();

  EthernetLinkStatus linkStatus();
  EthernetHardwareStatus hardwareStatus();

  uint8_t* macAddress(uint8_t* mac);
  void MACAddress(uint8_t *mac_address);

  IPAddress localIP();
  IPAddress subnetMask();
  IPAddress gatewayIP();
  IPAddress dnsServerIP();
  IPAddress dnsIP(int n = 0);
  bool dhcpIsEnabled();

  void setDnsServerIP(const IPAddress dns_server);
  bool setDNS(IPAddress dns_server1, IPAddress dns_server2 = INADDR_NONE);

  bool setHostname(const char* hostname); // only the pointer is stored!
  const char* hostname(char* buffer = name);

  bool startMDNS(const char* hostname, const char* serverName, uint16_t serverPort);

  bool hostByName(const char* hostname, IPAddress& result);

  bool ping(const char* hostname);
  bool ping(IPAddress ip);

  bool sntp(const char* server1, const char* server2 = nullptr);
  unsigned long getTime();

  const char* firmwareVersion(char* buffer = fwVersion);
  EspAtDrvError getLastDriverError();

  bool sleepMode(EspAtSleepMode mode);
  bool deepSleep();
  bool reset(uint8_t resetPin = -1);

  bool wifiOff(bool save = false);

private:
  EthernetHardwareStatus hwStatus = EthernetNoHardware;

  // this members are removed by compiler if the corresponding function is not used
  static char fwVersion[]; // static is for use as default parameter value of function
  static char name[]; // hostname

};

extern EthernetClass Ethernet;

typedef WiFiUDP EthernetUDP;
typedef WiFiServer EthernetServer;
typedef WiFiClient EthernetClient;
typedef WiFiSSLClient EthernetSSLClient;

#endif
