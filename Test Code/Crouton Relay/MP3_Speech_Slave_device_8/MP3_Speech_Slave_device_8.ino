#include <Wire.h>
#include <Arduino.h>
#include <avr/io.h>
#include "config.h"
#include "player.h"
#include "vs10xx.h"

#include <Fat16.h>
#include <Fat16Util.h>
#include "newSDLib.h"

int song;
int isplaying;

/*I2C registers 
 * 0x00 Status
 * 0x01 B button
 * 0x02 A button
 * 0x03 Button 1
 * 0x04 Button 2
 * 0x05 Button 3 
 */

#define ADDRESS 0x08 //My I2C address

void setup()
{
  Serial.begin(9600);
  Wire.begin(ADDRESS);
  Wire.onReceive(receiveEvent);
  
  //Below is for MP3 player
  InitSPI();
  InitIOForVs10xx();
  InitIOForKeys();
  InitIOForLEDs();
  Mp3Reset();
  if (!initialSDCard())
    return;

  //RED_LED_ON();//light red LED
}


void loop()
{ 
}

void receiveEvent(int howMany) {
 
while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    //Serial.print(c);   
    }
int x = Wire.read();
//Serial.print(x);

/*I2C registers 
 * 0x00 Status
 * 0x01 B button
 * 0x02 A button
 * 0x03 Button 1
 * 0x04 Button 2
 * 0x05 Button 3 
 */

switch(x) {
  case 1:
  playFile("buttonb.wav");
  break;
  case 2:
  playFile("buttona.wav");
  break;
  case 3:
  playFile("one.wav");
  break;
  case 4:
  playFile("two.wav");
  break;
  case 5:
  playFile("three.wav");
  break;
  default:
  break;
        }
  }


