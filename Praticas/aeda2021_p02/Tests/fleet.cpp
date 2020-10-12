#include "fleet.h"
#include <string>
#include <algorithm>

using namespace std;

vector<Vehicle *> Fleet::getVehicles() const {
    return vehicles;
}

void Fleet::addVehicle(Vehicle *vl) {
    vehicles.push_back(vl);
}

int Fleet::numVehicles() const {
    return vehicles.size();
}

int Fleet::lowestYear() const {
    if (vehicles.empty()) return 0;
    vector<int> years;
    for (const auto& v: vehicles){
        years.push_back(v->getYear());
    }
    return *min(years.begin(), years.end());
}

ostream &operator<<(ostream &o, const Fleet &f) {
    vector<Vehicle*> vehicles = f.getVehicles();
    for (const auto& v: vehicles){
        v->info(o);
    }
    return o;
}

vector<Vehicle *> Fleet::operator()(int yearM) const {
    vector<Vehicle*> sameYearVehicles;
    for (const auto& v: vehicles){
        if (v->getYear() == yearM){
            sameYearVehicles.push_back(v);
        }
    }
    return sameYearVehicles;
}

float Fleet::totalTax() const {
    float total = 0;
    for (const auto& v: vehicles){
        total += v->calculateTax();
    }
    return total;
}

unsigned Fleet::removeOldVehicles(int yl) {
    int counter = 0;
    for (int i = 0; i < vehicles.size(); ++i){
        if (vehicles.at(i)->getYear() <= yl){
            vehicles.erase(vehicles.begin() + i);
            i--;
            counter++;
        }
    }
    return counter;
}
