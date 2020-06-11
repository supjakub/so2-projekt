#pragma once
#include <mutex>

class Storage {
public:
    Storage();
    bool lock();
    void unlock();
    std::string status;
    std::string soldier;

private:
    std::mutex mutex;
};