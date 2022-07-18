#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Keyboard.h>


#define PIN 8
#define NUMPIXELS 8
#define BRIGTHNESS 60
#define COOLDOWN_TIME 100
#define DELAY 10
#define LENGTH(X) sizeof(X)/sizeof(X[0])

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
uint16_t buttonpin[] = {0,1,3,2,5,4,6,7};
uint16_t keyboard_key[] = {KEY_F13, KEY_F14, KEY_F15, KEY_F16, KEY_F17, KEY_F18, KEY_F19, KEY_F20};
uint16_t button_timer[] = {0,0,0,0,0,0,0,0};

void setup() {
  for(uint16_t i = 0; i < LENGTH(buttonpin); i++){
    pinMode(buttonpin[i], INPUT_PULLUP);
  }
  pixels.begin();
  Keyboard.begin();
}

void loop() {
  uint8_t led_pin_state[LENGTH(buttonpin)]; 
  for(uint16_t i = 0; i < LENGTH(buttonpin); i++){
    led_pin_state[i] = BRIGTHNESS * digitalRead(buttonpin[i]);
    if(led_pin_state[i] > 0){
      if(button_timer[i] == 0){
        Keyboard.press(keyboard_key[i]);
        button_timer[i] = COOLDOWN_TIME / DELAY;
        Keyboard.releaseAll();
      }else{
        button_timer[i]--;
      }
    }
  }

  for(uint16_t i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color( led_pin_state[i] , (BRIGTHNESS - led_pin_state[i] ), 0));
  }

  pixels.show();
  delay(10);
}