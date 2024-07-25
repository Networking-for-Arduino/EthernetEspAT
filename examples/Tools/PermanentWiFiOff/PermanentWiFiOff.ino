
#include <EthernetEspAT.h>

// Emulate Serial1 on pins 6/7 if not present
#if defined(ARDUINO_ARCH_AVR) && !defined(HAVE_HWSERIAL1)
#include <SoftwareSerial.h>
SoftwareSerial Serial1(6, 7); // RX, TX
#define AT_BAUD_RATE 9600
#else
#define AT_BAUD_RATE 115200
#endif

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial1.begin(AT_BAUD_RATE);
  if (!Ethernet.init(Serial1)) {
    Serial.println();
    Serial.println("Communication with the network module failed!");
    // don't continue
    while (true);
  }

  Ethernet.wifiOff(true);

}

void loop() {
  Ethernet.maintain();
}
