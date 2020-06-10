#pragma once
#include "cannon.h"
#include <string>
#include <thread>
#include <vector>
class Engineer {
public:
    Engineer();
    void repair(Cannon* cannon);
    void inspect(std::vector<Cannon*> cannons);
    std::string status;
    std::string progress;

};