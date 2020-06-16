#include "medic.h"
using namespace std;
Medic::Medic() {
    this->status = "czeka ";
    this->progress = ".";
}

void Medic::inspect(vector<Soldier*> soldiers, vector<Engineer*> engineers) {
   std::unique_lock<std::mutex>var_lock(mtx);
   var.wait(var_lock);
   while(!queue.empty()) {
       int index = queue.back();
       queue.pop_back();
       if (index < 15) {
           soldiers[index]->mtx.lock();
           helpSoldier(soldiers[index]);
           soldiers[index]->mtx.unlock();
       }
       else {
           engineers[index - 15]->mtx.lock();
           helpEngineer(engineers[index - 15]);
           engineers[index - 15]->mtx.unlock();
       }
   }
}

void Medic::helpSoldier(Soldier* soldier) {
    soldier->dead = 2;
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
    soldier->dead = 3;
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