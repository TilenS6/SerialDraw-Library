#include "Arduino.h"
#define ArduinoSerialDraw_h

//By TilenS and JurijTSL
//Download from github: https://github.com/TilenS6/ArduinoSerialDraw-Library

class ASD {
  public:
    ASD(int baud);
    void initialise();
    void pixel(int x, int y, String color);
    void background(String color);
    void fillArea(int x, int y, int w, int h, String color);
    void clearPage();
    void fillPage(String color);
    void clearPixel(int x, int y);
    void setTitle(int width, int height);
  private:
    String stringToColor(String in);
};
