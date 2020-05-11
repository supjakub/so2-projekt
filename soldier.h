#include "cannon.h"
#include "storage.h"
#include <thread>
#include <vector>
using namespace std;

class Soldier {
public:
    Soldier(Cannon* cannon, vector<Storage*> storage, int id);
    void fire();
    void reload(int n);
    int id;
    string status;
    string progress;
    void shoot(vector<Soldier*> enemies, int n);
    int hp;

private:
    Cannon* cannon;
    vector<Storage*> storage;
};