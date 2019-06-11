#ifndef PROM_H
#define PROM_H

#include <vector> 

class Prom {
    int passangerCount = 0;
    bool promIsByTheShore();
public:
    int x, y; 
    int id;
    float screenX, screenY;
    //wspolrzedne wektora przesuniecia
    int xVectora, yVectora;
    bool inPort=false; 
    
    Prom( int, int, int);
    ~Prom();
    void moveProm();
    void drawProm();
    bool shouldWaitForPassangers();
    bool isFull();
    void promToPort();
    void addPassanger(); 
    int getSeatsLeft();
    int getPromId();
    void addPassangers(int);    

};

#endif
