#include "cannon.h"
using namespace std;

Cannon::Cannon(){
    this->destroyed = 0;
    this->symbol = 'O';
    this->engineer = " ";
    this->loaded = false;
}

// void Cannon::lock(){
//     mutex.lock();
// }

// void Cannon::unlock(){
//     mutex.unlock();
// }

void Cannon::destroy() {
    int luck = rand() % 101;
    if (luck <= 30) {
        this->destroyed = 2;
        this->symbol = 'X';
    }
}

void Cannon::repair() {
    this->destroyed = 0;
    this->symbol = 'O';
}