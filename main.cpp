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

vector<Soldier*> soldiers;
vector<Cannon*> cannons;
vector<Storage*> storages;

void execute(Soldier* soldier, atomic<bool>& running)
{
    while(running)
    {
        soldier->fire();
        soldier->reload(STORAGES_NO);
    }
}

void displayGUI() {
    for (int i = 0; i < SOLDIERS_NO; i++) {
        move(i + 1, 0);
        printw("Zolnierz nr ");
        printw(to_string(i + 1).c_str());
    }
    for (int i = 0; i < STORAGES_NO; i++) {
        move(i + 18, 0);
        printw("Magazyn nr ");
        printw(to_string(i + 1).c_str());
    }
}

void display(atomic<bool> &displaying) {
    displayGUI();
    while(displaying) {
        usleep(100);
        for (int i = 0; i < SOLDIERS_NO; i++) {
            mvprintw(i+1,15,soldiers[i]->status.c_str());
            mvprintw(i+1,30,soldiers[i]->progress.c_str());
        }
        for (int i = 0; i < STORAGES_NO; i++)
            mvprintw(i + 18,15,storages[i]->status.c_str());
        refresh();
    }
    clear();
}

int main(){
    initscr();

    srand(time(NULL));
    for (int i = 0; i < STORAGES_NO; i++)
        storages.push_back(new Storage());
    for (int i = 0; i < SOLDIERS_NO; i++) {
        cannons.push_back(new Cannon());
        soldiers.push_back(new Soldier(cannons[i], storages, i));
    }

    thread soldier_threads[SOLDIERS_NO];

    atomic<bool> running{true};

    for (int i = 0; i < SOLDIERS_NO; i++)
        soldier_threads[i] = thread(execute, soldiers[i], ref(running));

    atomic<bool> displaying{true};

    thread display_thread(display, ref(displaying));

    int key = 0;
    do {
        noecho();
        key = getchar();
    } while (key != 27);

    running = false;
    displaying = false;

    for (int i = 0; i < SOLDIERS_NO; i++)
        soldier_threads[i].join();

    display_thread.join();
    endwin();

        return 0;

}