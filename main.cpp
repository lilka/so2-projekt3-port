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
//Prom *prom;
int id=0;
bool flag = true;
vector<thread> threads;
vector<Passanger*> passangers;
SafeQueue<Passanger*> PassangerQueue; 
vector<Prom*> proms; 
vector<thread> promThreads;
SafeQueue<Prom*> promsQueue; 




void refreshScreen(){

    while(flag) {
        clear();
            river->drawRiver();
            river->drawSecondRiver();
            river->drawPort();
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
    //  if(prom->shouldWaitForPassanger()){
    //      for (int i=0; i<5; i++){
    //          Passanger* passanger=PassangerQueue.dequeue();
    //         // passanger->enterProm();
    //          prom->addPassanger();
    //          }
    // }
    // else{
     prom->moveProm();
     usleep(90000);
     }
    
 }
//}

void makeNewProm(){
    
    
for(int i=0; i<3;i++){
    Prom* porm;
    if(i == 0){
        porm = new Prom(7,70,i);
     }
     if(i== 1 ){
         porm = new Prom(21,90,i);
     }
     if(i==2){
         porm = new Prom(42,138,i);
     }
   
        proms.push_back(porm);
   
        promThreads.push_back(thread(moveProm, proms.back()));
        promsQueue.enqueue(porm);
       usleep(50000);
     

      } 

}





void movePassanger(Passanger *passanger){
 while(flag
  //&&  !passanger->isOnProm())  
  ){
    ofstream myfile;
    myfile.open ("output.txt");
    myfile << "Writing this to a file.\n";
    myfile<<"Ball pos x"<<passanger->x<<"ball pos y"<<passanger->y<<endl; 
    myfile<<"Queue"<<PassangerQueue.q.size();
    myfile<<"Queue proms"<<promsQueue.q.size();
    myfile.close();
     
     passanger->movePassanger();
     usleep(90000);
 }
    
        passangers.erase(std::remove(passangers.begin(), passangers.end(), passanger), passangers.end());
    
     
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
        passanger->isInQueue=true;
        
        
        usleep(2000000);



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
  
   for(int i=0; i<3;i++){
        promThreads[i].join();
    }
    

    for(int i = 0; i<threads.size(); i++){
        threads[i].join();
    }

    

    endwin();
    return 0;

}

