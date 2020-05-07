#include "cannon.h"

Cannon::Cannon(){

}

void Cannon::lock(){
    mutex.lock();
}

void Cannon::unlock(){
    mutex.unlock();
}