#ifndef PORT_H
#define PORT_H

#include <mutex>
#include <deque>
#include "Prom.h"

class Port{
  int passangerCount = 0;
  std::mutex promMutex;
  std::deque<Prom*> proms;
  void addProm(Prom*);
public:
  Port();
  void draw(); 
  void enqueue(Prom* p);
  void addPassanger();
  int releasePassangers(int max);
};

#endif
