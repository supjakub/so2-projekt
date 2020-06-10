#pragma once
#include <mutex>

class Storage {
public:
    Storage();
    bool lock();
    void unlock();
    std::string status;

private:
    std::mutex mutex;
};