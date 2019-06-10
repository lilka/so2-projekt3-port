#include <ncurses.h>
#include "People.h"

People::People( int initX, int initY) {
   
    screenX = initX;
    screenY = initY;

    x=28;
    y=10;



    xVectora = 0;
    yVectora = -1;

}

void People::movePeople() {
   

     x += xVectora;
    y += yVectora;


   if( x>= screenX ) {
        xVectora *= -1;
    }

   if(x<=0){
       xVectora *=-1;
     
    }

    if( y >= 51  ) {
        yVectora *= -1;
    }

   if(y <= 0){
        yVectora *= -1;
        
    }
   
}

void People::drawPeople() {
    move(x,y);
    printw("p");
 }

void People::enterProm(){
    inProm=true;
}
bool People::isOnProm(){
    return this->inProm;
}
 
