#include <mutex>
#include <vector>

class Hospital {
public:
    Hospital();
    std::mutex beds [5];
    int lockBed();
    void unlockBed(int n);
    int freeBeds;
};