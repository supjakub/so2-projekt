#include "engineer.h"
using namespace std;

Engineer::Engineer(int n, Medic* friendlyMedic) {
    this->status = "czeka   ";
    this->progress = ".";
    this->hp = 5;
    this->dead = 0;
    this->id = n;
    this->medic = " ";
    this->friendlyMedic = friendlyMedic;
}

void Engineer::repair(Cannon* cannon) {
    cannon->mutex.lock();
    this->status = "naprawia";
    cannon->destroyed = 1;
    cannon->mutex.unlock();
    int time = rand() % (301) + 300;
    int prog;
    this->progress = "0";
    for (int i = 0; i < 10; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
        prog = stoi(progress);
        prog++;
        this->progress = std::to_string(prog);
    }
    cannon->mutex.lock();
    cannon->repair();
    cannon->mutex.unlock();
    this->status = "czeka   ";
    this->progress = ".";
}

void Engineer::inspect(std::vector<Cannon*> cannons) {
    for (int i = 0; i < 15; i++) {
        if (cannons[i]->destroyed == 2) {
        cannons[i]->engineer = std::to_string(this->id + 1);
        this->repair(cannons[i]);
        cannons[i]->mutex.lock();
        cannons[i]->engineer = " ";
        cannons[i]->mutex.unlock();
        }
    }
}

void Engineer::heal(Hospital* hospital) {
    this->mtx.lock();
    this->status = "czeka     ";
    this->mtx.unlock();
    this->progress = ".";
    int bed = hospital->lockBed();
    this->mtx.lock();
    this->status = "w szpitalu";
    this->mtx.unlock();
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
    this->mtx.lock();
    this->hp = 5;
    this->dead = 0;
    this->status = "czeka     ";
    this->mtx.unlock();
    this->progress = ".";
}

void Engineer::callForHelp() {
    lock_guard<mutex> lck(friendlyMedic->mtx);
    friendlyMedic->queue.push_back(id + 15);
    friendlyMedic->mtx.unlock();
    friendlyMedic->var.notify_one();
}