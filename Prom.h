
#include <vector> 



class Prom {
public:
    int x, y; 
    int id;
    float screenX, screenY;
    //wspolrzedne wektora przesuniecia
    int xVectora, yVectora;
    int numberOfPeople=0;
    bool inPort=false; 
   // std::vector<People *> people;
    

    

    Prom( int, int, int);
    ~Prom();
    void moveProm();
    void drawProm();
    bool isFull();
    bool promIsByTheShore();
    void promToPort();
    void addPassanger(); 
    bool shouldWaitForPassanger();
    

};

