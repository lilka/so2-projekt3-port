#include "Screen.h"
#include "River.h"
#include "Prom.h"
#include "People.h"
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
vector<People*> peoples;
SafeQueue<People*> peopleQueue; 




void refreshScreen(){

    while(flag) {
        clear();
            river->drawRiver();
            river->drawSecondRiver();
            river->drawPort();
            prom->drawProm();
                for (int i = 0; i < peoples.size(); i++) {
                        peoples[i]->drawPeople();
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
     if(prom->shouldWaitForPeople()){
         for (int i=0; i<5; i++){
             People* passanger=peopleQueue.dequeue();
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


void movePeople(People *people){
 while((flag && !people->isOnProm())){
    ofstream myfile;
    myfile.open ("output.txt");
    myfile << "Writing this to a file.\n";
    myfile<<"Prom pos x"<<prom->x<<"lift pos y"<<prom->y<<endl; 
    myfile<<"Ball pos x"<<people->x<<"ball pos y"<<people->y<<endl; 
    myfile<<"Queue"<<peopleQueue.q.size();
    myfile.close();
     
     people->movePeople();
     usleep(90000);
 }
    if(people->y==51){
        
        peoples.erase(std::remove(peoples.begin(), peoples.end(), people), peoples.end());
    }
     
}

void makeNewPeople(){

    float x = screen->getScreenWidth();
    float y = screen->getScreenHeight();

    short tmp;
 
    while(flag)
    {

        tmp = rand() % 8 +1;
        People *people = new People(x, y);
        peoples.push_back(people);
   
        threads.push_back(thread(movePeople, peoples.back()));
        peopleQueue.enqueue(people);
        
        
        usleep(1000000);



    }
}





int main() {
    srand(time(NULL));
    screen= new Screen();
    thread generateNewProm(makeNewProm);
    thread generateNewPeople(makeNewPeople);
    thread generateriver(makeRiver);
    thread refreshScreenThread(refreshScreen);
    thread escapeThread(escape);
    
    
    escapeThread.join();
    generateNewPeople.join();
    refreshScreenThread.join();
    generateriver.join();
    generateNewProm.join();
  


    for(int i = 0; i<threads.size(); i++){
        threads[i].join();
    }
    

    endwin();
    return 0;

}

