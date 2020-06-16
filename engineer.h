#pragma once
#include <string>
#include <thread>
#include <vector>
#include <mutex>
#include "hospital.h"
#include "cannon.h"
#include "medic.h"
using namespace std;

class Medic;

class Engineer {
public:
    Engineer(int n, Medic* friendlyMedic);
    void repair(Cannon* cannon);
    void inspect(std::vector<Cannon*> cannons);
    std::string status;
    std::string progress;
    int hp;
    void heal(Hospital* hospital);
    int dead = 0;
    int id;
    std::string medic;
    std::mutex mtx;
    void callForHelp();
    Medic* friendlyMedic;
};