#include <Wire.h>       //I2C Lib for si4703
#include <radio.h>      //lib for si4703
#include <si4703.h>     //driver for radio

#define sup 3       //sation up on pin3
#define sdn 4       //station down on pin4
#define vup 5       //volume down on pin5
#define vdn 6       //volume down on pin5

SI4703 radio;
unsigned short station = 10350;
byte volume = 4;

void setup() {

pinMode(vup, INPUT_PULLUP);
pinMode(vdn, INPUT_PULLUP);
pinMode(sup, INPUT_PULLUP);
pinMode(sdn, INPUT_PULLUP);

Serial.begin(9600);
radio.init();

radio.setBandFrequency(RADIO_BAND_FM, station);
radio.setVolume(volume);
radio.setMono(false);
radio.setMute(false);

}

void loop() {

if(digitalRead(sup) == 0){
  station += 20;
  radio.setBandFrequency(RADIO_BAND_FM, station);
}

if(digitalRead(sdn) == 0){
  station -= 20;
  radio.setBandFrequency(RADIO_BAND_FM, station);
}

if(digitalRead(vup) == 0){
  volume ++;
  radio.setVolume(volume);
}

if(digitalRead(vdn) == 0){
  volume --;
  radio.setVolume(volume);
}

}
