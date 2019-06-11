#include <ncurses.h>
#include "Prom.h"

Prom::Prom( int initX, int initY, int newId) {
   

    screenX = initX;
    screenY = initY;

    x=initX;
    y =initY;
    
    id=newId;
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

   if(y <= 188){
         yVectora *= -1;
    
    }
    // if (y==138){
    //    // numberOfPeople=0;
    // }
   if (y==69){
       promToPort();
   }
}

void Prom::drawProm() {
    // if(promIsByTheShore()==true && (isFull()==false)){
    //     if(numberOfPeople==0){
    //      //   promToPort();
    //     }
    //     if(numberOfPeople==1){
    //         move(27,57);
    //        printw("(p           )");
    //        }
    //     if(numberOfPeople==2){
    //         move(27,57);
    //        printw("(pp        )");
    //        }
    //     if(numberOfPeople==3){
    //         move(27,57);
    //        printw("(ppp      )");
    //        }
    //     if(numberOfPeople==4){
    //         move(27,57);
    //        printw("(pppp     )");
    //        }
    //     if(numberOfPeople==5){
    //         move(27,57);
    //        printw("(ppppp     )");
    //        }
    //     if(numberOfPeople==6){
    //         move(27,57);
    //        printw("(ppppp     )");
    //        }
    //     if(numberOfPeople==7){
    //         move(27,57);
    //        printw("(pppppp    )");
    //        }
    //      if(numberOfPeople==8){
    //         move(27,57);
    //        printw("(ppppppp    )");
    //        }
    //     if(numberOfPeople==9){
    //         move(27,57);
    //        printw("(pppppppp    )");
    //        }
        
         
         
        
    // }
    // else if(isFull()==true){
    //     move(x,y);
    //     printw("(pppppppp    )");
       
    // }
    // else{
    while(inPort==true){
        move(27,57);
        printw("(            )");
    }
    move(x,y);
    printw("(            )");
   // }

 }

 bool Prom::shouldWaitForPassanger(){
     return !isFull() && promIsByTheShore(); 
 }

bool Prom::isFull(){
    return this->numberOfPeople==10;  
}

 bool Prom::promIsByTheShore(){
     return (x==0 && y==69);
}

 void Prom::promToPort(){
     move(27,57);
     printw("(            )");
 }

 void Prom::addPassanger(){
      numberOfPeople++; 
      
 }

 int Prom::getPromId(){
     return id; 
 }

