#include <ncurses.h>
#include "Prom.h"

Prom::Prom( int initX, int initY) {
   

    screenX = initX;
    screenY = initY;

    x=0;
    y =138;

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
        
    }
   
}

void Prom::drawProm() {
    if(promIsByTheShore()==true && (isFull()==false)){
        if(numberOfPeople==0){
            promToPort();
        }
        if(numberOfPeople==1){
            move(27,57);
           printw("(p           )");
           }
        if(numberOfPeople==2){
            move(27,57);
           printw("(pp        )");
           }
        if(numberOfPeople==3){
            move(27,57);
           printw("(ppp      )");
           }
         
        
    }
    else if(isFull()==true){
        move(x,y);
        printw("(pppp    )");
        moveProm();
    }
    else{
    move(x,y);
    printw("(            )");
    }

 }

 bool Prom::shouldWaitForPeople(){
     return !isFull() && promIsByTheShore(); 
 }

bool Prom::isFull(){
    return this->numberOfPeople==4;  
}

 bool Prom::promIsByTheShore(){
     return (x==0 && y==69);
}

 void Prom::promToPort(){
     move(27,57);
     printw("(            )");
     inPort=true;
 }

 void Prom::addPassanger(){
      numberOfPeople++; 
      d
 }

