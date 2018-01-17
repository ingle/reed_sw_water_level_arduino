# reed_sw_water_level_arduino
Arduino (Sparkfun RedBoard) code and schematic for water level sensor using reed switches. 
A floating magnet will trigger these switches as the water level rises or falls causing
the voltage to change from a voltage divider circuit. The analog voltage is read and
decoded into a level number in the Arduino code.

The level information is printed over hardware serial port and also sent through Bluetooth
using an HC-06 module connected to pins 10/11 using a software serial port.

Bluetooth output can be examined, for example, using a Bluetooth Terminal app on your
smartphone and pairing with the HC-06 module.


![wiring diagram](https://raw.githubusercontent.com/ingle/reed_sw_water_level_arduino/master/wiring.png)
