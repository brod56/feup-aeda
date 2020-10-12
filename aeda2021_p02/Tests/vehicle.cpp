#include "vehicle.h"
#include <iostream>
#include <vector>

using namespace std;
char SPACE = ' ';

Vehicle::Vehicle(string b, int m, int y) :
    brand{b}, month{m}, year{y}{

}

string Vehicle::getBrand() const {
    return brand;
}

int Vehicle::getYear() const {
    return year;
}

int Vehicle::info() const {
    info(cout);
    return 3;
}

int Vehicle::info(ostream &o) const {
    o << year << SPACE << month << SPACE << year << endl;
    return 3;
}

bool Vehicle::operator<(const Vehicle& v) const{
    return year < v.getYear() ||
            (year == v.getYear() && month < v.getMonth());
}

int Vehicle::getMonth() const {
    return month;
}

MotorVehicle::MotorVehicle(string b, int m, int y, string f, int cyl):
    Vehicle{b,m,y}, fuel{f}, cylinder{cyl}{

}

string MotorVehicle::getFuel() const {
    return fuel;
}

int MotorVehicle::info() const {
    info(cout);
    return 5;
}

int MotorVehicle::info(ostream &o) const {
    o << year << SPACE << month << SPACE << year <<
         fuel << SPACE << cylinder << endl;
    return 5;
}

float MotorVehicle::calculateTax() const {
    bool newAge = year > 1995;
    if (fuel == "gas") {
        if (cylinder <= 1000) return newAge ? 14.56 : 8.10;
        else if (cylinder <= 1300) return newAge ? 29.06 : 14.56;
        else if (cylinder <= 1750) return newAge ? 45.15: 22.65;
        else if (cylinder <= 2600) return newAge ? 113.98: 54.89;
        else if (cylinder <= 3500) return newAge ? 181.17: 87.13;
        else return newAge ? 320.89: 148.37;
    } else {
        if (cylinder <= 1500) return newAge ? 14.56: 8.10;
        else if (cylinder <= 2000) return newAge ? 29.06: 14.56;
        else if (cylinder <= 3000) return newAge ? 45.15: 22.65;
        else return newAge ? 113.98: 54.89;
    }
}

Car::Car(string b, int m, int y, string f, int cyl) :
    MotorVehicle(b,m,y,f,cyl){

}

int Car::info() const {
    return MotorVehicle::info();
}

int Car::info(ostream &o) const {
    return MotorVehicle::info(o);
}

Truck::Truck(string b, int m, int y, string f, int cyl, int ml) :
    MotorVehicle(b,m,y,f,cyl), maximumLoad{ml} {

}

int Truck::info() const {
    MotorVehicle::info();
    cout << maximumLoad << endl;
    return 6;
}

int Truck::info(ostream &o) const {
    MotorVehicle::info(o);
    o << maximumLoad << endl;
    return 6;
}

Bicycle::Bicycle(string b, int m, int y, string t):
    Vehicle(b,m,y), type{t} {

}

int Bicycle::info() const {
    return info(cout);
}

int Bicycle::info(ostream &o) const {
    Vehicle::info(o);
    o << type << endl;
    return 4;
}

float Bicycle::calculateTax() const {
    return 0;
}
