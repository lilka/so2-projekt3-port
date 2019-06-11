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
#include "Port.h"

using namespace std;

Screen *screen;
River *river;
Port* port=new Port();
bool flag = true;
vector<thread> threads;
vector<Passanger*> passangers;
SafeQueue<Passanger*> PassangerQueue; 
vector<Prom*> proms {
  new Prom(7, 70, 0),
  new Prom(21, 90, 1),
  new Prom(42, 138, 2)
};
vector<thread> promThreads;
SafeQueue<Prom*> promsQueue; 

void refreshScreen(){

    while(flag) {
      clear();
      river->drawRiver();
      river->drawSecondRiver();
      port->draw();
      for(int i=0; i<promThreads.size(); i++){
        proms[i]->drawProm();
      }

      for (int i = 0; i < passangers.size(); i++) {
        passangers[i]->drawPassanger();
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
    if(prom->shouldWaitForPassangers()) {
      port->packProm(prom);
    } else {
      prom->moveProm();
      usleep(90000);
    }
  }
}

void initProms(){
  for(int i=0; i<proms.size();i++){
    promThreads.push_back(thread(moveProm, proms[i]));
    promsQueue.enqueue(proms[i]);
  } 
}

void movePassanger(Passanger *passanger){
 while(flag
  //&&  !passanger->isOnProm())  
  ){
    ofstream myfile;
    myfile.open ("output.txt");
    myfile<<"X: "<<proms[0]->x<< " Y: "<<proms[0]->y<<endl; 
    //myfile<<"Queue"<<PassangerQueue.q.size();
    //myfile<<"Queue proms"<<promsQueue.q.size();
    myfile.close();
     
    passanger->movePassanger();
    if(passanger->enterPort(port)) {
      passangers.erase(std::remove(passangers.begin(), passangers.end(), passanger), passangers.end());
    }
     usleep(90000);
 }
}

void makeNewPassanger(){

    float x = screen->getScreenWidth();
    float y = screen->getScreenHeight();

    short tmp;
 
    while(flag)
    {

        Passanger *passanger = new Passanger(x, y);
        passangers.push_back(passanger);
   
        threads.push_back(thread(movePassanger, passangers.back()));
        PassangerQueue.enqueue(passanger);

        usleep(2000000);
    }
}

int main() {
    srand(time(NULL));
    screen= new Screen();
    initProms();
    thread generateNewPassanger(makeNewPassanger);
    thread generateriver(makeRiver);
    thread refreshScreenThread(refreshScreen);
    thread escapeThread(escape);
    
    escapeThread.join();
    generateNewPassanger.join();
    refreshScreenThread.join();
    generateriver.join();
  
   for(int i=0; i<3;i++){
        promThreads[i].join();
    }

    for(int i = 0; i<threads.size(); i++){
        threads[i].join();
    }

    endwin();
    return 0;
}

