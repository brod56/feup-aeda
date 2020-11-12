#include "zoo.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;

void stripSpecial(string& s){
    string newString;
    for (const auto& c: s){
        if (isalpha(c) || isdigit(c) || c == ' '){
            newString.push_back(c);
        }
    }
    s = newString;
}

unsigned Zoo::numAnimals() const {
    return animals.size();
}

unsigned Zoo::numVeterinarians() const {
    return veterinarians.size();
}

void Zoo::addAnimal(Animal *a1) {
    animals.push_back(a1);
}

string Zoo::getInfo() const {
    std::ostringstream info;
    for (const auto& animal: animals){
        info << animal->getInfo() << endl;
    }
    return info.str();
}

bool Zoo::isYoung(string nameA) {
    for (const auto& animal: animals){
        if (nameA == animal->getName() && animal->isYoung()) {
            return true;
        }
    }
    return false;
}

void Zoo::allocateVeterinarians(istream &isV) {
    string name, code;
    for (std::string line; getline(isV,line);){
        stripSpecial(line);
        if (!isdigit(line.at(0))){
            name = line;
        }
        else{
            code = line;
            veterinarians.push_back(new Veterinary(name,std::stoi(code)));
        }
    }

    //distribute uniformly
    for (int i = 0; i < animals.size(); ++i){
        if (i >= veterinarians.size()) {
            animals.at(i)->setVeterinary(veterinarians.at(rand() % veterinarians.size()));
        }
        else{
            animals.at(i)->setVeterinary(veterinarians.at(i));
        }
    }
}

Zoo::~Zoo() {
    for (const auto& v: veterinarians){
        delete v;
    }
}

bool Zoo::removeVeterinary(string nameV) {
    for (int i = 0; i < veterinarians.size(); ++i){
        if (nameV == veterinarians.at(i)->getName()){
            // change vet to the next
            for (const auto& animal: animals){
                if (animal->getVeterinary()->getName() == nameV){
                    if (i+1 < veterinarians.size()){
                        animal->setVeterinary(veterinarians.at(i+1));
                    }
                    else animal->setVeterinary(NULL);
                }
            }

            delete veterinarians.at(i);
            veterinarians.erase(veterinarians.begin() + i);
            return true;
        }
    }
    return false;
}

bool Zoo::operator<(Zoo &zoo2) const {
    int sum1 = 0, sum2 = 0;
    vector<Animal*> animals1 = animals, animals2 = zoo2.animals;
    for (const auto& a1: animals1) sum1 += a1->getAge();
    for (const auto& a2: animals2) sum2 += a2->getAge();
    return sum1 < sum2;
}

