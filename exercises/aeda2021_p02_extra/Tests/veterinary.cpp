#include "veterinary.h"
#include <sstream>
using namespace std;

string Veterinary::getName() const {
    return name;
}

Veterinary::Veterinary(string nome, int cod):
    name(nome), codOrder(cod){

}

string Veterinary::getInfo() const {
    std::ostringstream info;
    info << name << ", " << codOrder;
    return info.str();
}


