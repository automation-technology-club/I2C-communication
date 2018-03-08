/*
 * Set up a I2C slave device, using a Seeed Studio MP3 Shield
 * v1.1 - and setting up various files for playback.
 * This is used with the D1 Mini OLED 5 Button Demo I2C sketch
 * it will get a HEX code from the D1 Mini and play a WAV file.
 * This is only an example to base other projects on.
 * 
 *  Based on code from:
 * https://www.arduino.cc/en/Tutorial/MasterWriter
 * and
 * http://dsscircuits.com/articles/arduino-i2c-slave-guide
 * Documented below.
 * 
Copyright (c) 2018 LeRoy Miller

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses>

If you find this or any of my projects useful or enjoyable please support me.  
Anything I do get goes to buy more parts and make more/better projects.  
https://www.patreon.com/kd8bxp  
https://ko-fi.com/lfmiller  

https://github.com/kd8bxp
https://www.youtube.com/channel/UCP6Vh4hfyJF288MTaRAF36w  
https://kd8bxp.blogspot.com/  
*/

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
  case 0x01:
  playFile("buttonb.wav");
  break;
  case 0x02:
  playFile("buttona.wav");
  break;
  case 0x03:
  playFile("one.wav");
  break;
  case 0x04:
  playFile("two.wav");
  break;
  case 0x05:
  playFile("three.wav");
  break;
  default:
  break;
        }
  }


