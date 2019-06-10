main: Screen.o River.o Prom.o Passanger.o  main.cpp
	g++ -std=c++11 Screen.o River.o Prom.o Passanger.o  main.cpp -lncurses -pthread -fpermissive

Screen.o: Screen.cpp Screen.h
	g++  -c Screen.cpp -std=c++11 -lncurses -fpermissive

River.o: River.cpp River.h
	g++  -c River.cpp -std=c++11 -lncurses -fpermissive

Prom.o:Prom.cpp Prom.h
	g++  -c Prom.cpp -std=c++11 -lncurses -fpermissive

Passanger.o:Passanger.cpp Passanger.h
	g++  -c Passanger.cpp -std=c++11 -lncurses -fpermissive

SafeQueue.o: SafeQueue.cpp
	g++ -c SafeQueue.cpp -std=c++11 -lncurses -fpermissive

clean:
	rm -f *.o test
