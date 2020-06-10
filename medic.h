#pragma once
#include "soldier.h"
#include "engineer.h"
class Medic {
public:
    Medic();
    void inspect(vector<Soldier*> soldiers, vector<Engineer*> engineers);
    void helpSoldier(Soldier* soldier);
    void helpEngineer(Engineer* engineer);
    std::string status;
    std::string progress;
};