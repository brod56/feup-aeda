/*
 * BankOfficer.h
 */

#ifndef SRC_BANKOFFICER_H_
#define SRC_BANKOFFICER_H_

#include "Account.h"
#include <string>
#include <vector>
#include <set>

class BankOfficer {
	unsigned int id;
	string name;
	vector<Account *> myAccounts;
public:
	BankOfficer();
	void setName(string nm);
	void addAccount(Account *a);
	void addAccount(vector<Account *> accounts);
	string getName() const;
	vector<Account *> getAccounts() const;
	unsigned int getID() const;

	//-------
	BankOfficer(string nm);
	vector<Account *> removeBankOfficer(string name);
	bool operator >(const BankOfficer& b2) const;
};

template<class T>
unsigned int numberDifferent(const std::vector<T> &v1) {
    std::set<T> s(v1.begin(),v1.end());
    unsigned int sum = 0;
    for (const auto& e: s){
        sum += s.count(e);
    }
    return sum;
}

#endif /* SRC_BANKOFFICER_H_ */
