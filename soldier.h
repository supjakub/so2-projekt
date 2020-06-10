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
    void fire();
    void reload();
    int id;
    string status;
    string progress;
    void shoot(vector<Soldier*> enemySoldiers, vector<Engineer*> enemyEngineers);
    int hp;
    void heal(Hospital* hospital);
    Cannon* cannon;
private:
    vector<Storage*> storage;
};