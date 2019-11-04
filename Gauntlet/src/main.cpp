#include <Arduino.h>
#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

//https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-use
// rpi shutdown button to program
//https://www.instructables.com/id/Simple-Raspberry-Pi-Shutdown-Button/

//by command line
//https://github.com/arduino/arduino-cli
//harder by platformio hex
//https://community.platformio.org/t/can-platformio-upload-a-firmware-hex-file-only-uploading-sketch-to-arduino-via-raspberry/1301/13

//IR
//https://learn.sparkfun.com/tutorials/ir-communication/all

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN     6// Which pin on the Arduino
#define LED_COUNT  6 // How many NeoPixels are attached to the Arduino?

#define BRIGHTNESS 255  // NeoPixel brightness, 0 (min) to 255 (max)


// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

void colorSet(uint32_t color, int lednum) {
    strip.setPixelColor(lednum, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match


}


void dump(decode_results *results) {
  // Dumps out the decode_results structure.
  // Call this after IRrecv::decode()
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) {
    Serial.print("Unknown encoding: ");
  }
  else if (results->decode_type == NEC) {
    Serial.print("Decoded NEC: ");

  }
  else if (results->decode_type == SONY) {
    Serial.print("Decoded SONY: ");
  }
  else if (results->decode_type == RC5) {
    Serial.print("Decoded RC5: ");
  }
  else if (results->decode_type == RC6) {
    Serial.print("Decoded RC6: ");
  }
  else if (results->decode_type == PANASONIC) {
    Serial.print("Decoded PANASONIC - Address: ");
    Serial.print(results->address, HEX);
    Serial.print(" Value: ");
  }
  else if (results->decode_type == LG) {
    Serial.print("Decoded LG: ");
  }
  else if (results->decode_type == JVC) {
    Serial.print("Decoded JVC: ");
  }
  else if (results->decode_type == AIWA_RC_T501) {
    Serial.print("Decoded AIWA RC T501: ");
  }
  else if (results->decode_type == WHYNTER) {
    Serial.print("Decoded Whynter: ");
  }
  Serial.print(results->value, HEX);
  Serial.print(" (");
  Serial.print(results->bits, DEC);
  Serial.println(" bits)");
  Serial.print("Raw (");
  Serial.print(count, DEC);
  Serial.print("): ");

  for (int i = 1; i < count; i++) {
    if (i & 1) {
      Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
    }
    else {
      Serial.write('-');
      Serial.print((unsigned long) results->rawbuf[i]*USECPERTICK, DEC);
    }
    Serial.print(" ");
  }
  Serial.println();
}

void fadeOn(int del) {
  for(int i=0;i<=255;i++){
    strip.setPixelColor(0, strip.Color(i,   0,   0) );
    strip.setPixelColor(0, strip.Color(0,   i,   0) );
    strip.setPixelColor(0, strip.Color(0,   0,   i) );
    strip.setPixelColor(0, strip.Color(i,   0,   i) );
    strip.setPixelColor(0, strip.Color(i,   i,   0) );
    strip.show();                          //  Update strip to match
    delay(del);
  }

}


void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)

  fadeOn(50);
}


void loop() {
  colorSet(strip.Color(255,   0,   0)     , 0);//red
  colorSet(strip.Color(0,   255,   0)     , 1);//green
  colorSet(strip.Color(0,   0,   255)     , 2);//blue
  colorSet(strip.Color(255,   0, 255)     , 3);//purple
  colorSet(strip.Color(255, 255,   0)     , 4);//yellow

  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    dump(&results);
    irrecv.resume(); // Receive the next value
  }

}
