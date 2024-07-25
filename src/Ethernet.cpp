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

#include "Ethernet.h"
#include <utility/EspAtDrv.h>

// these statics are removed by compiler, if not used
char EthernetClass::fwVersion[15] = {0};
char EthernetClass::name[33] = {0}; // hostname

EthernetClass::EthernetClass() {
}

bool EthernetClass::init(Stream& serial, int8_t resetPin) {
  bool ok = EspAtDrv.init(&serial, resetPin);
  if (ok) {
    hwStatus = EthernetHardwareFound;
  }
  return ok;
}

bool EthernetClass::setPersistent(bool persistent) {
  return EspAtDrv.sysPersistent(persistent);
}

int EthernetClass::begin(uint8_t *mac, unsigned long timeout) {
  if (mac != nullptr && !EspAtDrv.ethSetMac(mac))
    return 0;
  if (!EspAtDrv.ethEnableDHCP())
    return false;
  if (timeout) {
    const unsigned long start = millis();
    while ((millis() - start) < timeout) {
      if (localIP() != INADDR_NONE)
        return true;
      delay(200);
    }
  }
  return (localIP() != INADDR_NONE);
}

bool EthernetClass::begin(uint8_t *mac, IPAddress localIP, IPAddress dnsIP, IPAddress gatewayIP, IPAddress netmask) {
  (void) mac;
  if (dnsIP == INADDR_NONE) {
    dnsIP = localIP;
    dnsIP[3] = 1;
  }
  return EspAtDrv.ethStaticIp(localIP, gatewayIP, netmask) && setDNS(dnsIP);
}

int EthernetClass::begin(unsigned long timeout) {
  return begin(nullptr, timeout);
}

bool EthernetClass::begin(IPAddress ip, IPAddress dns, IPAddress gateway, IPAddress subnet) {
  return begin(nullptr, ip, dns, gateway, subnet);
}

int EthernetClass::maintain() {
  EspAtDrv.maintain();
  return 0;
}

void EthernetClass::end() {

}

EthernetLinkStatus EthernetClass::linkStatus() {
  return EspAtDrv.ethStatus() ? LinkON : LinkOFF;
}

EthernetHardwareStatus EthernetClass::hardwareStatus() {
  return hwStatus;
}

void EthernetClass::MACAddress(uint8_t *mac) {
  macAddress(mac);
}

IPAddress EthernetClass::dnsServerIP() {
  return dnsIP();
}

void EthernetClass::setDnsServerIP(const IPAddress dns) {
  setDNS(dns);
}

bool EthernetClass::setDNS(IPAddress dns_server1, IPAddress dns_server2) {
  return EspAtDrv.setDNS(dns_server1, dns_server2);
}

bool EthernetClass::setHostname(const char* name) {
  return EspAtDrv.setEthHostname(name);
}

const char* EthernetClass::hostname(char* buffer) {
  if (!EspAtDrv.ethHostnameQuery(buffer)) {
    buffer[0] = 0;
  }
  return buffer;
}

uint8_t* EthernetClass::macAddress(uint8_t* mac) {
  if (!EspAtDrv.ethMacQuery(mac))
    return nullptr;
  return mac;
}

IPAddress EthernetClass::localIP() {
  IPAddress ip;
  IPAddress gw;
  IPAddress mask;
  EspAtDrv.ethIpQuery(ip, gw, mask);
  return ip;
}

IPAddress EthernetClass::gatewayIP() {
  IPAddress ip;
  IPAddress gw;
  IPAddress mask;
  EspAtDrv.ethIpQuery(ip, gw, mask);
  return gw;
}

IPAddress EthernetClass::subnetMask() {
  IPAddress ip;
  IPAddress gw;
  IPAddress mask;
  EspAtDrv.ethIpQuery(ip, gw, mask);
  return mask;
}

IPAddress EthernetClass::dnsIP(int n) {
  IPAddress dns1;
  IPAddress dns2;
  EspAtDrv.dnsQuery(dns1, dns2);
  switch (n) {
    case 0:
      return dns1;
    case 1:
      return dns2;
  }
  return IPAddress(0, 0, 0, 0);
}

bool EthernetClass::dhcpIsEnabled() {
  bool sta;
  bool ap;
  bool eth;
  if (!EspAtDrv.dhcpStateQuery(sta, ap, eth))
    return false;
  return eth;
}


bool EthernetClass::startMDNS(const char* hostname, const char* serverName, uint16_t serverPort) {
  return EspAtDrv.mDNS(hostname, serverName, serverPort);
}

bool EthernetClass::hostByName(const char* hostname, IPAddress& result) {
  return EspAtDrv.resolve(hostname, result);
}

bool EthernetClass::ping(const char* hostname) {
  return EspAtDrv.ping(hostname);
}

bool EthernetClass::ping(IPAddress ip) {
  char s[16];
  EspAtDrv.ip2str(ip, s);
  return ping(s);
}

bool EthernetClass::sntp(const char* server1, const char* server2) {
  return EspAtDrv.sntpCfg(server1, server2);
}

unsigned long EthernetClass::getTime() {
  return EspAtDrv.sntpTime();
}

const char* EthernetClass::firmwareVersion(char* buffer) {
  EspAtDrv.firmwareVersion(buffer);
  return buffer;
}

EspAtDrvError EthernetClass::getLastDriverError() {
  return EspAtDrv.getLastErrorCode();
}

bool EthernetClass::sleepMode(EspAtSleepMode mode) {
  return EspAtDrv.sleepMode(mode);
}

bool EthernetClass::deepSleep() {
  return EspAtDrv.deepSleep();
}

bool EthernetClass::reset(uint8_t resetPin) {
  return EspAtDrv.reset(resetPin);
}

bool EthernetClass::wifiOff(bool save) {
  return EspAtDrv.wifiOff(save);
}


EthernetClass Ethernet;
