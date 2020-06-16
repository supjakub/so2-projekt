#include "medic.h"
using namespace std;
Medic::Medic() {
    this->status = "czeka ";
    this->progress = ".";
}

void Medic::inspect(vector<Soldier*> soldiers, vector<Engineer*> engineers) {
    unique_lock<mutex> lck(this->mtx);
    this->var.wait(lck);
    while (!queue.empty()) {
        int index = queue.back();
        queue.pop_back();
        if (index < 15)
            this->helpSoldier(soldiers[index]);
        else
            this->helpEngineer(engineers[index - 15]);
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
    this->progress = "0 ";
    for (int i = 0; i < 10; i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
        prog = stoi(progress);
        prog++;
        this->progress = to_string(prog).append(" ");
    }
    soldier->mtx.lock();
    soldier->dead = 3;
    soldier->mtx.unlock();
    soldier->medic = " ";
    this->status = "czeka ";
    this->progress = ". ";
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