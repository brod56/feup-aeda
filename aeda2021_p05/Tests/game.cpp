#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


unsigned int Game::numberOfWords(string phrase)
{
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

// TODO
Game::Game()
{
}

// TODO
Game::Game(list<Kid>& l2)
{
}

// TODO
void Game::addKid(const Kid &k1)
{
}

// TODO
list<Kid> Game::getKids() const
{
    list<Kid> res;
    return res;
}

// TODO
string Game::write() const
{
    string res;
    return res;
}

// TODO
Kid& Game::loseGame(string phrase)
{
    Kid *k1 = new Kid();
    return *k1;
}

// TODO
list<Kid>& Game::reverse()
{
    return kids;
}

// TODO
list<Kid> Game::removeOlder(unsigned id)
{
    list<Kid> res;
    return res;
}

// TODO
void Game::setKids(const list<Kid>& l1)
{
}

// TODO
bool Game::operator==(Game& g2)
{
	return true;
}

// TODO
list<Kid> Game::shuffle() const
{
    list<Kid> res;
    return res;
}
