#include "storage.h"

Storage::Storage() {
    status = "wolny ";
    soldier = " ";
}

bool Storage::lock() {
    if (mutex.try_lock()) {
        this->status = "zajety przez";
    }
}

void Storage::unlock() {
    mutex.unlock();
    this->status = "wolny ";
}