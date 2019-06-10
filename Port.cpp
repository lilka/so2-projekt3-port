#include <ncurses.h>
#include "Port.h"

Port::Port(){}

void Port::drawPort(){
    for(int i = 0; i<8; i++){
        move(25+i, 55);
        printw("|");
    }

    for(int i = 0; i<15; i++){
        move(25, 55+i);
        printw("-");
    }

    for(int i = 0; i<15; i++){
        move(32, 55+i);
        printw("-");
    }
}

 int Port::getPromInsideId(){
     return promInsideId;
 }
  void Port::setPromInsideId(int Id){
     this->promInsideId=Id;
  }
  bool Port::isPromInside(){
      return this->promInside; 
  }
