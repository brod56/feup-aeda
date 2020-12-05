#ifndef PLAYER_H_
#define PLAYER_H_

#include "bet.h"
#include <string>
#include <utility>

static const int maxBetSize = 12;

struct betHash {
    // second unordered_set template argument -> hash function
	int operator() (const Bet& b) const {
		return (int) b.getNumbers().size() % maxBetSize;
	}

	// third unordered_set template argument -> predicate ("equal to")
	bool operator() (const Bet& b1, const Bet& b2) const {
		return b1.getNumbers() == b2.getNumbers();
	}
};

typedef std::unordered_set<Bet, betHash, betHash> tabHBet;

class Player {
	tabHBet bets;
	std::string name;
public:
	explicit Player(std::string nm="anonymous") { name=std::move(nm); }
	void addBet(const Bet & ap);
	unsigned betsInNumber(unsigned num) const;
	tabHBet drawnBets(const tabHInt& draw) const;
	unsigned getNumBets() const { return bets.size(); }
};

#endif 
