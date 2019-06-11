#include "Port.h"

class Passanger{
public:
    int x, y; 
    float screenX, screenY;
    //wspolrzedne wektora przesuniecia
    int xVectora, yVectora;

    Passanger( int, int);
    void movePassanger();
    void drawPassanger();
    bool enterPort(Port*);
};
