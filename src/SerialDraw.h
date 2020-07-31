#include "Arduino.h"
#define SerialDraw_h

//By TilenS and JurijTSL
//Download from github: https://github.com/TilenS6/ArduinoSerialDraw-Library

class ASD {
  public:
    ASD(int baud);
    void initialise(int width, int height, String tit);
    void pixel(int x, int y, String color);
    void background(String color);
    void fillArea(int x, int y, int w, int h, String color);
    void clearPage();
    void clearPixel(int x, int y);
    void setScore(int score);
  private:
    String stringToColor(String in);
};
