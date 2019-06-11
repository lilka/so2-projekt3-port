#ifndef PROM_H
#define PROM_H

#include <vector> 

class Prom {
    int passangerCount = 0;
    bool promIsByTheShore();
public:
    int x, y; 
    float screenX, screenY;
    //wspolrzedne wektora przesuniecia
    int xVectora, yVectora;
    
    Prom( int, int );
    ~Prom();
    void moveProm();
    void drawProm();
    bool shouldWaitForPassangers();
    bool isFull();
    int getSeatsLeft();
    void addPassangers(int);    
};

#endif
