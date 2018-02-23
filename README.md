# CANdemo
2 node CAN bus demo using the Arduino core for the ESP32

Author: Michael Sikora

Hardware:
2x Adafruit Huzzah32 featherboards with the ESP32 module.
2x CJMCU-230 board with the SN65HVD230 CAN transciever. With the 120 ohm resistor between CAN_H and CAN_L removed.
4x potentiometer, I am using am extra A500K that I had.
2x Lithium ion polymer batteries from Adafruit. I am using a 2500 mAh and a tiny one (the mAh label is rubbed off)

Connections

Same for both ESPs
ESP32 ----------------- CJMCU-230
A4      ----------------- CRX
A5      ----------------- CTX
3V      ----------------- 3V3
GND     ----------------- GND

update 2018.02.23

4 potentiometers used on A1, A2, A3, and A4. LED backpack and 3 external LEDs used on the receiver to visualize received packages.

