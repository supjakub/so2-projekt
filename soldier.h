#pragma once
#include "cannon.h"
#include "storage.h"
#include <thread>
#include <vector>
#include "hospital.h"
#include "engineer.h"
using namespace std;

class Soldier {
public:
    Soldier(Cannon* cannon, vector<Storage*> storage, int id);
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
private:
    vector<Storage*> storage;
};