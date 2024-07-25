/*
  Web client

 This sketch connects to a website (http://arduino.cc)
 using the Ethernet module.

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 modified in Jul 2019 for WiFiEspAT library
 modified in Jul 2024 for EthernetEspAT library
 by Juraj Andrassy https://github.com/jandrassy
 */

#include <EthernetEspAT.h>

// Emulate Serial1 on pins 6/7 if not present
#if defined(ARDUINO_ARCH_AVR) && !defined(HAVE_HWSERIAL1)
#include <SoftwareSerial.h>
SoftwareSerial Serial1(6, 7); // RX, TX
#define AT_BAUD_RATE 9600
#else
#define AT_BAUD_RATE 115200
#endif

const char* server = "arduino.tips";

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 177);

EthernetClient client;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial1.begin(AT_BAUD_RATE);
  Ethernet.init(Serial1);

  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println();
    Serial.println("Communication with the network module failed!");
    // don't continue
    while (true);
  }

  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin() == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to configure using IP address instead of DHCP:
    Ethernet.begin(ip);
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }

  Serial.println("Starting connection to server...");
  if (client.connect(server, 80)) {
    Serial.println("connected to server");

    client.println("GET /asciilogo.txt HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();
    client.flush();
  }
}

void loop() {

  // if there are incoming bytes available
  // from the server, read them and print them
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  // if the server's disconnected, stop the client
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();

    // do nothing forevermore
    while (true);
  }
}
