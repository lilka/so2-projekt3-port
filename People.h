

class People{
public:
    int x, y; 
    float screenX, screenY;
    //wspolrzedne wektora przesuniecia
    int xVectora, yVectora;
    bool used=false;
    bool inProm=false;
    

    People( int, int);
    void movePeople();
    void drawPeople();
    void enterProm(); 
    bool isOnProm(); 

};