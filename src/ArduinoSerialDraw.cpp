#include "Arduino.h"
#include "ArduinoSerialDraw.h"

//By TilenS and JurijTSL
//Download from github: https://github.com/TilenS6/ArduinoSerialDraw-Library

String colors[] = {
  "black",  "white", "cyan", "darkgray", "gray", "green", "lightgray",  "magenta", "orange",
  "pink", "red", "blue", "yellow", "darkgreen"
};

// return type could also be an int as it is only used internally.
String ASD::stringToColor(String in) {
  in.toLowerCase();
  for (int i = 0; i < 14; i++) {
    if (in == colors[i]) return String(i+1); 
  }
  return String(0);   // default return value;  fixes bug if you put this line at end of the existing function
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
const unsigned long timeout = 100;

void waitForResponse() {
  uint32_t start = millis();
  while (millis() - start < timeout) {
    yield();  // needed for ESP32 / 8266 support (has to do with wifi in background something)
    if (Serial.available() > 0) {
      Serial.readBytes(in, 1);  // do not read more as otherwise the array will overflow.
       if (in[0] == 'k') break;
    }
  }
}

void ASD::pixel(int x, int y, String color) {
  Serial.println("p," + String(x) + "," + String(y) + "," + stringToColor(color));
  waitForResponse();
}

void ASD::background(String color) {
  Serial.println("b," + stringToColor(color));
  waitForResponse();
}

void ASD::fillArea(int startX, int startY, int endX, int endY, String color) {
  Serial.println("a," + String(startX) + "," +  String(startY) + "," +  String(endX) + "," +  String(endY) + "," +  stringToColor(color));
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
