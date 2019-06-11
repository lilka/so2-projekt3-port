#include <ncurses.h>
#include "Passanger.h"
#include "Port.h"

Passanger::Passanger( int initX, int initY) {
   
    screenX = initX;
    screenY = initY;

    x=28;
    y=10;



    xVectora = 0;
    yVectora = -1;

}

void Passanger::movePassanger() {
     x += xVectora;
    y += yVectora;


   if( x>= screenX ) {
        xVectora *= -1;
    }

   if(x<=0){
       xVectora *=-1;
     
    }

    if( y  > 51  ) {
         yVectora *= -1;
     }

   if(y <= 0){
        yVectora *= -1;
        
    }
}

void Passanger::drawPassanger() {
    move(x,y);
    printw("p");

 }

 void Passanger::deletePassanger(){
     printw(" ");
 }
 

bool Passanger::enterPort(Port *port) {
  if (!isInQueue && y == 51) {
    isInQueue = true;
    port->addPassanger();
    return true;
  }

  return false;
}
