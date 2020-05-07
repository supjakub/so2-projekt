all:
	g++ -pthread main.cpp cannon.cpp cannon.h soldier.cpp soldier.h storage.cpp storage.h -o battle -lncurses