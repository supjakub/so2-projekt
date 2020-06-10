#include "engineer.h"

Engineer::Engineer() {
    this->status = "czeka   ";
    this->progress = ".";
}

void Engineer::repair(Cannon* cannon) {
    cannon->lock();
    this->status = "naprawia";
    cannon->destroyed = 1;
    int time = rand() % (301) + 300;
    int prog;
    this->progress = "0";
    for (int i = 0; i < 10; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
        prog = stoi(progress);
        prog++;
        this->progress = std::to_string(prog);
    }
    cannon->repair();
    cannon->unlock();
    this->status = "czeka       ";
    this->progress = ".";
}

void Engineer::inspect(std::vector<Cannon*> cannons) {
    for (int i = 0; i < 15; i++) {
        if (cannons[i]->destroyed == 2)
            this->repair(cannons[i]);
    }
}