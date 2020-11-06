#include <queue>
#include <cstdlib>
#include "counter.h"
#include "exceptions.h"
using namespace std;

Client::Client() : numGifts(1 + rand() % 5) {
}

unsigned Client::getNumGifts() const {
    return numGifts;
}

Counter::Counter(unsigned wt): wrappingTime(wt),
    actualTime(0), nextEnter(1 + rand()%20),
    nextLeave(0), numAttendedClients(0){
}

unsigned Counter::getActualTime() const {
    return actualTime;
}

unsigned Counter::getNextEnter() const {
    return nextEnter;
}

unsigned Counter::getNumAttendedClients() const {
    return numAttendedClients;
}

unsigned Counter::getWrappingTime() const {
    return wrappingTime;
}

unsigned Counter::getNextLeave() const {
    return nextLeave;
}

Client & Counter::getNextClient() {
    if (clients.empty()) throw EmptyQueue();
    return clients.front();
}

void Counter::enter()
{
    Client c;
    if (clients.empty())
        nextLeave = (actualTime + c.getNumGifts()) * wrappingTime;
    clients.push(c);
    std::cout << "time = " << actualTime << "\nnew customer arrived with " << c.getNumGifts() << " gifts\n";
    nextEnter = 1 + rand() % 20;

}

void Counter::leave()
{
    if (clients.empty()) throw EmptyQueue();
    clients.pop();
    numAttendedClients++;
    nextLeave = (actualTime + clients.front().getNumGifts()) * wrappingTime;
}

void Counter:: nextEvent()
{
    if (nextLeave <= nextEnter && !clients.empty()){
        leave();
        actualTime += nextLeave;
    }
    else{
        enter();
        actualTime += nextEnter;
    }
}

ostream & operator << (ostream & out, const Counter & c2)
{
    out << "Attended " << c2.getNumAttendedClients()
    << " clients. " << c2.getSize() << " more waiting.\n";
    return out;
}

unsigned Counter::getSize() const {
    return clients.size();
}


