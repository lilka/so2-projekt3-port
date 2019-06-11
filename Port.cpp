#include <ncurses.h>
#include "Port.h"

Port::Port(){}

void Port::draw(){
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

  for(int i = 0; i < passangerCount; i++) {
    move(20, 60 - i);
    printw("w");
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

void Port::addPassanger() { passangerCount++; }
