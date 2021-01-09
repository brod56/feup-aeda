#ifndef SRC_HOTEL_H_
#define SRC_HOTEL_H_

#include <vector>
#include <list>

class NoSuchFloorException {
public:
    explicit NoSuchFloorException(int floor) : floor(floor){}
    int getFloor() { return floor;}
private:
    int floor;
};

template <class Chamber>
class Hotel {
	std::vector<Chamber *> chambers;
	const unsigned int maxCapacity;
	const std::string city;
    std::list<Chamber> reservationsDone;
public:
	Hotel(int size, std::string municipality);
	~Hotel();
	std::vector<Chamber *> getChambers() const;
	void setChambers(std::vector<Chamber *> chambers);
	int getCapacity() const;
    std::list<Chamber> getReservationsDone() const;
	bool addChamber(Chamber *chamber);
    void addReservationDone(Chamber chamber);
    Chamber* removeChamber(std::string code, int floor);
	float avgArea(int floor) const;
	void sortChambers();
	bool doReservation(std::string code, int floor);
    std::list<Chamber> roomsNeverReserved() const;
};

class NoSuchChamberException {
public:
	NoSuchChamberException() { }
};

template <class Chamber>
Hotel<Chamber>::Hotel(int size, std::string municipality) : maxCapacity(size), city(municipality) {
}

template <class Chamber>
Hotel<Chamber>::~Hotel(){
	typename std::vector<Chamber *>::const_iterator it;
	for (it=chambers.begin(); it!=chambers.end(); it++) {
		delete *it;
	}
}

template<class Chamber>
std::vector<Chamber *> Hotel<Chamber>::getChambers() const {
	return chambers;
}

template<class Chamber>
void Hotel<Chamber>::setChambers(std::vector<Chamber*> chambers) {
	this->chambers = chambers;
}

template<class Chamber>
int Hotel<Chamber>::getCapacity() const {
	return maxCapacity;
}

template<class Chamber>
void Hotel<Chamber>::addReservationDone(Chamber chamber) {
    reservationsDone.push_back(chamber);
}

template<class Chamber>
std::list<Chamber> Hotel<Chamber>::getReservationsDone() const {
    return reservationsDone;
}

//------------------------------------------------------
//------------------------------------------------------

template<class Chamber>
bool Hotel<Chamber>::addChamber(Chamber *chamber) {
    auto comp = [chamber](const Chamber* c2){
        return *c2 == *chamber;
    };
    if (std::find_if(chambers.begin(),chambers.end(),comp) != chambers.end() ||
    chambers.size() >= maxCapacity){
        return false;
    }
    chambers.push_back(chamber);
    return true;
}


template<class Chamber>
void Hotel<Chamber>::sortChambers() {
    auto comp = [](const Room* c1, const Room* c2){
        return (c1->getCode() < c2->getCode()) || c1->getFloor() > c2->getFloor();
    };
    std::sort(chambers.begin(),chambers.end(),comp);
}

template<class Chamber>
Chamber* Hotel<Chamber>::removeChamber(std::string code, int floor) {
    bool found = false;
    std::vector<Room*>::iterator it = chambers.begin();
    Room* toRemove;
    for (; it != chambers.end(); ++it){
        if ((*it)->getCode() == code && (*it)->getFloor() == floor){
            found = true;
            toRemove = *it;
            chambers.erase(it);
            break;
        }
    }
    if (!found) throw NoSuchChamberException();
    return toRemove;
}

template<class Chamber>
float Hotel<Chamber>::avgArea(int floor) const {
    bool foundFloor = false;
    float sum = 0.0f;
    int count = 0;
    for (const Room* r: chambers){
        if (r->getFloor() != floor) continue;
        if (!foundFloor) foundFloor = true;
        sum += r->getArea();
        count++;
    }
    if (!foundFloor) throw NoSuchFloorException(floor);
    return sum/count;
}

template<class Chamber>
bool Hotel<Chamber>::doReservation(std::string code, int floor){
    for (Room* r: chambers){
        if (r->getCode() == code && r->getFloor() == floor
        && !r->getReservation()){
            reservationsDone.push_back(*r);
            r->setReservation(true);
            return true;
        }
    }
    return false;
}

template<class Chamber>
std::list<Chamber> Hotel<Chamber>::roomsNeverReserved() const {
    std::list<Chamber> notReserved;
    for (const Room* r: chambers){
        bool reserved = false;
        for (const Room& r2: reservationsDone){
            if (r2 == *r){
                reserved = true;
                break;
            }
        }
        if (!reserved) notReserved.push_back(*r);
    }
    return notReserved;
}



#endif /* SRC_HOTEL_H_ */
