

class Passanger{
public:
    int x, y; 
    float screenX, screenY;
    //wspolrzedne wektora przesuniecia
    int xVectora, yVectora;
    bool used=false;
   // bool inProm=false;
    bool isInQueue=false; 
    

    Passanger( int, int);
    void movePassanger();
    void drawPassanger();
   // void enterProm(); 
   // bool isOnProm(); 
    void deletePassanger();

};