#include <ncurses.h>
#include "Passanger.h"

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

    // if(isInQueue && isOnProm()){
    //     deletePassanger();
    // }
    if(isInQueue && y>=51 && y<=60 && x>=20){
         y++; 
         x--;
         
         
         
    }

    if(y==60){
       y=60;
       x=20;
    }
}

void Passanger::drawPassanger() {
    move(x,y);
    printw("p");

 }

 void Passanger::deletePassanger(){
     printw(" ");
 }

 void Passanger::goToQueue(){
     for(int i =0; i<9; i++){
         y=y+i; 
         move(x,y);
         printw("p");
     }
 }
 

// void Passanger::enterProm(){
//     inProm=true;
// }
// bool Passanger::isOnProm(){
//     return this->inProm;
// }
 
