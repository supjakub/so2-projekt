#include <iostream>
#include <thread>
#include <iostream>
#include <atomic>
#include <ncurses.h>
#include <unistd.h>
#include "soldier.h"
#include "engineer.h"
#include "medic.h"
using namespace std;

vector<Soldier*> blue_soldiers;
vector<Cannon*> blue_cannons;
vector<Storage*> blue_storages;
vector<Soldier*> red_soldiers;
vector<Cannon*> red_cannons;
vector<Storage*> red_storages;
Hospital* hospital = new Hospital();
vector<Engineer*> blue_engineers;
vector<Engineer*> red_engineers;
Medic* blue_medic = new Medic();
Medic* red_medic = new Medic;

void soldierExecute(Soldier* soldier, atomic<bool>& running, vector<Soldier*> enemySoldiers, vector<Engineer*> enemyEngineers)
{
    while(running) {
        while (soldier->dead == 0) {
            soldier->reload();
            if (soldier->dead != 0) {
                break;
            }
            soldier->fire(enemySoldiers, enemyEngineers);
            if (soldier->dead != 0) {
                break;
            }
        }
        if (soldier->dead == 3)
            soldier->heal(hospital);
    }
}

void engineerExecute(Engineer* engineer, atomic<bool>& running, vector<Cannon*> cannons) {
    while(running) {
        while (engineer->dead == 0) {
            engineer->inspect(cannons);
            if (engineer->hp <= 0) {
                engineer->status = "ranny   ";
                engineer->dead = 1;
                break;
            }
        }
        if (engineer->dead == 3)
            engineer->heal(hospital);
    }
}

void medicExecute(Medic* medic, atomic<bool>& running, vector<Soldier*> soldiers, vector<Engineer*> engineers) {
    while (running) {
        medic->inspect(soldiers, engineers);
    }
}

void displayGUI() {
    mvprintw(0,0,"Zolnierze");
    mvprintw(0,16,"P");
    mvprintw(0,18,"H");
    mvprintw(0,20,"D");
    mvprintw(0,22,"C");
    mvprintw(0,25,"I");
    for (int i = 0; i < 15; i++) {
        move(i + 1, 0);
        printw(to_string(i + 1).c_str());
    }
    mvprintw(17,0,"Magazyny");
    for (int i = 0; i < 3; i++) {
        move(i + 18, 0);
        printw(to_string(i + 1).c_str());
    }
    mvprintw(17,21,"Inzynierzy");
    for (int i = 0; i < 3; i++) {
        move(i + 18, 21);
        printw(to_string(i + 1).c_str());
    }
    mvprintw(22,0,"Medyk");

    mvprintw(0,111,"Zolnierze");
    mvprintw(0,104,"P");
    mvprintw(0,102,"H");
    mvprintw(0,100,"D");
    mvprintw(0,97,"C");
    mvprintw(0,94,"I");
    for (int i = 0; i < 15; i++) {
        move(i + 1, 120);
        printw(to_string(i + 1).c_str());
    }
    mvprintw(17,105,"Magazyny");
    for (int i = 0; i < 3; i++) {
        move(i + 18, 105);
        printw(to_string(i + 1).c_str());
    }
    mvprintw(17,85,"Inzynierzy");
    for (int i = 0; i < 3; i++) {
        move(i + 18, 85);
        printw(to_string(i + 1).c_str());
    }
    mvprintw(22,85,"Medyk");
    mvprintw(17,50,"Szpital");

    mvprintw(0,40,"Legenda:");
    mvprintw(1,40,"P - progres");
    mvprintw(2,40,"H - punkty zycia HP");
    mvprintw(3,40,"D - dzialo");
    mvprintw(4,40,"(O - dzialajace)");
    mvprintw(5,40,"(X - zepsute)");
    mvprintw(6,40,"C - nr celu");
    mvprintw(7,40,"I - ktory inzynier naprawia");
    mvprintw(8,40,"M - obecnosc medyka");
    }

void display(atomic<bool> &displaying) {
    displayGUI();
    while(displaying) {
        usleep(100);
        for (int i = 0; i < 15; i++) {
            mvprintw(i+1,3,blue_soldiers[i]->status.c_str());
            mvprintw(i+1,16,blue_soldiers[i]->progress.c_str());
            mvprintw(i+1,18,to_string(blue_soldiers[i]->hp).c_str());
            mvprintw(i+1,20,blue_soldiers[i]->cannon->symbol.c_str());
            mvprintw(i+1,22,blue_soldiers[i]->target.c_str());
            mvprintw(i+1,25,blue_soldiers[i]->cannon->engineer.c_str());
            mvprintw(i+1,27,blue_soldiers[i]->medic.c_str());
        }
        for (int i = 0; i < 3; i++) {
            mvprintw(i + 18,3,blue_storages[i]->status.c_str());
            mvprintw(i+18,16,blue_storages[i]->soldier.c_str());
        }
        for (int i = 0; i < 3; i++) {
            mvprintw(i+18,23,blue_engineers[i]->status.c_str());
            mvprintw(i+18,32,blue_engineers[i]->progress.c_str());
            mvprintw(i+18,34,to_string(blue_engineers[i]->hp).c_str());
            mvprintw(i+18,36,blue_engineers[i]->medic.c_str());
        }
        mvprintw(22,7,blue_medic->status.c_str());
        mvprintw(22,14,blue_medic->progress.c_str());

        for (int i = 0; i < 15; i++) {
            mvprintw(i+1,106,red_soldiers[i]->status.c_str());
            mvprintw(i+1,104,red_soldiers[i]->progress.c_str());
            mvprintw(i+1,102,to_string(red_soldiers[i]->hp).c_str());
            mvprintw(i+1,100,red_soldiers[i]->cannon->symbol.c_str());
            mvprintw(i+1,97,red_soldiers[i]->target.c_str());
            mvprintw(i+1,94,red_soldiers[i]->cannon->engineer.c_str());
            mvprintw(i+1,92,red_soldiers[i]->medic.c_str());
        }
        for (int i = 0; i < 3; i++) {
            mvprintw(i + 18,107,red_storages[i]->status.c_str());
            mvprintw(i+18,120,red_storages[i]->soldier.c_str());
        }
        for (int i = 0; i < 3; i++) {
            mvprintw(i+18,87,red_engineers[i]->status.c_str());
            mvprintw(i+18,97,red_engineers[i]->progress.c_str());
            mvprintw(i+18,99,to_string(red_engineers[i]->hp).c_str());
            mvprintw(i+18,101,red_engineers[i]->medic.c_str());
        }
        mvprintw(22,92,red_medic->status.c_str());
        mvprintw(22,100,red_medic->progress.c_str());
        mvprintw(18,52,to_string(hospital->freeBeds).c_str());
        mvprintw(18,53,"/9");
        refresh();
    }
    clear();
}

int main(){
    initscr();

    srand(time(NULL));
    for (int i = 0; i < 3; i++) {
        blue_storages.push_back(new Storage());
        red_storages.push_back(new Storage());
        blue_engineers.push_back(new Engineer(i + 1));
        red_engineers.push_back(new Engineer(i + 1));      
    }

    for (int i = 0; i < 15; i++) {
        blue_cannons.push_back(new Cannon());
        blue_soldiers.push_back(new Soldier(blue_cannons[i], blue_storages, i));
        red_cannons.push_back(new Cannon());
        red_soldiers.push_back(new Soldier(red_cannons[i], red_storages, i));
    }


    thread soldier_threads[30];
    thread engineer_threads[6];
    thread medic_threads[2];

    atomic<bool> running{true};

    for (int i = 0; i < 15; i++)
        soldier_threads[i] = thread(soldierExecute, blue_soldiers[i], ref(running), red_soldiers, red_engineers);
    for (int i = 15, j = 0; i < 30; i++, j++)
        soldier_threads[i] = thread(soldierExecute, red_soldiers[j], ref(running), blue_soldiers, blue_engineers);
    for (int i = 0; i < 3; i++)
        engineer_threads[i] = thread(engineerExecute, blue_engineers[i], ref(running), blue_cannons);
    for (int i = 3, j = 0; i < 6; i++, j++)
        engineer_threads[i] = thread(engineerExecute, red_engineers[j], ref(running), red_cannons);
    medic_threads[0] = thread(medicExecute, blue_medic, ref(running), blue_soldiers, blue_engineers);
    medic_threads[1] = thread(medicExecute, red_medic, ref(running), red_soldiers, red_engineers);
    atomic<bool> displaying{true};

    thread display_thread(display, ref(displaying));

    int key = 0;
    do {
        noecho();
        key = getchar();
    } while (key != 27);

    running = false;
    displaying = false;

    for (int i = 0; i < 30; i++)
        soldier_threads[i].join();
    for (int i = 0; i < 6; i++)
        engineer_threads[i].join();
    for (int i = 0; i < 2; i++)
        medic_threads[i].join();

    display_thread.join();
    endwin();

    return 0;
}