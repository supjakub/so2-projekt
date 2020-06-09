#include <iostream>
#include <thread>
#include <iostream>
#include <atomic>
#include <ncurses.h>
#include <unistd.h>
#include "soldier.h"

using namespace std;
const int SOLDIERS_NO = 15;
const int STORAGES_NO = 3;

vector<Soldier*> blue_soldiers;
vector<Cannon*> blue_cannons;
vector<Storage*> blue_storages;
vector<Soldier*> red_soldiers;
vector<Cannon*> red_cannons;
vector<Storage*> red_storages;

void execute(Soldier* soldier, atomic<bool>& running, vector<Soldier*> enemies)
{
    while(running)
    {
        if (soldier->hp > 0) {
            soldier->reload();
        }
        if (soldier->hp > 0) { 
        soldier->fire();
        soldier->shoot(enemies);
        }
    }
}

void displayGUI() {
    mvprintw(0,0,"Zolnierze niebiescy");
    for (int i = 0; i < 15; i++) {
        move(i + 1, 0);
        printw(to_string(i + 1).c_str());
    }
    mvprintw(17,0,"Magazyny niebieskie");
    for (int i = 0; i < 3; i++) {
        move(i + 18, 0);
        printw(to_string(i + 1).c_str());
    }
    mvprintw(0,50,"Zolnierze czerwoni");
    for (int i = 0; i < 15; i++) {
        move(i + 1, 50);
        printw(to_string(i + 1).c_str());
    }
    mvprintw(17,50,"Magazyny czerwone");
    for (int i = 0; i < 3; i++) {
        move(i + 18, 50);
        printw(to_string(i + 1).c_str());
    }
}

void display(atomic<bool> &displaying) {
    displayGUI();
    while(displaying) {
        usleep(100);
        for (int i = 0; i < 15; i++) {
            mvprintw(i+1,5,blue_soldiers[i]->status.c_str());
            mvprintw(i+1,18,blue_soldiers[i]->progress.c_str());
            mvprintw(i+1,20,to_string(blue_soldiers[i]->hp).c_str());
        }
        for (int i = 0; i < 3; i++)
            mvprintw(i + 18,5,blue_storages[i]->status.c_str());

        for (int i = 0; i < 15; i++) {
            mvprintw(i+1,55,red_soldiers[i]->status.c_str());
            mvprintw(i+1,68,red_soldiers[i]->progress.c_str());
        }
        for (int i = 0; i < 3; i++)
            mvprintw(i + 18,55,red_storages[i]->status.c_str());
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
    }

    for (int i = 0; i < 15; i++) {
        blue_cannons.push_back(new Cannon());
        blue_soldiers.push_back(new Soldier(blue_cannons[i], blue_storages, i));
        red_cannons.push_back(new Cannon());
        red_soldiers.push_back(new Soldier(red_cannons[i], red_storages, i));
    }

    thread soldier_threads[30];

    atomic<bool> running{true};

    for (int i = 0; i < 15; i++)
        soldier_threads[i] = thread(execute, blue_soldiers[i], ref(running), red_soldiers);
    for (int i = 15, j = 0; i < 30; i++, j++)
        soldier_threads[i] = thread(execute, red_soldiers[j], ref(running), blue_soldiers);

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

    display_thread.join();
    endwin();

        return 0;

}