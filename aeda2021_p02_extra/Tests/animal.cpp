#include "animal.h"
#include <sstream>
using namespace std;

int Animal::youngest = 999;

string Animal::getName() const {
	return name;
}

int Animal::getAge() const {
    return age;
}

void Animal::setVeterinary(Veterinary *vet) {
    this->vet = vet;
}

Veterinary *Animal::getVeterinary() const {
    return vet;
}

Animal::Animal(string name, int age) : name(name), age(age), vet(nullptr){
    if (age < youngest){
        youngest = age;
    }
}

int Animal::getYoungest() {
    return Animal::youngest;
}

string Animal::getInfo() const {
    std::ostringstream info;
    if (getVeterinary() != nullptr){
        info << name << ", " << age << ", " << getVeterinary()->getInfo();
    }
    else info << name << ", " << age;
    return info.str();
}


Dog::Dog(string name, int age, string breed) :
    Animal(name,age), breed(breed){

}

bool Dog::isYoung() const {
    return age < 5;
}

string Dog::getInfo() const {
    std::ostringstream info;
    if (getVeterinary() != nullptr){
        info << name << ", " << age << ", " << getVeterinary()->getInfo() << ", " << breed;
    }
    else info << name << ", " << age << ", " << breed;
    return info.str();
}

Flying::Flying(int maxv, int maxa) :
    maxVelocity(maxv), maxAltitude(maxa){

}

int Flying::getMaxVelocity() const {
    return maxVelocity;
}

int Flying::getMaxAltitude() const {
    return maxAltitude;
}

Bat::Bat(string name, int age, int maxv, int maxa) :
    Flying(maxv,maxa), Animal(name,age){

}

bool Bat::isYoung() const {
    return age < 4;
}

string Bat::getInfo() const {
    std::ostringstream info;
    if (getVeterinary() != nullptr){
        info << name << ", " << age << ", " << getVeterinary()->getInfo() << ", " << getMaxVelocity() << ", " << getMaxAltitude();
    }
    else info << name << ", " << age << ", " << getMaxVelocity() << ", " << getMaxAltitude();
    return info.str();
}
