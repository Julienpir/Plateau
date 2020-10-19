#include <FastLED.h>
#define NUM_LEDS 81
#define DATA_PIN 4
CRGB leds[NUM_LEDS];

//============================================================

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

}

//============================================================

void loop() {

for (int i=0; i<27; i++){
  leds[i] = CRGB::Blue;
  FastLED.show();
}

for (int i=27; i<54; i++){
  leds[i] = CRGB::White;
  FastLED.show();
}
for (int i=54; i<81; i++){
  leds[i] = CRGB::Red;
  FastLED.show();
}

/*
for (int i=0; i<27; i++){
  leds[i] = CRGB(0,107,99);
  FastLED.show();
}

for (int i=27; i<54; i++){
  leds[i] = CRGB(206,17,38);
  FastLED.show();
}
for (int i=54; i<81; i++){
  leds[i] = CRGB(255,206,0);
  FastLED.show();
}
leds[40] = CRGB(255,206,0);
  FastLED.show();
delay(1000000);
*/

}
