/*
 * BankOfficer.cpp
 */
#include <algorithm>
#include "BankOfficer.h"

BankOfficer::BankOfficer(): id(0) {}


void BankOfficer::setName(string nm){
	name = nm;
}

string BankOfficer::getName() const{
	return name;
}

vector<Account *> BankOfficer::getAccounts() const {
	return myAccounts;
}

void BankOfficer::addAccount(Account *a) {
	myAccounts.push_back(a);
}

unsigned int BankOfficer::getID() const{
	return id;
}


// ----------------------------------------------------------------------------------------------

BankOfficer::BankOfficer(string name) : myAccounts(), name(name){
    static unsigned int myid = 1;
    id = myid++;
}

bool BankOfficer::operator>(const BankOfficer& b2) const{
    if (myAccounts.size() > b2.getAccounts().size()) return true;
    else if (myAccounts.size() == b2.getAccounts().size()) return name > b2.getName();
    else return false;
}

void BankOfficer::addAccount(vector<Account *> accounts) {
    for (Account* acc: accounts) myAccounts.push_back(acc);
}



