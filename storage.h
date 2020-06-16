#pragma once
#include <mutex>

class Storage {
public:
    Storage();
    std::string status;
    std::string soldier;
    std::mutex mutex;    
};