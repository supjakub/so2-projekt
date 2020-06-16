#pragma once
#include "soldier.h"
#include "engineer.h"
#include <condition_variable>
#include <mutex>
#include <vector>
using namespace std;

class Soldier;

class Engineer;

class Medic {
public:
    Medic();
    void inspect(vector<Soldier*> soldiers, vector<Engineer*> engineers);
    void helpSoldier(Soldier* soldier);
    void helpEngineer(Engineer* engineer);
    std::string status;
    std::string progress;
    std::vector<int> queue;
    std::mutex mtx;
    std::condition_variable var;
};