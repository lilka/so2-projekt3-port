#include <ncurses.h>
#include <algorithm>
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

void Port::enqueue(Prom* newProm) {
  promMutex.lock();

  addProm(newProm);

  Prom* prom = proms.front();

  int releasedPassangers = releasePassangers(prom->getSeatsLeft());
  prom->addPassangers(releasedPassangers);

  if (prom->isFull()) {
    proms.pop_front();
  }

  promMutex.unlock();
}

void Port::addProm(Prom *prom) {
  bool exists = std::find(proms.begin(), proms.end(), prom) != proms.end();

  if (!exists)
    proms.push_back(prom);
}
