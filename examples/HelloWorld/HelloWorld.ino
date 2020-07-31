#include <SerialDraw.h>

ASD ASD(0);

void setup() {
  Serial.begin(1000000); //open serial for library to communicate with computer
  ASD.initialise(60, 60, "Hello World Example"); //configure communication and starts the software
  ASD.background("black"); //set background to black
}

void loop() {
  hello();
  world();
  delay(5000);
}

void hello() {
  //H
  ASD.fillArea(20, 24, 20, 28, "white");
  ASD.pixel(21, 26, "white");
  ASD.fillArea(22, 24, 22, 28, "white");

  //E
  ASD.fillArea(24, 24, 24, 28, "white");
  ASD.pixel(25, 24, "white");
  ASD.pixel(25, 26, "white");
  ASD.pixel(25, 28, "white");

  //L
  ASD.fillArea(27, 24, 27, 28, "white");
  ASD.pixel(28, 28, "white");

  //L
  ASD.fillArea(30, 24, 30, 28, "white");
  ASD.pixel(31, 28, "white");

  //O
  ASD.fillArea(33, 25, 33, 27, "white");
  ASD.fillArea(36, 25, 36, 27, "white");
  ASD.fillArea(34, 24, 35, 24, "white");
  ASD.fillArea(34, 28, 35, 28, "white");
}

void world() {
  //W
  ASD.fillArea(20, 30, 20, 33, "white");
  ASD.fillArea(22, 30, 22, 33, "white");
  ASD.fillArea(24, 30, 24, 33, "white");
  ASD.pixel(21, 34, "white");
  ASD.pixel(23, 34, "white");

  //O
  ASD.fillArea(26, 31, 26, 33, "white");
  ASD.fillArea(29, 31, 29, 33, "white");
  ASD.fillArea(27, 30, 28, 30, "white");
  ASD.fillArea(27, 34, 28, 34, "white");

  //R
  ASD.fillArea(31, 30, 31, 34, "white");
  ASD.fillArea(32, 30, 33, 30, "white");
  ASD.fillArea(32, 32, 33, 32, "white");
  ASD.fillArea(34, 33, 34, 34, "white");
  ASD.pixel(34, 31, "white");

  //L
  ASD.fillArea(36, 30, 36, 34, "white");
  ASD.pixel(37, 34, "white");

  //D
  ASD.fillArea(39, 30, 39, 34, "white");
  ASD.fillArea(40, 30, 41, 30, "white");
  ASD.fillArea(40, 34, 41, 34, "white");
  ASD.fillArea(42, 31, 42, 33, "white");
}
