#include "game.h"
#include <sstream>
#include <algorithm>

ostream &operator << (ostream &os, Circle &c1)
{
	os << c1.getPoints() << "-" << (c1.getState() ? "true" : "false")
	<< "-" << c1.getNVisits() << "\n";
	return os;
}

void Circle::addVisit() {
    nVisits++;
}

Game::Game(int h, vector<int> &points, vector<bool> &states) {
    if (points.empty() || states.empty()) return;
    game = *makeTree(points,states);
}


string Game::writeGame() {
    stringstream ss;
	for (auto it = BTItrLevel<Circle>(game); !it.isAtEnd(); it.advance()){
	    ss << it.retrieve();
	}
	return ss.str();
}


int Game::move()
{
    size_t pos = 0, jump = 0;
    auto it = BTItrLevel<Circle>(game);
    int points = it.retrieve().getPoints();

	for(;;){
	    if (!it.retrieve().getState()) jump = 2*pos + 1; // false, go left
	    else jump = 2*pos + 2;

        it.retrieve().addVisit();
        it.retrieve().changeState();

	    while (pos<jump && !it.isAtEnd()){
	        it.advance();
	        pos++;
	    }
	    if (it.isAtEnd()){
	        return points;
	    }
	    else {
	        points = it.retrieve().getPoints();
	    }
	}
}


int Game::mostVisited()
{
	std::vector<int> visits;
	bool start = true;
	for (auto it = BTItrLevel<Circle>(game); !it.isAtEnd(); it.advance()){
	    if (start){
	        start = false;
	        continue;
	    }
	    visits.push_back(it.retrieve().getNVisits());
	}
	return *std::max_element(visits.begin(),visits.end());
}

BinaryTree<Circle>* Game::makeTree(vector<int> points, vector<bool> states, size_t pos) {
    size_t leftPos = 2*pos + 1, rightPos = 2*pos + 2;
    auto* c = new Circle(points.at(pos),states.at(pos));
    if (rightPos < points.size()){
        return new BinaryTree<Circle>(*c,*makeTree(points,states,leftPos),*makeTree(points,states,rightPos));
    }
    return new BinaryTree<Circle>(*c);
}