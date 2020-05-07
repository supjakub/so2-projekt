#include "storage.h"

Storage::Storage() {
    status = "wolne ";
}

bool Storage::lock() {
    if (mutex.try_lock()) {
        this->status = "zajety";
    }
}

void Storage::unlock() {
    mutex.unlock();
    this->status = "wolne ";
}