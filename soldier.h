#include "cannon.h"
#include "storage.h"
#include <thread>
#include <vector>
#include "hospital.h"
using namespace std;

class Soldier {
public:
    Soldier(Cannon* cannon, vector<Storage*> storage, int id);
    void fire();
    void reload();
    int id;
    string status;
    string progress;
    void shoot(vector<Soldier*> enemies);
    int hp;
    void heal(Hospital* hospital);

private:
    Cannon* cannon;
    vector<Storage*> storage;
};