---
layout: default
title: "The Basics: Lesson 1"
permalink: /basic-lesson-1/
---
# Getting to know Arduino!

My board is an Arduino Uno R3 manufactured by OSOYOO. Let's get to know the board and the hardware components.

![Pin Out Board](/assets/images/pin_out_board.png)
Pin Out Board from OSOYOO Tutorial

## The Brains - Microcontroller Chip

My chip is the **ATmega328P** microcontroller. It uses a **16 MHz** piezoelectric crystal that acts as a clock signal to keep everything in sync. Here's a breakdown of its onboard memory: 

- 32 KB Flash - stores uploaded code
- 2 KB SRAM - for temporary memory like variables
- 1 KB EEPROM - saves data after power cycles

## The Power
There are two main power sources: USB and DC Jack. The USB can be used for both power and programming. It's recommended using 7-12V for the DC jack, with a maximum of 20V. The board includes onboard voltage regulators that provide 5V and 3.3V outputs. For safety, there is a resettable fuse to protect against shorts or overdraws and a reset pin that can be used manually or via code.

## LEDs
There are 4 LEDs:
-  On - Board has power
- TX - Board is transmitting data
- RX - Board is receiving data
- L - programmable, connected to digital pin 13. 

These are useful for providing serial communication feedback and for troubleshooting/testing

## Pins
There are 14 Digital Pins. 0 and 1 are RX and TX, respectively, and it is used for serial communication. Pins 2-13 are general purpose, but notably pins 3, 5, 6, 9, 10, and 11 support PWM (pulse-width modulation) to simulate analog output. Pin 13 is connected to the L LED.

There are 6 analog pins (which can also be digital) that read 0-5V. 

Finally, there's AREF for external analog reference voltage, and SDA/SCL for I2C sensor communication, like infrared or temperature sensors.

## Power Header Pins
There's 5V and 3.3V regulated power out for components, as well as 3 ground pins. The VIN pin is for raw input voltage from the DC jack, and the IOREF is for shield use.

## What I learned
This gave me a deeper appreciation for what's happening under the hood when I upload a sketch. The main takeaways are: 
- Where my code lives and how it runs
- How to interact with inputs/outputs
- Safely powering components
- Why software needs to be written with real-world timing, voltage, and communication limits in mind

This foundation will help make STEVE a functioning, reliable, and safe robot car. Next up: Hello World and Building Steve!

## References
- Basic Lesson 1 and 2 from [OSOYOO Robot Car Kit](https://osoyoo.com/2020/05/12/v2-1-robot-car-kit-for-arduino-tutorial-introduction/#3)
- [How to Use A Breadboard For Electronics and Circuits](https://www.sciencebuddies.org/science-fair-projects/references/how-to-use-a-breadboard#integrated-circuits)
- [How Microcontrollers Work](https://electronics.howstuffworks.com/microcontroller.htm)

## [Return Home](https://megcrunyan.github.io/steve/)