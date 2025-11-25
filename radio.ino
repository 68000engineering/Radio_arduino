#include <Wire.h>       //I2C Lib for si4703
#include <radio.h>      //lib for si4703
#include <si4703.h>     //driver for radio
#include <TM1637Display.h>

#define sup 3       //sation up on pin3
#define sdn 4       //station down on pin4
#define vup 5       //volume down on pin5
#define vdn 6       //volume down on pin5
#define CLK 11      //displ CLK on pin 11
#define DIO 12      //displ DIO on pin 12

using namespace std;

SI4703 radio;
TM1637Display display = TM1637Display(CLK, DIO);

int station = 10350;
int volume = 4;

void increaseVolume(){
  if(volume<100) volume++;
  display.showNumberDec(volume);
}

void decreaseVolume(){
  if(volume>0) volume--;
  display.showNumberDec(volume);
}

void setup() {

pinMode(vup, INPUT_PULLUP);
pinMode(vdn, INPUT_PULLUP);
pinMode(sup, INPUT_PULLUP);
pinMode(sdn, INPUT_PULLUP);

Serial.begin(115200);
display.clear();

/*
radio.init();
radio.setBandFrequency(RADIO_BAND_FM, station);
radio.setVolume(volume);
radio.setMono(false);
radio.setMute(false);
*/
}
void loop() {
Serial.print("Station - ");
Serial.println(station, DEC);
Serial.print("Volume - ");
Serial.println(volume, DEC);

display.setBrightness(7);

if(digitalRead(sup) == 0){
  station += 100;
  int station_disp = station/10;
  display.showNumberDec(station_disp);
  //radio.setBandFrequency(RADIO_BAND_FM, station);
}

if(digitalRead(sdn) == 0){
  station -= 100;
  int station_disp = station/10;
  display.showNumberDec(station_disp);
  //radio.setBandFrequency(RADIO_BAND_FM, station);
}

if(digitalRead(vup) == 0){
  increaseVolume();
  //radio.setVolume(volume);
}

if(digitalRead(vdn) == 0){
  decreaseVolume();
  //radio.setVolume(volume);
}

delay(200);

}
