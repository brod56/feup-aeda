#include "player.h"

void Player::addBet(const Bet& b) {
    bets.insert(b);
}

unsigned Player::betsInNumber(unsigned num) const {
    unsigned count = 0;
	for (const auto& bet: bets){
	    if (bet.contains(num)) count++;
	}
	return count;
}

tabHBet Player::drawnBets(const tabHInt& draw) const {
	tabHBet res;
	for (const auto& bet: bets){
	    if (bet.countRights(draw) > 3) res.insert(bet);
	}
	return res;
}
