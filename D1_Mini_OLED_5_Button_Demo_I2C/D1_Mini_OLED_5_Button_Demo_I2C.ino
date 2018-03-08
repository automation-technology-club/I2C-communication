/*
 * 
 * Button Demo for the version 2.0 OLED shield with 2 buttons.
 * Usage - Hit a button, see the button name on the screen.
 * Added 3 more buttons, and I2C communication to another microcontroller.
 * When a button is pushed, it will display the button name on the 
 * OLED, and send a HEX code to the other controller.
 * The 2nd controller will use the hex code to do something ("useful")
 * 
 * Based on code from:
 * https://www.arduino.cc/en/Tutorial/MasterWriter
 * and
 * http://dsscircuits.com/articles/arduino-i2c-slave-guide
 * Documented below.
 * 
 * Example By LeRoy Miller (C) 2018
 * If you find this or any of my projects useful or enjoyable please support me.  
Anything I do get goes to buy more parts and make more/better projects.  
https://www.patreon.com/kd8bxp  
https://ko-fi.com/lfmiller 
https://www.youtube.com/channel/UCP6Vh4hfyJF288MTaRAF36w  
https://kd8bxp.blogspot.com/  

Required Library: Adafruit_D1_SSD1306 which is a slightly modified version
of mcauser's Adafruit SSD1306 library for the D1 Mini with 64x48 OLED screen
Mine is a renaming so that the Original Adafruit Library and 
MCAuser's library can live together.
https://github.com/kd8bxp/mcauser-64x48-OLED-SSD1306-library

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
 */
 

#include <Wire.h>
#include <Adafruit_D1_SSD1306.h>

#define OLED_RESET 0
Adafruit_D1_SSD1306 display(OLED_RESET);

//I2C 0x00 status (Not used.)
#define BPIN D4 //I2C 0x01
#define APIN D3 //I2C 0x02
#define BUTTON1 D5 //I2C 0x03
#define BUTTON2 D6 //I2C 0x04
#define BUTTON3 D7 //I2C 0x05

#define REMOTE 0x08 //I2C address of slave device

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Wire.begin();

  // Clear the buffer.
  display.clearDisplay();
  display.display();
 pinMode(BPIN, INPUT_PULLUP); //B
 pinMode(APIN, INPUT_PULLUP); //A
 pinMode(BUTTON1, INPUT_PULLUP); // 1
 pinMode(BUTTON2, INPUT_PULLUP); // 2
 pinMode(BUTTON3, INPUT_PULLUP); // 3

 attachInterrupt(digitalPinToInterrupt(BPIN), displayB, HIGH);
 attachInterrupt(digitalPinToInterrupt(APIN), displayA, HIGH);
 attachInterrupt(digitalPinToInterrupt(BUTTON1), displayB1, HIGH);
 attachInterrupt(digitalPinToInterrupt(BUTTON2), displayB2, HIGH);
 attachInterrupt(digitalPinToInterrupt(BUTTON3), displayB3, HIGH);
 
}

void loop() {
  yield();
}

void SendoverI2C(int reg) {
  Wire.beginTransmission(REMOTE); //transmit to REMOTE device
  Wire.write(reg);
  Wire.endTransmission();
}

void displayB() {
  //I2C Register 0x01
  display.clearDisplay();
  display.setTextSize(5);
  display.setTextColor(WHITE);
  display.setCursor(10,10);
  display.println("B");
  SendoverI2C(0x01);
  display.display();
  
}

void displayA() {
  //I2C register 0x02
  display.clearDisplay();
  display.setTextSize(5);
  display.setTextColor(WHITE);
  display.setCursor(10,10);
  display.println("A");
  SendoverI2C(0x02);
  display.display();
  
}

void displayB1() {
  //I2C register 0x03
  display.clearDisplay();
  display.setTextSize(5);
  display.setTextColor(WHITE);
  display.setCursor(10,10);
  display.println("1");
  SendoverI2C(0x03);
  display.display();
  
}

void displayB2() {
  //I2C register 0x04
  display.clearDisplay();
  display.setTextSize(5);
  display.setTextColor(WHITE);
  display.setCursor(10,10);
  display.println("2");
  SendoverI2C(0x04);
  display.display();
  
}

void displayB3() {
  //I2C register 0x05
  display.clearDisplay();
  display.setTextSize(5);
  display.setTextColor(WHITE);
  display.setCursor(10,10);
  display.println("3");
  SendoverI2C(0x05);
  display.display();
  
}


