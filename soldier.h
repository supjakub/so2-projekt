#pragma once
#include <thread>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <condition_variable>

#include "cannon.h"
#include "storage.h"
#include "hospital.h"
#include "engineer.h"
#include "medic.h"
using namespace std;

class Medic;

class Soldier {
public:
    Soldier(Cannon* cannon, vector<Storage*> storage, int id, Medic* enemyMedic);
    void fire(vector<Soldier*> enemySoldiers, vector<Engineer*> enemyEngineers);
    void reload();
    int id;
    string status;
    string progress;
    int hp;
    void heal(Hospital* hospital);
    Cannon* cannon;
    int dead;
    string target;
    string medic;
    mutex mtx;
    Medic* enemyMedic;
private:
    vector<Storage*> storage;
};