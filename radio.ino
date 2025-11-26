#include <Wire.h>       //I2C Lib for si4703
#include <TM1637Display.h>//Lib display
#include <Si4703_Breakout.h> //Lib for radio

#define sup 4       //sation up on pin3
#define sdn 5       //station down on pin4
#define vup 6       //volume down on pin5
#define vdn 7       //volume down on pin5
#define CLK 11      //displ CLK on pin 11
#define DIO 12      //displ DIO on pin 12

int resetPin = 2;
int SDIO = A4;
int SCLK = A5;

Si4703_Breakout radio(resetPin, SDIO, SCLK);

using namespace std;


TM1637Display display = TM1637Display(CLK, DIO);

int station = 1035;
int volume = 4;

void increaseVolume(){
  volume ++;
  if (volume == 16) volume = 15;
    radio.setVolume(volume);
  display.showNumberDec(volume);
}

void decreaseVolume(){
  volume --;
  if (volume < 0) volume = 0;
    radio.setVolume(volume);
  display.showNumberDec(volume);
}

void setup() {

pinMode(vup, INPUT_PULLUP);
pinMode(vdn, INPUT_PULLUP);
pinMode(sup, INPUT_PULLUP);
pinMode(sdn, INPUT_PULLUP);

Serial.begin(9600);
display.clear();

radio.powerOn();
radio.setVolume(4);
}

void loop() {
Serial.print("Station - ");
Serial.println(station, DEC);
Serial.print("Volume - ");
Serial.println(volume, DEC);

display.setBrightness(7);

if(digitalRead(sup) == 0){
  station += 1;
  radio.setChannel(station);
  display.showNumberDec(station);
}

if(digitalRead(sdn) == 0){
  station -= 1;
  radio.setChannel(station);
  display.showNumberDec(station);
}

if(digitalRead(vup) == 0){
  increaseVolume();
}

if(digitalRead(vdn) == 0){
  decreaseVolume();
}

delay(200);

}
