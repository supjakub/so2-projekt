
#include <iostream>
#include <thread>
#include <iostream>
#include <atomic>
#include <ncurses.h>
#include <unistd.h>
#include "soldier.h"
#include "engineer.h"
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

void soldierExecute(Soldier* soldier, atomic<bool>& running, vector<Soldier*> enemies)
{
    while(running)
    {
        if (soldier->hp > 0) {
            soldier->reload();
        }
        else
            soldier->heal(hospital);
        if (soldier->hp > 0) { 
            soldier->fire();
            soldier->shoot(enemies);
        }
        else
            soldier->heal(hospital);
    }
}

void engineerExecute(Engineer* engineer, atomic<bool>& running, vector<Cannon*> cannons) {
    while (running) {
        engineer->inspect(cannons);
    }
}

void displayGUI() {
    mvprintw(0,0,"Zolnierze");
    for (int i = 0; i < 15; i++) {
        move(i + 1, 0);
        printw(to_string(i + 1).c_str());
    }
    mvprintw(17,0,"Magazyny");
    for (int i = 0; i < 3; i++) {
        move(i + 18, 0);
        printw(to_string(i + 1).c_str());
    }
    mvprintw(17,15,"Inzynierzy");
    for (int i = 0; i < 3; i++) {
        move(i + 18, 15);
        printw(to_string(i + 1).c_str());
    }
    mvprintw(0,100,"Zolnierze");
    for (int i = 0; i < 15; i++) {
        move(i + 1, 100);
        printw(to_string(i + 1).c_str());
    }
    mvprintw(17,100,"Magazyny");
    for (int i = 0; i < 3; i++) {
        move(i + 18, 100);
        printw(to_string(i + 1).c_str());
    }
    mvprintw(17,85,"Inzynierzy");
    for (int i = 0; i < 3; i++) {
        move(i + 18, 85);
        printw(to_string(i + 1).c_str());
    }
    mvprintw(17,50,"Szpital");
}

void display(atomic<bool> &displaying) {
    displayGUI();
    while(displaying) {
        usleep(100);
        for (int i = 0; i < 15; i++) {
            mvprintw(i+1,5,blue_soldiers[i]->status.c_str());
            mvprintw(i+1,18,blue_soldiers[i]->progress.c_str());
            mvprintw(i+1,20,to_string(blue_soldiers[i]->hp).c_str());
            mvprintw(i+1,23,blue_soldiers[i]->cannon->symbol.c_str());
        }
        for (int i = 0; i < 3; i++)
            mvprintw(i + 18,5,blue_storages[i]->status.c_str());
        for (int i = 0; i < 3; i++) {
            mvprintw(i+18,20,blue_engineers[i]->status.c_str());
            mvprintw(i+18,32,blue_engineers[i]->progress.c_str());
        }

        for (int i = 0; i < 15; i++) {
            mvprintw(i+1,105,red_soldiers[i]->status.c_str());
            mvprintw(i+1,118,red_soldiers[i]->progress.c_str());
            mvprintw(i+1,120,to_string(red_soldiers[i]->hp).c_str());
            mvprintw(i+1,95,red_soldiers[i]->cannon->symbol.c_str());
        }
        for (int i = 0; i < 3; i++)
            mvprintw(i + 18,105,red_storages[i]->status.c_str());
        for (int i = 0; i < 3; i++) {
            mvprintw(i+18,87,red_engineers[i]->status.c_str());
            mvprintw(i+18,97,red_engineers[i]->progress.c_str());
        }
        mvprintw(18,53,to_string(hospital->freeBeds).c_str());
        mvprintw(18,54,"/5");
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
        blue_engineers.push_back(new Engineer());
        red_engineers.push_back(new Engineer());      
    }

    for (int i = 0; i < 15; i++) {
        blue_cannons.push_back(new Cannon());
        blue_soldiers.push_back(new Soldier(blue_cannons[i], blue_storages, i));
        red_cannons.push_back(new Cannon());
        red_soldiers.push_back(new Soldier(red_cannons[i], red_storages, i));
    }


    thread soldier_threads[30];
    thread engineer_threads[6];

    atomic<bool> running{true};

    for (int i = 0; i < 15; i++)
        soldier_threads[i] = thread(soldierExecute, blue_soldiers[i], ref(running), red_soldiers);
    for (int i = 15, j = 0; i < 30; i++, j++)
        soldier_threads[i] = thread(soldierExecute, red_soldiers[j], ref(running), blue_soldiers);
    for (int i = 0; i < 3; i++)
        engineer_threads[i] = thread(engineerExecute, blue_engineers[i], ref(running), blue_cannons);
    for (int i = 3, j = 0; i < 6; i++, j++)
        engineer_threads[i] = thread(engineerExecute, red_engineers[j], ref(running), red_cannons);
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

    display_thread.join();
    endwin();

    return 0;

}