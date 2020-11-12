/*
 * Bank.cpp
 */

#include "Bank.h"
#include <algorithm>
#include <string>

Bank::Bank() {}

void Bank::addAccount(Account *a) {
	accounts.push_back(a);
}

void Bank::addBankOfficer(BankOfficer b){
	bankOfficers.push_back(b);
}

vector<BankOfficer> Bank::getBankOfficers() const {
	return bankOfficers;
}

vector<Account *> Bank::getAccounts() const {
	return accounts;
}


// ----------------------------------------------------------------------------------------------

double Bank::getWithdraw(string cod1) const{
    double sum = 0.0;
	for (const Account* a: accounts){
	    if (a->getCodH() == cod1) sum += a->getWithdraw();
	}
	return sum;
}


vector<Account *> Bank::removeBankOfficer(string name){
	for (auto it = bankOfficers.begin(); it != bankOfficers.end(); ++it){
	    if (it->getName() == name){
	        vector<Account*> acc = it->getAccounts();
	        bankOfficers.erase(it);
	        return acc;
	    }
	}
	return vector<Account*>();
}

const BankOfficer & Bank::addAccountToBankOfficer(Account *ac, string name) {
    for (BankOfficer& bo: bankOfficers){
        if (bo.getName() == name){
            bo.addAccount(ac);
            return bo;
        }
    }
    throw NoBankOfficerException(name);
}


void Bank::sortAccounts() {
    auto comp = [](const Account* acc1, const Account* acc2){
        if (acc1->getBalance() < acc2->getBalance())
            return true;
        if (acc1->getBalance() == acc2->getBalance())
            return acc1->getCodIBAN() < acc2->getCodIBAN();
        return false;
    };
    std::sort(accounts.begin(),accounts.end(),comp);
}

