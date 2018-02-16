// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <CAN.h>

int dialPin = A2;
uint32_t value = 0;
char sendWord[4];

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

  Serial.println();

  delay(100);

//  // send extended packet: id is 29 bits, packet can contain up to 8 bytes of data
//  Serial.print("Sending extended packet ... ");
//
//  CAN.beginExtendedPacket(0xabcdef);
//  CAN.write('w');
//  CAN.write('o');
//  CAN.write('r');
//  CAN.write('l');
//  CAN.write('d');
//  CAN.endPacket();
//
////  Serial.println("done");
//
//  delay(1000);
}

