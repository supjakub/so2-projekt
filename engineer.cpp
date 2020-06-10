#include "engineer.h"

Engineer::Engineer() {
    this->status = "czeka   ";
    this->progress = ".";
    this->hp = 5;
    this->dead = 0;
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
    this->status = "czeka   ";
    this->progress = ".";
}

void Engineer::inspect(std::vector<Cannon*> cannons) {
    if (this->hp > 0) {
        for (int i = 0; i < 15; i++) {
            if (cannons[i]->destroyed == 2)
                this->repair(cannons[i]);
        }
    }
}

void Engineer::heal(Hospital* hospital) {
    this->status = "czeka     ";
    this->progress = ".";
    int bed = hospital->lockBed();
    this->status = "w szpitalu";
    int time = rand() % (301) + 600;
    int prog;
    this->progress = "0";
    for (int i = 0; i < 10; i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
        prog = stoi(progress);
        prog++;
        this->progress = std::to_string(prog);
    }
    hospital->unlockBed(bed);
    this->hp = 5;
    this->dead = 0;
    this->status = "czeka     ";
    this->progress = ".";
}