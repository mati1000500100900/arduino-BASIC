#include <LiquidCrystal.h>
#include "oop.h"

Screen s;
void setup() {
  Serial.begin(9600);
  lcd.begin(sx, sy);
  lcd.cursor();
  s.print("Arduino-BASIC v0.1");
  s.enter();
  s.print("Used "+String(sizeof(s)+sizeof(lcd))+"B");
  s.enter();
  s.enter();
}


void loop() {
  if (Serial.available()) {
    // read all the available characters
    while (Serial.available() > 0) {
      // display each character to the LCD
      char c=Serial.read();
      if(c==']') s.back();
      else if(c=='[') s.enter();
      else if(c=='\\') s.del();
      else s.add(c);
      s.draw();
    }
  }
}



