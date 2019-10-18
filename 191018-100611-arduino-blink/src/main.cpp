/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
//https://docs.platformio.org/en/latest/boards/teensy/teensy31.html
//teensy for PlatformIO

//https://github.com/platformio/platformio-vscode-ide/issues/603
//use platform=Arduino if using the API


#include "Arduino.h"

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);
  // wait for a second
  delay(2000);
  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);
   // wait for a second
  delay(2000);
}
