#include "soldier.h"
using namespace std;

Soldier::Soldier(Cannon* cannon, vector<Storage*> storage, int id, Medic* friendlyMedic) {
    this->cannon = cannon;
    this->storage = storage;
    this->id = id;
    this->progress = ".";
    this->hp = 5;
    this->dead = 0;
    this->target = "  ";
    this->medic = " ";
    this->friendlyMedic = friendlyMedic;
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
        this_thread::sleep_for(chrono::milliseconds(time));
        prog = stoi(progress);
        prog++;
        if (prog > 9) {
            prog = 9;
        }
        this->progress = to_string(prog);
    }
    if (hit < 15 && enemySoldiers[hit]->dead == 0) {
        enemySoldiers[hit]->mtx.lock();
        if (enemySoldiers[hit]->hp > 0) {
            enemySoldiers[hit]->hp--;
            if (enemySoldiers[hit]->hp <= 0) {
                enemySoldiers[hit]->dead = 1;
                enemySoldiers[hit]->status = "ranny       ";
            }
        }
        enemySoldiers[hit]->mtx.unlock();
    }

    if (hit >= 15 && enemyEngineers[hit-15]->dead == 0) {
        enemyEngineers[hit-15]->mtx.lock();
        if (enemyEngineers[hit-15]->hp > 0) {
            enemyEngineers[hit-15]->hp--;
            if (enemyEngineers[hit-15]->hp <= 0) {
                enemyEngineers[hit-15]->dead = 1;
                enemyEngineers[hit-15]->status = "ranny   ";
            }
        }
        enemyEngineers[hit-15]->mtx.unlock();
    }

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
        if (this->dead != 0)
            return;
        for (int i = 0; i < 3; i++) {
            if (this->storage[i]->mutex.try_lock()) {
                storage[i]->status = "zajety przez";
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
        this_thread::sleep_for(chrono::milliseconds(time));
        prog = stoi(progress);
        prog++;
        this->progress = to_string(prog);
    }
    storage[storage_index]->mutex.unlock();
    storage[storage_index]->status = "wolny ";
    this->status = "czeka       ";
    this->progress = ".";
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
        this_thread::sleep_for(chrono::milliseconds(time));
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

void Soldier::callForHelp() {
    lock_guard<mutex> lck(friendlyMedic->mtx);
    friendlyMedic->queue.push_back(id);
    friendlyMedic->mtx.unlock();
    friendlyMedic->var.notify_one();
}

