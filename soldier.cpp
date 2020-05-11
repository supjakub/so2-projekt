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
    cannon->unlock();
}

void Soldier::reload(int n) {
    this->status = "czeka       ";
    this->progress = ".";
    bool flag = false;
    int storage_index;
    do {
        for (int i = 0; i < n; i++) {
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
}

void Soldier::shoot(vector<Soldier*> enemies, int n){
    for (int i = 0; i <= n; i++) {
        int hit = rand() % n;
        enemies[hit]->hp--;
    }
}



