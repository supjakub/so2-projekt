#pragma once
#include <string>
#include <thread>
#include <vector>
#include <mutex>
#include "hospital.h"
#include "cannon.h"
using namespace std;

class Engineer {
public:
    Engineer(int n);
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
};