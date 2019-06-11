#include <ncurses.h>
#include "Port.h"
#include "Prom.h"

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

void Port::addPassanger() { passangerCount++; }

int Port::releasePassangers(int max) {
  int released;

  if (passangerCount >= max) {
    released = max;
    passangerCount -= max;
  }
  else {
    released = passangerCount;
    passangerCount = 0;
  }

  return released;
}

void Port::packProm(Prom* prom) {
  promMutex.lock();

  if (promInside == NULL)
    promInside = prom;

  if (promInside == prom) {
    int releasedPassangers = releasePassangers(prom->getSeatsLeft());
    prom->addPassangers(releasedPassangers);

    if (prom->isFull()) {
      promInside = NULL;
    }
  }

  promMutex.unlock();
}

