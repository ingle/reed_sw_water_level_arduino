/* To see the water level on your phone install Serial Bluetooth Terminal
 *  (Android). First time users: pair HC-06 with passcode 1234.
 *  Open Serial Bluetooth Terminal app and connect to HC-06. In settings,
 *  use text mode with CR line ending. Turn on timestamps.
 */

#include <SoftwareSerial.h>
/* Software serial library allows using digital IO pins as
 *  serial TX/RX. Here we setup pin 10 as RX and pin 11 as TX.
 *  Connect HC-06 TX/RX to these pins. See wiring diagram.
 */
SoftwareSerial BluetoothPort(/*RX*/10, /*TX*/11);

#define READ_DELAY_MS 2000
#define NUM_LEVELS 5
#define INVALID_LEVEL -1

const int analog_input_pin = A0;
int last_valid_level = -1;
/* Counts for each level: obtained by experimenting */
int level_ref_counts[NUM_LEVELS] = {510, 681, 767, 819, 853};

void setup() {
  /* Serial refers to the "native" hardware serial port that
  talks to your computer over USB. */
  Serial.begin(9600);
  while(!Serial)
  {
    ; /*wait until native hardware serial port is ready*/
  }
  
  /* Now setup software serial port to talk to HC06 bluetooth
   *  module which requires 38400 baud.
   */
  BluetoothPort.begin(9600);
}

void loop() {
  float voltage;
  int adc_counts;
  voltage = get_voltage(analog_input_pin);
  adc_counts = analogRead(analog_input_pin);
  int level = get_level(adc_counts);
  if(level != INVALID_LEVEL)
  {
    last_valid_level = level;
  }
  if(last_valid_level != INVALID_LEVEL)
  {
    // Print new water level on USB hardware serial port
    Serial.print(" Level: ");
    Serial.println(last_valid_level);
    // Print new water level on Bluetooth serial port
    BluetoothPort.print(" Level: ");
    BluetoothPort.print(last_valid_level);
    BluetoothPort.print("\r");
  }
  
  delay(READ_DELAY_MS);
}

/* Returns voltage corresponding the ADC counts.
 * 0 corresponds to 0V and 1023 corresponds to 5V.
 */
float get_voltage(int pin)
{
  return (analogRead(pin)*5.0/1023.0);
}

/* Returns level number i.e. magnet location 1 through 5.
If magnet is not close to any reed switch, returns -1. */
int get_level(int counts)
{
  int level = INVALID_LEVEL;
  for(int i=0; i<NUM_LEVELS; i++)
  {
    /* check if measured counts are within +/-2 counts of reference count for a level*/
    if(counts>=level_ref_counts[i]-2 && counts<=level_ref_counts[i]+2)
    {
      level = i+1;
    }
  }
  return(level);
}


