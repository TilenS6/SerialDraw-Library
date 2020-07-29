#include "Arduino.h"
#include "ArduinoSerialDraw.h"

//By TilenS and JurijTSL
//Download from github: https://github.com/TilenS6/ArduinoSerialDraw-Library

String ASD::stringToColor(String in) {
  in.toLowerCase();
  if (in == "black") {
    return "1";
  } else if (in == "white") {
    return "2";
  } else if (in == "cyan") {
    return "3";
  } else if (in == "darkgray") {
    return "4";
  } else if (in == "gray") {
    return "5";
  } else if (in == "green") {
    return "6";
  } else if (in == "lightgray") {
    return "7";
  } else if (in == "magenta") {
    return "8";
  } else if (in == "orange") {
    return "9";
  } else if (in == "pink") {
    return "10";
  } else if (in == "red") {
    return "11";
  } else if (in == "blue") {
    return "12";
  } else if (in == "yellow") {
    return "13";
  } else if (in == "darkgreen") {
    return "14";
  }
}

ASD::ASD(int baud) {
}

void ASD::initialise() {
  for (int i = 0; i < 8; i++) {
    Serial.println("flush");
    delay(10);
  }
  Serial.println("trigger");
  delay(10);
}

boolean gotIt = false;
char in[1];
long mil = 0;

void waitForResponse() {
  gotIt = false;
  mil = millis();
  while (Serial.available() == 0 && (millis() - mil) < 100) {};
  mil = millis();
  while (Serial.available()>0 && !gotIt) {
    Serial.readBytes(in, Serial.available());
    if (in[0] == 'k' || (millis() - mil) > 100) {
	  gotIt = true;
    }
  }
}

void ASD::pixel(int x, int y, String color) {
  String _color = stringToColor(color);
  Serial.println("p," + String(x) + "," + String(y) + "," + String(_color));
  waitForResponse();
}

void ASD::background(String color) {
  String _color = stringToColor(color);
  Serial.println("b," + String(_color));
  waitForResponse();
}

void ASD::fillArea(int startX, int startY, int endX, int endY, String color) {
  String _color = stringToColor(color);
  Serial.println("a," + String(startX) + "," +  String(startY) + "," +  String(endX) + "," +  String(endY) + "," +  String(_color));
  waitForResponse();
}

void ASD::clearPixel(int x, int y) {
  Serial.println("c," + String(x) + "," + String(y));
  waitForResponse();
}

void ASD::clearPage() {
  Serial.println("l");
  waitForResponse();
}
