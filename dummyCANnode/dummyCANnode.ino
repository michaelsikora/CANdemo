// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <CAN.h>

const int dialPin = A4;
const int piezoPin1 = A1;
const int piezoPin2 = A2;
const int piezoPin3 = A3;
uint32_t value = 0;
uint32_t value2 = 0;
uint32_t value3 = 0;
uint32_t value4 = 0;

char sendWord[4]; char sendWord1[4];
char sendWord2[4]; char sendWord3[4];

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("CAN Sender");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
  sendWord[4] = '    ';
}

void loop() {
  // send packet: id is 11 bits, packet can contain up to 8 bytes of data
  Serial.print("Sending packet ... ");

  value = analogRead(dialPin);
  sprintf(sendWord, "%04i", value);  
  Serial.print(sendWord[0]);
  Serial.print(sendWord[1]);
  Serial.print(sendWord[2]);  
  Serial.print(sendWord[3]);
  CAN.beginPacket(0x55);
  CAN.write(sendWord[0]);
  CAN.write(sendWord[1]);
  CAN.write(sendWord[2]);
  CAN.write(sendWord[3]);

  CAN.endPacket();

  delay(100);
  
  value2 = analogRead(piezoPin1);
  sprintf(sendWord1, "%04i", value2);  
  Serial.print(sendWord1[0]);
  Serial.print(sendWord1[1]);
  Serial.print(sendWord1[2]);  
  Serial.print(sendWord1[3]);
  CAN.beginPacket(0x60);
  CAN.write(sendWord1[0]);
  CAN.write(sendWord1[1]);
  CAN.write(sendWord1[2]);
  CAN.write(sendWord1[3]);

  CAN.endPacket();

  delay(100);
    
  value3 = analogRead(piezoPin2);
  sprintf(sendWord2, "%04i", value3);  
  Serial.print(sendWord2[0]);
  Serial.print(sendWord2[1]);
  Serial.print(sendWord2[2]);  
  Serial.print(sendWord2[3]);
  CAN.beginPacket(0x61);
  CAN.write(sendWord2[0]);
  CAN.write(sendWord2[1]);
  CAN.write(sendWord2[2]);
  CAN.write(sendWord2[3]);

  CAN.endPacket();

  delay(100);
    
  value4 = analogRead(piezoPin3);
  sprintf(sendWord3, "%04i", value4);  
  Serial.print(sendWord3[0]);
  Serial.print(sendWord3[1]);
  Serial.print(sendWord3[2]);  
  Serial.print(sendWord3[3]);
  CAN.beginPacket(0x62);
  CAN.write(sendWord3[0]);
  CAN.write(sendWord3[1]);
  CAN.write(sendWord3[2]);
  CAN.write(sendWord3[3]);

  CAN.endPacket();

  Serial.println();
  delay(100);
}

