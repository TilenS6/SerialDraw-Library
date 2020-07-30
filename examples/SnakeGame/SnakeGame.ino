#include <SerialDraw.h>

ASD ASD(0);

int orient = 2; //0-left 1-right 3-up 2-down
int orientTmp = 2;
int len = 3; //lenght of snake
int highScore = 0; //high score of game
int headX = 1; //x position of head of snake - using for detecting collision
int headY = 1; //y position of head of snake
boolean collide = false; //will go true if snake collides with itself or walls

int snakePos[50][2] = { {0, 0}, //snake position - it has "array in array" one for x, other for y. It stores position of every block of snake and it is progressively shifting down for snake to move
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0},
                        {0, 0}};
                        
int foodX = 30; //stores x of food in field, starts in the middle...
int foodY = 30; //...and y

void setup() {
  Serial.begin(1000000); //open serial for library to communicate to computer
  pinMode(A0, INPUT); //joystick port for left- right+
  pinMode(A1, INPUT); //joystick port for up- down+
  ASD.initialise(60, 60, "Demo Snake Game"); //configure communication and starts the software
  ASD.background("black"); //set background to black
  ASD.pixel(foodX, foodY, "red"); //draw food on the screen
}

void loop() {
  if (!collide) { //checks if it collided with something. if not:
    nextInterval(orient); //calculate next position and colision
    foodCheck(); //checks if head is on the food
    refreshScreen(); //draws new calculations on the screen
    delay(50); //---------------- HERE you can adjust speed of snake (deafult:50) ----------------
  } else {
    ASD.clearPage();
    ASD.background("red");
    delay(2000); //wait for you to realize you are died
    if (highScore < len) { //stores high score
      highScore = len;
    }
    len = 3; //reseting all variables to start game over
    foodX = 30;
    foodY = 30;
    collide = false;
    ASD.clearPage();
    ASD.background("black");
    for (int i = 0; i < 50; i++) { //formatting snake position array
      snakePos[i][0] = 0;
      snakePos[i][1] = 0;
    }
    headX = 1;
    headY = 1;
    orient = 2;
    ASD.pixel(foodX, foodY, "red");
  }
}

int angStic() { //---------------- HERE you can configure your user iput device. Im using joystick but remember to return right value: 0-left 1-right 2-down 3-up 4-not changing
  if (analogRead(A0) < 10 && orient != 1) {
    return 0;
  } else if (analogRead(A0) > 1013 && orient != 0) {
    return 1;
  } else if (analogRead(A1) < 10 && orient != 2) {
    return 3;
  } else if (analogRead(A1) > 1013 && orient != 3) {
    return 2;
  } else {
    return 4;
  }
}

void refreshScreen() { //draw fresh position of snake
  ASD.pixel(snakePos[0][0], snakePos[0][1], "green");
  ASD.clearPixel(snakePos[len][0], snakePos[len][1]);
}

void foodCheck() { //checks if head is on the food
  if (headX == foodX && headY == foodY) {
    if (len < 50) { //add lenght to snake unless you have max lenght (49)
      len++;
    }
    calculateAgain:
    foodX = random(1, 59); //chose new food position
    foodY = random(1, 59);
    for (int i = 49; i > 0; i--) {
      if (snakePos[i][0] == headX && snakePos[i][1] == headY) { //checks if food is on the snake, if it is the it will calculate again
        goto calculateAgain;
      }
    }
    ASD.pixel(foodX, foodY, "red"); //draw food on the screen
  }
}

void nextInterval(int ori) { //calculates new snake position
  orientTmp = angStic();
  if (orientTmp != 4) {
    orient = orientTmp;
  }
  
  for (int i = 49; i > 0; i--) { //shift every data in coordinates array
    snakePos[i][0] = snakePos[i-1][0];
    snakePos[i][1] = snakePos[i-1][1];
  }
  
  if (ori == 0) { //calculate where head must be in next step
    snakePos[0][0] = headX-1;
    snakePos[0][1] = headY;
  } else if (ori == 1) {
    snakePos[0][0] = headX+1;
    snakePos[0][1] = headY;
  } else if (ori == 2) {
    snakePos[0][0] = headX;
    snakePos[0][1] = headY+1;
  } else if (ori == 3) {
    snakePos[0][0] = headX;
    snakePos[0][1] = headY-1;
  }
  
  headX = snakePos[0][0];
  headY = snakePos[0][1];

  for (int i = 1; i < len+1; i++) { //check if head is not colliding with body
    if (headX == snakePos[i][0] && headY == snakePos[i][1]) {
      collide = true;
    }
  }
  if (headX == -1 || headX == 60) { //check if head is not colliding with walls
    collide = true;
  }
  if (headY == -1 || headY == 60) {
    collide = true;
  }
}
