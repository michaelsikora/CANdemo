/*
  WiFi UDP Send and Receive String

 This sketch wait an UDP packet on localPort using a WiFi shield.
 When a packet is received an Acknowledge packet is sent to the client on port remotePort

 Circuit:
 * WiFi shield attached

 created 30 December 2012
 by dlf (Metodo2 srl)

 */


#include <WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

int status = WL_IDLE_STATUS;
const char *ssid = "MyESP32AP";
const char *pass = "testpassword";
int keyIndex = 0;            // your network key Index number (needed only for WEP)

unsigned int localPort = 9999;      // local port to listen on

char address[4];
char packetBuffer[4]; //buffer to hold incoming packet
char  ReplyBuffer[] = "acknowledged";       // a string to send back

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

char output[4];
uint8_t brightness;
uint8_t brightness1;
uint8_t brightness2;
uint8_t brightness3;

WiFiUDP Udp;

uint8_t ledR = A10;
uint8_t ledG = A11;
uint8_t ledB = A9; 
uint8_t ledArray[3] = {1, 2, 3}; // three led channels
long val;

char ad1[4]; char ad2[4];
char ad3[4]; char ad4[4];

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
    delay(20);
}

//---------------------------------------------------------------//
void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the presence of the shield:
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
  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWiFiStatus();

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  Udp.begin(localPort);
  
  ledcAttachPin(ledR, 1); // assign RGB led pins to channels
  ledcAttachPin(ledG, 2);
  ledcAttachPin(ledB, 3);

  ledcSetup(1, 12000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(2, 12000, 8);
  ledcSetup(3, 12000, 8);

    ledcWrite(1, 255);
    ledcWrite(2, 255);
    ledcWrite(3, 255);
      delay(2000);

      ad1[0] = '0'; ad1[1] = '0';
      ad1[2] = '5'; ad1[3] = '5';
      ad2[2] = '6'; ad2[3] = '0';
      ad3[2] = '6'; ad3[3] = '1';
      ad4[2] = '6'; ad4[3] = '2';
}

void loop() {

  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    
    // read the packet into packetBufffer
    int len2 = Udp.read(address, 4);    
    int len = Udp.read(packetBuffer, 4);
    long rssi = WiFi.RSSI();
    Serial.print("Recieved from ... ");
    Serial.print(address);
    Serial.print(" ... RSSI: ");
    Serial.print(rssi);
    Serial.print(" ... brightness: ");   
    val = atoi(packetBuffer);
    val = floor(val/1000); 
    if (val > 4095) { val = val/10;};
    Serial.print(val); 
    if (address[2] == ad1[2] && address[3] == ad1[3]) {      
    printChar4(packetBuffer);
    } else if (address[2] == ad2[2]) {
      if (address[3] == ad2[3]) {   
        brightness1 = map(atoi(packetBuffer),0,4095,0,100);
        ledcWrite(1, brightness1);  
      } else if (address[3] == ad3[3]) {    
        brightness2 = map(atoi(packetBuffer),0,4095,0,100);
        ledcWrite(2, brightness2); 
      } else if (address[3] == ad4[3]) { 
        brightness3 = map(atoi(packetBuffer),0,4095,0,100);
        ledcWrite(3, brightness3); 
      }
    }
    Serial.println();
  }
  delay(2);
}


void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}




