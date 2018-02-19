#include <LiquidCrystal.h>
#include <PS2Keyboard.h>
#include "oop.h"

const int DataPin = 9;
const int IRQpin =  2;

PS2Keyboard keyboard;

Screen s;
void setup() {
  keyboard.begin(DataPin, IRQpin);
  lcd.begin(sx, sy);
  lcd.blink();
  s.print("Arduino-BASIC v0.1");
  s.enter();
  s.print("Used " + String(sizeof(s) + sizeof(lcd) + sizeof(keyboard)) + "B");
  s.enter();
  s.enter();
}

void loop() {
  if (keyboard.available()) {
    char c = keyboard.read();
    if (c == PS2_ENTER) {
      s.enter();
      interpret();
    }
    else if (c == PS2_ESC) {
      s.back();
    }
    else if (c == PS2_DELETE) {
      s.del();
    }
    else if (c == PS2_PAGEDOWN) {
    }
    else if (c == PS2_PAGEUP) {
    }
    else if (c == PS2_LEFTARROW) {
    }
    else if (c == PS2_RIGHTARROW) {
    }
    else if (c == PS2_UPARROW) {
    }
    else if (c == PS2_DOWNARROW) {
    }
    else {
      s.add(c);
    }
    s.draw();
  }
}

void interpret() {
  String command = String(s.getCommand());
  String firstPart = command.substring(0, command.indexOf(' '));
  firstPart.toLowerCase();
  if (firstPart.equals("print")) {
    if (command.indexOf('"') != -1) {
      s.print(command.substring(command.indexOf('"') + 1, command.lastIndexOf('"')));
    }
    else if (command.indexOf('\'') != -1) {
      s.print(command.substring(command.indexOf('\'') + 1, command.lastIndexOf('\'')));
    }
    else if (mathEngine(command.substring(command.indexOf(' ') + 1))) {
    }
    else {
      s.print("SYNTAX ERROR");
    }
    s.enter();
  }
  else if (firstPart.equals("set")) {
    if (setPin(command.substring(command.indexOf(' ') + 1)));
    else {
      s.print("SYNTAX ERROR");
      s.enter();
    }
  }
  else {
    s.print("SYNTAX ERROR");
    s.enter();
  }
}

boolean mathEngine(String input) {
  float x, y;
  String cache;
  if (input.indexOf('+') != -1) {
    cache = input.substring(0, input.indexOf('+'));
    cache.trim();
    x = cache.toFloat();
    cache = input.substring(input.indexOf('+') + 1);
    cache.trim();
    y = cache.toFloat();
    s.print(String(x + y));
    return 1;
  }
  else if (input.indexOf('-') != -1) {
    cache = input.substring(0, input.indexOf('+'));
    cache.trim();
    x = cache.toFloat();
    cache = input.substring(input.indexOf('-') + 1);
    cache.trim();
    y = cache.toFloat();
    s.print(String(x - y));
    return 1;
  } else if (input.indexOf('*') != -1) {
    cache = input.substring(0, input.indexOf('*'));
    cache.trim();
    x = cache.toFloat();
    cache = input.substring(input.indexOf('*') + 1);
    cache.trim();
    y = cache.toFloat();
    s.print(String(x * y));
    return 1;
  } else if (input.indexOf('/') != -1) {
    cache = input.substring(0, input.indexOf('/'));
    cache.trim();
    x = cache.toFloat();
    cache = input.substring(input.indexOf('/') + 1);
    cache.trim();
    y = cache.toFloat();
    s.print(String(x / y));
    return 1;
  }
  else if (input.indexOf('^') != -1) {
    cache = input.substring(0, input.indexOf('^'));
    cache.trim();
    x = cache.toFloat();
    cache = input.substring(input.indexOf('^') + 1);
    cache.trim();
    y = cache.toFloat();
    s.print(String(pow(x, y)));
    return 1;
  } else if (input.indexOf('%') != -1) {
    cache = input.substring(0, input.indexOf('%'));
    cache.trim();
    x = cache.toFloat();
    cache = input.substring(input.indexOf('%') + 1);
    cache.trim();
    y = cache.toFloat();
    s.print(String((int)x % (int)y));
    return 1;
  } else if (input.indexOf("sqrt(") != -1) {
    cache = input.substring(input.indexOf("sqrt(") + 5, input.indexOf(')'));
    cache.trim();
    x = cache.toFloat();
    s.print(String(sqrt(x)));
    return 1;
  }
  return 0;
}

boolean setPin(String input) {
  char x, y;
  if (input.indexOf(' ') != -1) {
    x = input.substring(0, input.indexOf(' ')).toInt();
    y = input.substring(input.indexOf(' ') + 1).toInt();
    pinMode(x, OUTPUT);
    if (y == 0 || y == 1) digitalWrite(x, y);
    else analogWrite(x, y);
    return 1;
  }
  return 0;

}


