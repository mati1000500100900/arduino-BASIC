#include <LiquidCrystal.h>
#include "oop.h"

Screen s;
void setup() {
  Serial.begin(9600);
  lcd.begin(sx, sy);
  lcd.cursor();
  lcd.setCursor(0,3);
  lcd.print(sizeof(s));
}


void loop() {
  if (Serial.available()) {
    // read all the available characters
    while (Serial.available() > 0) {
      // display each character to the LCD
      char c=Serial.read();
      if(c==']') s.del();
      else if(c=='[') s.enter();
      else s.add(c);
      s.draw();
    }
  }
}



