#include <mutex>

class Cannon {
public:
    Cannon();
    void lock();
    void unlock();

private:
    std::mutex mutex;
};
