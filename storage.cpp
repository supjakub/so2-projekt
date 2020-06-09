#include "storage.h"

Storage::Storage() {
    status = "wolny ";
}

bool Storage::lock() {
    if (mutex.try_lock()) {
        this->status = "zajety";
    }
}

void Storage::unlock() {
    mutex.unlock();
    this->status = "wolny ";
}