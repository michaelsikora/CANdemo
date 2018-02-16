// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.


#include <CAN.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <WiFi.h>
#include <WiFiUdp.h>

WiFiUDP port;

int status = WL_IDLE_STATUS;
char packetBuffer[255];
unsigned int localPort = 9999;

const char *ssid = "MyESP32AP";
const char *password = "testpassword";

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

char output[4];
char  ReplyBuffer[4];

//WiFiServer server(80);


void printMessage(char *message, int repeats){
  // send a message!
  for (uint8_t jj=0; jj<repeats; jj++){
  for (uint8_t i=0; i<strlen(message)-4; i++) {
    alpha4.writeDigitAscii(0, toupper(message[i]));
    alpha4.writeDigitAscii(1, toupper(message[i+1]));
    alpha4.writeDigitAscii(2, toupper(message[i+2]));
    alpha4.writeDigitAscii(3, toupper(message[i+3]));
    alpha4.writeDisplay();
    
    delay(250);
  }
  }
}

void printNumber(uint32_t number){
    sprintf(output, "%i", number);
    Serial.println(output);
    alpha4.writeDigitAscii(0, output[0]);
    alpha4.writeDigitAscii(1, output[1]);
    alpha4.writeDigitAscii(2, output[2]);
    alpha4.writeDigitAscii(3, output[3]);
    alpha4.writeDisplay();
//    delay(250);
}

void printChar4(char* number){
    alpha4.writeDigitAscii(0, number[0]);
    alpha4.writeDigitAscii(1, number[1]);
    alpha4.writeDigitAscii(2, number[2]);
    alpha4.writeDigitAscii(3, number[3]);
    alpha4.writeDisplay();
//    delay(250);
}

//---------------------------------------------------------------//
void setup() {
  Serial.begin(9600);

  // Setup backpack
  alpha4.begin(0x70);  // pass in the address
  alpha4.setBrightness(1);

//  start up all segment scroll task.
  alpha4.writeDigitRaw(3, 0x0);
  alpha4.writeDigitRaw(0, 0xFFFF);
  alpha4.writeDisplay();
  delay(200);
  alpha4.writeDigitRaw(0, 0x0);
  alpha4.writeDigitRaw(1, 0xFFFF);
  alpha4.writeDisplay();
  delay(200);
  alpha4.writeDigitRaw(1, 0x0);
  alpha4.writeDigitRaw(2, 0xFFFF);
  alpha4.writeDisplay();
  delay(200);
  alpha4.writeDigitRaw(2, 0x0);
  alpha4.writeDigitRaw(3, 0xFFFF);
  alpha4.writeDisplay();
  delay(200);

  alpha4.clear();
  alpha4.writeDisplay();
  
  while (!Serial);

  Serial.println("CAN Receiver");
  printMessage("    CAN Bus Started     ",1);

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }

  status = WiFi.softAP(ssid, password);
//  server.begin();
   
  Serial.println();
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  port.begin(localPort);
}

void loop() {
 // listen for incoming clients
//  WiFiClient client = server.available();
//  if (client) {
//    Serial.println("new client");
//      while (client.connected()) {
//        if (client.available()) {
  
  // try to parse packet
  int packetSize = CAN.parsePacket();
  
  if (packetSize) {
    if (CAN.packetId() == 0x55) {
      Serial.print("Recieved packet ... ");
      output[0] = (char)CAN.read();
      output[1] = (char)CAN.read();
      output[2] = (char)CAN.read();
      output[3] = (char)CAN.read();
       
      printChar4(output);
      Serial.print(output[0]);
      Serial.print(output[1]);
      Serial.print(output[2]);
      Serial.print(output[3]);
    
//    client.print(output[0]);
//    client.print(output[1]);
//    client.print(output[2]);
//    client.print(output[3]);
//    client.println();

//    Serial.println("192.168.4.2");
//    Serial.println(localPort);
        
        // send a reply, to the IP address and port that sent us the packet we received
    
    port.beginPacket("192.168.4.2",localPort);
    port.write(output[0]);
    port.write(output[1]);
    port.write(output[2]);
    port.write(output[3]);
    port.endPacket();
    printWiFiStatus();
     }
      Serial.println();
    }
    
    delay(20);
    
    delay(1);

    // close the connection:
//    client.stop();
//    Serial.println("client disonnected");
}


void printWiFiStatus() {
  // print the SSID of the network you're attached to:
//  Serial.print("SSID: ");
//  Serial.println(WiFi.SSID());
//
//  // print your WiFi shield's IP address:
//  IPAddress ip = WiFi.localIP();
//  Serial.print("IP Address: ");
//  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}





