/*
 * Account.h
 */

#ifndef SRC_ACCOUNT_H_
#define SRC_ACCOUNT_H_

#include <string>
#include<iostream>
using namespace std;


class Account {
protected:
	string holder;
	string codeHolder;
	string codeIBAN;
	double balance;
public:
	Account(string hold, string codeH, string codeA, double bal);
	virtual ~Account();
	string getCodH() const;
	string getCodIBAN() const;
	double getBalance() const;
    virtual double getCharge() const = 0;
    virtual double getWithdraw() const = 0;
};


class CheckingAccount: public Account {
	double limit; //lower limit for free checking
public:
	CheckingAccount (string hold, string codeH, string codeA, double bal, double lim);
    double getCharge() const override;
    double getWithdraw() const override;
};


class SavingsAccount: public Account {
protected:
	double rate;
public:
	SavingsAccount(string hold, string codeH, string codeA, double bal, double pct); //pct = percentage interest rate
    double getCharge() const override;
    double getWithdraw() const override;
};


class TimeAccount: public SavingsAccount {
	double funds_avail;
public:
	TimeAccount(string hold, string codeH, string codeA, double bal, double pct);
    double getWithdraw() const override;
};

#endif /* SRC_ACCOUNT_H_ */
