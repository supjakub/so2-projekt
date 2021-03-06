#pragma once
#include <mutex>

class Cannon {
public:
    Cannon();
    void lock();
    void unlock();
    int destroyed;
    std::string symbol;
    void destroy();
    void repair();
    std::string engineer;
    std::mutex mutex;
    bool loaded;
};
