#include "medic.h"
using namespace std;
Medic::Medic() {
    this->status = "czeka ";
    this->progress = ".";
}

void Medic::inspect(vector<Soldier*> soldiers, vector<Engineer*> engineers) {
   std::unique_lock<std::mutex>var_lock(mtx);
   var.wait(var_lock);
   if(!queue.empty()) {
       int index = queue.back();
       queue.pop_back();
       if (index < 15) {
           helpSoldier(soldiers[index]);
       }
       else {
           helpEngineer(engineers[index - 15]);
       }
   }
}

void Medic::helpSoldier(Soldier* soldier) {
    soldier->mtx.lock();
    soldier->dead = 2;
    soldier->medic = "M";
    soldier->mtx.unlock();
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
    soldier->medic = " ";
    soldier->mtx.unlock();
    this->status = "czeka ";
    this->progress = ".";
}

void Medic::helpEngineer(Engineer* engineer) {
    engineer->mtx.lock();
    engineer->dead = 2;
    engineer->medic = "M";
    engineer->mtx.unlock();
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
    engineer->mtx.lock();
    engineer->dead = 3;
    engineer->medic = " ";
    engineer->mtx.unlock();
    this->status = "czeka ";
    this->progress = ".";
}