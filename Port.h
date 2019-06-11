#ifndef PORT_H
#define PORT_H

#include <mutex>
#include "Prom.h"

class Port{
  std::mutex promMutex;
  int passangerCount = 0;
  Prom* promInside = NULL;
public:
  Port();
  void draw(); 
  void packProm(Prom* p);
  void addPassanger();
  int releasePassangers(int max);
};

#endif
