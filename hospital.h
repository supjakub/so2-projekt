#pragma once
#include <mutex>
#include <vector>

class Hospital {
public:
    Hospital();
    std::mutex beds [9];
    int lockBed();
    void unlockBed(int n);
    int freeBeds;
};