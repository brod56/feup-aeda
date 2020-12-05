#include "bet.h"

bool Bet::contains(unsigned num) const {
	return numbers.find(num) != numbers.end();
}

void Bet::generateBet(const std::vector<unsigned>& values, unsigned n) {
    for (const auto& v: values){
        if (!n) break;
        if (numbers.insert(v).second) n--;
    }
}

unsigned Bet::countRights(const tabHInt& draw) const {
    unsigned rights = 0;
	for (const auto& n: numbers){
	    if (draw.find(n) != draw.end()) rights++;
	}
	return rights;
}
