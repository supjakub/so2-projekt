all:
	g++ -pthread main.cpp cannon.cpp cannon.h soldier.cpp soldier.h storage.cpp storage.h hospital.cpp hospital.h engineer.cpp engineer.h medic.cpp medic.h -o battle -lncurses