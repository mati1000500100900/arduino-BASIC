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
    else {
      s.print(mathEngine(command.substring(command.indexOf(' ') + 1)));
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
String mathEngine(String input) {
  s.print(input);
  s.enter();
  if ((input.indexOf('(') != -1 && input.indexOf(')') != -1) || input.indexOf('^') != -1 || input.indexOf('*') != -1 || input.indexOf('/') != -1 || input.indexOf('+') != -1 || input.indexOf('-') != -1) {
    if (input.indexOf('(') != -1 && input.lastIndexOf(')') != -1) {
      return mathEngine(input.substring(0, input.indexOf('(')) + mathEngine(input.substring(input.indexOf('(') + 1, input.lastIndexOf(')'))) + input.substring(input.lastIndexOf(')') + 1));
    }
    else {
      char i = -1;
      if (input.indexOf('^') != -1) i = input.indexOf('^');
      else if (input.indexOf('*') != -1 || input.indexOf('/') != -1) {
        i = minornot(input.indexOf('*'), input.indexOf('/'));
      }
      else if (input.indexOf('+') != -1 || input.indexOf('-') != -1) {
        i = minornot(input.indexOf('+'), input.indexOf('-'));
      }

      if (i == -1) {
        return input;
      }
      else {
        char first = -1;
        if (input.lastIndexOf('^', i - 1) > first) first = input.lastIndexOf('^', i - 1);
        else if (input.lastIndexOf('*', i - 1) > first) first = input.lastIndexOf('*', i - 1);
        else if (input.lastIndexOf('/', i - 1) > first) first = input.lastIndexOf('/', i - 1);
        else if (input.lastIndexOf('+', i - 1) > first) first = input.lastIndexOf('+', i - 1);
        else if (input.lastIndexOf('-', i - 1) > first) first = input.lastIndexOf('-', i - 1);
        char last = -1;
        if (input.indexOf('^', i + 1) > last) last = input.indexOf('^', i + 1);
        else if (input.indexOf('*', i + 1) > last) last = input.indexOf('*', i + 1);
        else if (input.indexOf('/', i + 1) > last) last = input.indexOf('/', i + 1);
        else if (input.indexOf('+', i + 1) > last) last = input.indexOf('+', i + 1);
        else if (input.indexOf('-', i + 1) > last) last = input.indexOf('-', i + 1);

        if (first == -1 && last == -1) {
          String cache = input.substring(0, i);
          cache.trim();
          float x = cache.toFloat();
          cache = input.substring(i + 1);
          cache.trim();
          float y = cache.toFloat();
          if (input.lastIndexOf('^') != -1) return String(pow(x, y));
          else if (input.lastIndexOf('*') != -1) return String(x * y);
          else if (input.lastIndexOf('/') != -1) return String(x / y);
          else if (input.lastIndexOf('+') != -1) return String(x + y);
          else if (input.lastIndexOf('-') != -1) return String(x - y);
        }
        else if (first == -1) {
          return mathEngine(mathEngine(input.substring(0, last)) + input.substring(last));
        }
        else if (last == -1) {
          return mathEngine(input.substring(0, first + 1) + mathEngine(input.substring(first + 1)));
        }
        else {
          return mathEngine(input.substring(0, first + 1) + mathEngine(input.substring(first + 1, last)) + input.substring(last));
        }
      }
    }
  }
  else return input;
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
int minornot(int x, int y) {
  if (x == -1) return y;
  if (y == -1) return x;
  else return min(x, y);
}

