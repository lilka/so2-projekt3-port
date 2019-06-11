#include <ncurses.h>
#include "Prom.h"

const int PASSANGERS_MAX = 5;

Prom::Prom( int initX, int initY ) {
   

    screenX = initX;
    screenY = initY;

    x=initX;
    y =initY;
    
    xVectora = 0;
    yVectora = -1;

}

void Prom::moveProm() {
  x += xVectora;
  y += yVectora;


   if( x>= screenX ) {
        xVectora *= -1;
    }

   if(x<=0){
       xVectora *=-1;
     
    }

    if( y >= 70  ) {
        yVectora *= -1;
    }

   if(y <= 138){
         yVectora *= -1;
    
    }
    if (y==138){
       passangerCount = 0;
    }
   
}

void Prom::drawProm() {
  move(x,y);

  if (passangerCount > 0) {
    printw("(");
    for (int i = 1; i <= passangerCount; i++) {
      move(x, y + i);
      printw("P");
    }
    move(x, y + passangerCount + 1);
    printw(")");
  }
  else {
    printw("(            )");
  }
}

bool Prom::shouldWaitForPassangers(){
  return !isFull() && promIsByTheShore(); 
}

bool Prom::isFull(){
  return passangerCount == PASSANGERS_MAX;
}

 bool Prom::promIsByTheShore(){
   return y == 69;
}

 void Prom::addPassangers(int count){
   passangerCount += count;
 }

int Prom::getSeatsLeft() {
  return PASSANGERS_MAX - passangerCount;
}
