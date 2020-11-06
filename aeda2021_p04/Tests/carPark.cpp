#include "carPark.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>
using namespace std;

CarPark::CarPark(unsigned cap, unsigned nMaxCli): capacity(cap), numMaxClients(nMaxCli)
{
    freePlaces=cap;
}

vector<InfoCard> CarPark::getClients() const
{
    return clients;
}

unsigned CarPark::getNumPlaces() const
{
    return capacity;
}

unsigned CarPark::getNumOccupiedPlaces() const
{
    return capacity-freePlaces;
}

unsigned CarPark::getNumMaxClients() const
{
    return numMaxClients;
}

unsigned CarPark::getNumClients() const
{
    return clients.size();
}

int CarPark::clientPosition(const string & name) const
{
    return sequentialSearch(clients,InfoCard{name,false,0});
}

unsigned CarPark::getFrequency(const string &name) const
{
    int position = clientPosition(name);
    if (position != -1){
        return clients.at(position).frequency;
    }
    else{
        throw ClientDoesNotExist(name);
    }
}

bool CarPark::addClient(const string & name)
{
    if (clients.size() == numMaxClients) return false;
    if (clientPosition(name) != -1) return false;
    InfoCard info;
    info.name=name;
    info.present=false;
    clients.push_back(info);
    return true;
}

bool CarPark::removeClient(const string & name)
{
    for (auto it = clients.begin(); it != clients.end(); it++)
        if ( (*it).name == name ) {
            if ( !(*it).present ) {
                clients.erase(it);
                return true;
            }
            else return false;
        }
    return false;
}

bool CarPark::enter(const string & name)
{
    if (freePlaces == 0) return false;
    int pos = clientPosition(name);
    if (pos == -1 || clients[pos].present) return false;
    clients[pos].present = true;
    clients.at(pos).frequency++;
    freePlaces--;
    return true;
}

bool CarPark::leave(const string & name)
{
    int pos = clientPosition(name);
    if (pos == -1 || !clients.at(pos).present) return false;
    clients[pos].present = false;
    freePlaces++;
    return true;
}


InfoCard CarPark::getClientAtPos(unsigned p) const
{
    if (p >= clients.size()){
        throw PositionDoesNotExist(p);
    }
    return clients.at(p);
}

void CarPark::sortClientsByFrequency()
{
    insertionSort(clients);
}

void CarPark::sortClientsByName()
{
    auto comp = [](const InfoCard& c1, const InfoCard& c2){
        return c1.name < c2.name;
    };
    std::sort(clients.begin(), clients.end(), comp);
}

vector<string> CarPark::clientsBetween(unsigned f1, unsigned f2)
{
    insertionSort(clients);
    vector<string> names;
    for (const InfoCard& c: clients){
        if (c.frequency >= f1 && c.frequency <= f2){
            names.push_back(c.name);
        }
    }
    return names;
}

ostream & operator<<(ostream & os, const CarPark & cp)
{
    os << cp.getNumClients() << " clients, " << cp.getNumPlaces() << " places\n";
    return os;
}

bool InfoCard::operator==(const InfoCard &i2) const {
    return name == i2.name;
}

bool InfoCard::operator<(const InfoCard &i2) const {
    return frequency > i2.frequency
    || (frequency == i2.frequency && name < i2.name);
}

string ClientDoesNotExist::getName() {
    return name;
}

ClientDoesNotExist::ClientDoesNotExist(const string &name):
    name(name){
}

unsigned PositionDoesNotExist::getPosition() {
    return position;
}

PositionDoesNotExist::PositionDoesNotExist(unsigned position):
    position(position) {
}
