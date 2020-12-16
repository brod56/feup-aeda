#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <utility>
#include <vector>
#include <algorithm> //random_shuffle

using namespace std;

unsigned int Game::numberOfWords(string phrase) {
    if ( phrase.length() == 0 ) return 0;

    unsigned n=1;
    size_t pos = phrase.find(' ');
    while (pos != string::npos) {
        phrase = phrase.substr(pos+1);
        pos = phrase.find(' ');
        n++;
    }
    return n;
}

Game::Game() : kids(){
}

Game::Game(list<Kid>& l2) : kids(l2) {
}

void Game::addKid(const Kid &k1) {
    kids.push_back(k1);
}

list<Kid> Game::getKids() const {
    return kids;
}

string Game::write() const {
    std::string str;
    for (const auto& kid : kids){
        str += kid.write() + "\n";
    }
    return str;
}

Kid& Game::loseGame(const string& phrase) {
    unsigned n = numberOfWords(phrase);
    list<Kid> kidsTemp = kids;
    auto it = kidsTemp.begin();

    while (kidsTemp.size() > 1){
        unsigned remaining = n - 1; //current already counts
        do{
            if (++it == kidsTemp.end()) it = kidsTemp.begin();
        } while(--remaining);
        it = kidsTemp.erase(it);
        if (it == kidsTemp.end()) it = kidsTemp.begin();
    }

    return *std::find(kids.begin(),kids.end(),*kidsTemp.begin());
}

list<Kid>& Game::reverse() {
    kids.reverse();
    return kids;
}

list<Kid> Game::removeOlder(unsigned id) {
    list<Kid> oldKids;
    for (auto it = kids.begin(); it != kids.end(); ++it){
        if (it->getAge() > id){
            oldKids.push_back(*it);
            it = kids.erase(it);
        }
    }
    return oldKids;
}

void Game::setKids(const list<Kid>& l1) {
    kids = l1;
}

bool Game::operator==(Game& g2) {
	return kids == g2.getKids();
}

list<Kid> Game::shuffle() const {
    vector<Kid> shuffledKids(kids.begin(), kids.end());
    std::shuffle(shuffledKids.begin(),shuffledKids.end(), std::mt19937(std::random_device()()));
    return list<Kid>(shuffledKids.begin(),shuffledKids.end());
}

