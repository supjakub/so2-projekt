#include "soldier.h"
#include <thread>
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

Soldier::Soldier(Cannon* cannon, vector<Storage*> storage, int id) {
    this->cannon = cannon;
    this->storage = storage;
    this->id = id;
    this->progress = ".";
    this->hp = 5;
}


void Soldier::fire() {
    while (cannon->destroyed != 0) {
    }
    cannon->lock();
    this->status = "strzela     ";
    int time = rand() % (301) + 300;
    int prog;
    this->progress = "0";
    for (int i = 0; i < 10; i++) {
        this_thread::sleep_for(std::chrono::milliseconds(time));
        prog = stoi(progress);
        prog++;
        this->progress = to_string(prog);
    }
    cannon->destroy();
    cannon->unlock();
    this->status = "czeka       ";
    this->progress = ".";
}

void Soldier::reload() {
    this->status = "czeka       ";
    this->progress = ".";
    bool flag = false;
    int storage_index;
    do {
        for (int i = 0; i < 3; i++) {
            if (this->storage[i]->lock()) {
                flag = true;
                storage_index = i;
                break;
            }
        }
    } while (!flag);
    this->status = "przeladowuje";
    int time = rand() % (301) + 300;
    int prog;
    this->progress = "0";
    for (int i = 0; i < 10; i++){
        this_thread::sleep_for(std::chrono::milliseconds(time));
        prog = stoi(progress);
        prog++;
        this->progress = to_string(prog);
    }
    storage[storage_index]->unlock();
    this->status = "czeka       ";
    this->progress = ".";
}

void Soldier::shoot(vector<Soldier*> enemies){
    int hit = rand() % 15;
    if (enemies[hit]->hp > 0) {
        enemies[hit]->hp--;
    }
}

void Soldier::heal(Hospital* hospital) {
    this->status = "czeka       ";
    this->progress = ".";
    int bed = hospital->lockBed();
    this->status = "w szpitalu  ";
    int time = rand() % (301) + 600;
    int prog;
    this->progress = "0";
    for (int i = 0; i < 10; i++){
        this_thread::sleep_for(std::chrono::milliseconds(time));
        prog = stoi(progress);
        prog++;
        this->progress = to_string(prog);
    }
    hospital->unlockBed(bed);
    this->hp = 5;
    this->status = "czeka       ";
    this->progress = ".";
}

