// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.


#include <CAN.h>
#include <WiFi.h>
#include <WiFiUdp.h>

WiFiUDP port;

int status = WL_IDLE_STATUS;
char packetBuffer[255];
unsigned int localPort = 9999;

const char *ssid = "MyESP32AP";
const char *password = "testpassword";

char output[4];
char address[4];
char  ReplyBuffer[4];



//---------------------------------------------------------------//
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  Serial.println("CAN Receiver");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }

  status = WiFi.softAP(ssid, password);
   
  Serial.println();
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  port.begin(localPort);
}

void loop() {
  
  // try to parse packet
  int packetSize = CAN.parsePacket();
  
  if (packetSize) {    
    if (CAN.packetId() == 0x55) {
      Serial.print("Recieved packet ... ");
      output[0] = (char)CAN.read();
      output[1] = (char)CAN.read();
      output[2] = (char)CAN.read();
      output[3] = (char)CAN.read();
      address[0] = '0';
      address[1] = '0';
      address[2] = '5';
      address[3] = '5';
      
      Serial.print(address[0]);
      Serial.print(address[1]);
      Serial.print(address[2]);
      Serial.print(address[3]);       
      Serial.print(output[0]);
      Serial.print(output[1]);
      Serial.print(output[2]);
      Serial.print(output[3]);

    port.beginPacket("192.168.4.2",localPort);
    port.write(address[0]);
    port.write(address[1]);
    port.write(address[2]);
    port.write(address[3]);
    port.write(output[0]);
    port.write(output[1]);
    port.write(output[2]);
    port.write(output[3]);
    port.endPacket();
          Serial.println();
    printWiFiStatus();
     } else if (CAN.packetId() == 0x60) {
      Serial.print("Recieved packet ... ");
      output[0] = (char)CAN.read();
      output[1] = (char)CAN.read();
      output[2] = (char)CAN.read();
      output[3] = (char)CAN.read();
      address[0] = '0';
      address[1] = '0';
      address[2] = '6';
      address[3] = '0';      
      Serial.print(address[0]);
      Serial.print(address[1]);
      Serial.print(address[2]);
      Serial.print(address[3]); 
      Serial.print(output[0]);
      Serial.print(output[1]);
      Serial.print(output[2]);
      Serial.print(output[3]);

    port.beginPacket("192.168.4.2",localPort);
    port.write(address[0]);
    port.write(address[1]);
    port.write(address[2]);
    port.write(address[3]);
    port.write(output[0]);
    port.write(output[1]);
    port.write(output[2]);
    port.write(output[3]);
    port.endPacket();
          Serial.println();
    printWiFiStatus();
     } else if (CAN.packetId() == 0x61) {
      Serial.print("Recieved packet ... ");
      output[0] = (char)CAN.read();
      output[1] = (char)CAN.read();
      output[2] = (char)CAN.read();
      output[3] = (char)CAN.read();
      address[0] = '0';
      address[1] = '0';
      address[2] = '6';
      address[3] = '1';      
      Serial.print(address[0]);
      Serial.print(address[1]);
      Serial.print(address[2]);
      Serial.print(address[3]); 
      Serial.print(output[0]);
      Serial.print(output[1]);
      Serial.print(output[2]);
      Serial.print(output[3]);

    port.beginPacket("192.168.4.2",localPort);
    port.write(address[0]);
    port.write(address[1]);
    port.write(address[2]);
    port.write(address[3]);
    port.write(output[0]);
    port.write(output[1]);
    port.write(output[2]);
    port.write(output[3]);
    port.endPacket();
          Serial.println();
    printWiFiStatus();
     } else if (CAN.packetId() == 0x62) {
      Serial.print("Recieved packet ... ");
      output[0] = (char)CAN.read();
      output[1] = (char)CAN.read();
      output[2] = (char)CAN.read();
      output[3] = (char)CAN.read();
      address[0] = '0';
      address[1] = '0';
      address[2] = '6';
      address[3] = '2';      
      Serial.print(address[0]);
      Serial.print(address[1]);
      Serial.print(address[2]);
      Serial.print(address[3]); 
      Serial.print(output[0]);
      Serial.print(output[1]);
      Serial.print(output[2]);
      Serial.print(output[3]);

    port.beginPacket("192.168.4.2",localPort);
    port.write(address[0]);
    port.write(address[1]);
    port.write(address[2]);
    port.write(address[3]);
    port.write(output[0]);
    port.write(output[1]);
    port.write(output[2]);
    port.write(output[3]);
    port.endPacket();
          Serial.println();
    printWiFiStatus();
     }
      Serial.println();
    delay(10);
    }
    
    delay(10);
}


void printWiFiStatus() {
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}





