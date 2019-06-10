#include "Screen.h"
#include "River.h"
#include "Prom.h"
#include "Passanger.h"
#include <mutex>
#include <thread>
#include <vector>
#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <string>
#include <unistd.h>
#include "SafeQueue.cpp"


using namespace std;

Screen *screen;
River *river;
Prom *prom;
bool flag = true;
vector<thread> threads;
vector<Passanger*> Passangers;
SafeQueue<Passanger*> PassangerQueue; 




void refreshScreen(){

    while(flag) {
        clear();
            river->drawRiver();
            river->drawSecondRiver();
            river->drawPort();
            prom->drawProm();
                for (int i = 0; i < Passangers.size(); i++) {
                        Passangers[i]->drawPassanger();
                 }
                 
        refresh();
        usleep(20000);
    }
    clear();
    endwin();
}

void escape(){
    int inputChar;
    while(flag){
        inputChar = getch();
        if(inputChar == 'q'){
            flag= false;
        }
    }
}

void makeRiver(){
    float x = screen->getScreenWidth();
    float y = screen->getScreenHeight();

     river = new River(x, y);
     usleep(50000);

}

void moveProm(Prom *prom){
 while((flag)){
     if(prom->shouldWaitForPassanger()){
         for (int i=0; i<5; i++){
             Passanger* passanger=PassangerQueue.dequeue();
             passanger->enterProm();
             prom->addPassanger();
             }
    }
    else{
     prom->moveProm();
     usleep(90000);
     }
    
 }
}

void makeNewProm(){
     float x = 0;
     float y = 138;

     prom=new Prom(x,y);
     moveProm(prom);

     usleep(50000);

}


void movePassanger(Passanger *passanger){
 while((flag && !passanger->isOnProm())  ){
    ofstream myfile;
    myfile.open ("output.txt");
    myfile << "Writing this to a file.\n";
    myfile<<"Prom pos x"<<prom->x<<"lift pos y"<<prom->y<<endl; 
    myfile<<"Ball pos x"<<passanger->x<<"ball pos y"<<passanger->y<<endl; 
    myfile<<"Queue"<<PassangerQueue.q.size();
    myfile.close();
     
     passanger->movePassanger();
     usleep(90000);
 }
    
        Passangers.erase(std::remove(Passangers.begin(), Passangers.end(), passanger), Passangers.end());
    
     
}

void makeNewPassanger(){

    float x = screen->getScreenWidth();
    float y = screen->getScreenHeight();

    short tmp;
 
    while(flag)
    {

        tmp = rand() % 8 +1;
        Passanger *passanger = new Passanger(x, y);
        Passangers.push_back(passanger);
   
        threads.push_back(thread(movePassanger, Passangers.back()));
        PassangerQueue.enqueue(passanger);
        passanger->isInQueue=true;
        
        
        usleep(1000000);



    }
}





int main() {
    srand(time(NULL));
    screen= new Screen();
    thread generateNewProm(makeNewProm);
    thread generateNewPassanger(makeNewPassanger);
    thread generateriver(makeRiver);
    thread refreshScreenThread(refreshScreen);
    thread escapeThread(escape);
    
    
    escapeThread.join();
    generateNewPassanger.join();
    refreshScreenThread.join();
    generateriver.join();
    generateNewProm.join();
  


    for(int i = 0; i<threads.size(); i++){
        threads[i].join();
    }
    

    endwin();
    return 0;

}

