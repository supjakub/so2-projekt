#include "hospital.h"

Hospital::Hospital() {
    this->freeBeds = 5;
}

int Hospital::lockBed() {
    while (true) {
        for (int i = 0; i < 5; i++) {
            if(this->beds[i].try_lock()) {
                this->freeBeds--;
                return i;
            }
        }
    }
}

void Hospital::unlockBed(int n) {
    beds[n].unlock();
    this->freeBeds++;
}