#include <Wire.h>       //I2C Lib 
#include <LiquidCrystal.h> //Lib display
#include <Si4703_Breakout.h> //Lib for radio

#define sup  A3     //sation up on pin3
#define sdn A2       //station down on pin4
#define vup A1       //volume down on pin5
#define vdn  A0       //volume down on pin5


// FM-Tuner Pins
#define resetPin  2
#define  SDIO A4
#define SCLK A5

//display definition via 4-bit connection
LiquidCrystal lcd(12, 11, 4, 5, 6, 7);

Si4703_Breakout radio(resetPin, SDIO, SCLK);

short station = 10000; // working freq
byte volume = 4; // current volume output on Si4703

void clearRow(int row) {  //clear 1 row function
  lcd.setCursor(0, row); 
  lcd.print(" ");
  lcd.print(" ");
  lcd.print(" "); 
  lcd.print(" "); 
  lcd.print(" "); 
  lcd.print(" "); 
  lcd.print(" "); 
  lcd.print(" "); 
  lcd.print(" "); 
  lcd.print(" "); 
  lcd.print(" "); 
  lcd.print(" "); 
  lcd.print(" "); 
  lcd.print(" "); 
  lcd.print(" "); 
  lcd.print(" "); 
  lcd.setCursor(0, row);
}

void disp_vol(){
  clearRow(1);
  lcd.setCursor(0, 1);
  lcd.print("VOLUME:");
  lcd.setCursor(9, 1);
  lcd.print(volume);
}

void disp_station(){
  short mhz = station / 100;
  short khz = station % 100;
  clearRow(0);
  lcd.setCursor(0, 0);
  lcd.print("STATION:");
  lcd.setCursor(8, 0);
  lcd.print(mhz);
  lcd.print("."); 
  lcd.print(khz);
}

void increaseVolume(){
  volume ++;
  if (volume == 16) volume = 15;
    radio.setVolume(volume);
    disp_vol();
    delay(50);
}

void decreaseVolume(){
  
  if (!volume) volume++;
    
    volume --;
    radio.setVolume(volume);
    disp_vol();
    delay(50);
}

void increaseStation(){
  station += 5;
  if (station == 10400){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MAX");
    lcd.setCursor(0, 1);
    lcd.print("FREQUENCY!");
    lcd.clear();
    station = 10350;
  }
  else{
    radio.setChannel(station);
  }
  disp_station();
  delay(50);
}

void decreaseStation(){
  station -= 5;
  if (station == 8000){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LOW");
    lcd.setCursor(0, 1);
    lcd.print("FREQUENCY!");
    lcd.clear();
    station = 8005;
  }
  else{
    radio.setChannel(station);
  }
  disp_station();
  delay(50);
}

void setup() {

pinMode(vup, INPUT_PULLUP);
pinMode(vdn, INPUT_PULLUP);
pinMode(sup, INPUT_PULLUP);
pinMode(sdn, INPUT_PULLUP);

lcd.begin (16,2);
lcd.clear();

lcd.setCursor(0, 0);
lcd.print("ROBBO RADIO mk.I");
delay(3000);
lcd.clear();
disp_vol();
disp_station();

radio.powerOn();
radio.setVolume(4);
}

void loop() {

if(digitalRead(sup) == 0){
  decreaseStation();
}

if(digitalRead(sdn) == 0){
  increaseStation();
}

if(digitalRead(vup) == 0){
  increaseVolume();
}

if(digitalRead(vdn) == 0){
  decreaseVolume();
}

}
