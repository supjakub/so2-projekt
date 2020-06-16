#include "medic.h"
using namespace std;
Medic::Medic() {
    this->status = "czeka ";
    this->progress = ".";
}

void Medic::inspect(vector<Soldier*> soldiers, vector<Engineer*> engineers) {
   for (int i = 0; i < 15; i++) {
       if (soldiers[i]->dead == 1)
        helpSoldier(soldiers[i]);
    }
   for (int i = 0; i < 3; i++) {
       if (engineers[i]->dead == 1)
            helpEngineer(engineers[i]);
   } 
}

void Medic::helpSoldier(Soldier* soldier) {
    soldier->mtx.lock();
    soldier->dead = 2;
    soldier->mtx.unlock();
    soldier->medic = "M";
    this->status = "pomaga";
    int time = rand() % (301) + 600;
    int prog;
    this->progress = "0";
    for (int i = 0; i < 10; i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
        prog = stoi(progress);
        prog++;
        this->progress = to_string(prog);
    }
    soldier->mtx.lock();
    soldier->dead = 3;
    soldier->mtx.unlock();
    soldier->medic = " ";
    this->status = "czeka ";
    this->progress = ".";
}

void Medic::helpEngineer(Engineer* engineer) {
    engineer->dead = 2;
    engineer->medic = "M";
    this->status = "pomaga";
    int time = rand() % (301) + 600;
    int prog;
    this->progress = "0";
    for (int i = 0; i < 10; i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
        prog = stoi(progress);
        prog++;
        this->progress = to_string(prog);
    }
    engineer->dead = 3;
    engineer->medic = " ";
    this->status = "czeka ";
    this->progress = ".";
}