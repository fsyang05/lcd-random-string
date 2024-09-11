# lcd-random-string
Simple program displaying randomly chosen string from user-defined array, using LiquidCrystal I2C library (https://github.com/johnrickman/LiquidCrystal_I2C). Supports line wrapping.

Other notes included as comments in program file.

## Prerequisites
Program was written entirely in the Arduino IDE with standard C dependencies:
```
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
```
And the LiquidCrystal I2C library installed from the IDE's library manager.
```
#include <LiquidCrystal_I2C.h>
```

## Physical Parts
- Elegoo MEGA2560
- LCD with I2C module (obtained from Amazon)
- Breadboard
- Analog joystick (used for discrete SW functionality)
  - Note that any discrete component would work here, e.g. buttons, sensors.
- Wiring

## Notes and Warnings
This program supports line wrapping, but does not support scrolling. Thus all messages are limimted to the char limit for the given LCD display (32 chars since a 16x2 display was used here).  

Because of this limitation, the display will cut off words that exceed the 16 char limit for either given line. A potential working solution could be to implement text scrolling.
