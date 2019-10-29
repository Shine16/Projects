#include <Arduino.h>

void setup() {
  Serial.begin(9600);
  Serial.println("Test");
}

void loop () {
  Serial.println("Test");
  delay(500);
}

//https://community.platformio.org/t/solved-esp32-serial-monitor-not-working/2858/4
