#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Keyboard.h>


#define PIN 8
#define NUMPIXELS 8
#define BRIGTHNESS 125
#define LENGTH(X) sizeof(X)/sizeof(X[0])

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
uint16_t buttonpin[] = {0,1,3,2,5,4,6,7};
uint16_t keyboard_key[] = {KEY_TAB, KEY_F14, KEY_F15, KEY_F16, KEY_F17, KEY_F18, KEY_F19, KEY_F20};


void setup() {
  pixels.begin();
  Keyboard.begin();
}

void loop() {
  int button_pin_state[LENGTH(buttonpin)];
  for(uint16_t i = 0; i < LENGTH(buttonpin); i++){
    button_pin_state[i] = BRIGTHNESS * digitalRead(buttonpin[i]);
    if(button_pin_state[i] == BRIGTHNESS){
      Keyboard.press(KEY_TAB);
    }else{
      Keyboard.release(KEY_TAB);
    }
  }

  for(uint16_t i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color( button_pin_state[i] , (BRIGTHNESS - button_pin_state[i] ), 0));
  }

  pixels.show();
  delay(10);
}