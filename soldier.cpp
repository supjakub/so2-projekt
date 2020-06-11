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
    this->dead = 0;
    this->target = "  ";
}


void Soldier::fire(vector<Soldier*> enemySoldiers, vector<Engineer*> enemyEngineers) {
    while (cannon->destroyed != 0) {
    }
    cannon->lock();
    this->status = "strzela     ";
    int time = rand() % (301) + 300;
    int prog;
    this->progress = "0";
    int hit = rand() % 18;
    this->target = to_string(hit + 1);
    for (int i = 0; i < 10; i++) {
        this_thread::sleep_for(std::chrono::milliseconds(time));
        prog = stoi(progress);
        prog++;
        this->progress = to_string(prog);
    }
    if (hit < 15 && enemySoldiers[hit]->hp > 0)
        enemySoldiers[hit]->hp--;
    if (hit >= 15 && enemyEngineers[hit - 15]->hp > 0)
        enemyEngineers[hit - 15]->hp--;
    cannon->destroy();
    cannon->unlock();
    this->status = "czeka       ";
    this->progress = ".";
    this->target = "  ";
}

void Soldier::reload() {
    this->status = "czeka       ";
    this->progress = ".";
    bool flag = false;
    int storage_index;
    do {
        if (this->hp <= 0)
            return;
        for (int i = 0; i < 3; i++) {
            if (this->storage[i]->lock()) {
                storage[i]->soldier = to_string(this->id + 1).append(" ");
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

// void Soldier::shoot(vector<Soldier*> enemySoldiers, vector<Engineer*> enemyEngineers){
//     int hit = rand() % 18;
//     if (hit < 15 && enemySoldiers[hit]->hp > 0)
//         enemySoldiers[hit]->hp--;
//     if (hit >= 15 && enemyEngineers[hit - 15]->hp > 0)
//         enemyEngineers[hit - 15]->hp--;
// }

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
    this->dead = 0;
    this->status = "czeka       ";
    this->progress = ".";
}

